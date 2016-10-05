// atlspassport.h : Defines the ATL Server request handler class
//
#pragma once

#include "passporthandlert.h"

class CatlspassportHandler : public CPassportHandlerT<CatlspassportHandler>
{
public:
	HTTP_CODE ValidateAndExchange()
	{
		return HTTP_SUCCESS;
	}
 	
}; // class CatlspassportHandler

BEGIN_HANDLER_MAP()
	HANDLER_ENTRY("Default", CatlspassportHandler)
END_HANDLER_MAP()