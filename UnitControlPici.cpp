//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include "UnitMain.h"
#include "UnitPici.h"
#include "UnitControlPici.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormControlPici *FormControlPici;
static bool pici_toOpenOrClose=false;
String g_piciNumber,g_piciProductName,g_piciProductDesc,g_piciProductCode,g_piciProductLine,g_piciCheckweigher,g_piciOperator,g_curPiciFile,g_curStatFile,g_curFinalReport;
int g_PiciCounter=0, g_CurPiciProductID=0,g_LastPiciProductID=0,g_PiciCapacity=0;
TDateTime piciStartTime,piciOverTime;
//---------------------------------------------------------------------------
__fastcall TFormControlPici::TFormControlPici(TComponent* Owner)
        : TForm(Owner)
{ this->Caption=PROJECT_COMPANY;
}
//---------------------------------------------------------------------------
void __fastcall TFormControlPici::FormShow(TObject *Sender)
{ PanelTop->Caption=(pici_toOpenOrClose)?"开始批次":"停止批次";
  Edit_ProductName->Text=g_piciProductName;
  Edit_ProductDesc->Text=g_piciProductDesc;
  Edit_ProductCode->Text=g_piciProductCode;
  if(!pici_toOpenOrClose)
  {  Edit_ProductLine->Text=g_piciProductLine;
     Edit_Checkweigher->Text=g_piciCheckweigher;
     Edit_PiciNumber->Text=g_piciNumber;
     Edit_PiciOperator->Text=g_piciOperator;
     if(g_PiciCapacity>0 && g_PiciCapacity!=DefaultPiciCapacity)Edit_PiciCapacity->Text=IntToStr(g_PiciCapacity);
  }

  Edit_ProductLine->Enabled=pici_toOpenOrClose;
  Edit_Checkweigher->Enabled=pici_toOpenOrClose;
  Edit_PiciNumber->Enabled=pici_toOpenOrClose;
  Edit_PiciOperator->Enabled=pici_toOpenOrClose;
  Edit_PiciCapacity->Enabled=pici_toOpenOrClose;
}
//---------------------------------------------------------------------------
bool Query_StartPici(int productID,String productName,String productDesc,String productCode)
{ if(g_CurPiciProductID)
  { Application->MessageBox("请先停止运行中的批次！","提示",MB_OK|MB_ICONSTOP);
  }
  else if(productID)
  { g_CurPiciProductID=productID;
    g_piciProductName=productName;
    g_piciProductDesc=productDesc;
    g_piciProductCode=productCode;
    pici_toOpenOrClose=true;  //to开始批次
    FormControlPici=new TFormControlPici(Application);
    if(FormControlPici->ShowModal()==mrOk)
    { g_PiciCounter=0;
      return true;
    }else g_CurPiciProductID=0;
  }
  return false;
}
bool Query_StopPici(void)
{ if(g_CurPiciProductID)
  { pici_toOpenOrClose=false;//to结束批次
    FormControlPici=new TFormControlPici(Application);
    if(FormControlPici->ShowModal()==mrOk)
    { g_LastPiciProductID=g_CurPiciProductID;
      return true;
    }
  }
  else
  { Application->MessageBox("没有运行中的批次！","提示",MB_OK|MB_ICONSTOP);
  }
  return false;
}

//---------------------------------------------------------------------------
void __fastcall TFormControlPici::MN_OKClick(TObject *Sender)
{  if(pici_toOpenOrClose)
   { g_piciNumber=Edit_PiciNumber->Text.Trim();


     g_piciProductLine=Edit_ProductLine->Text.Trim();
     g_piciCheckweigher=Edit_Checkweigher->Text.Trim();
     g_piciOperator=Edit_PiciOperator->Text.Trim();
     if(Edit_PiciCapacity->Text.IsEmpty())g_PiciCapacity=0;
     else g_PiciCapacity=atoi(Edit_PiciCapacity->Text.c_str());

     if(!g_piciNumber.IsEmpty())
     {  String strDir=ExtractFilePath(Application->ExeName)+DIRECTORY_PICI;
        char xls_filename[32];
        sprintf(xls_filename,"%03d-%s",g_CurPiciProductID,g_piciNumber.c_str());
        g_curPiciFile=strDir+"\\w-"+xls_filename+".xls";
        g_curStatFile=strDir+"\\s-"+xls_filename+".xls";
        g_curFinalReport=strDir+"\\f-"+xls_filename+".xls";
        if(FileExists(g_curPiciFile))
        { int ret=Application->MessageBox("该产品批次已经存在，是否覆盖？","提示",MB_OKCANCEL|MB_ICONQUESTION);
          if(ret!=ID_OK)return;
        }
      }
      piciStartTime=Now();
      g_PiciCounter=0;
      this->ModalResult=mrOk;

   }
   else
   { piciOverTime=Now();
     this->ModalResult=mrOk;
     FormMain->comm_open(false);
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormControlPici::MN_CancelClick(TObject *Sender)
{ this->ModalResult=mrCancel;
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

