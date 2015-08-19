//---------------------------------------------------------------------------

#ifndef UnitPiciH
#define UnitPiciH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFormPici : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel2;
        TLabel *Label_Weight;
        TStaticText *LabelUnit;
        TStaticText *StaticText_ProductID;
        TPanel *Panel_LL;
        TPanel *Panel_TP;
        TPanel *Panel_UL;
        TLabel *Label_ValueLL;
        TLabel *Label_ValueTP;
        TLabel *Label_ValueUL;
        TMainMenu *MainMenu1;
        TMenuItem *MN_Action;
        TMenuItem *MN_StopPici;
        TMenuItem *MN_Close;
        TMenuItem *MN_LoadProduct;
        TMenuItem *N3;
        TMenuItem *MN_StatMode1;
        TMenuItem *MN_StatMode2;
        TLabel *Label_picitick;
        TLabel *Label5;
        TLabel *Label_PiciNumber;
        TGroupBox *GroupBox_Stat1;
        TLabel *Label2;
        TEdit *Edit_StandardDeviation;
        TLabel *LabelUnit1;
        TLabel *Label4;
        TEdit *Edit_Average;
        TLabel *LabelUnit2;
        TLabel *Label7;
        TEdit *Edit_MinWeight;
        TLabel *LabelUnit3;
        TLabel *Label9;
        TEdit *Edit_MaxWeight;
        TLabel *LabelUnit4;
        TLabel *Label11;
        TEdit *Edit_QualifiedRate;
        TLabel *Label13;
        TEdit *Edit_totalNum;
        TLabel *Label14;
        TLabel *Label15;
        TEdit *Edit_totalWeight;
        TLabel *LabelUnit5;
        TGroupBox *GroupBox_Stat2;
        TLabel *Label17;
        TLabel *LabelUnit6;
        TLabel *Label19;
        TLabel *LabelUnit7;
        TLabel *Label21;
        TLabel *LabelUnit8;
        TLabel *Label23;
        TLabel *LabelUnit9;
        TLabel *Label27;
        TLabel *Label28;
        TLabel *Label29;
        TLabel *LabelUnit10;
        TEdit *Edit_StandardDeviation1;
        TEdit *Edit_Average1;
        TEdit *Edit_MinWeight1;
        TEdit *Edit_MaxWeight1;
        TEdit *Edit_totalNum1;
        TEdit *Edit_totalWeight1;
        TLabel *Label12;
        TMenuItem *MN_ResumePici;
        TLabel *Label25;
        TMenuItem *MN_StatCancel;
        TSpeedButton *SpeedButton_grossornet;
        TBevel *Bevel1;
        TBevel *Bevel2;
        TMenuItem *MN_Lock;
        TLabel *Label_PiciState;
        TTimer *SecondsTimer;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall MN_StopPiciClick(TObject *Sender);
        void __fastcall MN_CloseClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall MN_StatMode1Click(TObject *Sender);
        void __fastcall MN_LoadProductClick(TObject *Sender);
        void __fastcall MN_ResumePiciClick(TObject *Sender);
        void __fastcall MN_StatCancelClick(TObject *Sender);
        void __fastcall SpeedButton_PiciControlClick(TObject *Sender);
        void __fastcall SpeedButton_grossornetClick(TObject *Sender);
        void __fastcall MN_LockClick(TObject *Sender);
        void __fastcall SecondsTimerTimer(TObject *Sender);
private:	// User declarations
        int qualified_counter;
        bool bNetWeight,connected;
        TDateTime *weight_times;
        float *weight_values,correction_factor,totalweight,weight_maximum,weight_minimum,totalweight1,weight_minimum1,weight_maximum1,read_weight;
        float weight_tp,weight_ul,weight_ll,weight_tare,weight_range_ul,weight_range_ll;
        String strDefaultUnit;
        TPanel *mark_panels[3];
        void forceCalcStat(void);
        void refresh_stat(void);
        void __fastcall Wnd_Proc(TMessage &Msg);
        BEGIN_MESSAGE_MAP
          MESSAGE_HANDLER(MSG_WEIGH_NOTIFY, TMessage, Wnd_Proc)
        END_MESSAGE_MAP(TForm)
        //void update_show(bool bSaveRecored);
public:		// User declarations
        __fastcall TFormPici(TComponent* Owner);
       void UpdatePiciState(bool piciOnOff);
       void GenStatFile(void);
       void GenOriginalRecordFile(void);
       void GenFinalReportFile(void);
       void LockControl(bool bLockOrNot);
//---------------------------------------------------------------------------

};
//---------------------------------------------------------------------------
extern PACKAGE TFormPici *FormPici;

//---------------------------------------------------------------------------
#endif
