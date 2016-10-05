// RemoteWeatherService.h : Defines the ATL Server request handler class
//
#pragma once

namespace RemoteWeatherService
{
	LPOLESTR	g_arCities[] = 
	{
		L"Toronto",
		L"Seattle",
		L"New York",
		L"Los Angeles",
	};


// IRemoteWeatherService - web service interface declaration
//
[
	uuid("C82F69D4-4E0E-4291-8133-D3724FB81B24"), 
	object
]
__interface IRemoteWeatherService
{
	[id(1)] HRESULT GetCityList([out, retval] int*	pnSize, 
								[out, size_is(*pnSize)] BSTR **arCityList);

	[id(2)] HRESULT GetCityForecast([in] BSTR	bstrCity, 
								[out, retval] double *dForecastTemperature);
};


// RemoteWeatherService - web service implementation
//
[
	request_handler(name="Default", sdl="GenRemoteWeatherServiceWSDL"),
	soap_handler(
		name="RemoteWeatherService", 
		namespace="urn:RemoteWeatherService",
		protocol="soap"
	)
]
class CRemoteWeatherService :
	public IRemoteWeatherService
{
public:
	[ soap_method ]
	HRESULT GetCityList(int*	pnSize, 
						BSTR**	arCityList)
	{
		*pnSize	=	sizeof(g_arCities) / sizeof(g_arCities[0]);
		*arCityList = (BSTR*)GetMemMgr()->Allocate( *pnSize * sizeof(BSTR*));

		for( int nIndex = 0; nIndex < *pnSize; nIndex ++ )
		{
			(*arCityList)[nIndex] = ::SysAllocString( g_arCities[nIndex] );
		}
		
		return S_OK;
	}

	[ soap_method ]
	HRESULT GetCityForecast(BSTR	bstrCity, 
							double *dForecastTemperature)
	{
		for( int nIndex = 0; nIndex < sizeof(g_arCities) / sizeof (g_arCities[0]); nIndex ++ )
		{
			if( wcsicmp(bstrCity, g_arCities[nIndex]) == 0 )
			{
				*dForecastTemperature = 95.5 + nIndex;
				return S_OK;
			}
		}

		return S_FALSE;
	}
	// TODO: Add additional web service methods here
}; // class CRemoteWeatherService

} // namespace RemoteWeatherService
