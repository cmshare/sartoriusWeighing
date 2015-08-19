//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "UnitMain.h"
#include "UnitDebug.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormDebug *FormDebug;
//---------------------------------------------------------------------------
__fastcall TFormDebug::TFormDebug(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormDebug::Button_ClearClick(TObject *Sender)
{ RichEdit1->Clear();
}
//---------------------------------------------------------------------------
#define LINE_BUF_SIZE  2048
static char linebuf[LINE_BUF_SIZE+1];
void  TFormDebug::appendData(char *data,int datalen)
{ data_to_hex(data,datalen,linebuf,LINE_BUF_SIZE);
  RichEdit1->Lines->Add(linebuf);
}
