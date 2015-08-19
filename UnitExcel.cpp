//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "UnitMain.h"
#include <stdio.h>
//#include "Excel_2K_SRVR.h"     //necessary
//---------------------------------------------------------------------------
#include <oleserver.hpp>//包含此头文件
//#pragma link "Excel_2K_SRVR"    //necessary

Variant Wb,Sheet,ERange,EBorders;
Variant *AppExcel=NULL;
//---------------------------------------------------------------------------
#define  PG  OlePropertyGet
#define  PS  OlePropertySet
#define  FN  OleFunction
#define  PR  OleProcedure
bool CreateExcelAPP(void)
{ if(!AppExcel)
  { try
    { AppExcel=new Variant;
      *AppExcel = Variant::CreateObject("Excel.Application");
    }
    catch(...)
    { if(AppExcel)
      { delete AppExcel;
        AppExcel=NULL;
      }
      ShowMessage("无法启动Excel,可能是没有安装!");
    }
  }
  return AppExcel;
}
//---------------------------------------------------------------------------
void DestroyExcelApp(void)
{ if(AppExcel)
  { AppExcel->OleFunction("Quit");
    delete AppExcel;
    AppExcel=NULL;
  }
}
//---------------------------------------------------------------------------
#define path_max_size  255
String NewTempXlsFile(void)
{ char namebuf[path_max_size];
  int name_len=GetTempPath(path_max_size,namebuf);
  for(int i=0;i<255;i++)
  { sprintf(namebuf+name_len,"tmp%d.xls",i);
    if(FileExists(namebuf))
    { DeleteFile(namebuf);
    }
    else return namebuf;
  }
  return "temp.xls";
}
//---------------------------------------------------------------------------
void ExcelOpen(char *xlsfile,int sheetcount)
{ if(!FileExists(xlsfile))
  { Application->MessageBox("Excel表文件不存在,无法打开！","错误",MB_ICONSTOP|MB_OK);
    return;
  }
  try
  { if(!CreateExcelAPP())
    { Application->MessageBox("无法启动Excel","错误",MB_ICONSTOP|MB_OK);
      return;
    }

    AppExcel->PG("WorkBooks").PR("Open",xlsfile);
    Wb = AppExcel->PG("ActiveWorkBook");
    Sheet = Wb.PG("ActiveSheet");//获得当前默认的Sheet
    Sheet.PS("Name","sheet0");

    for(int i=1;i<sheetcount;i++)
    { Sheet.PR( "Select");
      Sheet.PR("Copy");
      //这时造成一个新的工作簿
      Variant   vWorkbookDst = AppExcel->PG("ActiveWorkBook");
      Variant   vSheetDst = vWorkbookDst.PG("ActiveSheet");
      vSheetDst.PR( "Select");
      //把新工作簿的表移回最初的工作簿
      vSheetDst.PR( "Move",Sheet);
    }

    for(int i=sheetcount;i>0;i--)
    { char tempbuf[64];
      sprintf(tempbuf,"Sheet%d",i);
      Wb.PG("WorkSheets",i).PR("Activate");//先激活后才能修改
      Wb.PG("ActiveSheet").PS("Name",tempbuf);
    }
    AppExcel->PS("Visible",true);//使Excel可见
  }
  catch(...)
  { DestroyExcelApp();
    Application->MessageBox("操作Excel表格错误！","错误",MB_ICONSTOP|MB_OK);
  }
}

//---------------------------------------------------------------------------
char *xlsHead="\
<html xmlns:x=\"urn:schemas-microsoft-com:office:excel\">\
<head>\
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=gb2312\">\
        <!--[if gte mso 9]><xml>\
            <x:ExcelWorkbook>\
                <x:ExcelWorksheets>\
                    <x:ExcelWorksheet>\
                        <x:Name>工作表标题</x:Name>\
                        <x:WorksheetOptions>\
                            <x:Print>\
                                <x:ValidPrinterInfo />\
                            </x:Print>\
                        </x:WorksheetOptions>\
                    </x:ExcelWorksheet>\
                </x:ExcelWorksheets>\
            </x:ExcelWorkbook>\
        </xml>\
        <![endif]-->\
<style>\
<!--\
@page\
	{margin:0in .75in 0in .75in;\
	mso-header-margin:0in;\
	mso-footer-margin:0in;}\
	TD   {FONT-FAMILY:宋体;FONT-SIZE: 10pt;line-height: 100%;}\
	BODY {FONT-FAMILY:ARIAL;FONT-SIZE:10pt;}\
-->\
</style>\
</head>\
<body>\
";

void ExcelOpen_TestWeight(String xlsfilepath)
{ void QueryToExcel_TestWeight(String  strTitle,String  strPath);
  const int SHEET_COUNT=1;
  try
  { if(!CreateExcelAPP())
    { Application->MessageBox("无法启动Excel","错误",MB_ICONSTOP|MB_OK);
      return;
    }
    AppExcel->PG("WorkBooks").OleProcedure("Add",1);
    Wb = AppExcel->PG("ActiveWorkBook");
    Sheet = Wb.PG("ActiveSheet");//获得当前默认的Sheet
    Sheet.PS("Name","sheet0");
   // xlsfilepath=NewTempXlsFile();

    for(int i=0;i<SHEET_COUNT;i++)
    { QueryToExcel_TestWeight("产品测试",xlsfilepath);
      AppExcel->PG("WorkBooks").PR("Open",xlsfilepath.c_str());
      Variant   vWorkbookDst = AppExcel->PG("ActiveWorkBook");
      Variant   vSheetDst = vWorkbookDst.PG("ActiveSheet");
      vSheetDst.PR( "Select");
      //把新工作簿的表移回最初的工作簿
      vSheetDst.PR( "Move",Sheet);
    }
    for(int i=SHEET_COUNT;i>0;i--)
    { char tempbuf[64];
      sprintf(tempbuf,"Sheet%d",i);
      Wb.PG("WorkSheets",i).PR("Activate");//先激活后才能修改
      Wb.PG("ActiveSheet").PS("Name",tempbuf);
    }
    Wb.PG("WorkSheets",SHEET_COUNT+1).PR("delete");
    AppExcel->PS("Visible",true);//使Excel可见
  }
  catch(...)
  { DestroyExcelApp();
    Application->MessageBox("操作Excel表格错误！","错误",MB_ICONSTOP|MB_OK);
  }
}



void ExcelOpen_CategoryList(String xlsfilepath)
{ void QueryToExcel_CategoryList(String  strTitle,String  strPath);
  const int SHEET_COUNT=1;
  try
  { if(!CreateExcelAPP())
    { Application->MessageBox("无法启动Excel","错误",MB_ICONSTOP|MB_OK);
      return;
    }
    AppExcel->PG("WorkBooks").OleProcedure("Add",1);
    Wb = AppExcel->PG("ActiveWorkBook");
    Sheet = Wb.PG("ActiveSheet");//获得当前默认的Sheet
    Sheet.PS("Name","sheet0");
    //xlsfilepath=NewTempXlsFile();

    for(int i=0;i<SHEET_COUNT;i++)
    { QueryToExcel_CategoryList("产品目录",xlsfilepath);
      AppExcel->PG("WorkBooks").PR("Open",xlsfilepath.c_str());
      Variant   vWorkbookDst = AppExcel->PG("ActiveWorkBook");
      Variant   vSheetDst = vWorkbookDst.PG("ActiveSheet");
      vSheetDst.PR( "Select");
      //把新工作簿的表移回最初的工作簿
      vSheetDst.PR( "Move",Sheet);
    }
    for(int i=SHEET_COUNT;i>0;i--)
    { char tempbuf[64];
      sprintf(tempbuf,"Sheet%d",i);
      Wb.PG("WorkSheets",i).PR("Activate");//先激活后才能修改
      Wb.PG("ActiveSheet").PS("Name",tempbuf);
    }
    Wb.PG("WorkSheets",SHEET_COUNT+1).PR("delete");
    AppExcel->PS("Visible",true);//使Excel可见
  }
  catch(...)
  { DestroyExcelApp();
    Application->MessageBox("操作Excel表格错误！","错误",MB_ICONSTOP|MB_OK);
  }
}

void ExcelOpen_ProductDetail(String xlsfilepath)
{ void QueryToExcel_ProductDetail(String  strTitle,String xlsfilepath);
  const int SHEET_COUNT=1;
  try
  { if(!CreateExcelAPP())
    { Application->MessageBox("无法启动Excel","错误",MB_ICONSTOP|MB_OK);
      return;
    }
    AppExcel->PG("WorkBooks").OleProcedure("Add",1);
    Wb = AppExcel->PG("ActiveWorkBook");
    Sheet = Wb.PG("ActiveSheet");//获得当前默认的Sheet
    Sheet.PS("Name","sheet0");
    for(int i=0;i<SHEET_COUNT;i++)
    { QueryToExcel_ProductDetail("产品参数",xlsfilepath);
      AppExcel->PG("WorkBooks").PR("Open",xlsfilepath.c_str());
      Variant   vWorkbookDst = AppExcel->PG("ActiveWorkBook");
      Variant   vSheetDst = vWorkbookDst.PG("ActiveSheet");
      vSheetDst.PR( "Select");
      //把新工作簿的表移回最初的工作簿
      vSheetDst.PR( "Move",Sheet);
    }
    for(int i=SHEET_COUNT;i>0;i--)
    { char tempbuf[64];
      sprintf(tempbuf,"Sheet%d",i);
      Wb.PG("WorkSheets",i).PR("Activate");//先激活后才能修改
      Wb.PG("ActiveSheet").PS("Name",tempbuf);
    }
    Wb.PG("WorkSheets",SHEET_COUNT+1).PR("delete");
    AppExcel->PS("Visible",true);//使Excel可见
  }
  catch(...)
  { DestroyExcelApp();
    Application->MessageBox("操作Excel表格错误！","错误",MB_ICONSTOP|MB_OK);
  }
}

void ExcelOpen_DevParams(String xlsfilepath)
{ void QueryToExcel_DevParams(String  strTitle,String  strPath);
  const int SHEET_COUNT=1;
  try
  { if(!CreateExcelAPP())
    { Application->MessageBox("无法启动Excel","错误",MB_ICONSTOP|MB_OK);
      return;
    }
    AppExcel->PG("WorkBooks").OleProcedure("Add",1);
    Wb = AppExcel->PG("ActiveWorkBook");
    Sheet = Wb.PG("ActiveSheet");//获得当前默认的Sheet
    Sheet.PS("Name","sheet0");
    //xlsfilepath=NewTempXlsFile();

    for(int i=0;i<SHEET_COUNT;i++)
    { QueryToExcel_DevParams("设备参数",xlsfilepath);
      AppExcel->PG("WorkBooks").PR("Open",xlsfilepath.c_str());
      Variant   vWorkbookDst = AppExcel->PG("ActiveWorkBook");
      Variant   vSheetDst = vWorkbookDst.PG("ActiveSheet");
      vSheetDst.PR( "Select");
      //把新工作簿的表移回最初的工作簿
      vSheetDst.PR( "Move",Sheet);
    }
    for(int i=SHEET_COUNT;i>0;i--)
    { char tempbuf[64];
      sprintf(tempbuf,"Sheet%d",i);
      Wb.PG("WorkSheets",i).PR("Activate");//先激活后才能修改
      Wb.PG("ActiveSheet").PS("Name",tempbuf);
    }
    Wb.PG("WorkSheets",SHEET_COUNT+1).PR("delete");
    AppExcel->PS("Visible",true);//使Excel可见
  }
  catch(...)
  { DestroyExcelApp();
    Application->MessageBox("操作Excel表格错误！","错误",MB_ICONSTOP|MB_OK);
  }
}


#if 0
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonSaveClick(TObject *Sender)
{ const char *SheetTitles[]={"登记染色","登记灯芯绒","其它"};
  String ExcelFileName="E:\\source\\bcb\\ExcelApp\\test2.xls";//必须使用绝对路径，否则出错。

  try
  { if(!CreateExcelAPP())
    { Application->MessageBox("无法启动Excel","错误",MB_ICONSTOP|MB_OK);
      return;
    }
    AppExcel->PS("Visible",true);//使Excel可见
    AppExcel->PG("WorkBooks").OleProcedure("Add");
    Wb = AppExcel->PG("ActiveWorkBook");


    //建立3张工作表worksheet 及修改worksheet标题
    for(int i=Wb.PG("Sheets").PG("Count");i<3;i++)
    { AppExcel->PG("Sheets").OleProcedure("Add");
    }
    for(int i=0;i<3;i++)
    { Wb.PG("WorkSheets",i+1).PR("Activate");//先激活后才能修改
      Wb.PG("ActiveSheet").PS("Name",SheetTitles[i]);
    }

    //设置并获得当前默认的Sheet
    Wb.PG("WorkSheets",1).PR("Activate");
    Sheet = Wb.PG("ActiveSheet");


    //画表格边框
    int iRows = 3;
    int columCount=DBGrid1->Columns->Count;
    char strRange[64];
    sprintf(strRange,"%c%d:%c%d",'A',iRows,'A'+columCount-1,iRows);
    ERange = Sheet.OlePropertyGet("Range",strRange);
    EBorders = ERange.OlePropertyGet("Borders");
    EBorders.OlePropertySet("linestyle",xlContinuous);//xlContinuous
    EBorders.OlePropertySet("weight",xlThin);
    EBorders.OlePropertySet("colorindex",xlAutomatic);
    for(int iCols=1;iCols<1+columCount;iCols++)
    {  Sheet.PG("Cells",iRows,iCols).PS("Value",DBGrid1->Columns->Items[iCols-1]->Title->Caption.c_str());
    }
    iRows++;
    for(int iCols=1;iCols<1+columCount;iCols++)
    {  Sheet.PG("Cells",iRows,iCols).PS("Value",DBGrid1->Columns->Items[iCols-1]->Title->Caption.c_str());
    }

    Wb.OleFunction("SaveAs", ExcelFileName.c_str());  //表格保存为
  }
  catch(...)
  { DestroyExcelApp();
    Application->MessageBox("操作Excel表格错误！","错误",MB_ICONSTOP|MB_OK);
  }

}
//---------------------------------------------------------------------------
#endif
