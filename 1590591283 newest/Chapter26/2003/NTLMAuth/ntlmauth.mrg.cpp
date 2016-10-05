// Created by Microsoft (R) C/C++ Compiler Version 13.10.2318
//
// c:\documents and settings\pranishk\my documents\visual studio projects\ntlmauth\ntlmauth.mrg.cpp
// compiler-generated file created 01/12/03 at 15:03:23
//
// This C++ source file is intended to be a representation of the
// source code injected by the compiler.  It may not compile or
// run exactly as the original source file.
//

// NTLMAuth.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
//+++ Start Injected Code
[no_injected_text(true)];      // Suppress injected text, it has already been injected
#pragma warning(disable: 4543) // Suppress warnings about skipping injected text
#pragma warning(disable: 4199) // Suppress warnings from attribute providers

// M00PRAGMA("\n\nNOTE: This merged source file should be visually inspected for correctness.\n\n")
//--- End Injected Code


// For custom assert and trace handling with WebDbg.exe
#ifdef _DEBUG
CDebugReportHook g_ReportHook;

//+++ Start Injected Code For Attribute 'module'
#injected_line 11 "c:\\documents and settings\\pranishk\\my documents\\visual studio projects\\ntlmauth\\ntlmauth.cpp"

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

extern "C" const __declspec(selectany) GUID __LIBID_ = {0x19351e05,0x4620,0x36aa,{0xb3,0x3b,0x55,0xcb,0x5b,0xad,0x72,0x05}};
struct __declspec(uuid("19351e05-4620-36aa-b33b-55cb5bad7205")) MyNTLMAuth;

//--- End Injected Code For Attribute 'module'

#endif

#include "NTLMAuth.h"
[ module(name="MyNTLMAuth", type="dll") ]
class CDllMainOverride
 :
    /*+++ Added Baseclass */ public CAtlDllModuleT<CDllMainOverride>
{
public:
	BOOL WINAPI DllMain(DWORD dwReason, LPVOID lpReserved)
	{
#if defined(_M_IX86)
		if (dwReason == DLL_PROCESS_ATTACH)
		{
			// stack overflow handler
			_set_security_error_handler( AtlsSecErrHandlerFunc );
		}
#endif
		return __super::DllMain(dwReason, lpReserved);
	}

	//+++ Start Injected Code For Attribute 'module'
    #injected_line 11 "c:\\documents and settings\\pranishk\\my documents\\visual studio projects\\ntlmauth\\ntlmauth.cpp"

						DECLARE_LIBID(__uuidof(MyNTLMAuth))
					
	//--- End Injected Code For Attribute 'module'
};

//+++ Start Injected Code For Attribute 'module'
#injected_line 11 "c:\\documents and settings\\pranishk\\my documents\\visual studio projects\\ntlmauth\\ntlmauth.cpp"

extern CDllMainOverride _AtlModule;

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 11 "c:\\documents and settings\\pranishk\\my documents\\visual studio projects\\ntlmauth\\ntlmauth.cpp"
extern "C" STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 11 "c:\\documents and settings\\pranishk\\my documents\\visual studio projects\\ntlmauth\\ntlmauth.cpp"
extern "C" STDAPI DllRegisterServer(void);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 11 "c:\\documents and settings\\pranishk\\my documents\\visual studio projects\\ntlmauth\\ntlmauth.cpp"
extern "C" STDAPI DllUnregisterServer(void);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 11 "c:\\documents and settings\\pranishk\\my documents\\visual studio projects\\ntlmauth\\ntlmauth.cpp"
extern "C" STDAPI DllCanUnloadNow(void);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 11 "c:\\documents and settings\\pranishk\\my documents\\visual studio projects\\ntlmauth\\ntlmauth.cpp"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved);

//--- End Injected Code For Attribute 'module'


//+++ Start Injected Code For Attribute 'module'
#injected_line 11 "c:\\documents and settings\\pranishk\\my documents\\visual studio projects\\ntlmauth\\ntlmauth.cpp"

CDllMainOverride _AtlModule;

#injected_line 11 "c:\\documents and settings\\pranishk\\my documents\\visual studio projects\\ntlmauth\\ntlmauth.cpp"
extern "C" STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv) 
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}
#injected_line 11 "c:\\documents and settings\\pranishk\\my documents\\visual studio projects\\ntlmauth\\ntlmauth.cpp"
extern "C" STDAPI DllRegisterServer(void) 
{
    return _AtlModule.DllRegisterServer();
}
#injected_line 11 "c:\\documents and settings\\pranishk\\my documents\\visual studio projects\\ntlmauth\\ntlmauth.cpp"
extern "C" STDAPI DllUnregisterServer(void) 
{
    return _AtlModule.DllUnregisterServer();
}
#injected_line 11 "c:\\documents and settings\\pranishk\\my documents\\visual studio projects\\ntlmauth\\ntlmauth.cpp"
extern "C" STDAPI DllCanUnloadNow(void) 
{
    return _AtlModule.DllCanUnloadNow();
}
#injected_line 11 "c:\\documents and settings\\pranishk\\my documents\\visual studio projects\\ntlmauth\\ntlmauth.cpp"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) 
{
    hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved);
}
#injected_line 11 "c:\\documents and settings\\pranishk\\my documents\\visual studio projects\\ntlmauth\\ntlmauth.cpp"

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
