// PerThreadSvcIsapi.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
// For custom assert and trace handling with WebDbg.exe
#ifdef _DEBUG
CDebugReportHook g_ReportHook;
#endif
[ module(name="MyPerThreadSvc", type="dll") ];
[ emitidl(restricted) ];


#include "PerThreadSvcDef.h"
#include "RemoteWeatherService.h"


// Implementation for the IPerThreadWeatherService
class	CPerThreadWeatherSvc : public IPerThreadWeatherSvc
{
public:
	CPerThreadWeatherSvc() : m_pSvc(NULL) {}


	HRESULT	Initialize( ISAXXMLReader* pXMLReader, HANDLE heap )
	{
		// Create the service proxy 
		m_pSvc	=	new RemoteWeatherService::CRemoteWeatherService(pXMLReader);

		if( m_pSvc )
		{
			// Set the memory manager of the proxy class to use the current 
			// per-thread heap
			m_Heap.Attach( heap, false);
			m_pSvc->SetMemMgr( &m_Heap );
		}
		return m_pSvc ? S_OK : E_FAIL;
	}

	HRESULT	Uninitialize( )
	{
		m_Heap.Detach();
		delete m_pSvc;
		return S_OK;
	}

	ULONG	STDMETHODCALLTYPE  AddRef()
	{
		return 1;
	}

	ULONG	STDMETHODCALLTYPE Release()
	{
		return 1;
	}

	HRESULT	STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject)
	{
		if( !ppvObject )
		{
			return E_POINTER;
		}

		if( IsEqualIID( riid, IID_IUnknown))
		{
			*ppvObject = static_cast<IUnknown*>(this);
		}
		else if( IsEqualIID( riid, __uuidof(IPerThreadWeatherSvc)))
		{
			*ppvObject = static_cast<IPerThreadWeatherSvc*>(this);
		}
		else
		{
			return E_NOINTERFACE;
		}
		AddRef();
		return S_OK;
	}

	HRESULT GetCityList(int* pCount, BSTR**	arCities)
	{
		if( m_pSvc )
			return m_pSvc->GetCityList( arCities, pCount);
		else
			return E_POINTER;
	}
	HRESULT GetCityForecast(BSTR bstrCity, double* pdRet)
	{
		if( m_pSvc )
			return m_pSvc->GetCityForecast(bstrCity, pdRet);
		else
			return E_POINTER;
	}

	HRESULT CleanupCityList(BSTR* arCities, int nCount)
	{
		if( m_pSvc )
		{
			AtlCleanupArrayEx( arCities, nCount, m_pSvc->GetMemMgr() );
			m_pSvc->GetMemMgr()->Free( arCities );
			return S_OK;
		}
		else
			return E_POINTER;
	}

protected:
	// The service proxy class
	RemoteWeatherService::CRemoteWeatherService	*m_pSvc;
	
	// Wrapper for the per thread heap
	CWin32Heap									 m_Heap;
};



class CExtendedIsapiWorker : public CIsapiWorker
{
public:
	CPerThreadWeatherSvc		m_WeatherSvc;
	virtual BOOL Initialize(void *pvParam) throw()
	{
		BOOL	bBaseRet	=	__super::Initialize( pvParam );

		if( bBaseRet )
		{
			// Initialize the per-thread service
			// Pass the SAXXMLReader as parameter to be used in the SOAP client
			// Also, pass the current per-thread heap to be used in the SOAP client
			bBaseRet	=	SUCCEEDED(m_WeatherSvc.Initialize( m_spReader, m_hHeap));
		}

		return bBaseRet;
	}

	virtual void Terminate(void* pvParam) throw()
	{
		m_WeatherSvc.Uninitialize();
		__super::Terminate(pvParam);
	}
};

class CIsapiEx : public CIsapiExtension<CThreadPool<CExtendedIsapiWorker> > 
{
	virtual HRESULT STDMETHODCALLTYPE QueryService(
		REFGUID guidService,
		REFIID riid,
		void **ppvObject)
	{
		if (!ppvObject)
			return E_POINTER;
		if (InlineIsEqualGUID(guidService, __uuidof(IPerThreadWeatherSvc)))
		{
			CExtendedIsapiWorker *p = (CExtendedIsapiWorker*)GetThreadWorker();
			ATLASSERT( p != NULL );
			return p->m_WeatherSvc.QueryInterface(riid, ppvObject);
		}

		// otherwise look it up in the servicemap
		return __super::QueryService(guidService, riid, ppvObject);
	}
};

// The ATL Server ISAPI extension
CIsapiEx theExtension;


// Delegate ISAPI exports to theExtension
//
extern "C" DWORD WINAPI HttpExtensionProc(LPEXTENSION_CONTROL_BLOCK lpECB)
{
	return theExtension.HttpExtensionProc(lpECB);
}

extern "C" BOOL WINAPI GetExtensionVersion(HSE_VERSION_INFO* pVer)
{
	return theExtension.GetExtensionVersion(pVer);
}

extern "C" BOOL WINAPI TerminateExtension(DWORD dwFlags)
{
	return theExtension.TerminateExtension(dwFlags);
}
