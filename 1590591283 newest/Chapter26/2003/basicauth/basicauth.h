// basicauth.h : Defines the ATL Server request handler class
//
#pragma once
#define SECURE 

namespace basicauthService
{
// all struct, enum, and typedefs for your webservice should go inside the namespace

// IbasicauthService - web service interface declaration
//
[
	uuid("3A5603DC-D2F9-4512-9059-E61BC667A54F"), 
	object
]
__interface IbasicauthService
{
	// HelloWorld is a sample ATL Server web service method.  It shows how to
	// declare a web service method and its in-parameters and out-parameters
	[id(1)] HRESULT HelloWorld([in] BSTR bstrInput, [out, retval] BSTR *bstrOutput);
	// TODO: Add additional web service methods here
};


// basicauthService - web service implementation
//
[
	request_handler(name="Default", sdl="GenbasicauthWSDL"),
	soap_handler(
		name="basicauthService", 
		namespace="urn:basicauthService",
		protocol="soap"
	)
]
class CbasicauthService :
	public IbasicauthService
{
private:
	BOOL Auth;
	CHttpRequest m_HttpRequest;
public:
		// override HandleRequest
	HTTP_CODE HandleRequest(AtlServerRequest *pRequestInfo, IServiceProvider * pProvider)
	{

		// We need to create an m_HttpRequest in order to Authenticate create a m_HttpRequest
		// that we can authenticate against.
		HTTP_CODE hRet = m_HttpRequest.Initialize(pRequestInfo->pServerContext, 
										0,
										0);
		Auth = FALSE;
		CString str;
		CString type = "BASIC";
		BOOL b = m_HttpRequest.GetAuthenticationType(str);
#ifdef SECURE
		if ((b == TRUE) && (str == type))
		{
			Auth = TRUE;
		}
#endif
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
}; // class CbasicauthService

} // namespace basicauthService
