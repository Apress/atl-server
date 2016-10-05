// SimpleService.h : Defines the ATL Server request handler class
//
#pragma once
#include "..\SimpleServiceIsapi\CMyIsapiExtension.h"

[ request_handler("Default") ]
class CSimpleServiceHandler
{
private:
	// Put private members here
	CComPtr<ISimpleCounter> m_SimpleCounter;
	long counter;

protected:
	// Put protected members here

public:
	// Put public members here

	HTTP_CODE ValidateAndExchange()
	{
		HRESULT hr = m_spServiceProvider->QueryService(__uuidof(ISimpleCounter), &m_SimpleCounter)		;
		if (FAILED(hr))
		{
			m_SimpleCounter = 0;
		}
		m_SimpleCounter->Set();
		// Set the content-type
		m_HttpResponse.SetContentType("text/html");
		return HTTP_SUCCESS;
	}
 
protected:
	// Here is an example of how to use a replacement tag with the stencil processor
	[ tag_name(name="Hello") ]
	HTTP_CODE OnHello(void)
	{
		m_HttpResponse << "Hello World!";
		return HTTP_SUCCESS;
	}

	[ tag_name(name="Counter") ]
	HTTP_CODE OnCounter(void)
	{
		m_SimpleCounter->Get(&counter);
		m_HttpResponse << counter;
		return HTTP_SUCCESS;
	}
}; // class CSimpleServiceHandler
