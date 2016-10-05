#pragma once

#include <atlisapi.h>
#include <passport.h>

class CPassportExtensionWorker : public CIsapiWorker
{
private:
	CComPtr<IPassportManager2> m_spPassportManager;
	
public:
	CPassportExtensionWorker() : m_spPassportManager(NULL)
	{
	}

	~CPassportExtensionWorker()
	{
	}
	
	virtual BOOL Initialize(void *pvParam)
	{
		if (!CIsapiWorker::Initialize(pvParam))
            return FALSE;

		// create Passport manager	
		if (FAILED(m_spPassportManager.CoCreateInstance(CLSID_Manager)))
		{
			return FALSE;
		}								
        return TRUE;
	}


	virtual BOOL GetWorkerData(DWORD dwParam, void ** ppvData) throw()
	{		
		ATLASSERT(m_spPassportManager);
		if (!m_spPassportManager)
		{
			return FALSE;
		}
				
		*ppvData = (void*) &m_spPassportManager;		

		return TRUE;		
	}
};

template <	class ThreadPoolClass			= CThreadPool<CPassportExtensionWorker>, 
			class CStatClass				= CNoRequestStats, 
			class HttpUserErrorTextProvider = CDefaultErrorProvider, 
			class WorkerThreadTraits		= DefaultThreadTraits>

class CPassportExtension : public CIsapiExtension<	ThreadPoolClass, 
													CStatClass, 
													HttpUserErrorTextProvider, 
													WorkerThreadTraits>
{
protected:

	typedef CIsapiExtension<ThreadPoolClass, 
							CStatClass, 
							HttpUserErrorTextProvider, 
							WorkerThreadTraits> baseISAPI;

	typedef CWorkerThread<WorkerThreadTraits> WorkerThreadClass;

public:
	
	HRESULT STDMETHODCALLTYPE QueryService(	REFGUID guidService, 
											REFIID	riid, 
											void** ppvObject)
	{
		if (InlineIsEqualGUID(guidService, IID_IPassportManager2))
		{
			CIsapiWorker *pWorker = GetThreadWorker();
			if (pWorker)
			{
				IPassportManager2 *pPassportManager(NULL);
				if (pWorker->GetWorkerData(NULL, (void **)&pPassportManager))
				{
					*ppvObject = static_cast<IPassportManager2 *>(pPassportManager);
					return S_OK;
				}
			}
		}
		
		return baseISAPI::QueryService(guidService, riid, ppvObject);
	}
};