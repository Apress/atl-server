#pragma once

#include <atlisapi.h>
#include <atlutil.h>
#include <windows.h>
#include <pdh.h>

//
// Remove one thread per request if CPU useage is equal to or higher than this value.
//
#define CPU_UPPER_THRESHOLD 80

//
// Add one thread per request if CPU useage is equal to or lower than this value.
//
#define CPU_LOWER_THRESHOLD 20

//
// Limit the maximum number of threads per CPU to this value.
//
#define CPU_MAX_THREADS		25

/////////////////////////////////////////////////////////////////////////////////////////////
// CDynamicThreadPool - This class extends the functionality of CThreadPool by dynamically
// resizing itself when it receives a request based on the following criteria:
//
//		- If the CPU useage is less than or equal to a certain CPU useage percentage (CPU_LOWER_THRESHOLD), 
//		  there are no free threads, and we have not reached our maximum (CPU_MAX_THREADS), add another thread
//		  to the pool before queuing the request.
//
//		- If the CPU useage is equal to or higher than a certain CPU useage percentage (CPU_UPPER_THRESHOLD),
//		  then remove 1 thread from the pool before queuing the request.
/////////////////////////////////////////////////////////////////////////////////////////////
template < class Worker       = CIsapiWorker, 
		   class ThreadTraits = DefaultThreadTraits >
class CDynamicThreadPool : 
	public CThreadPool< Worker, ThreadTraits >
{
private:
	PDH_HQUERY				m_pdhQuery;
	PDH_HCOUNTER			m_pdhCounter;
	int						m_maxThreads;
	CComPtr<IRequestStats>  m_requestStats;

public:
	CDynamicThreadPool() : 
		m_pdhQuery(NULL),
		m_pdhCounter(NULL),
		m_maxThreads(0),
		CThreadPool< Worker, ThreadTraits>()
	{
	}

	//
	// We need to do the following types of additional initialization:
	//
	//		1. Get and keep a pointer to IRequestStats from pvWorkerParam.
	//		2. Set the maximum number of threads we can create based on the number of CPUs.
	//		3. Setup PDH handles so that we can query the processor time performance object.
	//
	// No matter what, always return the base implementation of Initialize
	//
	HRESULT Initialize(void *pvWorkerParam=NULL, int nNumThreads=0, DWORD dwStackSize=0, HANDLE hCompletion=INVALID_HANDLE_VALUE) throw()
	{	        
        TCHAR *counterPath = NULL;		

		//
		// 1. Get and keep a pointer to IRequestStats from pvWorkerParam.
		//
		if (!pvWorkerParam)
		{
			//
			// If we can't get the IRequestStats pointer, don't bother doing the rest
			// of the initialization.
			//
			goto error;
		}
	
		IIsapiExtension *isapiExtension = NULL;
		isapiExtension = static_cast<IIsapiExtension*> (pvWorkerParam);
		
		if (FAILED(isapiExtension->QueryInterface(__uuidof(IRequestStats), (void**)&m_requestStats)))
		{
			//
			// If we can't get the IRequestStats pointer, don't bother doing the rest
			// of the initialization.
			//
			goto error;
		}

		//
		// 2. Set the maximum number of threads we can create based on the number of CPUs.
		//
		SYSTEM_INFO systemInfo;
		ZeroMemory(&systemInfo, sizeof(SYSTEM_INFO));

		GetSystemInfo(&systemInfo);	
		m_maxThreads = systemInfo.dwNumberOfProcessors * CPU_MAX_THREADS;
			
		//
		// 3. Setup PDH handles so that we can query the processor time performance object.
		//
			
		//
		// Clean PDH handles just in case.
		//
		CleanPdh();
			
		PDH_STATUS pdhStatus = PdhOpenQuery(NULL, NULL, &m_pdhQuery);
		if (pdhStatus !=  ERROR_SUCCESS)
		{
			goto error;
		}

		//
		// Build a path to the processor time performance object.
		//
		PDH_COUNTER_PATH_ELEMENTS pdhPathElements[1];
	
		pdhPathElements[0].dwInstanceIndex  = (DWORD)-1;
		pdhPathElements[0].szCounterName    = TEXT("% Processor Time");
		pdhPathElements[0].szInstanceName   = TEXT("_Total");
		pdhPathElements[0].szMachineName    = NULL;
		pdhPathElements[0].szObjectName     = TEXT("Processor");
		pdhPathElements[0].szParentInstance = NULL;

		//
		// Get the size of the path.
		//
		DWORD counterPathSize = 0;
		pdhStatus = PdhMakeCounterPath(pdhPathElements, 
									   NULL, 
									   &counterPathSize, 
									   NULL);
		if (pdhStatus !=  ERROR_SUCCESS)
		{
			goto error;
		}

		//
		// Allocate room for the counter path.
		//		
		counterPath = new TCHAR[counterPathSize];
		if (!counterPath)
		{
			goto error;
		}

		//
		// Get the counter path.
		//
		pdhStatus = PdhMakeCounterPath(pdhPathElements, 
									   counterPath, 
									   &counterPathSize, 
									   NULL);
		if (pdhStatus !=  ERROR_SUCCESS)
		{
			goto error;
		}

		// 
		// Add the processor time counter to our query.
		//
		m_pdhCounter = NULL;
		pdhStatus = PdhAddCounter(m_pdhQuery, 
								  counterPath, 
								  NULL, 
								  &m_pdhCounter);
		if (pdhStatus !=  ERROR_SUCCESS)
		{
			goto error;
		}
			
		//
		// If we got here, we were successful
		//
		goto success;
error:
		//
		// If we failed, clean up our handles.
		//
		CleanPdh();

success:
		if (counterPath)
		{
			delete[] counterPath;
			counterPath = NULL;
		}		
		
		//
		// Return the base initialization.
		//
		return __super::Initialize(pvWorkerParam, nNumThreads, dwStackSize, hCompletion);
	}
	
	virtual ~CDynamicThreadPool()
	{
		CleanPdh();
	}

	//
	// Override QueueRequest function to include dynamic size analysis.
	//
    BOOL QueueRequest( typename Worker::RequestType request ) throw()
	{
		//
		// Get our current CPU utilization
		//
		LONG processorTime = GetProcessorTime();

		if (processorTime >= CPU_UPPER_THRESHOLD)
		{
			//
			// If we match our upper CPU utilization shutdown a thread before queuing this 
			// request.  This will hopefully slow down the number of requests we are processing,
			// which will give the CPU a chance to recover and process the currently executing requests.
			//
			int numThreads = 0;
			if (SUCCEEDED(GetSize(&numThreads)) && numThreads > 1)
			{
				SetSize(numThreads - 1 );
			}
		}
		else if (processorTime <= CPU_LOWER_THRESHOLD)
		{
			//
			// Otherwise, if we match the lower CPU utilization boundary, look at the number of active threads.
			// If there are no free threads and we have not reached our maximum number of threads, add another
			// thread to the pool before queuing this current request.
			//
			int numThreads = 0;
			if (SUCCEEDED(GetSize(&numThreads))					 &&		// can we get number of threads?
				m_requestStats->GetActiveThreads() == numThreads &&		// are there any free threads?
				numThreads < m_maxThreads)								// have we created the max. number of threads?
			{
				SetSize(numThreads + 1);
			}
		}

		return __super::QueueRequest( request );
	}

private:
	LONG GetProcessorTime()
	{
		LONG				 processorTime = 0;
		PDH_FMT_COUNTERVALUE pdhCounterValue;
		ZeroMemory(&pdhCounterValue, sizeof(PDH_FMT_COUNTERVALUE));

		if (PdhCollectQueryData(m_pdhQuery) == ERROR_SUCCESS)
		{
			if (PdhGetFormattedCounterValue(m_pdhCounter,
											PDH_FMT_LONG,
											NULL,
											&pdhCounterValue))
			{
				processorTime = pdhCounterValue.longValue;
			}
		}
		
		return processorTime;
	}

	void CleanPdh()
	{
		if (m_pdhCounter != NULL)
		{
			PdhRemoveCounter(m_pdhCounter);
		}

		if (m_pdhQuery != NULL)
		{
			PdhCloseQuery(m_pdhQuery);
		}		
	}
};
