[
  db_source(L"Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=WebJukebox.mdb;Mode=Share Deny None;Extended Properties=\"\";Jet OLEDB:System database=\"\";Jet OLEDB:Registry Path=\"\";Jet OLEDB:Database Password=\"\";Jet OLEDB:Engine Type=5;Jet OLEDB:Database Locking Mode=1;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password=\"\";Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False"),
	db_command(L" \
	SELECT \
		Description, \
		ID, \
		Location, \
		Musician, \
		Name \
		FROM `Song List` ORDER BY Description")
]
class CDescriptionList
{
public:
  [ db_column(1) ] TCHAR m_Description[8000];
	[ db_column(2) ] LONG m_ID;
  [ db_column(3) ] TCHAR m_Location[51];	
	[ db_column(4) ] TCHAR m_Musician[201];	
	[ db_column(5) ] TCHAR m_Name[51];	
};

[
  db_source(L"Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=WebJukebox.mdb;Mode=Share Deny None;Extended Properties=\"\";Jet OLEDB:System database=\"\";Jet OLEDB:Registry Path=\"\";Jet OLEDB:Database Password=\"\";Jet OLEDB:Engine Type=5;Jet OLEDB:Database Locking Mode=1;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password=\"\";Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False"),
	db_command(L" \
	SELECT \
		Description, \
		ID, \
		Location, \
		Musician, \
		Name \
		FROM `Song List` ORDER BY Name")
]
class CNameList
{
public:
  [ db_column(1) ] TCHAR m_Description[8000];
	[ db_column(2) ] LONG m_ID;
  [ db_column(3) ] TCHAR m_Location[51];	
	[ db_column(4) ] TCHAR m_Musician[201];	
	[ db_column(5) ] TCHAR m_Name[51];	
};

[
  db_source(L"Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=WebJukebox.mdb;Mode=Share Deny None;Extended Properties=\"\";Jet OLEDB:System database=\"\";Jet OLEDB:Registry Path=\"\";Jet OLEDB:Database Password=\"\";Jet OLEDB:Engine Type=5;Jet OLEDB:Database Locking Mode=1;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password=\"\";Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False"),
	db_command(L" \
	SELECT \
		Description, \
		ID, \
		Location, \
		Musician, \
		Name \
		FROM `Song List` ORDER BY Musician")
]
class CMusicianList
{
public:
  [ db_column(1) ] TCHAR m_Description[8000];
	[ db_column(2) ] LONG m_ID;
  [ db_column(3) ] TCHAR m_Location[51];	
	[ db_column(4) ] TCHAR m_Musician[201];	
	[ db_column(5) ] TCHAR m_Name[51];	
};

[
  db_source(L"Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=WebJukebox.mdb;Mode=Share Deny None;Extended Properties=\"\";Jet OLEDB:System database=\"\";Jet OLEDB:Registry Path=\"\";Jet OLEDB:Database Password=\"\";Jet OLEDB:Engine Type=5;Jet OLEDB:Database Locking Mode=1;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password=\"\";Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False"),
	db_command(L" \
	SELECT \
		Description, \
		ID, \
		Location, \
		Musician, \
		Name \
		FROM `Song List` ORDER BY Location")
]
class CLocationList
{
public:
  [ db_column(1) ] TCHAR m_Description[8000];
	[ db_column(2) ] LONG m_ID;
  [ db_column(3) ] TCHAR m_Location[51];	
	[ db_column(4) ] TCHAR m_Musician[201];	
	[ db_column(5) ] TCHAR m_Name[51];	
};



class CSongData
{
public:
  int m_Sortby;
  CLocationList m_locationList;       // 0
  CNameList m_nameList;               // 1
  CMusicianList m_musicianList;       // 2
  CDescriptionList m_descriptionList; // 3
 
  void SetSorting(int sort)
  {
    if ((0<=sort)&&(sort<=3))
      m_Sortby = sort;
    else
      m_Sortby = 0;
  }

  HRESULT OpenAll()
  {
    switch(m_Sortby)
    {
    case(0):
      return m_locationList.OpenAll();
      break;
    case(1):
      return m_nameList.OpenAll();
      break;
    case(2):
      return m_musicianList.OpenAll();
      break;
    case(3):
      return m_descriptionList.OpenAll();
      break;
    }
    return E_FAIL;
  }

  HRESULT MoveNext()
  {
    switch(m_Sortby)
    {
    case(0):
      return m_locationList.MoveNext();
      break;
    case(1):
      return m_nameList.MoveNext();
      break;
    case(2):
      return m_musicianList.MoveNext();
      break;
    case(3):
      return m_descriptionList.MoveNext();
      break;
    }
    return E_FAIL;
  }

  CString GetLocation()
  {
    switch(m_Sortby)
    {
    case(0):
      return m_locationList.m_Location;
      break;
    case(1):
      return m_nameList.m_Location;
      break;
    case(2):
      return m_musicianList.m_Location;
      break;
    case(3):
      return m_descriptionList.m_Location;
      break;
    }
    return NULL;
  }

  CString GetName()
  {
    switch(m_Sortby)
    {
    case(0):
      return m_locationList.m_Name;
      break;
    case(1):
      return m_nameList.m_Name;
      break;
    case(2):
      return m_musicianList.m_Name;
      break;
    case(3):
      return m_descriptionList.m_Name;
      break;
    }
    return NULL;
  }

  CString GetMusician()
  {
    switch(m_Sortby)
    {
    case(0):
      return m_locationList.m_Musician;
      break;
    case(1):
      return m_nameList.m_Musician;
      break;
    case(2):
      return m_musicianList.m_Musician;
      break;
    case(3):
      return m_descriptionList.m_Musician;
      break;
    }
    return NULL;
  }

  CString GetDescription()
  {
    switch(m_Sortby)
    {
    case(0):
      return m_locationList.m_Description;
      break;
    case(1):
      return m_nameList.m_Description;
      break;
    case(2):
      return m_musicianList.m_Description;
      break;
    case(3):
      return m_descriptionList.m_Description;
      break;
    }
    return NULL;
  }

};
