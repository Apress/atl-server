// Created by Microsoft (R) C/C++ Compiler Version 13.10.2318
//
// c:\documents and settings\pranishk\my documents\visual studio projects\ntlmauth\ntlmauth.mrg.h
// compiler-generated file created 01/12/03 at 15:03:20
//
// This C++ source file is intended to be a representation of the
// source code injected by the compiler.  It may not compile or
// run exactly as the original source file.
//


//+++ Start Injected Code
[no_injected_text(true)];      // Suppress injected text, it has already been injected
#pragma warning(disable: 4543) // Suppress warnings about skipping injected text
#pragma warning(disable: 4199) // Suppress warnings from attribute providers

// M00PRAGMA("\n\nNOTE: This merged source file should be visually inspected for correctness.\n\n")
//--- End Injected Code

// NTLMAuth.h : Defines the ATL Server request handler class
//
#pragma once

namespace NTLMAuthService
{
// all struct, enum, and typedefs for your webservice should go inside the namespace

// INTLMAuthService - web service interface declaration
//
[
	uuid("A1922823-CFB0-4787-AB7C-3D79599FF512"), 
	object
]
__interface INTLMAuthService
{
	// HelloWorld is a sample ATL Server web service method.  It shows how to
	// declare a web service method and its in-parameters and out-parameters
	[id(1)] HRESULT HelloWorld([in] BSTR bstrInput, [out, retval] BSTR *bstrOutput);
	// TODO: Add additional web service methods here
};


// NTLMAuthService - web service implementation
//
[
	request_handler(name="Default", sdl="GenNTLMAuthWSDL"),
	soap_handler(
		name="NTLMAuthService", 
		namespace="urn:NTLMAuthService",
		protocol="soap"
	)
]
class CNTLMAuthService :
	public INTLMAuthService
,
    /*+++ Added Baseclass */ public CSoapHandler<CNTLMAuthService>
{
private:
	BOOL Auth;
	CHttpRequest m_HttpRequest;
public:
	
	// override HandleRequest
	HTTP_CODE HandleRequest(AtlServerRequest *pRequestInfo, IServiceProvider * pProvider)
	{

		// We need to create an m_HttpRequest in order to Authenticate.
		HTTP_CODE hRet = m_HttpRequest.Initialize(pRequestInfo->pServerContext, 
										0,
										0);
		Auth = FALSE;
		CString str;
		CString ntlm = "NTLM";
		BOOL b = m_HttpRequest.GetAuthenticationType(str);
		if ((b == TRUE) && (str == ntlm))
		{
			Auth = TRUE;
		}
		return __super::HandleRequest(pRequestInfo, pProvider);
	}

	// This is a sample web service method that shows how to use the 
	// soap_method attribute to expose a method as a web method
	[ soap_method ]
	HRESULT HelloWorld(/*[in]*/ BSTR bstrInput, /*[out, retval]*/ BSTR *bstrOutput)
	{
		if (Auth == TRUE)
		{
			CComBSTR bstrOut(L"Hello ");
			bstrOut += bstrInput;
			bstrOut += L"!";
			*bstrOutput = bstrOut.Detach();
			return S_OK;
		}
		else
			return S_FALSE;
	}
	// TODO: Add additional web service methods here

	//+++ Start Injected Code For Attribute 'soap_handler'
#injected_line 28 "c:\\documents and settings\\pranishk\\my documents\\visual studio projects\\ntlmauth\\ntlmauth.h"
    const _soapmap ** GetFunctionMap() throw();
    const _soapmap ** GetHeaderMap() throw();
    void * GetHeaderValue() throw();
    const wchar_t * GetNamespaceUri() throw();
    const char * GetNamespaceUriA() throw();
    const char * GetServiceName() throw();
    HRESULT CallFunction(void *pvParam, const wchar_t *wszLocalName, int cchLocalName, size_t nItem);

	//--- End Injected Code For Attribute 'soap_handler'
};

//+++ Start Injected Code For Attribute 'request_handler'
#injected_line 27 "c:\\documents and settings\\pranishk\\my documents\\visual studio projects\\ntlmauth\\ntlmauth.h"

				
HANDLER_ENTRY_SDL("Default", CNTLMAuthService, ::NTLMAuthService::CNTLMAuthService, GenNTLMAuthWSDL)

			
//--- End Injected Code For Attribute 'request_handler'


//+++ Start Injected Code For Attribute 'soap_handler'
#injected_line 28 "c:\\documents and settings\\pranishk\\my documents\\visual studio projects\\ntlmauth\\ntlmauth.h"
struct ___NTLMAuthService_CNTLMAuthService_HelloWorld_struct
    {
    BSTR bstrInput;
    BSTR bstrOutput;
};

extern __declspec(selectany) const _soapmapentry ___NTLMAuthService_CNTLMAuthService_HelloWorld_entries[] =
    {
    
    	{
    		0xF6041A8C, 
    		"bstrOutput", 
    		L"bstrOutput", 
    		sizeof("bstrOutput")-1, 
    		SOAPTYPE_STRING, 
    		SOAPFLAG_RETVAL | SOAPFLAG_OUT | SOAPFLAG_NULLABLE,
    		offsetof(___NTLMAuthService_CNTLMAuthService_HelloWorld_struct, bstrOutput),
    		NULL,
    		NULL,
    		-1,
    	},
    
    	{
    		0xA9ECBD0B, 
    		"bstrInput", 
    		L"bstrInput", 
    		sizeof("bstrInput")-1, 
    		SOAPTYPE_STRING, 
    		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_NULLABLE,
    		offsetof(___NTLMAuthService_CNTLMAuthService_HelloWorld_struct, bstrInput),
    		NULL,
    		NULL,
    		-1,
    	},
    	{ 0x00000000 }
    };

extern __declspec(selectany) const _soapmap ___NTLMAuthService_CNTLMAuthService_HelloWorld_map =
    {
    	0x46BA99FC,
    	"HelloWorld",
    	L"HelloWorld",
    	sizeof("HelloWorld")-1,
    	sizeof("HelloWorld")-1,
    	SOAPMAP_FUNC,
    	___NTLMAuthService_CNTLMAuthService_HelloWorld_entries,
    	sizeof(___NTLMAuthService_CNTLMAuthService_HelloWorld_struct),
    	1,
    	0,
    	SOAPFLAG_NONE | SOAPFLAG_RPC | SOAPFLAG_ENCODED,
    	0x93220F6D,
    	"urn:NTLMAuthService",
    	L"urn:NTLMAuthService",
    	sizeof("urn:NTLMAuthService")-1
    };

extern __declspec(selectany) const _soapmapentry ___NTLMAuthService_CNTLMAuthService_HelloWorld_atlsoapheader_entries[] =
    {
    	{ 0x00000000 }
    };

extern __declspec(selectany) const _soapmap ___NTLMAuthService_CNTLMAuthService_HelloWorld_atlsoapheader_map =
    {
    	0x46BA99FC,
    	"HelloWorld",
    	L"HelloWorld",
    	sizeof("HelloWorld")-1,
    	sizeof("HelloWorld")-1,
    	SOAPMAP_HEADER,
    	___NTLMAuthService_CNTLMAuthService_HelloWorld_atlsoapheader_entries,
    	0,
    	0,
    	-1,
    	SOAPFLAG_NONE | SOAPFLAG_RPC | SOAPFLAG_ENCODED,
    	0x93220F6D,
    	"urn:NTLMAuthService",
    	L"urn:NTLMAuthService",
    	sizeof("urn:NTLMAuthService")-1
    };
extern __declspec(selectany) const _soapmap * ___NTLMAuthService_CNTLMAuthService_funcs[] =
    {
    	&___NTLMAuthService_CNTLMAuthService_HelloWorld_map,
    	NULL
    };

extern __declspec(selectany) const _soapmap * ___NTLMAuthService_CNTLMAuthService_headers[] =
    {
    	&___NTLMAuthService_CNTLMAuthService_HelloWorld_atlsoapheader_map,
    	NULL
    };

ATL_NOINLINE inline const _soapmap ** CNTLMAuthService::GetFunctionMap()
    {
    return ___NTLMAuthService_CNTLMAuthService_funcs;
};

ATL_NOINLINE inline const _soapmap ** CNTLMAuthService::GetHeaderMap()
    {
    return ___NTLMAuthService_CNTLMAuthService_headers;
}

ATL_NOINLINE inline void * CNTLMAuthService::GetHeaderValue()
    {
    return this;
}

ATL_NOINLINE inline HRESULT CNTLMAuthService::CallFunction(
    	void *pvParam, 
    	const wchar_t *wszLocalName, 
    	int cchLocalName,
    	size_t nItem)
    {
    wszLocalName;
    cchLocalName;

    HRESULT hr = S_OK;

    switch(nItem)
	{
    case 0:
        {
            ___NTLMAuthService_CNTLMAuthService_HelloWorld_struct *p = (___NTLMAuthService_CNTLMAuthService_HelloWorld_struct *) pvParam;
            hr = HelloWorld(p->bstrInput, &p->bstrOutput);
            break;
        }
    default:
        hr = E_FAIL;
    }

    return hr;
}

ATL_NOINLINE inline const wchar_t * CNTLMAuthService::GetNamespaceUri()
    {
    return L"urn:NTLMAuthService";
}

ATL_NOINLINE inline const char * CNTLMAuthService::GetNamespaceUriA()
    {
    return "urn:NTLMAuthService";
}

ATL_NOINLINE inline const char * CNTLMAuthService::GetServiceName()
    {
    return "NTLMAuthService";
}

//--- End Injected Code For Attribute 'soap_handler'
 // class CNTLMAuthService

} // namespace NTLMAuthService
