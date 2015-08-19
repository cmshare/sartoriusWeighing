//---------------------------------------------------------------------------

#ifndef UnitCatalogH
#define UnitCatalogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <DB.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFormCatalog : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TDBGrid *DBGrid1;
        TDataSource *DataSource1;
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *MN_Print;
        TMenuItem *N3;
        TMenuItem *MN_Close;
        TMenuItem *MN_Clear;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall DBGrid1DblClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall MN_CloseClick(TObject *Sender);
        void __fastcall MN_PrintClick(TObject *Sender);
        void __fastcall MN_ClearClick(TObject *Sender);
private:	// User declarations
        void reload_catalog(void);
public:		// User declarations
        __fastcall TFormCatalog(TComponent* Owner);
         void CategoryToHTML(String  strTitle,String  strPath);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormCatalog *FormCatalog;
//---------------------------------------------------------------------------
#endif
