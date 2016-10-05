#pragma once

#include "stdafx.h"

template <	class THandler,
			class ThreadModel=CComSingleThreadModel,
			class TagReplacerType=CHtmlTagReplacer<THandler>
		 >
class CPassportHandlerT : public CRequestHandlerT<THandler, ThreadModel, TagReplacerType>
{
protected:
	typedef  CRequestHandlerT<THandler, ThreadModel, TagReplacerType> baseType;

	// keep this protected so derived classes can call methods directly if they want to
	IPassportManager2	*m_passportManager;

	// these values are used in a number of Passport manager API calls
	CComVariant			m_returnURL;				// value of the url of the current page
	CComVariant			m_timeWindow;				// will be left empty by default
	CComVariant			m_forceLogin;				// true by default
	CComVariant			m_coBrandArgs;				// empty by default	
	CComVariant			m_langId;					// value of GetThreadLocale
	CComVariant			m_usingHTTPS;				// determined by whether url contains https or not	
	CComVariant			m_namespace;				// empty by default	
	CComVariant			m_kpp;						// empty by default
	CComVariant			m_useSecureAuth;			// empty by default

public:
	CPassportHandlerT() : 
		m_passportManager(NULL),
		m_forceLogin(true),		
		m_langId(GetThreadLocale())
	{
	}

	virtual ~CPassportHandlerT(void)
	{}
	
	HTTP_CODE InitializeHandler(AtlServerRequest *pRequestInfo, IServiceProvider *pProvider)
	{		
		// do regular initialization
		HTTP_CODE httpCode = baseType::InitializeHandler(pRequestInfo, pProvider);
		
		if (httpCode == HTTP_SUCCESS)
		{
			if (!m_passportManager)
			{
				// create an instance of our passport manager
				if (FAILED(CoCreateInstance(CLSID_Manager, 
											NULL, 
											CLSCTX_INPROC_SERVER, 
											IID_IPassportManager2, 
											(void**)&m_passportManager)))
				{
					return HTTP_S_FALSE;
				}			
			}

			// initialize the passport manager with the ECB
			DWORD bufferSize(ATL_MAX_COOKIE_LEN);
			CHAR  cookieHeader[ATL_MAX_COOKIE_LEN + 1];
			cookieHeader[0] = 0;

			if (FAILED(m_passportManager->OnStartPageECB((BYTE*)pRequestInfo->pECB, 
														 &bufferSize, 
														 cookieHeader)))
			{
				return HTTP_S_FALSE;
			}
			
			// Initialize some default values.  We'll use these values as default parameters
			// to a number of Passport Manager API calls.
			CString url;
			bool	https(false);
			if (!GetURL(url, https))
			{
				return HTTP_S_FALSE;
			}		

			m_returnURL  = url;
			m_usingHTTPS = https;
			
			// make sure we're not caching
			m_HttpResponse.SetCacheControl("no-cache");

			// response type has to be text
			m_HttpResponse.SetContentType("text/html");
		}

		return httpCode;
	}

	HTTP_CODE Uninitialize(HTTP_CODE hcError)
	{
		if (m_passportManager)
		{
			m_passportManager->Release();
			m_passportManager = NULL;
		}

		return hcError;
	}

	HTTP_CODE OnGetProfile(TCHAR *profileName)
	{
		ATLASSERT(m_passportManager);
		ATLASSERT(profileName);

		CComVariant value;
		if (FAILED(m_passportManager->get_Profile(CComBSTR(profileName), &value)))
		{
			return HTTP_S_FALSE;
		}		
				
		switch (value.vt)
		{
		case VT_I1: 
			m_HttpResponse << value.cVal;
			break;
		case VT_I4:
			m_HttpResponse << value.intVal;
			break;
		case VT_BSTR:
			m_HttpResponse << value.bstrVal;
			break;
		default:
			m_HttpResponse << "Uknown type!";
			break;
		}

		return HTTP_SUCCESS;
	}

	HTTP_CODE OnIsAuthenticated()
	{
		ATLASSERT(m_passportManager);

		VARIANT_BOOL isAuthenticated(VARIANT_FALSE);
		if (FAILED(m_passportManager->IsAuthenticated(	m_timeWindow, 
														m_forceLogin, 
														m_useSecureAuth, 
														&isAuthenticated)))
		{
			return HTTP_S_FALSE;
		}

		return isAuthenticated == VARIANT_TRUE ? HTTP_SUCCESS : HTTP_S_FALSE; 		
	}

	HTTP_CODE OnLogoTag()
	{	
		ATLASSERT(m_passportManager);

		BSTR logoTag(NULL);
		if (FAILED(m_passportManager->LogoTag(m_returnURL,
											  m_timeWindow,
											  m_forceLogin,
											  m_coBrandArgs, 
											  m_langId, 
											  m_usingHTTPS, 
											  m_namespace, 
											  m_kpp, 
											  m_useSecureAuth, 
											  &logoTag)))
		{
			m_HttpResponse << "ERROR - could not get LogoTag";
			return HTTP_S_FALSE;
		}
		
		// output the logo tag link
		m_HttpResponse << logoTag;

		// clean up the BSTR
		::SysFreeString(logoTag);

		return HTTP_SUCCESS;
	}

	BEGIN_REPLACEMENT_METHOD_MAP(THandler)
		REPLACEMENT_METHOD_ENTRY("Passport_LogoTag",			OnLogoTag)
		REPLACEMENT_METHOD_ENTRY("Passport_IsAuthenticated",	OnIsAuthenticated)
		REPLACEMENT_METHOD_ENTRY_EX_STR("Passport_GetProfile",	OnGetProfile)
	END_REPLACEMENT_METHOD_MAP()

private:
	bool GetURL(CString& url, bool& bHttps)
	{
		char szURL[ATL_URL_MAX_URL_LENGTH];
		DWORD dwUrlSize = sizeof(szURL);
		char szServer[ATL_URL_MAX_HOST_NAME_LENGTH];
		DWORD dwServerSize = sizeof(szServer);
		char szHttps[16];
		DWORD dwHttpsLen = sizeof(szHttps);
		
		if (m_spServerContext->GetServerVariable("URL", szURL, &dwUrlSize) != FALSE)
		{
			if (m_spServerContext->GetServerVariable("SERVER_NAME", szServer, &dwServerSize) != FALSE)
			{
				bHttps = false;
				if ((m_spServerContext->GetServerVariable("HTTPS", szHttps, &dwHttpsLen) != FALSE) &&
					(!_stricmp(szHttps, "ON")))
				{
					bHttps = true;
				}
				_ATLTRY
				{					
					url.Format("http%s://%s%s", bHttps ? "s" : "", szServer, szURL);
					return true;
				}
				_ATLCATCHALL()
				{
					return false;
				}
			}
		}
		return false;
	}
};

