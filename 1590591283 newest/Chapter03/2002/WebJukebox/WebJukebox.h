// WebJukebox.h : Defines the ATL Server request handler class
//
#pragma once
#include "SongList.h"

[ request_handler("Default") ]
class CWebJukeboxHandler
{
public:
	// Put public members here
  CSongList m_songList;
  HRESULT hr;

	HTTP_CODE ValidateAndExchange()
	{
		// Set the content-type
		m_HttpResponse.SetContentType("text/html");
    hr = m_songList.OpenAll();
    //AtlTraceErrorRecords(hr);
    if (hr != S_OK) return HTTP_S_FALSE;
    return HTTP_SUCCESS;
	}
 
protected:

	[ tag_name(name="MoreSongs") ]
	HTTP_CODE OnMoreSongs(void)
	{
    hr = m_songList.MoveNext();
    if (hr != S_OK) return HTTP_S_FALSE;
		return HTTP_SUCCESS;
	}

 	[ tag_name(name="Name") ]
	HTTP_CODE OnName(void)
	{
    m_HttpResponse << m_songList.m_Name;
		return HTTP_SUCCESS;
	}

 	[ tag_name(name="Location") ]
	HTTP_CODE OnLocation(void) 
	{
    m_HttpResponse << m_songList.m_Location;
		return HTTP_SUCCESS;
	}

 	[ tag_name(name="Musician") ]
	HTTP_CODE OnMusician(void)
	{
    m_HttpResponse << m_songList.m_Musician;
		return HTTP_SUCCESS;
	}

 	[ tag_name(name="Description") ]
	HTTP_CODE OnDescription(void)
	{
    m_HttpResponse << m_songList.m_Description;
		return HTTP_SUCCESS;
	}
}; // class CWebJukeboxHandler
