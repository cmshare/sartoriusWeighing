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
  MyQuery->ParamCheck=false; /*�������Ҫ��
  ���sql�Ĳ���������Parameters.ParamByName���ģ�����ֱ��д��sqltext����ģ������д�ð�ŵģ����query��ParamCheck���Ը�Ϊfalse������delphi���ð�ŵ����ǲ�����־��*/
  MyQuery->SQL->Text="select right('00'+CSTR(pid),3) as ���,weight as ����ֵ ,addtime as ����ʱ�� from `weighlogs` where addtime>#"+dateTimeBegin+"# and addtime<#"+dateTimeEnd+"# order by addtime desc";
  MyQuery->Active=true;

  for(int i=0;i<3;i++)
  { DBGrid1->Columns->Items[i]->Width=200;
    DBGrid1->Columns->Items[i]->Alignment=taCenter;
    DBGrid1->Columns->Items[i]->Title->Alignment=taCenter;
  }
   
}
//---------------------------------------------------------------------------

