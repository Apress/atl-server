
#ifndef PERTHREADSERVICE_INCLUDED_H
#define PERTHREADSERVICE_INCLUDED_H


#pragma once


// IPerThreadSvc.
__interface __declspec(uuid("5BC416A1-CBA5-4769-9DEB-75E673E229FF"))
	IPerThreadWeatherSvc : public IUnknown
{
	// Gets the list of cities
	HRESULT GetCityList(int* pCount, BSTR**	arCities);
	HRESULT GetCityForecast(BSTR bstrCity, double* pdRet);
	HRESULT CleanupCityList(BSTR* arCities, int nCount);
};



#endif // PERTHREADSERVICE_INCLUDED_H