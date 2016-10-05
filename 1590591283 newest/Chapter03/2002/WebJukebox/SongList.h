// SongList.h : Declaration of the CSongList

#pragma once

// code generated on Tuesday, January 29, 2002, 10:30 PM

[
	
db_source(L"Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=WebJukebox.mdb;Mode=Share Deny None;Extended Properties=\"\";Jet OLEDB:System database=\"\";Jet OLEDB:Registry Path=\"\";Jet OLEDB:Database Password=\"\";Jet OLEDB:Engine Type=5;Jet OLEDB:Database Locking Mode=1;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password=\"\";Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False"),
	db_command(L" \
	SELECT \
		Description, \
		ID, \
		Location, \
		Musician, \
		Name \
		FROM `Song List`")
]
class CSongList
{
public:
// This table/command contains column(s) that can be accessed
// via an ISequentialStream interface.  Not all providers, however,
// support this feature, and even those that do support it, are
// often limited to just one ISequentialStream per rowset.
// If you want to use streams in this accessor, use the sample
// line(s) of code below, and set the DBPROP_ISequentialStream
// rowset propery to true.  You can than use the Read() method
// to read the data.  For more information on
// ISequentialStream binding see the documentation

	// In order to fix several issues with some providers, the code below may bind
	// columns in a different order than reported by the provider

	// [ db_column(1, status=m_dwDescriptionStatus, length=m_dwDescriptionLength) ] ISequentialStream* m_Description;	// Description of the Song
	[ db_column(1, status=m_dwDescriptionStatus, length=m_dwDescriptionLength) ] TCHAR m_Description[8000];	// Description of the Song
	[ db_column(2, status=m_dwIDStatus, length=m_dwIDLength) ] LONG m_ID;
	[ db_column(3, status=m_dwLocationStatus, length=m_dwLocationLength) ] TCHAR m_Location[51];	// Location of the Song Relative to the Root Directory
	[ db_column(4, status=m_dwMusicianStatus, length=m_dwMusicianLength) ] TCHAR m_Musician[201];	// Name of the Musician
	[ db_column(5, status=m_dwNameStatus, length=m_dwNameLength) ] TCHAR m_Name[51];	// Name of the Song

	// The following wizard-generated data members contain status
	// values for the corresponding fields. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Data Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!

	DBSTATUS m_dwDescriptionStatus;
	DBSTATUS m_dwIDStatus;
	DBSTATUS m_dwLocationStatus;
	DBSTATUS m_dwMusicianStatus;
	DBSTATUS m_dwNameStatus;

	// The following wizard-generated data members contain length
	// values for the corresponding fields.
	// NOTE: For variable-length columns, you must initialize these
	//       fields before setting/inserting data!

	DBLENGTH m_dwDescriptionLength;
	DBLENGTH m_dwIDLength;
	DBLENGTH m_dwLocationLength;
	DBLENGTH m_dwMusicianLength;
	DBLENGTH m_dwNameLength;


	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		// pPropSet->AddProperty(DBPROP_ISequentialStream, true);
	}
};


