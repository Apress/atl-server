// DynamicThreadPoolExample.h : Defines the ATL Server request handler class
//
#pragma once

[ request_handler("Default") ]
class CDynamicThreadPoolExampleHandler
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
}; // class CDynamicThreadPoolExampleHandler
