#pragma once

__interface ATL_NO_VTABLE __declspec(uuid("b3902ede-b647-4616-8ca4-1dcb98a015b0"))
ISimpleCounter : public IUnknown
{
	STDMETHOD (Set) ();
	STDMETHOD (Get) (long*);
};

class CSimpleCounter : public ISimpleCounter, public CComObjectRootEx<CComGlobalsThreadModel>
{
	BEGIN_COM_MAP(CSimpleCounter)
		COM_INTERFACE_ENTRY(ISimpleCounter)
	END_COM_MAP()

protected:
		long m_Counter;
	
public:
	void Init(void)
	{
		m_Counter = 0;
	}

	STDMETHOD (Set)(void)
	{
		InterlockedIncrement(&m_Counter);
		return S_OK;
	}

	STDMETHOD (Get)(long *input)
	{
		*input = m_Counter;
		return S_OK;
	}
};