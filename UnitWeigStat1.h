//---------------------------------------------------------------------------

#ifndef UnitWeigStat1H
#define UnitWeigStat1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFormWeighStat1 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button_Return;
        void __fastcall Button_ReturnClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TFormWeighStat1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormWeighStat1 *FormWeighStat1;
//---------------------------------------------------------------------------
#endif
