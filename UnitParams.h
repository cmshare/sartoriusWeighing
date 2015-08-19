//---------------------------------------------------------------------------

#ifndef UnitParamsH
#define UnitParamsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormParams : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TEdit *Edit_ctcd;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *Edit_zjjl;
        TLabel *Label4;
        TLabel *Label5;
        TEdit *Edit_zzj;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *Edit_passrate;
        TLabel *Label8;
        TLabel *Label9;
        TEdit *Edit_pdsd;
        TLabel *Label10;
        TLabel *Label11;
        TEdit *Edit_sjpl;
        TLabel *Label12;
        TGroupBox *GroupBox2;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TLabel *Label18;
        TLabel *Label19;
        TLabel *Label20;
        TLabel *Label21;
        TLabel *Label22;
        TLabel *Label23;
        TEdit *Edit_zdpdsd;
        TEdit *Edit_zxpdsd;
        TEdit *Edit_zdpl;
        TEdit *Edit_zdcz;
        TEdit *Edit_xsfd;
        TLabel *Label25;
        TEdit *Edit_zxpl;
        TLabel *Label26;
        TEdit *Edit_zxcz;
        TMenuItem *MN_Save;
        TMenuItem *MN_Close;
        TPanel *PanelTop;
        TLabel *Label24;
        TLabel *Label27;
        TComboBox *ComboBox_autozero;
        TMenuItem *MN_Modify;
        TMenuItem *MN_Print;
        void __fastcall MN_CloseClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall OnCtcdChanged(TObject *Sender);
        void __fastcall MN_SaveClick(TObject *Sender);
        void __fastcall MN_ModifyClick(TObject *Sender);
        void __fastcall EditNum_KeyPress(TObject *Sender, char &Key);
        void __fastcall MN_PrintClick(TObject *Sender);
private:	// User declarations
       
        void input_enalbe(bool bEnable);
public:		// User declarations
        __fastcall TFormParams(TComponent* Owner);
        void DevParamsToHTML(String strTitle,String strPath);

};
//---------------------------------------------------------------------------
extern PACKAGE TFormParams *FormParams;
//---------------------------------------------------------------------------
#endif
