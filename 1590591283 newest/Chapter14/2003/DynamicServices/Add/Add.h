// Add.h : Defines the ATL Server request handler class
//
#pragma once


#include "..\Include\CommonInterfaces.h"


class	CBinaryAdd : public CBinaryOperationHelper
{
protected:
	int		m_nData;
public:
	CBinaryAdd()
	{
		m_nData = 101;
	}
	// This is the generic interface of a binary arithmetic operation
	HRESULT Perform(double	inA, double inB, double* pOutRet)
	{
		if( !pOutRet )
			return E_POINTER;

		*pOutRet = inA + inB;

		return S_OK;
	}
};

// {AC632542-1999-48b0-957B-51D60790FB0D}
DEFINE_GUID(g_AddGUID, 
		0xac632542, 0x1999, 0x48b0, 0x95, 0x7b, 0x51, 0xd6, 0x7, 0x90, 0xfb, 0xd);
CBinaryAdd		g_Service;
LPCSTR			g_szAppDLL	=	"Add";

[ request_handler("Default") ]
class CAddHandler
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
									g_AddGUID, __uuidof(IBinaryOperation), 
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
			hRet = spRegistrar->RegisterServiceName( g_AddGUID, __uuidof(IBinaryOperation), g_szAppDLL);
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
}; // class CAddHandler
