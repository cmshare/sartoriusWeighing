//---------------------------------------------------------------------------

#ifndef UnitUartTestH
#define UnitUartTestH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormDebug : public TForm
{
__published:	// IDE-managed Components
        TRichEdit *RichEdit1;
        TPanel *Panel1;
        TButton *Button_Clear;
        void __fastcall Button_ClearClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormDebug(TComponent* Owner);
        void appendData(char *data,int datalen);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDebug *FormDebug;
//---------------------------------------------------------------------------
#endif
