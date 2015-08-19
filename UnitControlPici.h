//---------------------------------------------------------------------------

#ifndef UnitControlPiciH
#define UnitControlPiciH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFormControlPici : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelTop;
        TLabel *Label1;
        TEdit *Edit_ProductName;
        TLabel *Label2;
        TEdit *Edit_PiciCapacity;
        TBevel *Bevel1;
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *MN_OK;
        TMenuItem *MN_Cancel;
        TLabel *Label3;
        TEdit *Edit_ProductDesc;
        TLabel *Label4;
        TEdit *Edit_ProductCode;
        TLabel *Label5;
        TEdit *Edit_ProductLine;
        TLabel *Label6;
        TEdit *Edit_Checkweigher;
        TLabel *Label7;
        TEdit *Edit_PiciNumber;
        TLabel *Label8;
        TEdit *Edit_PiciOperator;
        TLabel *Label9;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall MN_CancelClick(TObject *Sender);
        void __fastcall MN_OKClick(TObject *Sender);
private:	// User declarations

public:		// User declarations
        __fastcall TFormControlPici(TComponent* Owner);
        void StartPici(int prodictID,String productName);
        void StopPici(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormControlPici *FormControlPici;


//---------------------------------------------------------------------------
#endif
