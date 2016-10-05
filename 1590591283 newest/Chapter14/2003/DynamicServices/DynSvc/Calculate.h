// DynSvc.h : Defines the ATL Server request handler class
//
#pragma once
#include "..\Include\CommonInterfaces.h"

[ request_handler("Calculate") ]
class CCalculateHandler
{
private:
	// Put private members here

protected:
	CString							m_strService;
	double							m_dParam1;
	double							m_dParam2;
	double							m_dResult;
public:
	// Put public members here

	HTTP_CODE ValidateAndExchange()
	{
		
		// Set the content-type
		// m_HttpResponse.SetContentType("text/html");

		LPCSTR	szTmp = m_HttpRequest.GetFormVars().Lookup("service");
		if (!szTmp) 
		{
			m_HttpResponse << "Missing 'service' parameter<br>";
			return HTTP_FAIL;
		}
		m_strService	=	szTmp;
	
		
		szTmp = m_HttpRequest.GetFormVars().Lookup("param1");
		if (!szTmp) 
		{
			m_HttpResponse << "Missing 'param1' parameter. Assuming 0<br>";
			m_dParam1	=	0;
		}
		else
		{
			m_dParam1	=	atof(szTmp);	
		}
		
		szTmp = m_HttpRequest.GetFormVars().Lookup("param2");
		if (!szTmp) 
		{
			m_HttpResponse << "Missing 'param2' parameter. Assuming 0<br>";
			m_dParam2	=	0;
		}
		else
		{
			m_dParam2	=	atof(szTmp);	
		}		



		// TODO: Put all initialization and validation code here
		CComPtr<IRegistrarService>		spRegistrar;
		CComPtr<IBinaryOperation>		spBinOp;

		if( !SUCCEEDED(m_spServiceProvider->QueryService(__uuidof(IRegistrarService), &spRegistrar)))
		{
			m_HttpResponse << "An error occurred while accessing the Registrar name service from the ISAPI<br>";
			return HTTP_FAIL;
		}

		GUID guid;
		IID	 iid;
		if( FAILED(spRegistrar->ResolveServiceName ( m_strService, &guid, &iid)) || iid != __uuidof(IBinaryOperation))
		{
			m_HttpResponse << "Service " << m_strService << " seems not to be registered<br>";
			return HTTP_FAIL;
		}


		if( !SUCCEEDED(m_spServiceProvider->QueryService(guid, &spBinOp)))
		{
			m_HttpResponse << "An error occurred while accessing the "
							<< m_strService << " name service from the ISAPI<br>";
			return HTTP_FAIL;
		}

		spBinOp->Perform( m_dParam1, m_dParam2, &m_dResult);

		return HTTP_SUCCESS;
	}
 
protected:


	[ tag_name(name="ServiceName") ]
	HTTP_CODE OnServiceName(void)
	{
		m_HttpResponse << m_strService;
		return HTTP_SUCCESS;
	}

	[ tag_name(name="Param1") ]
	HTTP_CODE OnParam1(void)
	{
		m_HttpResponse << m_dParam1;
		return HTTP_SUCCESS;
	}
	[ tag_name(name="Param2") ]
	HTTP_CODE OnParam2(void)
	{
		m_HttpResponse << m_dParam2;
		return HTTP_SUCCESS;
	}
	[ tag_name(name="Result") ]
	HTTP_CODE OnResult(void)
	{
		m_HttpResponse << m_dResult;
		return HTTP_SUCCESS;
	}
}; // class CDynSvcHandler
