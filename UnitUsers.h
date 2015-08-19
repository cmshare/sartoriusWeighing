//---------------------------------------------------------------------------

#ifndef UnitUsersH
#define UnitUsersH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFormUsers : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TGroupBox *GroupBoxEditor;
        TLabel *Label5;
        TEdit *Edit_Username;
        TLabel *Label2;
        TComboBox *ComboBox_Grade;
        TLabel *Label1;
        TLabel *Label3;
        TEdit *Edit_Password;
        TEdit *Edit_Password2;
        TCheckBox *CheckBox_Security;
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *MN_Add;
        TMenuItem *MN_Modify;
        TMenuItem *MN_Delete;
        TMenuItem *MN_Save;
        TMenuItem *MN_Close;
        TGroupBox *GroupBox1;
        TListBox *ListBoxUsers;
        TLabel *Label4;
        TEdit *Edit_MaxIdleTime;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Button_DeleteClick(TObject *Sender);
        void __fastcall Button_AddClick(TObject *Sender);
        void __fastcall Button_ModifyClick(TObject *Sender);
        void __fastcall Button_SaveClick(TObject *Sender);
        void __fastcall MN_CloseClick(TObject *Sender);
        void __fastcall Edit_MaxIdleTimeKeyPress(TObject *Sender, char &Key);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall CheckBox_SecurityClick(TObject *Sender);
private:	// User declarations
        int EditorMode,editGroupID;
        void RefreshUserList(void);
        void RefreshInputState(void);
public:		// User declarations
        __fastcall TFormUsers(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormUsers *FormUsers;
//---------------------------------------------------------------------------
#endif
