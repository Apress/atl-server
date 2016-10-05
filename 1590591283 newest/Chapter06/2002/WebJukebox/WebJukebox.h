// WebJukebox.h : Defines the ATL Server request handler class
//
#pragma once
#include "OrderedData.h"

[ request_handler("Default") ]
class CWebJukeboxHandler
{
public:
	// Put public members here
  HRESULT hr;
  CSongData m_List;
  CHttpRequestParams *formFields;
  
  bool FormDataExists()
  {
    formFields = (CHttpRequestParams *) &(m_HttpRequest.GetFormVars());
    if (formFields->GetCount())
      return true;
    else 
      return false;
  }
  
  HTTP_CODE OpenSorted()
  {
    CStringA strName, strValue;
    POSITION pos = formFields->GetStartPosition();
    formFields->GetNextAssoc(pos, strName, strValue);
    if (strName == "Name")
    {
      m_List.m_Sortby = 1;
    }
    else if (strName == "Musician")
    {
      m_List.m_Sortby = 2;
    }
    else if (strName == "Description")
    {
      m_List.m_Sortby = 3;
    }
    hr = m_List.OpenAll();
    if (hr != S_OK) return HTTP_S_FALSE;
    return HTTP_SUCCESS;
  }

	HTTP_CODE ValidateAndExchange()
	{
    m_List.m_Sortby = 0;
		// Set the content-type
		m_HttpResponse.SetContentType("text/html");
    //AtlTraceErrorRecords(hr);
    if (FormDataExists())
    {
      return OpenSorted();
    }
    else
    {
      hr = m_List.OpenAll();
      if (hr != S_OK) return HTTP_S_FALSE;
    }
    return HTTP_SUCCESS;
	}
 
protected:

	[ tag_name(name="MoreSongs") ]
	HTTP_CODE OnMoreSongs(void)
	{
    hr = m_List.MoveNext();
    if (hr != S_OK) return HTTP_S_FALSE;
		return HTTP_SUCCESS;
	}

 	[ tag_name(name="Name") ]
	HTTP_CODE OnName(void)
	{
    m_HttpResponse << m_List.GetName();
		return HTTP_SUCCESS;
	}

 	[ tag_name(name="Location") ]
	HTTP_CODE OnLocation(void) 
	{
    m_HttpResponse << m_List.GetLocation();
		return HTTP_SUCCESS;
	}

 	[ tag_name(name="Musician") ]
	HTTP_CODE OnMusician(void)
	{
    m_HttpResponse << m_List.GetMusician();
		return HTTP_SUCCESS;
	}

 	[ tag_name(name="Description") ]
	HTTP_CODE OnDescription(void)
	{
    m_HttpResponse << m_List.GetDescription();
		return HTTP_SUCCESS;
	}
}; // class CWebJukeboxHandler
