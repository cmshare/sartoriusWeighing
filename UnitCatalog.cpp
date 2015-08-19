//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop
#include "UnitMain.h"
#include "UnitCatalog.h"
#include "UnitCatalogEdit.h"
#include "UnitControlPici.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormCatalog *FormCatalog;
int CatalogEditID=0;

//---------------------------------------------------------------------------
__fastcall TFormCatalog::TFormCatalog(TComponent* Owner)
        : TForm(Owner)
{  this->Caption=PROJECT_COMPANY;
}
//---------------------------------------------------------------------------
void __fastcall TFormCatalog::FormShow(TObject *Sender)
{ DataSource1->DataSet=MyQuery;
  reload_catalog();
  MN_Print->Enabled=(g_usergrade>USER_GRADE_OPERATOR);
  MN_Clear->Enabled=MN_Print->Enabled;
}
//---------------------------------------------------------------------------
void TFormCatalog::reload_catalog(void)
{ MyQuery->Active=false;
  MyQuery->SQL->Text="select right('00'+CSTR(id),3) as 序号,name as 产品名称 ,code as 产品编号, description as 产品描述 ,updatetime as 更新时间 from `catalog` order by id asc";
  MyQuery->Active=true;

  DBGrid1->Columns->Items[0]->Width=50;
  DBGrid1->Columns->Items[0]->Title->Alignment=taCenter;
  DBGrid1->Columns->Items[0]->Alignment=taCenter;
  DBGrid1->Columns->Items[1]->Width=250;
  DBGrid1->Columns->Items[1]->Title->Alignment=taCenter;
  DBGrid1->Columns->Items[2]->Width=100;
  DBGrid1->Columns->Items[2]->Title->Alignment=taCenter;
  DBGrid1->Columns->Items[3]->Width=250;
  DBGrid1->Columns->Items[3]->Title->Alignment=taCenter;
 // DBGrid1->Columns->Items[4]->Width=100;
  DBGrid1->Columns->Items[4]->Title->Alignment=taCenter;
}
//---------------------------------------------------------------------------
void __fastcall TFormCatalog::DBGrid1DblClick(TObject *Sender)
{ g_CurrentProductID=MyQuery->Fields->FieldByNumber(1)->AsInteger;
  if(DBGrid1->SelectedIndex==0)
  {  g_directNewCatalog=false;
      //this->ModalResult=RET_EDIT;
      this->Hide();
      FormCatalogEdit=new TFormCatalogEdit(Application);
      FormCatalogEdit->ShowModal();
      FormCatalogEdit=NULL;
      this->Show();
  }
  else if(DBGrid1->SelectedIndex==1)
  { String productName=MyQuery->Fields->FieldByNumber(2)->AsString;
    String productCode=MyQuery->Fields->FieldByNumber(3)->AsString;
    String productDesc=MyQuery->Fields->FieldByNumber(4)->AsString;
    if(!productName.IsEmpty())
    {  if(conn_mode==0 || FormMain->comm_open(true))
       { if(g_CurPiciProductID>0)
         { ShowMessage("请先停止运行中的批次！");
           this->ModalResult=RET_PICI;
         }
         else if(Query_StartPici(g_CurrentProductID,productName,productDesc,productCode))
         { this->ModalResult=RET_PICI;
         }
       }
       else ShowMessage("通信连接失败，请检查通信接口及参数配置！");
     }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormCatalog::FormClose(TObject *Sender,
      TCloseAction &Action)
{ MyQuery->Active=false;
  DataSource1->DataSet=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TFormCatalog::MN_CloseClick(TObject *Sender)
{ this->Close();
}
//---------------------------------------------------------------------------
void TFormCatalog::CategoryToHTML(String  strTitle,String  strPath)
{ extern char *xlsHead;
  int fieldcount=DBGrid1->Columns->Count;
  FILE * f=fopen(strPath.c_str(),"wb");
  fprintf(f,"%s\r\n",xlsHead);
  fprintf(f,"<center><strong><font size=4>%s</font></strong></center>",strTitle.c_str());
  fprintf(f,"<table width=640 border=1><tr bgcolor=#DFDFDF>\r\n");
  for(int i=0;i<fieldcount;i++)
  { if(DBGrid1->Columns->Items[i]->Visible)
       fprintf(f,"<td align=\"center\"><strong>%s</strong></td>\r\n",DBGrid1->Columns->Items[i]->Title->Caption.c_str());
  }
  fprintf(f,"</tr>\r\n");
  MyQuery->First();
  while(!MyQuery->Eof)
  { String productName=MyQuery->Fields->FieldByNumber(2)->AsString;
    if(!productName.IsEmpty())
    { String productDesc=MyQuery->Fields->FieldByNumber(4)->AsString;
      String productCode=MyQuery->Fields->FieldByNumber(3)->AsString;

      fprintf(f,"<tr>\r\n");
      for(int i=0;i<fieldcount;i++)
      { if(DBGrid1->Columns->Items[i]->Visible)
        fprintf(f,"<td align=\"center\">%s</td>\r\n",MyQuery->Fields->Fields[i]->AsString.c_str());
      }
      fprintf(f,"</tr>\r\n");
    }
    MyQuery->Next();
  }
  MyQuery->First();
  fprintf(f,"</table>");
  fprintf(f,"</body></html>");
  fclose(f);
}
//---------------------------------------------------------------------------
void QueryToExcel_CategoryList(String  strTitle,String  strPath)
{  FormCatalog->CategoryToHTML(strTitle,strPath);
}
//---------------------------------------------------------------------------
void __fastcall TFormCatalog::MN_PrintClick(TObject *Sender)
{  extern void ExcelOpen_CategoryList(String);
   String xlsPath=ExtractFilePath(Application->ExeName)+DIRECTORY_PRODUCT_CATALOG+"\\catalog.xls";
   ExcelOpen_CategoryList(xlsPath);
}
//---------------------------------------------------------------------------
void __fastcall TFormCatalog::MN_ClearClick(TObject *Sender)
{  if(Application->MessageBox("确定清空产品目录？","警告",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
   { MyQuery->Active=false;
     ExecSQL("update `catalog` set name='',code='',description='',updatetime=null where name<>''");
     reload_catalog();
   }
}
//---------------------------------------------------------------------------

