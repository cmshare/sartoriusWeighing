//---------------------------------------------------------------------------

#ifndef UnitStaticH
#define UnitStaticH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include "UnitMain.h"
//---------------------------------------------------------------------------
class TFormStatic : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *MN_Action;
        TMenuItem *MN_ZeroWeight;
        TMenuItem *MN_NetWeight;
        TMenuItem *MN_Close;
        TMenuItem *N5;
        TPanel *PanelTop;
        TPanel *Panel2;
        TLabel *Label_Weight;
        TStaticText *LabelUnit;
        TTimer *WeighTimer;
        TMenuItem *MN_GrossWeight;
        TLabel *LabelNetGross;
        TMenuItem *MN_Lock;
        void __fastcall MN_CloseClick(TObject *Sender);
        void __fastcall MN_ZeroWeightClick(TObject *Sender);
        void __fastcall MN_NetWeightClick(TObject *Sender);
        void __fastcall WeighTimerTimer(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall MN_GrossWeightClick(TObject *Sender);
        void __fastcall MN_LockClick(TObject *Sender);
private:	// User declarations
        int weight_counter,curUnit;
        bool connected;
        void __fastcall Wnd_Proc(TMessage &Msg);
        BEGIN_MESSAGE_MAP
          MESSAGE_HANDLER(MSG_WEIGH_NOTIFY, TMessage, Wnd_Proc)
        END_MESSAGE_MAP(TForm)
public:		// User declarations
        __fastcall TFormStatic(TComponent* Owner);
       void LockControl(bool bLockOrNot);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormStatic *FormStatic;
//---------------------------------------------------------------------------
#endif
