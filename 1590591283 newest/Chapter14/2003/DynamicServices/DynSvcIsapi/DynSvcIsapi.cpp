// DynSvcIsapi.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
// For custom assert and trace handling with WebDbg.exe
#ifdef _DEBUG
CDebugReportHook g_ReportHook;
#endif
[ module(name="MyDynSvc", type="dll") ];
[ emitidl(restricted) ];

#include "Registrar.h"





class CMyExtension : public CIsapiExtension<>
{
	CRegistrar		m_internalRegistrarSvc;
public:
	virtual HRESULT STDMETHODCALLTYPE QueryService(
		REFGUID guidService,
		REFIID riid,
		void **ppvObject)
	{
		if( IsEqualIID(riid, __uuidof(IRegistrarService)) )
			return m_internalRegistrarSvc.QueryInterface( riid, ppvObject);
		else
			return	__super::QueryService( guidService, riid, ppvObject);
	}
};

// The ATL Server ISAPI extension
//ExtensionType theExtension;
CMyExtension	theExtension;


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
