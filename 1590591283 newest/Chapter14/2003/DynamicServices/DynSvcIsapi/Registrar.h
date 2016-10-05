#ifndef REGISTRAR_H_INCLUDED
#define REGISTRAR_H_INCLUDED

#include "..\Include\CommonInterfaces.h"
#include <atlcoll.h>
#pragma once



template<class TLock>
class CAutoLock
{
protected:
	TLock&		m_lock;
public:
	CAutoLock(TLock& lock) : m_lock(lock)
	{
		CCriticalSection sc;
		m_lock.Enter();
	}
	~CAutoLock()
	{
		m_lock.Leave();
	}
};

class	CRegistrar : public IRegistrarService
{
public:
	ULONG	STDMETHODCALLTYPE  AddRef()
	{
		return 1;
	}

	ULONG	STDMETHODCALLTYPE Release()
	{
		return 1;
	}

	HRESULT	STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject)
	{
		if( !ppvObject )
		{
			return E_POINTER;
		}

		if( IsEqualIID( riid, IID_IUnknown))
		{
			*ppvObject = static_cast<IUnknown*>(this);
		}
		else if( IsEqualIID( riid, __uuidof(IRegistrarService)))
		{
			*ppvObject = static_cast<IRegistrarService*>(this);
		}
		else
		{
			return E_NOINTERFACE;
		}
		AddRef();
		return S_OK;
	}

protected:
	CCriticalSection		m_lock;
	struct stService
	{
		CString	strSvc;
		GUID	guid;
		IID		riid;
	};

	CAtlArray<stService>		m_arSvcs;

	int		FindIndex(LPCTSTR szName)
	{
		if( !szName)
			return -1;

		for( size_t iIndex = 0; iIndex < m_arSvcs.GetCount(); iIndex++)
		{
			if( m_arSvcs[iIndex].strSvc.CompareNoCase( szName) == 0 )
				return (int)iIndex;
		}
		return -1;
	}

public:
	// Public methods
	// Registers a service name
	HRESULT	RegisterServiceName	( REFGUID ServiceID, REFIID refIID, LPCTSTR szServiceName)
	{
		CAutoLock<CCriticalSection>	lock(m_lock);
		if( !szServiceName)
			return E_POINTER;

		if( FindIndex( szServiceName) >= 0 )
			return S_FALSE;

		stService stAdd;
		stAdd.strSvc	=	szServiceName;
		stAdd.guid		=	ServiceID;
		stAdd.riid		=	refIID;

		m_arSvcs.Add( stAdd );

		return S_OK;
	}
	
	// Resolves a service name and returns the GUID of the service and the one of 
	// the service interface
	HRESULT	ResolveServiceName 	( LPCTSTR szServiceName, GUID* pGUID, IID* pRefIID)
	{
		CAutoLock<CCriticalSection> lock(m_lock);
		if( !szServiceName ||
			!pGUID ||
			!pRefIID )
			return E_POINTER;

		int iIndex = FindIndex( szServiceName );

		if( iIndex < 0 )
			return S_FALSE;

		*pGUID		=	m_arSvcs[iIndex].guid;
		*pRefIID	=	m_arSvcs[iIndex].riid;

		return S_OK;
	}
	
	// Removes a service
	HRESULT	RemoveService		( LPCTSTR szServiceName)
	{
		if( !szServiceName )
			return E_POINTER;
		CAutoLock<CCriticalSection> lock(m_lock);

		int iIndex = FindIndex( szServiceName );

		if( iIndex < 0 )
			return E_FAIL;

		m_arSvcs.RemoveAt( iIndex );

		return S_OK;
	}
	
	// Methods to iterate through the list of services
	HRESULT GetServiceCount		( DWORD* pdwCount)
	{
		if( !pdwCount )
		{
			return E_POINTER;
		}
		*pdwCount	=	(DWORD)m_arSvcs.GetCount();

		return S_OK;
	}
	HRESULT GetServiceName		( DWORD nIndex, LPCTSTR* pszServiceName)
	{
		CAutoLock<CCriticalSection> lock(m_lock);
		
		if( !pszServiceName )
			return E_POINTER;

		if( nIndex >= m_arSvcs.GetCount() )
			return S_FALSE;

		*pszServiceName	=	(LPCTSTR)m_arSvcs[nIndex].strSvc.GetBuffer();

		return S_OK;
	}

};
#endif //REGISTRAR_H_INCLUDED