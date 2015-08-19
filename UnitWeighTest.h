//---------------------------------------------------------------------------

#ifndef UnitWeighTestH
#define UnitWeighTestH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "UnitMain.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFormWeighTest : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelTop;
        TListView *ListView1;
        TPanel *Panel1;
        TPanel *Panel2;
        TStaticText *LabelUnit;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *Edit_StandardDeviation;
        TEdit *Edit_Average;
        TEdit *Edit_Maximum;
        TEdit *Edit_Minimum;
        TLabel *Label_Weight;
        TLabel *LabelUnit5;
        TLabel *LabelUnit4;
        TLabel *LabelUnit3;
        TMainMenu *MainMenu1;
        TMenuItem *MN_Action;
        TMenuItem *MN_Save;
        TMenuItem *MN_Close;
        TLabel *Label7;
        TEdit *Edit_WeightCount;
        TLabel *Label9;
        TTimer *Timer1;
        TMenuItem *MN_Clear;
        TLabel *Label10;
        TEdit *Edit_pdsd;
        TLabel *Label11;
        TLabel *LabelUnit1;
        TMenuItem *MN_Lock;
        TLabel *Label13;
        TEdit *Edit1_Deviation1;
        TLabel *LabelUnit2;
        TEdit *Edit_Static;
        TLabel *Label15;
        TLabel *LabelUnit6;
        TEdit *Edit1_Deviation2;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall MN_CloseClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall MN_SaveClick(TObject *Sender);
        void __fastcall MN_ClearClick(TObject *Sender);
        void __fastcall MN_LockClick(TObject *Sender);
        void __fastcall Edit_StaticKeyPress(TObject *Sender, char &Key);
        void __fastcall Edit_StaticChange(TObject *Sender);
private:	// User declarations
        int weight_counter,curUnit;
        bool connected;
        String strDefaultUnit;
        float weight_maximum,weight_minimum,weight_total,weight_static;
        void refresh_stat(void);

        void __fastcall Wnd_Proc(TMessage &Msg);
        BEGIN_MESSAGE_MAP
          MESSAGE_HANDLER(MSG_WEIGH_NOTIFY, TMessage, Wnd_Proc)
        END_MESSAGE_MAP(TForm)
public:		// User declarations
        __fastcall TFormWeighTest(TComponent* Owner);
        void TestWeightToHTML(String  strTitle,String  strPath);
        void LockControl(bool bLockOrNot);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormWeighTest *FormWeighTest;
//---------------------------------------------------------------------------
#endif
