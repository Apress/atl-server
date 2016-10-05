#include "SimpleCounter.h"

template <class ThreadPoolClass=CThreadPool<CIsapiWorker>,
		  class CStatClass=CNoRequestStats,
		  class HttpUserErrorTextProvider=CDefaultErrorProvider,
		  class WorkerThreadTraits=DefaultThreadTraits >
class CMyIsapiExtension : public CIsapiExtension<
							ThreadPoolClass, 
							CStatClass,
							HttpUserErrorTextProvider,
							WorkerThreadTraits>
{
	typedef CIsapiExtension<ThreadPoolClass, CStatClass, HttpUserErrorTextProvider, 
		WorkerThreadTraits> baseISAPI;

	CComObjectGlobal<CSimpleCounter> g_Counter;
public:
	BOOL GetExtensionVersion(HSE_VERSION_INFO* pVer)
	{
		if (!baseISAPI::GetExtensionVersion(pVer))
		{
			return FALSE;
		}
		
		if (GetCriticalIsapiError() != 0)
		{
			return TRUE;
		}
		g_Counter.Init();
		return TRUE;
	}

	HRESULT STDMETHODCALLTYPE QueryService(REFGUID guidService, 
			REFIID riid, void** ppvObject)
	{
		if (InlineIsEqualGUID(guidService, __uuidof(ISimpleCounter)))
			return g_Counter.QueryInterface(riid, ppvObject);
		return baseISAPI::QueryService(guidService, riid, ppvObject);
	}

};