#pragma once
#include "products.h"

#define CONNECTION_STRINGW L"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=Northwind;Data Source=testing\\vsdotnet;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=SHAMALLIGATOR2;Use Encryption for Data=False;Tag with column collation when possible=False"
#define CONNECTION_STRINGT _T( "Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=Northwind;Data Source=testing\\vsdotnet;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=SHAMALLIGATOR2;Use Encryption for Data=False;Tag with column collation when possible=False" )

[ request_handler("Default") ]
class CDataAccessHandler
{
private:
	CProducts    m_products;

public:
	HTTP_CODE ValidateAndExchange()
	{		
		m_HttpResponse.SetContentType("text/html");
		
		CDataConnection dataConnection;
		if( FAILED( GetDataSource( m_spServiceProvider, CONNECTION_STRINGT, CONNECTION_STRINGW, &dataConnection ) ) )
		{
			return HTTP_S_FALSE;
		}
		
		if( FAILED( m_products.Open( dataConnection ) ) )
		{
			return HTTP_S_FALSE;
		}

		return HTTP_SUCCESS;
	}

	[tag_name( "HasMoreData" )]
	HTTP_CODE OnHasMoreProducts()
	{
		if( m_products.MoveNext() == DB_S_ENDOFROWSET )
		{
			return HTTP_SUCCESS;
		}
		else
		{
			return HTTP_S_FALSE;
		}
	}

	[tag_name( "ProductName" )]
	HTTP_CODE OnProductName()
	{
		m_HttpResponse << m_products.m_ProductName;

		return HTTP_SUCCESS;
	}

	[tag_name( "ProductPrice" )]
	HTTP_CODE OnProductPrice()
	{
		m_HttpResponse << m_products.m_UnitPrice;

		return HTTP_SUCCESS;
	}
};
