//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "UnitMain.h"
#include "UnitWeighLogs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormWeighLogs *FormWeighLogs;
//---------------------------------------------------------------------------
__fastcall TFormWeighLogs::TFormWeighLogs(TComponent* Owner)
        : TForm(Owner)
{ this->Caption=PROJECT_COMPANY;
  DatePickerBegin->Date=Now()-30;
}
//---------------------------------------------------------------------------
void __fastcall TFormWeighLogs::FormClose(TObject *Sender,
      TCloseAction &Action)
{ MyQuery->Active=false;
  DataSource1->DataSet=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TFormWeighLogs::FormShow(TObject *Sender)
{ DataSource1->DataSet=MyQuery;
  DatePickerEnd->Date=Now();
  TimePickerEnd->Time=Now();
  Button_Refresh->Click();
}
//---------------------------------------------------------------------------
void __fastcall TFormWeighLogs::Button_ReturnClick(TObject *Sender)
{ this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormWeighLogs::Button_RefreshClick(TObject *Sender)
{ String dateTimeBegin=DateToStr(DatePickerBegin->Date)+ " "+TimeToStr(TimePickerBegin->Time);
  String dateTimeEnd=DateToStr(DatePickerEnd->Date)+ " "+TimeToStr(TimePickerEnd->Time);
  MyQuery->Active=false;
  MyQuery->ParamCheck=false; /*这个很重要。
  如果sql的参数不是用Parameters.ParamByName给的，而是直接写在sqltext里面的，里面有带冒号的，请把query的ParamCheck属性改为false。否则，delphi会把冒号当成是参数标志。*/
  MyQuery->SQL->Text="select right('00'+CSTR(pid),3) as 序号,weight as 称重值 ,addtime as 日期时间 from `weighlogs` where addtime>#"+dateTimeBegin+"# and addtime<#"+dateTimeEnd+"# order by addtime desc";
  MyQuery->Active=true;

  for(int i=0;i<3;i++)
  { DBGrid1->Columns->Items[i]->Width=200;
    DBGrid1->Columns->Items[i]->Alignment=taCenter;
    DBGrid1->Columns->Items[i]->Title->Alignment=taCenter;
  }
   
}
//---------------------------------------------------------------------------

