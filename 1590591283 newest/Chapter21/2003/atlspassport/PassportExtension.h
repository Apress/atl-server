#pragma once

#include <atlisapi.h>
#include <passport.h>

class CPassportExtensionWorker : public CIsapiWorker
{
public:
	CPassportExtensionWorker()
	{
	}

	~CPassportExtensionWorker()
	{
	}

	virtual void Terminate(void* pvParam) throw()
	{
		if (m_passportManager)
		{
			m_passportManager->Release();
			m_passportManager = NULL;
		}

		CIsapiWorker::Terminate(pvParam);
	}
	
	virtual BOOL Initialize(void *pvParam)
	{
		if (!CIsapiWorker::Initialize(pvParam))
            return FALSE;

		// create Passport manager		
		if (FAILED(CoCreateInstance(CLSID_Manager, 
									NULL, 
									CLSCTX_INPROC_SERVER, 
									IID_IPassportManager2, 
									(void**)&m_passportManager)))
		{
			return FALSE;
		}		
        return TRUE;
	}

	virtual BOOL GetPassportManager(void **ppvData)
	{
		ATLASSERT(m_passportManager);
		if (!m_passportManager)
		{
			return FALSE;
		}
				
		*ppvData = (void*) &m_passportManager;
		return TRUE;		
	}
};

template <	class ThreadPoolClass			= CThreadPool<CaaaaaaExtensionWorker>, 
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
		if (InlineIsEqualGUID(guidService, __uuidof(IID_IPassportManager2)))
		{
			CIsapiWorker *pWorker = GetThreadWorker();
			if (pWorker)
			{
				IPassportManager2 *pPassportManager(NULL);
				if (pWorker->PassportManager((void **)&pPassportManager))
				{
					*ppvObject = static_cast<IPassportManager2 *>(pPassportManager);
					return S_OK;
				}
			}
		}
		
		return baseISAPI::QueryService(guidService, riid, ppvObject);
	}
};