//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitMain.h"
#include "UnitWeighStat1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormWeighStat1 *FormWeighStat1;
//---------------------------------------------------------------------------
__fastcall TFormWeighStat1::TFormWeighStat1(TComponent* Owner)
        : TForm(Owner)
{ this->Caption=PROJECT_COMPANY;
}
//---------------------------------------------------------------------------
void __fastcall TFormWeighStat1::Button_ReturnClick(TObject *Sender)
{
  this->Close();
}
//---------------------------------------------------------------------------

