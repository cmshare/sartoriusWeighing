//---------------------------------------------------------------------------

#ifndef UnitCatalogEditH
#define UnitCatalogEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFormCatalogEdit : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelTop;
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *MN_Save;
        TMenuItem *MN_Delete;
        TMenuItem *MN_Exit;
        TMenuItem *MN_Next;
        TMenuItem *MN_Modify;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TLabel *Label11;
        TLabel *Label2;
        TEdit *Edit_Code;
        TEdit *Edit_Description;
        TEdit *Edit_Name;
        TGroupBox *GroupBox2;
        TLabel *Label4;
        TLabel *Label8;
        TLabel *Label6;
        TEdit *Edit_ValueUL;
        TEdit *Edit_ValueLL;
        TEdit *Edit_ValueTP;
        TLabel *Label3;
        TLabel *Label7;
        TLabel *Label5;
        TLabel *Label16;
        TEdit *Edit_PassRate;
        TLabel *Label17;
        TLabel *Label18;
        TEdit *Edit_pdsd;
        TLabel *Label19;
        TLabel *Label20;
        TEdit *Edit_correctionFactor;
        TGroupBox *GroupBox3;
        TLabel *Label21;
        TLabel *Label22;
        TLabel *Label24;
        TLabel *Label25;
        TLabel *Label26;
        TEdit *Edit_tcActiontime;
        TEdit *Edit_tcWaittime;
        TLabel *Label9;
        TEdit *Edit_StatRange;
        TLabel *Label10;
        TLabel *Label14;
        TEdit *Edit_PackLength;
        TLabel *Label15;
        TLabel *Label12;
        TEdit *Edit_PresetTare;
        TLabel *Label13;
        TComboBox *ComboBox_mode;
        TMenuItem *MN_Previous;
        TMenuItem *MN_PrintExcel;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall MN_SaveClick(TObject *Sender);
        void __fastcall MN_DeleteClick(TObject *Sender);
        void __fastcall MN_ExitClick(TObject *Sender);
        void __fastcall Edit_Changed(TObject *Sender);
        void __fastcall MN_NextClick(TObject *Sender);
        void __fastcall MN_ModifyClick(TObject *Sender);
        void __fastcall MN_PreviousClick(TObject *Sender);
        void __fastcall MN_PrintExcelClick(TObject *Sender);
        void __fastcall EditNum_KeyPress(TObject *Sender, char &Key);
private:	// User declarations
        float dev_ctcd;
        bool SaveProduct(void);
        int get_next_emptyID(void);
        int get_prev_ProductID(void);
        void ShowProduct(void);
        void input_enable(bool bEnable);

public:		// User declarations
        void ProductToHTML(String strTitle,String xlsfilepath);
        __fastcall TFormCatalogEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormCatalogEdit *FormCatalogEdit;
//---------------------------------------------------------------------------
#endif
