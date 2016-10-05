// bkPerfmonClean.h : Defines the ATL Server request handler class
//
#pragma once
#include "..\bkPerfmonCleanIsapi\bkPerfmonCleanIsapi.h"

[ request_handler("Default") ]
class CbkPerfmonCleanHandler
{
private:
	CComPtr<IHitCounter> m_HitCounter;
public:
	HTTP_CODE ValidateAndExchange()
	{
		// Set the content-type
		m_HttpResponse.SetContentType("text/html");
		HRESULT hr = m_spServiceProvider->QueryService(__uuidof(IHitCounter), &m_HitCounter);
		if (FAILED(hr))
		{
			m_HitCounter = 0;
		}
		m_HitCounter->IncrementCounter();
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
}; 
