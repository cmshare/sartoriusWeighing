//---------------------------------------------------------------------------

#ifndef UnitWeighStat1H
#define UnitWeighStat1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormWeighStat1 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button_Return;
        TPanel *PanelTop;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *Edit_PiciName;
        TEdit *Edit_ProductName;
        TLabel *Label3;
        TEdit *Edit1;
        TLabel *Label4;
        TLabel *Label5;
        TEdit *Edit2;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *Edit3;
        TLabel *Label8;
        TLabel *Label9;
        TEdit *Edit4;
        TLabel *Label10;
        TLabel *Label11;
        TEdit *Edit5;
        TLabel *Label12;
        TLabel *Label13;
        TEdit *Edit6;
        TLabel *Label14;
        TLabel *Label15;
        TEdit *Edit7;
        TLabel *Label16;
        TLabel *Label17;
        TEdit *Edit8;
        TLabel *Label18;
        TLabel *Label_StatPeriod;
        TBevel *Bevel1;
        TBevel *Bevel2;
        TLabel *Label_StatID;
        TSpeedButton *SpeedButton1;
        void __fastcall Button_ReturnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormWeighStat1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormWeighStat1 *FormWeighStat1;
//---------------------------------------------------------------------------
#endif
