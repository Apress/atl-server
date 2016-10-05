// HelloWorldNoAttributes.h : Defines the ATL Server request handler class
//
#pragma once

class CHelloWorldNoAttributesHandler
	: public CRequestHandlerT<CHelloWorldNoAttributesHandler>
{
private:
	// Put private members here

protected:
	// Put protected members here

public:
	// Put public members here

	// TODO: Add additional tags to the replacement method map
	BEGIN_REPLACEMENT_METHOD_MAP(CHelloWorldNoAttributesHandler)
		REPLACEMENT_METHOD_ENTRY("Hello", OnHello)
	END_REPLACEMENT_METHOD_MAP()

	HTTP_CODE ValidateAndExchange()
	{
		// TODO: Put all initialization and validation code here
		
		// Set the content-type
		m_HttpResponse.SetContentType("text/html");
		
		return HTTP_SUCCESS;
	}
 
protected:
	// Here is an example of how to use a replacement tag with the stencil processor
	HTTP_CODE OnHello(void)
	{
		m_HttpResponse << "Hello World!";
		return HTTP_SUCCESS;
	}
}; // class CHelloWorldNoAttributesHandler
