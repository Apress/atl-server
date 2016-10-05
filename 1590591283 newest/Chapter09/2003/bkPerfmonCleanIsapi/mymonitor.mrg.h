// Created by Microsoft (R) C/C++ Compiler Version 13.00.9466
//
// c:\projects\bkperfmoncleanisapi\mymonitor.mrg.h
// compiler-generated file created 07/26/02 at 00:28:26
//
// This C++ source file is intended to be a representation of the
// source code injected by the compiler.  It may not compile or
// run exactly as the original source file.
//


//+++ Start Injected Code
[no_injected_text(true)];      // Suppress injected text, it has already been injected
#pragma warning(disable: 4543) // Suppress warnings about skipping injected text
#pragma warning(disable: 4199) // Suppress warnings from attribute providers

#pragma message("\n\nNOTE: This merged source file should be visually inspected for correctness.\n\n")
//--- End Injected Code

// MyMonitor.h: interface for the MyMonitor class.
//


#pragma once

// You can then add counters to those objects.  Use the context
// menu of MyMonitor in ClassView to add a PerfMon Object
// to your project.  Then use the context menu of the newly
// created PerfMon Object to add a PerfMon Counter.
[ perf_object(namestring = "My Object", helpstring = "Help for My Object", detail = PERF_DETAIL_NOVICE) ]
class MyObject
 :
    /*+++ Added Baseclass */ public CPerfObject
{
public:

	[ perf_counter(namestring = "My Counter", helpstring = "Help for My Counter", countertype = PERF_COUNTER_RAWCOUNT, defscale = 0, detail = PERF_DETAIL_NOVICE) ]
	LONG MyCounter;

	//+++ Start Injected Code For Attribute 'perf_object'
#injected_line 11 "c:\\projects\\bkperfmoncleanisapi\\mymonitor.h"
    DECLARE_PERF_OBJECT_EX(0, "My Object", "Help for My Object", 100, 0, sizeof(MyObject), ATLPERF_DEFAULT_MAXINSTNAMELENGTH, -1);
#injected_line 11 "c:\\projects\\bkperfmoncleanisapi\\mymonitor.h"
    BEGIN_COUNTER_MAP(MyObject)
        DEFINE_COUNTER_EX(MyCounter, 1, "My Counter", "Help for My Counter", 100, 65536, 0, 0)
    END_COUNTER_MAP()

	//--- End Injected Code For Attribute 'perf_object'
};

[ perfmon(name="Perf_MyMonitor", register=true) ]
class MyMonitor
 :
    /*+++ Added Baseclass */ public CPerfMon
{
	CComPtr<IDispatch> m_spPerfCache;
public:
	void InitPerf(IDispatch* pPerfCache)
	{
		m_spPerfCache = pPerfCache;
		m_spPerfCache.Invoke1(L"CachePerfCounter", &CComVariant(CComBSTR(GetAppName())));
	}

	//+++ Start Injected Code For Attribute 'perfmon'
#injected_line 20 "c:\\projects\\bkperfmoncleanisapi\\mymonitor.h"
    BEGIN_PERF_MAP("Perf_MyMonitor")
        CHAIN_PERF_OBJECT(MyObject);
    END_PERF_MAP()

	//--- End Injected Code For Attribute 'perfmon'
};

//+++ Start Injected Code For Attribute 'perfmon'
#injected_line 20 "c:\\projects\\bkperfmoncleanisapi\\mymonitor.h"

					PERFREG_ENTRY(MyMonitor)

				
//--- End Injected Code For Attribute 'perfmon'

