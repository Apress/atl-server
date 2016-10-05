// Created by Microsoft (R) C/C++ Compiler Version 13.00.9466
//
// c:\projects\bkperfmoncleanisapi\bkperfmoncleanisapi.mrg.cpp
// compiler-generated file created 07/26/02 at 00:28:27
//
// This C++ source file is intended to be a representation of the
// source code injected by the compiler.  It may not compile or
// run exactly as the original source file.
//

// bkPerfmonCleanIsapi.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
//+++ Start Injected Code
[no_injected_text(true)];      // Suppress injected text, it has already been injected
#pragma warning(disable: 4543) // Suppress warnings about skipping injected text
#pragma warning(disable: 4199) // Suppress warnings from attribute providers

#pragma message("\n\nNOTE: This merged source file should be visually inspected for correctness.\n\n")
//--- End Injected Code


#include "bkPerfmonCleanIsapi.h"
// For custom assert and trace handling with WebDbg.exe
#ifdef _DEBUG
CDebugReportHook g_ReportHook;
#endif
[ module(name="MybkPerfmonClean", type="dll") ];

//+++ Start Injected Code For Attribute 'module'
#injected_line 10 "c:\\projects\\bkperfmoncleanisapi\\bkperfmoncleanisapi.cpp"

#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct _GUID 
{
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[ 8 ];
} 
GUID;
#endif

extern "C" const __declspec(selectany) GUID __LIBID_ = {0xd08a1a1a,0x41ed,0x3a67,{0x88,0x9f,0xe0,0x9a,0x9e,0x25,0x70,0x65}};
struct __declspec(uuid("d08a1a1a-41ed-3a67-889f-e09a9e257065")) MybkPerfmonClean;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 10 "c:\\projects\\bkperfmoncleanisapi\\bkperfmoncleanisapi.cpp"

class CMybkPerfmonCleanModule;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 10 "c:\\projects\\bkperfmoncleanisapi\\bkperfmoncleanisapi.cpp"

extern CMybkPerfmonCleanModule _AtlModule;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 10 "c:\\projects\\bkperfmoncleanisapi\\bkperfmoncleanisapi.cpp"
extern "C" STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 10 "c:\\projects\\bkperfmoncleanisapi\\bkperfmoncleanisapi.cpp"
extern "C" STDAPI DllRegisterServer(void);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 10 "c:\\projects\\bkperfmoncleanisapi\\bkperfmoncleanisapi.cpp"
extern "C" STDAPI DllUnregisterServer(void);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 10 "c:\\projects\\bkperfmoncleanisapi\\bkperfmoncleanisapi.cpp"
extern "C" STDAPI DllCanUnloadNow(void);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 10 "c:\\projects\\bkperfmoncleanisapi\\bkperfmoncleanisapi.cpp"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 10 "c:\\projects\\bkperfmoncleanisapi\\bkperfmoncleanisapi.cpp"

class CMybkPerfmonCleanModule : public CAtlDllModuleT<CMybkPerfmonCleanModule>
    								
{
public:
    DECLARE_LIBID(__uuidof(MybkPerfmonClean))
        								
};

#injected_line 10 "c:\\projects\\bkperfmoncleanisapi\\bkperfmoncleanisapi.cpp"

CMybkPerfmonCleanModule _AtlModule;

#injected_line 10 "c:\\projects\\bkperfmoncleanisapi\\bkperfmoncleanisapi.cpp"
extern "C" STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv) 
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}
#injected_line 10 "c:\\projects\\bkperfmoncleanisapi\\bkperfmoncleanisapi.cpp"
extern "C" STDAPI DllRegisterServer(void) 
{
    return _AtlModule.DllRegisterServer();
}
#injected_line 10 "c:\\projects\\bkperfmoncleanisapi\\bkperfmoncleanisapi.cpp"
extern "C" STDAPI DllUnregisterServer(void) 
{
    return _AtlModule.DllUnregisterServer();
}
#injected_line 10 "c:\\projects\\bkperfmoncleanisapi\\bkperfmoncleanisapi.cpp"
extern "C" STDAPI DllCanUnloadNow(void) 
{
    return _AtlModule.DllCanUnloadNow();
}
#injected_line 10 "c:\\projects\\bkperfmoncleanisapi\\bkperfmoncleanisapi.cpp"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) 
{
    hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved);
}
#injected_line 10 "c:\\projects\\bkperfmoncleanisapi\\bkperfmoncleanisapi.cpp"

#if defined(_M_IX86)
#pragma comment(linker, "/EXPORT:DllMain=_DllMain@12,PRIVATE")
#pragma comment(linker, "/EXPORT:DllRegisterServer=_DllRegisterServer@0,PRIVATE")
#pragma comment(linker, "/EXPORT:DllUnregisterServer=_DllUnregisterServer@0,PRIVATE")
#pragma comment(linker, "/EXPORT:DllGetClassObject=_DllGetClassObject@12,PRIVATE")
#pragma comment(linker, "/EXPORT:DllCanUnloadNow=_DllCanUnloadNow@0,PRIVATE")
#elif defined(_M_IA64)
#pragma comment(linker, "/EXPORT:DllMain,PRIVATE")
#pragma comment(linker, "/EXPORT:DllRegisterServer,PRIVATE")
#pragma comment(linker, "/EXPORT:DllUnregisterServer,PRIVATE")
#pragma comment(linker, "/EXPORT:DllGetClassObject,PRIVATE")
#pragma comment(linker, "/EXPORT:DllCanUnloadNow,PRIVATE")
#endif	

//--- End Injected Code For Attribute 'module'

[ emitidl(restricted) ];

typedef MyCIsapiExtension<CThreadPool<CIsapiWorker>, CStdRequestStats> ExtensionType;

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
