#pragma once
#include <atlisapi.h>
#include <atlsession.h>
#include "MyMonitor.h"

__interface ATL_NO_VTABLE __declspec(uuid("A3B11C9C-C3B2-41ba-AA01-F086F4625B49"))
IHitCounter : public IUnknown
{
	STDMETHOD (IncrementCounter)();
};

class CHitCounter : public IHitCounter, public CComObjectRootEx<CComGlobalsThreadModel>
{
	BEGIN_COM_MAP(CHitCounter)
		COM_INTERFACE_ENTRY(IHitCounter)
	END_COM_MAP()

	MyObject *pObject;

	void InitCounter(MyObject *pIn)
	{
		pObject = pIn;
		pObject->MyCounter = 0;
	}

	STDMETHOD (IncrementCounter)()
	{
		InterlockedIncrement(reinterpret_cast<LONG *> (&pObject->MyCounter));
		return S_OK;
	}

};

template <class ThreadPoolClass=CThreadPool<CIsapiWorker>, 
	class CStatClass=CStdRequestStats,
	class HttpUserErrorTextProvider=CDefaultErrorProvider, 
	class WorkerThreadTraits=DefaultThreadTraits >
class MyCIsapiExtension : 
	public CIsapiExtension<ThreadPoolClass, 
		CStatClass,
		HttpUserErrorTextProvider, 
		WorkerThreadTraits>
{
protected:

	typedef CIsapiExtension<ThreadPoolClass, CStatClass, HttpUserErrorTextProvider, 
		WorkerThreadTraits> baseISAPI;
	typedef CWorkerThread<WorkerThreadTraits> WorkerThreadClass;

	MyMonitor m_Monitor;
	MyObject *m_pObject;
	CComObjectGlobal<CHitCounter> m_Counter;
public:

	BOOL GetExtensionVersion(HSE_VERSION_INFO* pVer)
	{
		HRESULT hr = m_Monitor.Initialize();
		if (hr != S_OK)
		{
			return FALSE;
		}
		CPerfLock lock(&m_Monitor);
		hr = lock.GetStatus();
		if (FAILED(hr))
		{
			return FALSE;
		}
		hr = m_Monitor.CreateInstanceByName(0,L"My Counter", reinterpret_cast<CPerfObject**>(&m_pObject));
		//hr = m_Monitor.CreateInstanceByName(1, L"Hit Counter",reinterpret_cast<CPerfObject**>(&m_pObject)); 
		if (FAILED(hr))
		{
			return FALSE;
		}
		m_Counter.InitCounter(m_pObject);
		
		if (!baseISAPI::GetExtensionVersion(pVer))
		{
			return FALSE;
		}
		
		if (GetCriticalIsapiError() != 0)
		{
			return TRUE;
		}
		return TRUE;
	}

	BOOL TerminateExtension(DWORD dwFlags)
	{
		m_Monitor.UnInitialize();
		BOOL bRet = baseISAPI::TerminateExtension(dwFlags);
		return bRet;
	}
	
	HRESULT STDMETHODCALLTYPE QueryService(REFGUID guidService, 
			REFIID riid, void** ppvObject)
	{
		if (InlineIsEqualGUID(guidService, __uuidof(IHitCounter)))
			return m_Counter.QueryInterface(riid, ppvObject);
		return baseISAPI::QueryService(guidService, riid, ppvObject);
	}

	virtual void OnThreadTerminate(DWORD /*dwThreadId*/)
	{
	}
}; // class CTestIsapiServicesExtension

