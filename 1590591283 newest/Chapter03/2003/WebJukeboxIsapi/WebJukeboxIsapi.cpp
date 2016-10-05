// WebJukeboxIsapi.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
// For custom assert and trace handling with WebDbg.exe
#ifdef _DEBUG
CDebugReportHook g_ReportHook;
#endif
[ module(name="MyWebJukebox", type="dll") ];
[ emitidl(restricted) ];

#include "WebJukeboxextension.h"

BEGIN_PERFREG_MAP()
	PERFREG_ENTRY(CRequestPerfMon)
END_PERFREG_MAP()

typedef CWebJukeboxExtension<CThreadPool<CWebJukeboxExtensionWorker>, CPerfMonRequestStats > ExtensionType;

// The ATL Server ISAPI extension
ExtensionType theExtension;


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
