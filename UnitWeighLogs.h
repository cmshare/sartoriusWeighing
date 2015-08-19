//---------------------------------------------------------------------------

#ifndef UnitWeighLogsH
#define UnitWeighLogsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TFormWeighLogs : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TSpeedButton *SpeedButton1;
        TDBGrid *DBGrid1;
        TPanel *Panel2;
        TLabel *Label1;
        TDateTimePicker *DatePickerBegin;
        TDataSource *DataSource1;
        TDateTimePicker *TimePickerBegin;
        TDateTimePicker *DatePickerEnd;
        TDateTimePicker *TimePickerEnd;
        TLabel *Label2;
        TSpeedButton *Button_Refresh;
        TButton *Button_Return;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Button_ReturnClick(TObject *Sender);
        void __fastcall Button_RefreshClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormWeighLogs(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormWeighLogs *FormWeighLogs;
//---------------------------------------------------------------------------
#endif
