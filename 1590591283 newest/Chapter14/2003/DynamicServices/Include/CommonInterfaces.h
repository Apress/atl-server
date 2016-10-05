
#ifndef COMMONINTERFACES_INCLUDED_H
#define COMMONINTERFACES_INCLUDED_H


#pragma once

// IRegistrarService
// This global ISAPI service is actually just a helper. It maps a name (string) to a 
// pair of GUIDs describing a dynamic service (the service GUID and the 
// interface GUID) allowing the user to actually specify by name 

__interface __declspec(uuid("1C57ABA0-B8E8-4106-9B66-351E59B4B7F8"))
	IRegistrarService : public IUnknown
{
	
	// Registers a service name
	HRESULT	RegisterServiceName	( REFGUID szServiceID, REFIID refIID, LPCTSTR szServiceName);
	
	// Resolves a service name and returns the GUID of the service and the one of 
	// the service interface
	HRESULT	ResolveServiceName 	( LPCTSTR szServiceName, GUID* pGUID, IID* pRefIID);
	
	// Removes a service
	HRESULT	RemoveService		( LPCTSTR szServiceName);
	
	// Methods to iterate through the list of services
	HRESULT GetServiceCount		( DWORD* pdwCount);
	HRESULT GetServiceName		( DWORD nIndex, LPCTSTR* pszServiceName);
};



// IBinaryOperation
// Interface to be implemented by multiple dynamic services
__interface __declspec(uuid("9704DC52-67DF-4536-981A-0C3784ED6E29"))
	IBinaryOperation : public IUnknown
{
	
	// This is the generic interface of a binary arithmetic operation
	HRESULT Perform(double	inA, double inB, double* pOutRet);
};



// Pure virtual class for implementing Binary Ops
class CBinaryOperationHelper : public IBinaryOperation
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
		else if( IsEqualIID( riid, __uuidof(IBinaryOperation)))
		{
			*ppvObject = static_cast<IBinaryOperation*>(this);
		}
		else
		{
			return E_NOINTERFACE;
		}
		AddRef();
		return S_OK;
	}
};

#endif // COMMONINTERFACES_INCLUDED_H