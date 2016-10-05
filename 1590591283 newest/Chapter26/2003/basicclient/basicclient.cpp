#include "localhost.h"
#include <atlbase.h>
//#define SECURE

class BasicAuth : public IAuthInfo
{
	HRESULT GetUsername(LPTSTR lpBuffer, DWORD *pdwBuffSize)
	{
		if (*pdwBuffSize < 10)
		{
			*pdwBuffSize = 10;
			return E_OUTOFMEMORY;
		}
		_tcscpy(lpBuffer,"pranishk\0");
		*pdwBuffSize = strlen(lpBuffer);
		return S_OK;
	}

	HRESULT GetPassword(LPTSTR szPwd, DWORD *pdwBuffSize)
	{
		if (*pdwBuffSize < 10)
		{
			*pdwBuffSize = 10;
			return E_OUTOFMEMORY;
		}
		_tcscpy(szPwd,"pranishk\0");
		*pdwBuffSize = strlen(szPwd);
		return S_OK;
	}

	HRESULT GetDomain(LPTSTR lpBuffer, DWORD *pdwBuffSize)
	{
		if (*pdwBuffSize < 10)
		{
			*pdwBuffSize = 10;
			return E_OUTOFMEMORY;
		}
		_tcscpy(lpBuffer,"REDMOND\0");
		*pdwBuffSize = strlen(lpBuffer);
		return S_OK;
	}
};

int main(void)
{
	CoInitialize(NULL);
	basicauthService::CbasicauthService svc;
#ifdef SECURE
	BasicAuth ba;
	CBasicAuthObject auth(&ba);
	svc.m_socket.AddAuthObj("BASIC", &auth);
#endif
	CComBSTR bstrIn, bstrOut;
	bstrIn = "World!";
	svc.HelloWorld(bstrIn, &bstrOut);
	printf("%S", bstrOut);
	return 0;
}