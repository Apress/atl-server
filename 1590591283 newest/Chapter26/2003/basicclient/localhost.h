//
// sproxy.exe generated file
// do not modify this file
//
// Created: 02/04/2003@20:57:59
//

#pragma once


#ifndef _WIN32_WINDOWS
#pragma message("warning: defining _WIN32_WINDOWS = 0x0410")
#define _WIN32_WINDOWS 0x0410
#endif

#include <atlsoap.h>

namespace basicauthService
{

template <typename TClient = CSoapSocketClientT<> >
class CbasicauthServiceT : 
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

	CbasicauthServiceT(ISAXXMLReader *pReader = NULL)
		:TClient(_T("http://pranishk-v1:80/basicauth/basicauth.dll\?Handler=Default"))
	{
		SetClient(true);
		SetReader(pReader);
	}
	
	~CbasicauthServiceT()
	{
		Uninitialize();
	}
	
	void Uninitialize()
	{
		UninitializeSOAP();
	}	

	HRESULT HelloWorld(
		BSTR bstrInput, 
		BSTR* __retval
	);
};

typedef CbasicauthServiceT<> CbasicauthService;

struct __CbasicauthService_HelloWorld_struct
{
	BSTR bstrInput;
	BSTR __retval;
};

extern __declspec(selectany) const _soapmapentry __CbasicauthService_HelloWorld_entries[] =
{

	{
		0xA9ECBD0B, 
		"bstrInput", 
		L"bstrInput", 
		sizeof("bstrInput")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_RPC | SOAPFLAG_ENCODED | SOAPFLAG_NULLABLE,
		offsetof(__CbasicauthService_HelloWorld_struct, bstrInput),
		NULL,
		NULL,
		-1,
	},
	{
		0x11515F60, 
		"return", 
		L"return", 
		sizeof("return")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_RPC | SOAPFLAG_ENCODED | SOAPFLAG_NULLABLE,
		offsetof(__CbasicauthService_HelloWorld_struct, __retval),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CbasicauthService_HelloWorld_map =
{
	0x46BA99FC,
	"HelloWorld",
	L"HelloWorld",
	sizeof("HelloWorld")-1,
	sizeof("HelloWorld")-1,
	SOAPMAP_FUNC,
	__CbasicauthService_HelloWorld_entries,
	sizeof(__CbasicauthService_HelloWorld_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_RPC | SOAPFLAG_ENCODED,
	0x53876B54,
	"urn:basicauthService",
	L"urn:basicauthService",
	sizeof("urn:basicauthService")-1
};

extern __declspec(selectany) const _soapmap * __CbasicauthService_funcs[] =
{
	&__CbasicauthService_HelloWorld_map,
	NULL
};

template <typename TClient>
inline HRESULT CbasicauthServiceT<TClient>::HelloWorld(
		BSTR bstrInput, 
		BSTR* __retval
	)
{
    if ( __retval == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CbasicauthService_HelloWorld_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.bstrInput = bstrInput;

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
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"#HelloWorld\"\r\n"));
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
ATL_NOINLINE inline const _soapmap ** CbasicauthServiceT<TClient>::GetFunctionMap()
{
	return __CbasicauthService_funcs;
}

template <typename TClient>
ATL_NOINLINE inline const _soapmap ** CbasicauthServiceT<TClient>::GetHeaderMap()
{
	static const _soapmapentry __CbasicauthService_HelloWorld_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CbasicauthService_HelloWorld_atlsoapheader_map = 
	{
		0x46BA99FC,
		"HelloWorld",
		L"HelloWorld",
		sizeof("HelloWorld")-1,
		sizeof("HelloWorld")-1,
		SOAPMAP_HEADER,
		__CbasicauthService_HelloWorld_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_RPC | SOAPFLAG_ENCODED,
		0x53876B54,
		"urn:basicauthService",
		L"urn:basicauthService",
		sizeof("urn:basicauthService")-1
	};


	static const _soapmap * __CbasicauthService_headers[] =
	{
		&__CbasicauthService_HelloWorld_atlsoapheader_map,
		NULL
	};
	
	return __CbasicauthService_headers;
}

template <typename TClient>
ATL_NOINLINE inline void * CbasicauthServiceT<TClient>::GetHeaderValue()
{
	return this;
}

template <typename TClient>
ATL_NOINLINE inline const wchar_t * CbasicauthServiceT<TClient>::GetNamespaceUri()
{
	return L"urn:basicauthService";
}

template <typename TClient>
ATL_NOINLINE inline const char * CbasicauthServiceT<TClient>::GetServiceName()
{
	return NULL;
}

template <typename TClient>
ATL_NOINLINE inline const char * CbasicauthServiceT<TClient>::GetNamespaceUriA()
{
	return "urn:basicauthService";
}

template <typename TClient>
ATL_NOINLINE inline HRESULT CbasicauthServiceT<TClient>::CallFunction(
	void *, 
	const wchar_t *, int,
	size_t)
{
	return E_NOTIMPL;
}

template <typename TClient>
ATL_NOINLINE inline HRESULT CbasicauthServiceT<TClient>::GetClientReader(ISAXXMLReader **ppReader)
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

} // namespace basicauthService
