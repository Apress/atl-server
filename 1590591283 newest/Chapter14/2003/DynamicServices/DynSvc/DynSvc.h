// DynSvc.h : Defines the ATL Server request handler class
//
#pragma once
#include <atlcoll.h>
#include "..\Include\CommonInterfaces.h"

[ request_handler("Default") ]
class CDynSvcHandler
{
private:
	// Put private members here

protected:
	// Put protected members here
	CAtlArray<CStringA, CStringElementTraits<CStringA>	>		m_arFiles;
	int								m_nFilePos;
	CComPtr<IRegistrarService>		m_spRegistrar;
	DWORD							m_dwSvcPos;
	DWORD							m_dwSvcCount;

public:
	// Put public members here

	HTTP_CODE ValidateAndExchange()
	{
		// TODO: Put all initialization and validation code here
		
		// Set the content-type
		// m_HttpResponse.SetContentType("text/html");

		LPCSTR	szDLLName = m_HttpRequest.GetFormVars().Lookup("dll");
		
		if( szDLLName )
		{
			return ServerTransferRequest(szDLLName);
		}

		if( !SUCCEEDED(m_spServiceProvider->QueryService(__uuidof(IRegistrarService), &m_spRegistrar)))
		{
			m_HttpResponse << "An error occurred while accessing the Registrar name service from the ISAPI<br>";
			return HTTP_FAIL;
		}
		return HTTP_SUCCESS;
	}
 
protected:

	// Here is an example of how to use a replacement tag with the stencil processor
	[ tag_name(name="GetServiceCount") ]
	HTTP_CODE OnGetServiceCount(void)
	{
		m_dwSvcPos	=	(DWORD)-1;
		if( !SUCCEEDED(m_spRegistrar->GetServiceCount(&m_dwSvcCount)) )
			return HTTP_FAIL;
		return HTTP_SUCCESS;
	}

	[ tag_name(name="GetNextService") ]
	HTTP_CODE OnGetNextService(void)
	{
		if( m_dwSvcPos == (DWORD)-1)
			m_dwSvcPos = 0;
		else
			m_dwSvcPos++;

		if( m_dwSvcPos < m_dwSvcCount )
			return HTTP_SUCCESS;
		return HTTP_S_FALSE;
	}

	[ tag_name(name="ServiceName") ]
	HTTP_CODE OnServiceName(void)
	{
		LPCTSTR	szName = NULL;
		HRESULT hRet = m_spRegistrar->GetServiceName( m_dwSvcPos, &szName);

		if( S_OK == hRet && szName )
		{
			m_HttpResponse << szName;
			return HTTP_SUCCESS;
		}
		return HTTP_FAIL;

	}

	// Here is an example of how to use a replacement tag with the stencil processor
	[ tag_name(name="GetFilesList") ]
	HTTP_CODE OnGetFilesList(void)
	{
		CStringA	strFileName = m_spServerContext->GetPathTranslated();
		int iBSPos = strFileName.ReverseFind('\\');

		m_nFilePos = -1;
		m_arFiles.RemoveAll();
		if( iBSPos < 0 )
		{
			return HTTP_SUCCESS;
		}
		CStringA	strPath	=	strFileName.Left(iBSPos + 1);
		CStringA	strMask	=	strPath + "*.dll";

		WIN32_FIND_DATA	wfd;
		HANDLE hFile = ::FindFirstFile( strMask, &wfd);
	
		if( hFile == INVALID_HANDLE_VALUE)
				return HTTP_SUCCESS;
	
		while(1)
		{
			bool		bAddFile	=	true;
			CStringA	strFile	=	wfd.cFileName;
			// Skip the request handler and the ISAPI DLL
			if( 0 == strFile.CompareNoCase("dynsvc.dll") )
				bAddFile = false;
			if( 0 == strFile.CompareNoCase("dynsvcisapi.dll") )
				bAddFile = false;
	
			if( bAddFile )
				m_arFiles.Add( strFile );

			if( !::FindNextFile(hFile, &wfd) )
				break;
		}

		::FindClose( hFile );

		return HTTP_SUCCESS;
	}

	[ tag_name(name="GetNextFile") ]
	HTTP_CODE OnGetNextFile(void)
	{
		m_nFilePos ++;
		if( m_nFilePos < m_arFiles.GetCount() )
			return HTTP_SUCCESS;
		else
			return HTTP_S_FALSE;
	}

	[ tag_name(name="FileName") ]
	HTTP_CODE OnFileName(void)
	{
		m_HttpResponse << m_arFiles.GetAt(m_nFilePos);
		return HTTP_SUCCESS;
	}
}; // class CDynSvcHandler
