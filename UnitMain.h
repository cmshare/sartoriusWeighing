//---------------------------------------------------------------------------

#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include "IniFiles.hpp"
#include "UrtNetDrv.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
//#define PRIVATE_APP
#define DEMO_LIMIT_TIME_M           0//60
//---------------------------------------------------------------------------
#ifdef PRIVATE_APP
   #define PROJECT_COMPANY       "喵小瞳 服务测试程序"
   #define PROJECT_TITLE         "喵小瞳 服务测试程序"
#else
   #define PROJECT_COMPANY       "赛多利斯工业称重设备（北京）有限公司"
    #if(DEMO_LIMIT_TIME_M>0)
     #define PROJECT_TITLE       "WM35称重管理软件(演示版)"
   #else
     #define PROJECT_TITLE       "WM35称重管理软件"
   #endif
#endif
#define PROJECT_NAME          "WM35"
#define PROJECT_VERSION       "V1.0.0"
#define MSG_WEIGH_NOTIFY       WM_USER+103
#define DIRECTORY_PICI        "pici"
#define DefaultPiciCapacity    65535
#define DIRECTORY_PRODUCT_PARAMS        "产品参数记录"
#define DIRECTORY_PRODUCT_CATALOG       "产品目录记录"
#define DIRECTORY_DEVICE_PARAMS         "设备参数记录"
#define DIRECTORY_PRODUCT_TEST          "产品测试记录"

enum {UNIT_NONE=0,UNIT_KG=1,UNIT_G=2,UNIT_T=3};
enum {emEditorAdd=0,emEditorModify,RET_EDIT=101,RET_PICI};
enum {USER_GRADE_NONE=0,USER_GRADE_OPERATOR,USER_GRADE_CHARGER,USER_GRADE_ADMIN,USER_GRADE_SECURITY};
#define CALC_PDSU(ctcd,passrate)   ((ctcd)*(passrate)*1.1/1000)
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label_ProjectTitle;
        TLabel *Label_ProjectVersion;
        TImage *Image1;
        TImage *Image2;
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *MN_Settings;
        TMenuItem *N3;
        TMenuItem *MN_Login;
        TMenuItem *MN_Quit;
        TMenuItem *N4;
        TMenuItem *MN_Open;
        TMenuItem *MN_Search;
        TMenuItem *MN_Product;
        TMenuItem *MN_NewProduct;
        TMenuItem *MN_LoadProduct;
        TMenuItem *MN_Connections;
        TMenuItem *MN_WeighTest;
        TMenuItem *MN_Usrmgr;
        TMenuItem *MN_DevParams;
        TMenuItem *MN_About;
        TPanel *PanelLogin;
        TLabel *Label1;
        TEdit *Edit_Username;
        TLabel *Label2;
        TEdit *Edit_Password;
        TMenuItem *MN_WeighStat;
        TMenuItem *MN_WeighLogs;
        TGroupBox *GroupBox_UartPort;
        TPanel *PanelConnections;
        TRadioGroup *RadioGroup_conn;
        TGroupBox *GroupBox1;
        TComboBox *ComboBox_PortNum;
        TComboBox *ComboBox_Baudrate;
        TComboBox *ComboBox_Parity;
        TComboBox *ComboBox_Databits;
        TComboBox *ComboBox_Stopbits;
        TGroupBox *GroupBox2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *Edit_ServerIP;
        TEdit *Edit_Serverport;
        TTimer *TimerHb;
        TMenuItem *MN_StaticWeigh;
        TTimer *TimerIdle;
        TPanel *PanelSearch;
        TLabel *Label5;
        TEdit *Edit_searchKey;
        TButton *Button_Seek;
        TListBox *ListBoxSearch;
        TMenuItem *MN_ProductParam;
        TMenuItem *MN_ProductCatalog;
        TMenuItem *MN_ProductTest;
        TMenuItem *MN_DeviceParam;
        TMenuItem *MN_debug;
        TMenuItem *MN_FinalReport;
        void __fastcall MN_QuitClick(TObject *Sender);
        void __fastcall MN_LoginClick(TObject *Sender);
        void __fastcall MN_AboutClick(TObject *Sender);
        void __fastcall MN_NewProductClick(TObject *Sender);
        void __fastcall MN_LoadProductClick(TObject *Sender);
        void __fastcall MN_UsrmgrClick(TObject *Sender);
        void __fastcall MN_WeighStatClick(TObject *Sender);
        void __fastcall MN_WeighTestClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall MN_SearchClick(TObject *Sender);
        void __fastcall RadioGroup_connClick(TObject *Sender);
        void __fastcall TimerHbTimer(TObject *Sender);
        void __fastcall MN_ConnectionsClick(TObject *Sender);
        void __fastcall MN_StaticWeighClick(TObject *Sender);
        void __fastcall TimerIdleTimer(TObject *Sender);
        void __fastcall Edit_PasswordKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall MN_DevParamsClick(TObject *Sender);
        void __fastcall Button_SeekClick(TObject *Sender);
        void __fastcall ListBoxSearchDblClick(TObject *Sender);
        void __fastcall MN_WeighLogsClick(TObject *Sender);
        void __fastcall MN_ProductParamClick(TObject *Sender);
        void __fastcall MN_ProductCatalogClick(TObject *Sender);
        void __fastcall MN_ProductTestClick(TObject *Sender);
        void __fastcall MN_DeviceParamClick(TObject *Sender);
        void __fastcall Edit_searchKeyKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall MN_debugClick(TObject *Sender);
        void __fastcall MN_FinalReportClick(TObject *Sender);
private:	// User declarations
        void InstallMDB(String path);
        void __fastcall UartDriverReceiveData(TObject *Sender, void *DataPtr, int DataSize);
        void __fastcall TcpDriverReceiveData(TObject* Sender, int PeerSocket, WORD PeerPort, DWORD PeerIP, char *pBuf, int DataLen);
        void RefreshCOMlist(void);
        void ShowDeviceSettings(void);
public:		// User declarations
        __fastcall TFormMain(TComponent* Owner);
        bool comm_open(bool onOff);
        void comm_send(char *sendtext);
        void comm_zeroweight(void);
        void comm_netweight(void);
        bool UserLoginCheck(String dlgTitle);
        void UI_update_login_state(bool bLoginOrNot);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
extern TADOQuery *MyQuery;
extern String g_piciNumber,g_username;
extern int conn_mode,g_CurrentProductID,g_CurPiciProductID,g_PiciCounter,g_usergrade,g_MaxIdleTimeMS,g_defaultUnit;
extern bool g_security,g_directNewCatalog;
extern bool Query_StartPici(int,String,String,String);
extern bool Query_StopPici(void);
extern TcmUart *UartDriver;
String WeightToStr(float weight);
void ExecSQL(const char *format, ...);
bool TableFieldExist(String tableName,String fieldName);
void ExcelOpen(char *xlsfile,int sheetcount);
//---------------------------------------------------------------------------
#endif
