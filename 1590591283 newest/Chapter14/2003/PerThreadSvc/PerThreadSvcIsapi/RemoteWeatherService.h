//
// sproxy.exe generated file
// do not modify this file
//
// Created: 09/29/2002@13:05:9
//

#pragma once

#include <atlsoap.h>

namespace RemoteWeatherService
{

template <typename TClient = CSoapSocketClientT<> >
class CRemoteWeatherServiceT : 
	public TClient, 
	public CSoapRootHandler
{
protected:

	const _soapmap ** GetFunctionMap();
	const _soapmap ** GetHeaderMap();
	void * GetHeaderValue();
	const wchar_t * GetNamespaceUri();
	const char * GetServiceName();
	const char * GetNamespaceUriA();
	HRESULT CallFunction(
		void *pvParam, 
		const wchar_t *wszLocalName, int cchLocalName,
		size_t nItem);
	HRESULT GetClientReader(ISAXXMLReader **ppReader);

public:

	HRESULT __stdcall QueryInterface(REFIID riid, void **ppv)
	{
		if (ppv == NULL)
		{
			return E_POINTER;
		}

		*ppv = NULL;

		if (InlineIsEqualGUID(riid, IID_IUnknown) ||
			InlineIsEqualGUID(riid, IID_ISAXContentHandler))
		{
			*ppv = static_cast<ISAXContentHandler *>(this);
			return S_OK;
		}

		return E_NOINTERFACE;
	}

	ULONG __stdcall AddRef()
	{
		return 1;
	}

	ULONG __stdcall Release()
	{
		return 1;
	}

	CRemoteWeatherServiceT(ISAXXMLReader *pReader = NULL)
		:TClient(_T("http://localhost/RemoteWeatherService/RemoteWeatherService.dll\?Handler=Default"))
	{
		SetClient(true);
		SetReader(pReader);
	}
	
	~CRemoteWeatherServiceT()
	{
		Uninitialize();
	}
	
	void Uninitialize()
	{
		UninitializeSOAP();
	}	

	HRESULT GetCityForecast(
		BSTR bstrCity, 
		double* __retval
	);

	HRESULT GetCityList(
		BSTR** arCityList, int* arCityList_nSizeIs
	);
};

typedef CRemoteWeatherServiceT<> CRemoteWeatherService;

struct __CRemoteWeatherService_GetCityForecast_struct
{
	BSTR bstrCity;
	double __retval;
};

extern __declspec(selectany) const _soapmapentry __CRemoteWeatherService_GetCityForecast_entries[] =
{

	{
		0x1C68A6B4, 
		"bstrCity", 
		L"bstrCity", 
		sizeof("bstrCity")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_RPC | SOAPFLAG_ENCODED | SOAPFLAG_NULLABLE,
		offsetof(__CRemoteWeatherService_GetCityForecast_struct, bstrCity),
		NULL,
		NULL,
		-1,
	},
	{
		0x11515F60, 
		"return", 
		L"return", 
		sizeof("return")-1, 
		SOAPTYPE_DOUBLE, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_RPC | SOAPFLAG_ENCODED,
		offsetof(__CRemoteWeatherService_GetCityForecast_struct, __retval),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CRemoteWeatherService_GetCityForecast_map =
{
	0x1251B530,
	"GetCityForecast",
	L"GetCityForecast",
	sizeof("GetCityForecast")-1,
	sizeof("GetCityForecast")-1,
	SOAPMAP_FUNC,
	__CRemoteWeatherService_GetCityForecast_entries,
	sizeof(__CRemoteWeatherService_GetCityForecast_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_RPC | SOAPFLAG_ENCODED,
	0xAAB85D5C,
	"urn:RemoteWeatherService",
	L"urn:RemoteWeatherService",
	sizeof("urn:RemoteWeatherService")-1
};


struct __CRemoteWeatherService_GetCityList_struct
{
	BSTR *arCityList;
	int __arCityList_nSizeIs;
};

extern __declspec(selectany) const _soapmapentry __CRemoteWeatherService_GetCityList_entries[] =
{

	{
		0xE6986AA8, 
		"arCityList", 
		L"arCityList", 
		sizeof("arCityList")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_DYNARR | SOAPFLAG_RPC | SOAPFLAG_ENCODED | SOAPFLAG_NULLABLE,
		offsetof(__CRemoteWeatherService_GetCityList_struct, arCityList),
		NULL,
		NULL,
		0+1,
	},
	{
		0xE6986AA8,
		"__arCityList_nSizeIs",
		L"__arCityList_nSizeIs",
		sizeof("__arCityList_nSizeIs")-1,
		SOAPTYPE_INT,
		SOAPFLAG_NOMARSHAL,
		offsetof(__CRemoteWeatherService_GetCityList_struct, __arCityList_nSizeIs),
		NULL,
		NULL,
		-1
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CRemoteWeatherService_GetCityList_map =
{
	0xDC71D635,
	"GetCityList",
	L"GetCityList",
	sizeof("GetCityList")-1,
	sizeof("GetCityList")-1,
	SOAPMAP_FUNC,
	__CRemoteWeatherService_GetCityList_entries,
	sizeof(__CRemoteWeatherService_GetCityList_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_RPC | SOAPFLAG_ENCODED,
	0xAAB85D5C,
	"urn:RemoteWeatherService",
	L"urn:RemoteWeatherService",
	sizeof("urn:RemoteWeatherService")-1
};

extern __declspec(selectany) const _soapmap * __CRemoteWeatherService_funcs[] =
{
	&__CRemoteWeatherService_GetCityForecast_map,
	&__CRemoteWeatherService_GetCityList_map,
	NULL
};

template <typename TClient>
inline HRESULT CRemoteWeatherServiceT<TClient>::GetCityForecast(
		BSTR bstrCity, 
		double* __retval
	)
{
	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CRemoteWeatherService_GetCityForecast_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.bstrCity = bstrCity;

	__atlsoap_hr = SetClientStruct(&__params, 0);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"#GetCityForecast\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*__retval = __params.__retval;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CRemoteWeatherServiceT<TClient>::GetCityList(
		BSTR** arCityList, int* __arCityList_nSizeIs
	)
{
	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CRemoteWeatherService_GetCityList_struct __params;
	memset(&__params, 0x00, sizeof(__params));

	__atlsoap_hr = SetClientStruct(&__params, 1);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"#GetCityList\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*arCityList = __params.arCityList;
	*__arCityList_nSizeIs = __params.__arCityList_nSizeIs;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
ATL_NOINLINE inline const _soapmap ** CRemoteWeatherServiceT<TClient>::GetFunctionMap()
{
	return __CRemoteWeatherService_funcs;
}

template <typename TClient>
ATL_NOINLINE inline const _soapmap ** CRemoteWeatherServiceT<TClient>::GetHeaderMap()
{
	static const _soapmapentry __CRemoteWeatherService_GetCityForecast_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CRemoteWeatherService_GetCityForecast_atlsoapheader_map = 
	{
		0x1251B530,
		"GetCityForecast",
		L"GetCityForecast",
		sizeof("GetCityForecast")-1,
		sizeof("GetCityForecast")-1,
		SOAPMAP_HEADER,
		__CRemoteWeatherService_GetCityForecast_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_RPC | SOAPFLAG_ENCODED,
		0xAAB85D5C,
		"urn:RemoteWeatherService",
		L"urn:RemoteWeatherService",
		sizeof("urn:RemoteWeatherService")-1
	};

	static const _soapmapentry __CRemoteWeatherService_GetCityList_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CRemoteWeatherService_GetCityList_atlsoapheader_map = 
	{
		0xDC71D635,
		"GetCityList",
		L"GetCityList",
		sizeof("GetCityList")-1,
		sizeof("GetCityList")-1,
		SOAPMAP_HEADER,
		__CRemoteWeatherService_GetCityList_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_RPC | SOAPFLAG_ENCODED,
		0xAAB85D5C,
		"urn:RemoteWeatherService",
		L"urn:RemoteWeatherService",
		sizeof("urn:RemoteWeatherService")-1
	};


	static const _soapmap * __CRemoteWeatherService_headers[] =
	{
		&__CRemoteWeatherService_GetCityForecast_atlsoapheader_map,
		&__CRemoteWeatherService_GetCityList_atlsoapheader_map,
		NULL
	};
	
	return __CRemoteWeatherService_headers;
}

template <typename TClient>
ATL_NOINLINE inline void * CRemoteWeatherServiceT<TClient>::GetHeaderValue()
{
	return this;
}

template <typename TClient>
ATL_NOINLINE inline const wchar_t * CRemoteWeatherServiceT<TClient>::GetNamespaceUri()
{
	return L"urn:RemoteWeatherService";
}

template <typename TClient>
ATL_NOINLINE inline const char * CRemoteWeatherServiceT<TClient>::GetServiceName()
{
	return NULL;
}

template <typename TClient>
ATL_NOINLINE inline const char * CRemoteWeatherServiceT<TClient>::GetNamespaceUriA()
{
	return "urn:RemoteWeatherService";
}

template <typename TClient>
ATL_NOINLINE inline HRESULT CRemoteWeatherServiceT<TClient>::CallFunction(
	void *, 
	const wchar_t *, int,
	size_t)
{
	return E_NOTIMPL;
}

template <typename TClient>
ATL_NOINLINE inline HRESULT CRemoteWeatherServiceT<TClient>::GetClientReader(ISAXXMLReader **ppReader)
{
	if (ppReader == NULL)
	{
		return E_INVALIDARG;
	}
	
	CComPtr<ISAXXMLReader> spReader = GetReader();
	if (spReader.p != NULL)
	{
		*ppReader = spReader.Detach();
		return S_OK;
	}
	return TClient::GetClientReader(ppReader);
}

} // namespace RemoteWeatherService
