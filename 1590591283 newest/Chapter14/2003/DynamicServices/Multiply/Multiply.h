// Multiply.h : Defines the ATL Server request handler class
//
#pragma once


#include "..\Include\CommonInterfaces.h"


class	CBinaryMultiply : public CBinaryOperationHelper
{
protected:
	int		m_nData;
public:
	CBinaryMultiply()
	{
		m_nData = 101;
	}
	// This is the generic interface of a binary arithmetic operation
	HRESULT Perform(double	inA, double inB, double* pOutRet)
	{
		if( !pOutRet )
			return E_POINTER;

		*pOutRet = inA * inB;

		return S_OK;
	}
};

// {6F3F99E0-5D11-4267-A0E7-89BFF010427A}
DEFINE_GUID(g_MultiplyGUID, 
	0x6f3f99e0, 0x5d11, 0x4267, 0xa0, 0xe7, 0x89, 0xbf, 0xf0, 0x10, 0x42, 0x7a);
CBinaryMultiply		g_Service;
LPCSTR			g_szAppDLL	=	"Multiply";

[ request_handler("Default") ]
class CMultiplyHandler
{
private:
	// Put private members here

protected:
	// Put protected members here

public:
	// Put public members here

	HTTP_CODE ValidateAndExchange()
	{
		// TODO: Put all initialization and validation code here
		
		// Set the content-type
		m_HttpResponse.SetContentType("text/html");

		// Get the Registrar Service and add the g_Service service
		// under the name of the current DLL
		CComPtr<IRegistrarService>	spRegistrar;
		CComPtr<IUnknown>			spUnk;
		HRESULT hRet;

		hRet	=	g_Service.QueryInterface(IID_IUnknown, (void**)&spUnk);
		
		if( SUCCEEDED(hRet) )
		{
			// Attempt to register the dynamic service
			hRet	=	m_spExtension->AddService( 
									g_MultiplyGUID, __uuidof(IBinaryOperation), 
									spUnk,
									m_hInstHandler);
		}

		if( SUCCEEDED(hRet) )
		{
			// Get the registrar service
			hRet = m_spServiceProvider->QueryService(__uuidof(IRegistrar), &spRegistrar);
		}
		
		 
		if( SUCCEEDED(hRet) )
		{
			// Register the service under the module name
			hRet = spRegistrar->RegisterServiceName( g_MultiplyGUID, __uuidof(IBinaryOperation), g_szAppDLL);
		}


		if( SUCCEEDED(hRet) )
		{
			m_HttpResponse << g_szAppDLL << " was loaded successfully<br>";
		}
		else
		{
			m_HttpResponse << "An error occurred while attempting to register the service in " 
						   << g_szAppDLL << "<br>";
		}
		m_HttpResponse << "Press browser's &lt;&lt;Back&gt;&gt; to return";

		return HTTP_SUCCESS;
	}
 
protected:
}; // class CMultiplyHandler
