//---------------------------------------------------------------------------

#ifndef UnitConnectionsH
#define UnitConnectionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormConnections : public TForm
{
__published:	// IDE-managed Components
        TRadioGroup *RadioGroup1;
        TGroupBox *GroupBox1;
        TComboBox *ComboBox_PortNum;
        TComboBox *ComboBox1;
        TComboBox *ComboBox2;
        TComboBox *ComboBox3;
        TComboBox *ComboBox4;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TGroupBox *GroupBox2;
        TEdit *Edit1;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *Edit2;
private:	// User declarations
        void RefreshCOMlist(void);
public:		// User declarations
        __fastcall TFormConnections(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormConnections *FormConnections;
//---------------------------------------------------------------------------
#endif
