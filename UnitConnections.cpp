//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitConnections.h"
#include "Registry.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormConnections *FormConnections;
#define MAX_COM_COUNT     64
static unsigned char SearlCOMM_List[MAX_COM_COUNT],SearlCOMM_Count=0;
extern int cur_uart_port;
//---------------------------------------------------------------------------
__fastcall TFormConnections::TFormConnections(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
