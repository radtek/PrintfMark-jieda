//#include "stdafx.h"
//#include <qtwidgets>
//#include "simplepane.h"
#include <Qtcore>

typedef struct _ImportData 
{
	QPointF m[2];		// marks
	QList<QPointF> p;	// points
	QList<QPointF> b;	// badmark
	QString n;			// product
} ImportData;

int readExcelData(const char* xlsFileName, ImportData& data);

#ifndef _STDAFX_H

#pragma region Import the type libraries

#import "libid:2DF8D04C-5BFA-101B-BDE5-00AA0044DE52" \
	rename("RGB", "MSORGB") \
	rename("DocumentProperties", "MSODocumentProperties")
// [-or-]
//#import "C:\\Program Files (x86)\\Common Files\\Microsoft Shared\\OFFICE15\\MSO.DLL"\
//    rename("RGB", "MSORGB") \
//    rename("DocumentProperties", "MSODocumentProperties")

using namespace Office;

#import "libid:0002E157-0000-0000-C000-000000000046"
// [-or-]
//#import "C:\\Program Files (x86)\\Common Files\\Microsoft Shared\\VBA\\VBA6\\VBE6EXT.OLB"\

//using namespace VBIDE;

#import "libid:00020813-0000-0000-C000-000000000046" \
	rename("DialogBox", "ExcelDialogBox") \
	rename("RGB", "ExcelRGB") \
	rename("CopyFile", "ExcelCopyFile") \
	rename("ReplaceText", "ExcelReplaceText") \
	no_auto_exclude
// [-or-]
//#import "C:\\Program Files (x86)\\Microsoft Office\\Office12\\EXCEL.EXE"\
//    rename("DialogBox", "ExcelDialogBox") \
//    rename("RGB", "ExcelRGB") \
//    rename("CopyFile", "ExcelCopyFile") \
//    rename("ReplaceText", "ExcelReplaceText") \
//    no_auto_exclude

#pragma endregion

//
//   FUNCTION: SafeArrayPutName(SAFEARRAY*, long, PCWSTR, PCWSTR);
//
//   PURPOSE: This is a helper function in the sample. It puts a user name 
//      (first name, last name) into a 2D safe array. The array is in this 
//      form:
//
//      John   Smith
//      Tom    Brown
//      Sue    Thomas
// 
//      Value in the first column is specified by pszFirstName. Value in the 
//      second column is specified by pszLastName. SafeArrayPutName is used 
//      add one entry (pszFirstName pszLastName) to the array on the row 
//      indicated by the index parameter.
//
//   PARAMETERS:
//      * psa - Pointer to an array descriptor created by SafeArrayCreate.
//      * index - The index of the name (first name, last name) in the array. 
//      i.e. the first dimension of the 2D array. 
//      * pszFirstName - The first name.
//      * pszLastName - The last name.
//
//   RETURN VALUE: An HRESULT value indicating whether the function succeeds 
//      or not. 
//
HRESULT SafeArrayPutName(SAFEARRAY* psa, long index, PCWSTR pszFirstName, 
	PCWSTR pszLastName)
{
	HRESULT hr;

	// Set the first name.
	long indices1[] = { index, 1 };
	VARIANT vtFirstName;
	vtFirstName.vt = VT_BSTR;
	vtFirstName.bstrVal = SysAllocString(pszFirstName);
	// Copies the VARIANT into the SafeArray
	hr = SafeArrayPutElement(psa, indices1, (void*)&vtFirstName);
	VariantClear(&vtFirstName);

	if (SUCCEEDED(hr))
	{
		// Next, set the last name.
		long indices2[] = { index, 2 };
		VARIANT vtLastName;
		vtLastName.vt = VT_BSTR;
		vtLastName.bstrVal = SysAllocString(pszLastName);
		hr = SafeArrayPutElement(psa, indices2, (void*)&vtLastName);
		VariantClear(&vtLastName);
	}

	return hr;
}

int readExcelData(const char* xlsFileName, ImportData& data)
{
	// Initializes the COM library on the current thread and identifies the
	// concurrency model as single-thread apartment (STA). 
	// [-or-] CoInitialize(NULL);
	// [-or-] CoCreateInstance(NULL);
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	Excel::_ApplicationPtr spXlApp;

	try
	{
		// Create the Excel.Application COM object using the #import 
		// directive and smart pointers.

		// Option 1) Create the object using the smart pointer's constructor
		// _ApplicationPtr is the original interface name, _Application, with 
		// a "Ptr" suffix.
		//Excel::_ApplicationPtr spXlApp(
		//    __uuidof(Excel::Application)    // CLSID of the component
		//    );

		// [-or-]

		// Option 2) Create the object using the smart pointer's function,
		// CreateInstance
		HRESULT hr = spXlApp.CreateInstance(__uuidof(Excel::Application));
		if (FAILED(hr))
		{
			//QMessageBox::warning(qApp->activeWindow(), QString::fromUtf16(L"详细报告"), QString::fromUtf16(L"CreateInstance failed w/err 0x%1\n").arg(hr, 8, 16, QChar('0')));
			CoUninitialize();
			return 1000;
		}

		//_putws(L"Excel.Application is started");

		// Make Excel invisible. (i.e. Application.Visible = 0)
		spXlApp->Visible[0] = VARIANT_FALSE;

		// Create a new Workbook. (i.e. Application.Workbooks.Add)
		Excel::WorkbooksPtr spXlBooks = spXlApp->Workbooks;
		Excel::_WorkbookPtr spXlBook = spXlBooks->Open(QString::fromLocal8Bit(xlsFileName).utf16(), false, true);

		//_putws(L"A new workbook is created");
		//_putws(L"CPK.xls openned");

		// Get the active Worksheet and set its name.
		//Excel::_WorksheetPtr spXlSheet = spXlBook->ActiveSheet;
		//spXlSheet->Name = _bstr_t(L"Report");
		Excel::SheetsPtr spXlSheets = spXlBook->Sheets;
		//_putws(L"The 'data' worksheet is selected");
		Excel::_WorksheetPtr spXlSheet = spXlSheets->GetItem(1);

		int rows = spXlSheet->UsedRange->Rows->Count;
		char szRange[10] = "";
		Excel::RangePtr spXlRange = spXlSheet->UsedRange;
		data.p.clear();
		for(int i=1; i<=rows; i++)
		{
			QString szText;
			QPointF point1, point2;
			sprintf_s(szRange, "A%d", i);
			_variant_t val = spXlSheet->GetRange(szRange)->GetValue2();
			if (val.vt == VT_BSTR)
				szText = QString::fromUtf16(val.bstrVal);
			if (val.vt == VT_R8)
				szText = QString("%1").arg(val.dblVal, 0, 'g');

			sprintf_s(szRange, "B%d", i);
			val = spXlSheet->GetRange(szRange)->GetValue2();
			if (val.vt == VT_R8)
				point1.rx() = val;

			sprintf_s(szRange, "C%d", i);
			val = spXlSheet->GetRange(szRange)->GetValue2();
			if (val.vt == VT_R8)
				point1.ry() = val;

			sprintf_s(szRange, "D%d", i);
			val = spXlSheet->GetRange(szRange)->GetValue2();
			if (val.vt == VT_R8)
				point2.rx() = val;

			sprintf_s(szRange, "E%d", i);
			val = spXlSheet->GetRange(szRange)->GetValue2();
			if (val.vt == VT_R8)
				point2.ry() = val;

			if (szText == "ID1")
			{
				data.m[0] = point1;
			}

			if (szText == "ID2")
			{
				data.m[1] = point1;
			}

			if (szText.startsWith("JP"))
			{
				data.p.append(point1);
				data.b.append(point2);
			}

			if (szText == QString::fromUtf16(L"机种"))
			{
				sprintf_s(szRange, "B%d", i);
				val = spXlSheet->GetRange(szRange)->GetValue2();
				if (val.vt == VT_BSTR)
					data.n = QString::fromUtf16(val.bstrVal);
			}

			//sprintf_s(szRange, "D%d", i);
			//val = spXlSheet->GetRange(szRange)->GetValue2();
			//if (val.vt != VT_NULL)
			//	tvData.z = val;
			////tvData.x = spXlRange->Cells[i,2].Value;
			////tvData.y = spXlRange->Cells[i,3].Value;
			////tvData.z = spXlRange->Cells[i,4].Value;

			//data.append(tvData);
			//row++;
			//////////////////////////////////////////////////////////////////////////
			//VARIANT saValues;
			//saValues.vt = VT_ARRAY | VT_VARIANT;
			//{
			//	SAFEARRAYBOUND sab[2];
			//	sab[0].lLbound = 1; sab[0].cElements = 1;
			//	sab[1].lLbound = 1; sab[1].cElements = 4;
			//	saValues.parray = SafeArrayCreate(VT_VARIANT, 2, sab);

			//	for (int i=0; i<rows; i++)
			//	{
			//		for (int j=0; j<10; j++)
			//		{
			//			HRESULT hr;

			//			// Set the first name.
			//			int index = i*10+j;
			//			long indices1[] = { i+1, j+1 };
			//			VARIANT vtValue;
			//			if (index < data.size())
			//			{
			//				vtValue.vt = VT_R8;
			//				vtValue.dblVal = data[i*10+j];
			//			}
			//			else
			//			{
			//				vtValue.vt = VT_NULL;
			//			}
			//			// Copies the VARIANT into the SafeArray
			//			hr = SafeArrayPutElement(saValues.parray, indices1, (void*)&vtValue);
			//			VariantClear(&vtValue);
			//		}
			//	}
			//	//SafeArrayPutName(saNames.parray, 1, L"John", L"Smith");
			//	//SafeArrayPutName(saNames.parray, 2, L"Tom", L"Brown");
			//	//SafeArrayPutName(saNames.parray, 3, L"Sue", L"Thomas");
			//	//SafeArrayPutName(saNames.parray, 4, L"Jane", L"Jones");
			//	//SafeArrayPutName(saNames.parray, 5, L"Adam", L"Johnson");
			//}

			//// Fill A2:B6 with the array of values (First and Last Names).

			//// Get Range object for the Range A2:B6
			//wchar_t szRange[16] = L"A1:J";
			//swprintf_s(szRange, L"A1:J%d", rows);

			//VARIANT param;
			//param.vt = VT_BSTR;
			//param.bstrVal = SysAllocString(szRange);
			//Excel::RangePtr spXlRange = spXlSheet->Range[param];

			//spXlRange->Value2 = saValues;

			//// Clear the safearray
			//VariantClear(&saValues);
		}

		// Save the workbook as a xlsx file and close it.
		//_putws(L"Save and close the workbook");
		//spXlBook->Save();

		spXlBook->Close();

		// Quit the Excel application. (i.e. Application.Quit)
		//_putws(L"Quit the Excel application");
		spXlApp->Quit();

		// Release the COM objects.
		// Releasing the references is not necessary for the smart pointers
		// ...
		// spXlApp.Release();
		// ...
	}
	catch (_com_error &err)
	{
		//QMessageBox::critical(qApp->activeWindow(), QString::fromUtf16(L"详细报告"), 
		//	QString::fromUtf16(L"Excel throws the error: %1\nDescription: %2\n").arg(QString::fromUtf16(err.ErrorMessage())).arg(QString::fromUtf16((LPCWSTR) err.Description())));
		spXlApp->Quit();
		CoUninitialize();
		return err.WCode();
	}

	// Uninitialize COM for this thread.
	CoUninitialize();
	return 0;
}

//bool fillExcelData(const char* xlsFileName, const QList<double>& data)
//{
//	// Initializes the COM library on the current thread and identifies the
//	// concurrency model as single-thread apartment (STA). 
//	// [-or-] CoInitialize(NULL);
//	// [-or-] CoCreateInstance(NULL);
//	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
//	Excel::_ApplicationPtr spXlApp;
//
//	try
//	{
//		// Create the Excel.Application COM object using the #import 
//		// directive and smart pointers.
//
//		// Option 1) Create the object using the smart pointer's constructor
//		// _ApplicationPtr is the original interface name, _Application, with 
//		// a "Ptr" suffix.
//		//Excel::_ApplicationPtr spXlApp(
//		//    __uuidof(Excel::Application)    // CLSID of the component
//		//    );
//
//		// [-or-]
//
//		// Option 2) Create the object using the smart pointer's function,
//		// CreateInstance
//		HRESULT hr = spXlApp.CreateInstance(__uuidof(Excel::Application));
//		if (FAILED(hr))
//		{
//			QMessageBox::warning(qApp->activeWindow(), QString::fromUtf16(L"详细报告"), QString::fromUtf16(L"CreateInstance failed w/err 0x%1\n").arg(hr, 8, 16, QChar('0')));
//			CoUninitialize();
//			return false;
//		}
//
//		//_putws(L"Excel.Application is started");
//
//		// Make Excel invisible. (i.e. Application.Visible = 0)
//		spXlApp->Visible[0] = VARIANT_FALSE;
//
//		// Create a new Workbook. (i.e. Application.Workbooks.Add)
//		Excel::WorkbooksPtr spXlBooks = spXlApp->Workbooks;
//		Excel::_WorkbookPtr spXlBook = spXlBooks->Open(QString::fromLocal8Bit(xlsFileName).utf16());
//
//		//_putws(L"A new workbook is created");
//		//_putws(L"CPK.xls openned");
//
//		// Get the active Worksheet and set its name.
//		//Excel::_WorksheetPtr spXlSheet = spXlBook->ActiveSheet;
//		//spXlSheet->Name = _bstr_t(L"Report");
//		Excel::SheetsPtr spXlSheets = spXlBook->Sheets;
//		//_putws(L"The 'data' worksheet is selected");
//		Excel::_WorksheetPtr spXlSheet = spXlSheets->GetItem(L"Data");
//
//		// Fill data into the worksheet's cells.
//		//_putws(L"Filling data into the worksheet ...");
//
//		// Construct a 5 x 2 safearray of user names
//		int rows = ceil(data.size()/10.0);
//		if(rows > 0)
//		{
//			VARIANT saValues;
//			saValues.vt = VT_ARRAY | VT_VARIANT;
//			{
//				SAFEARRAYBOUND sab[2];
//				sab[0].lLbound = 1; sab[0].cElements = rows;
//				sab[1].lLbound = 1; sab[1].cElements = 10;
//				saValues.parray = SafeArrayCreate(VT_VARIANT, 2, sab);
//
//				for (int i=0; i<rows; i++)
//				{
//					for (int j=0; j<10; j++)
//					{
//						HRESULT hr;
//
//						// Set the first name.
//						int index = i*10+j;
//						long indices1[] = { i+1, j+1 };
//						VARIANT vtValue;
//						if (index < data.size())
//						{
//							vtValue.vt = VT_R8;
//							vtValue.dblVal = data[i*10+j];
//						}
//						else
//						{
//							vtValue.vt = VT_NULL;
//						}
//						// Copies the VARIANT into the SafeArray
//						hr = SafeArrayPutElement(saValues.parray, indices1, (void*)&vtValue);
//						VariantClear(&vtValue);
//					}
//				}
//				//SafeArrayPutName(saNames.parray, 1, L"John", L"Smith");
//				//SafeArrayPutName(saNames.parray, 2, L"Tom", L"Brown");
//				//SafeArrayPutName(saNames.parray, 3, L"Sue", L"Thomas");
//				//SafeArrayPutName(saNames.parray, 4, L"Jane", L"Jones");
//				//SafeArrayPutName(saNames.parray, 5, L"Adam", L"Johnson");
//			}
//
//			// Fill A2:B6 with the array of values (First and Last Names).
//
//			// Get Range object for the Range A2:B6
//			wchar_t szRange[16] = L"A1:J";
//			swprintf_s(szRange, L"A1:J%d", rows);
//
//			VARIANT param;
//			param.vt = VT_BSTR;
//			param.bstrVal = SysAllocString(szRange);
//			Excel::RangePtr spXlRange = spXlSheet->Range[param];
//
//			spXlRange->Value2 = saValues;
//
//			// Clear the safearray
//			VariantClear(&saValues);
//		}
//
//		// Save the workbook as a xlsx file and close it.
//		//_putws(L"Save and close the workbook");
//		spXlBook->Save();
//
//		spXlBook->Close();
//
//		// Quit the Excel application. (i.e. Application.Quit)
//		//_putws(L"Quit the Excel application");
//		spXlApp->Quit();
//
//		// Release the COM objects.
//		// Releasing the references is not necessary for the smart pointers
//		// ...
//		// spXlApp.Release();
//		// ...
//	}
//	catch (_com_error &err)
//	{
//		QMessageBox::critical(qApp->activeWindow(), QString::fromUtf16(L"详细报告"), 
//			QString::fromUtf16(L"Excel throws the error: %1\nDescription: %2\n").arg(QString::fromUtf16(err.ErrorMessage())).arg(QString::fromUtf16((LPCWSTR) err.Description())));
//		spXlApp->Quit();
//		CoUninitialize();
//		return false;
//	}
//
//	// Uninitialize COM for this thread.
//	CoUninitialize();
//	return true;
//}

#endif
