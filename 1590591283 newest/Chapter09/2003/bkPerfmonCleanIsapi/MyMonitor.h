// MyMonitor.h: interface for the MyMonitor class.
//


#pragma once

// You can then add counters to those objects.  Use the context
// menu of MyMonitor in ClassView to add a PerfMon Object
// to your project.  Then use the context menu of the newly
// created PerfMon Object to add a PerfMon Counter.
[ perf_object(namestring = "My Object", helpstring = "Help for My Object", detail = PERF_DETAIL_NOVICE) ]
class MyObject
{
public:

	[ perf_counter(namestring = "My Counter", helpstring = "Help for My Counter", countertype = PERF_COUNTER_RAWCOUNT, defscale = 0, detail = PERF_DETAIL_NOVICE) ]
	LONG MyCounter;
};

[ perfmon(name="Perf_MyMonitor", register=true) ]
class MyMonitor
{
	CComPtr<IDispatch> m_spPerfCache;
public:
	void InitPerf(IDispatch* pPerfCache)
	{
		m_spPerfCache = pPerfCache;
		m_spPerfCache.Invoke1(L"CachePerfCounter", &CComVariant(CComBSTR(GetAppName())));
	}
};
