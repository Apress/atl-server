// PerThreadSvc.h : Defines the ATL Server request handler class
//
#pragma once
#include <atlcoll.h>
#include "..\PerThreadSvcIsapi\PerThreadSvcDef.h"

[ request_handler("Default") ]
class CPerThreadSvcHandler
{
private:

protected:
	struct stForecast
	{
		CStringW	strCity;
		double		dTemperature;
	};

	CAtlArray<stForecast>	m_arForecast;
	int						m_nCityIterator;
public:
	// Put public members here

	HTTP_CODE ValidateAndExchange()
	{
		// TODO: Put all initialization and validation code here
		
		// Set the content-type
		m_HttpResponse.SetContentType("text/html");

		CComPtr<IPerThreadWeatherSvc>	spSvc;
		if( !SUCCEEDED(m_spServiceProvider->QueryService( __uuidof(IPerThreadWeatherSvc), &spSvc)) )
		{
			return HTTP_FAIL;
		}

		BSTR*	arCities;
		int		nCount;
		if (!SUCCEEDED(spSvc->GetCityList( &nCount, &arCities)))
		{
			m_HttpResponse << "Error getting the city list";
		}

		for( int nIndex = 0; nIndex < nCount; nIndex ++)
		{
			stForecast	add;
			add.strCity.Append(arCities[nIndex]);
			if (!SUCCEEDED(spSvc->GetCityForecast(arCities[nIndex], &add.dTemperature)))
			{
				m_HttpResponse << "Error getting the city forecast";
			}
			m_arForecast.Add( add );
		}

		if (!SUCCEEDED(spSvc->CleanupCityList(arCities, nCount)))
		{
			m_HttpResponse << "Error cleaning up the city list";
		}

		m_nCityIterator = -1;
		return HTTP_SUCCESS;
	}
 
protected:
	// Here is an example of how to use a replacement tag with the stencil processor
	[ tag_name(name="GetNextCity") ]
	HTTP_CODE OnGetNextCity(void)
	{
		if( ++m_nCityIterator < m_arForecast.GetCount() )
		{
			return HTTP_SUCCESS;
		}
		else
			return HTTP_S_FALSE;
	}

	[ tag_name(name="CityName") ]
	HTTP_CODE OnCityName(void)
	{
		m_HttpResponse << m_arForecast[m_nCityIterator].strCity;
		return HTTP_SUCCESS;
	}

	[ tag_name(name="CityTemperature") ]
	HTTP_CODE OnCityTemperature(void)
	{
		m_HttpResponse << m_arForecast[m_nCityIterator].dTemperature;
		return HTTP_SUCCESS;
	}
}; // class CPerThreadSvcHandler
