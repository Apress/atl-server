// Products.h : Declaration of the CProducts

#pragma once

// code generated on Saturday, February 15, 2003, 4:23 PM

[	db_command(L" \
	SELECT \
		ProductID, \
		ProductName, \
		SupplierID, \
		CategoryID, \
		QuantityPerUnit, \
		UnitPrice, \
		UnitsInStock, \
		UnitsOnOrder, \
		ReorderLevel, \
		Discontinued \
		FROM dbo.Products")
]
class CProducts
{
public:
	[ db_column(1, status=m_dwProductIDStatus, length=m_dwProductIDLength) ] LONG m_ProductID;
	[ db_column(2, status=m_dwProductNameStatus, length=m_dwProductNameLength) ] TCHAR m_ProductName[41];
	[ db_column(3, status=m_dwSupplierIDStatus, length=m_dwSupplierIDLength) ] LONG m_SupplierID;
	[ db_column(4, status=m_dwCategoryIDStatus, length=m_dwCategoryIDLength) ] LONG m_CategoryID;
	[ db_column(5, status=m_dwQuantityPerUnitStatus, length=m_dwQuantityPerUnitLength) ] TCHAR m_QuantityPerUnit[21];
	[ db_column(6, status=m_dwUnitPriceStatus, length=m_dwUnitPriceLength) ] CURRENCY m_UnitPrice;
	[ db_column(7, status=m_dwUnitsInStockStatus, length=m_dwUnitsInStockLength) ] SHORT m_UnitsInStock;
	[ db_column(8, status=m_dwUnitsOnOrderStatus, length=m_dwUnitsOnOrderLength) ] SHORT m_UnitsOnOrder;
	[ db_column(9, status=m_dwReorderLevelStatus, length=m_dwReorderLevelLength) ] SHORT m_ReorderLevel;
	[ db_column(10, status=m_dwDiscontinuedStatus, length=m_dwDiscontinuedLength) ] VARIANT_BOOL m_Discontinued;

	// The following wizard-generated data members contain status
	// values for the corresponding fields. You
	// can use these values to hold NULL values that the database
	// returns or to hold error information when the compiler returns
	// errors. See Field Status Data Members in Wizard-Generated
	// Accessors in the Visual C++ documentation for more information
	// on using these fields.
	// NOTE: You must initialize these fields before setting/inserting data!

	DBSTATUS m_dwProductIDStatus;
	DBSTATUS m_dwProductNameStatus;
	DBSTATUS m_dwSupplierIDStatus;
	DBSTATUS m_dwCategoryIDStatus;
	DBSTATUS m_dwQuantityPerUnitStatus;
	DBSTATUS m_dwUnitPriceStatus;
	DBSTATUS m_dwUnitsInStockStatus;
	DBSTATUS m_dwUnitsOnOrderStatus;
	DBSTATUS m_dwReorderLevelStatus;
	DBSTATUS m_dwDiscontinuedStatus;

	// The following wizard-generated data members contain length
	// values for the corresponding fields.
	// NOTE: For variable-length columns, you must initialize these
	//       fields before setting/inserting data!

	DBLENGTH m_dwProductIDLength;
	DBLENGTH m_dwProductNameLength;
	DBLENGTH m_dwSupplierIDLength;
	DBLENGTH m_dwCategoryIDLength;
	DBLENGTH m_dwQuantityPerUnitLength;
	DBLENGTH m_dwUnitPriceLength;
	DBLENGTH m_dwUnitsInStockLength;
	DBLENGTH m_dwUnitsOnOrderLength;
	DBLENGTH m_dwReorderLevelLength;
	DBLENGTH m_dwDiscontinuedLength;


	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
	}
};


