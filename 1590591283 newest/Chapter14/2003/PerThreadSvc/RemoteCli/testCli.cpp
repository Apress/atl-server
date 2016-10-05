#define _WIN32_WINDOWS 0x0500
#include <stdio.h>
#include "RemoteWeatherService.h"
using namespace  RemoteWeatherService;



void main()
{
	CoInitialize(NULL);
	{
		CRemoteWeatherService	srv;
		
		BSTR*	arCities = NULL;
		int		nCityCount	=	0;
		
		srv.GetCityList(&arCities, &nCityCount);
		
		
		for ( int nIndex = 0; nIndex < nCityCount; nIndex ++)
		{
			double 	dRet;
			srv.GetCityForecast( arCities[nIndex], &dRet);
			printf("%ls -- %f\n", arCities[nIndex], dRet);
		}
		
		AtlCleanupArrayEx( arCities, nCityCount, srv.GetMemMgr() );
		srv.GetMemMgr()->Free( arCities );
		
	}
	CoUninitialize();
	
}