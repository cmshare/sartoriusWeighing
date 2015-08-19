//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "UnitMain.h"
#include "UnitStatic.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormStatic *FormStatic;
char cmd_static[]={0x1B,0x50,'\0'};
//---------------------------------------------------------------------------
__fastcall TFormStatic::TFormStatic(TComponent* Owner)
        : TForm(Owner)
{  this->Caption=PROJECT_COMPANY;
   int snd_interval=UartDriver->DelayForRX(strlen(cmd_static));
   WeighTimer->Interval=snd_interval+2;
   WeighTimer->Enabled=false;
   curUnit=UNIT_KG;
 // MN_NetWeight->Click();
}
//---------------------------------------------------------------------------
void __fastcall TFormStatic::MN_CloseClick(TObject *Sender)
{ this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormStatic::MN_ZeroWeightClick(TObject *Sender)
{ FormMain->comm_zeroweight();
}
//---------------------------------------------------------------------------
void __fastcall TFormStatic::MN_NetWeightClick(TObject *Sender)
{ FormMain->comm_netweight();
  //LabelNetGross->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TFormStatic::MN_GrossWeightClick(TObject *Sender)
{ char cmd_static[]={0x1B,0x6B,0x46,0x31,0x5F,'\0'};
  FormMain->comm_send(cmd_static);
  LabelNetGross->Visible=false;
}
//---------------------------------------------------------------------------
void __fastcall TFormStatic::WeighTimerTimer(TObject *Sender)
{ if(!connected)
  { ((TTimer *)Sender)->Enabled=false;
    Application->MessageBox("通信连接失败，请检查通信接口及参数配置！","提示",MB_OK|MB_ICONSTOP);
    this->Close();
  }
  else
  {
    FormMain->comm_send(cmd_static);
  }
}
//---------------------------------------------------------------------------
void _fastcall TFormStatic::Wnd_Proc(TMessage &Msg)
{  switch(Msg.Msg)
  { case WM_QUERYENDSESSION: Msg.Result=true;break;
    case MSG_WEIGH_NOTIFY:
         if(Msg.WParam>=0)
         {  float weight=*((float *)(&Msg.LParam));
            /*char strCounter[8];
            sprintf(strCounter,"NO.%03d",++weight_counter);
            LabelCounter->Caption=strCounter;*/
            if(Msg.WParam!=curUnit)
            { curUnit=Msg.WParam;
              if(curUnit==UNIT_KG) LabelUnit->Caption="kg";
              else if(curUnit==UNIT_G)  LabelUnit->Caption="g";
              else if(curUnit==UNIT_T)LabelUnit->Caption="t";
              else LabelUnit->Caption="?";
            }
            Label_Weight->Caption=WeightToStr(weight);
         }
         break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormStatic::FormClose(TObject *Sender,TCloseAction &Action)
{  WeighTimer->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TFormStatic::FormShow(TObject *Sender)
{  extern char *UNIT_CAPTIONS[4];

   connected=FormMain->comm_open(true);
   if(!connected)WeighTimer->Interval=500;
   WeighTimer->Enabled=true;

   LabelUnit->Caption=UNIT_CAPTIONS[g_defaultUnit];
}
//---------------------------------------------------------------------------
void TFormStatic::LockControl(bool bLockOrNot)
{ if(bLockOrNot==MN_Lock->Visible)return;
   if(!bLockOrNot)
   { if(FormMain->UserLoginCheck("密码验证"))FormMain->TimerIdle->Enabled=true;
     else return;
   }
   MN_Lock->Visible=bLockOrNot;
   MN_Action->Visible=!bLockOrNot;
   FormMain->UI_update_login_state(true);
}
void __fastcall TFormStatic::MN_LockClick(TObject *Sender)
{  LockControl(false);
}
//---------------------------------------------------------------------------

