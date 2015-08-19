// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 

#ifndef cmUartNetDrvHPP
#define cmUartNetDrvHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Forms.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit
#include <Menus.hpp>
#include <StdCtrls.hpp>
//-- user supplied -----------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
#define FORCE_WORD(variable) (*(unsigned short *)&(variable))
#define FORCE_DWORD(variable) (*(unsigned long *)&(variable))
#define GET_BIT(data,index)   ((unsigned char)((data)>>(index))&0x1)
#define SET_BIT(data,index,state)  {if(((unsigned char)((data)>>(index))&0x1)!=(state)){if(state)data |= (1<<(index));else data &= (~(1<<(index)));}}
#define HEX_CHAR(bytedata) (((bytedata)<10)?(bytedata)+'0':(bytedata)-10+'A')
#define UPPER_CASE(ch)  (char)(((ch)<'a'||(ch)>'z')?(ch):(ch)+224)
//---------------------------------------------------------------------------
#define BINODE_REMOVE(node)\
{ (node)->Next->Prev=(node)->Prev;\
  (node)->Prev->Next=(node)->Next;\
}
//---------------------------------------------------------------------------
#define BINODE_PREV_INSERT(node,objlist)\
{ (node)->Next=objlist;\
  (node)->Prev=(objlist)->Prev;\
  (node)->Next->Prev=node;\
  (node)->Prev->Next=node;\
}
//---------------------------------------------------------------------------
#define BINODE_NEXT_INSERT(node,objlist)\
{ (node)->Next=(objlist)->Next;\
  (node)->Prev=objlist;\
  (node)->Next->Prev=node;\
  (node)->Prev->Next=node;\
}
//---------------------------------------------------------------------------
typedef struct
{ int size, readpos, writepos, linecount,linetail;
  char buffer[0];
}TQueueBuffer;
//---------------------------------------------------------------------------
bool isNumeric(char *data);
int data_to_hex(void *srcData,int dataLen,char *hexBuf,int bufSize,char splitter=32);
int hex_to_data(char *hexStr,void *dataBuf,int bufSize=-1);
int hex_to_bin(char* hexStr,char *pBuf,int hexStrSize=-1);
int hex_to_dec(char* hexStr,char *pBuf,int hexStrSize=-1);
int hex_to_int(char hex);
int hex_to_int(char *hex);
int str_to_int(char *data);
int int_to_str(int idata,char *strdata);
int float_to_str(float fdata,int digit,char *strfloat);
double str_to_double(char *p);
float str_to_float(char *p);
char *stristr(char *src,char *obj);
int  StrReplace(char *pText,char *src,char *des);
void reverse_data(void *p_buf,int dLen);
bool data_equal(void *p1,void *p2,int dLen);
void set_checksum(void *p_buf,int buf_size,int checksummode=0);
bool valid_checksum(void *p_buf,int buf_size,int checksummode=0);
char *MemSearch(void *membuf,int memsize,void *data,int datasize);
char *format(const char* formatcode, ...);
//---------------------------------------------------------------------------
TQueueBuffer *QB_Create(int buffersize);
void  QB_Destroy(TQueueBuffer *qb);
void  QB_Clear(TQueueBuffer *qb);
int   QB_IsEmpty(TQueueBuffer *qb);
int   QB_GetUsedSize(TQueueBuffer *qb);
int   QB_GetFreeSize(TQueueBuffer *qb);
int   QB_BlockPrefetch(TQueueBuffer *qb,void **pbuf);
int   QB_BlockPrefetch2(TQueueBuffer *qb,void **pbuf,int minimum);
int   QB_Write(TQueueBuffer *qb,void *buf, int len);
int   QB_Read(TQueueBuffer *qb,void *buf, int len);
int   QB_Peek(TQueueBuffer *qb,void *buf,int len);
int   QB_BlockPeek(TQueueBuffer *qb,void **pbuf);
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <ExtCtrls.hpp>
#define MinsPerHour   60
#define SecsPerMin    60
#define MSecsPerSec   1000
#define MSecsPerMin   (SecsPerMin * MSecsPerSec)
#define MSecsPerHour  (MinsPerHour * SecsPerMin * MSecsPerSec)
//---------------------------------------------------------------------------
enum TDateTimeScale{dtsMilliSecond,dtsSecond,dtsMinute,dtsHour,dtsDay};
////////////////////////////////////////////////////////////////////////////////
TDateTime time_increase(TDateTime start_time,DWORD add_value,TDateTimeScale scale=dtsMilliSecond);
WORD time_get(TDateTime DateTime,TDateTimeScale scale);
TDateTime time_set(TDateTime &DateTime,WORD value,TDateTimeScale scale);
void Decode_Time(TDateTime DateTime,WORD *Day, WORD *Hour, WORD *Min, WORD *Sec, WORD *MSec);
TDateTime Encode_Time(WORD Day, WORD Hour, WORD Min, WORD Sec, WORD MSec);
void ListAllFile(String secPath,String secFilrer,bool bIncludeSubDir,TStrings *List);
String data_to_hexstr(void *p_buf,int dataLen,char splitter=32);
String float_to_str(float fdata,int digit);
wchar_t * wstristr(wchar_t *src,wchar_t *obj);
void AsyncSleep(int MSec);
//------------------------------------------------------------------------------
HRGN  cm_get_shape(int shape_width,int shape_height,TCanvas *shape_image,TColor shape_bgcolor=clNone);
bool  cm_wnd_shape(TWinControl *myWnd,HRGN p_shage);
bool  cm_wnd_clarify(TWinControl *myWnd);
int   Wnd_ControlDlg(Controls::TControl* ClientControl, AnsiString TitleText, int Flags = 0x0, Classes::TNotifyEvent OnShowEvent = 0x0);
void  Wnd_CloseDlg(int ret);
void  Wnd_SetUserButton(AnsiString buttonCaption3, AnsiString buttonCaption2, AnsiString buttonCaption1, AnsiString buttonCaption0);
int   Wnd_MessageDlg(AnsiString ContentText, AnsiString TitleText, int Flags);
void  Wnd_ShowMessage(AnsiString ContentText);
void  Wnd_SetMode(int language,int wndmode);
void  Wnd_UserBitmap(TGraphic* UserIcon);
void  Wnd_cmForm(TComponent* AOwner,String strTitle,bool bSizeable);
////////////////////////////////////////////////////////////////////////////////
enum TWndThings{wtTaskBar,wtTbButton,wtTbClient,wtTbTray,wtDeskTop};
enum TDirSort{dirProgramFiles,dirWindows,dirSystem,dirTemp,dirDeskTop,dirSendTo,dirFavorites,dirStartMenu,dirPrograms};
class TcmMemoFile
{ private:
    String file_path,file_mode;
  public:
    void Assign(char *path=NULL,char *mode=NULL);
    void Clear();
    void Append(char *str,char *tailStr=NULL);
    void Printf(const char* format, ...);
    TcmMemoFile(char *path=NULL,char *mode=NULL,bool reset=false);
};
class TcmSys
{ private:
  public:
    DWORD GetOsVersion();
    bool QuitWindows(DWORD Actions);
    void ShowWnd(TWndThings obj,bool show_hide);
    String GetSysDir(TDirSort which);
    //TcmSys();
};

/**************net_adapter config*******************/
#define MAX_ADAPTER_DESCRIPTION_LENGTH  128 // arb.
#define MAX_ADAPTER_NAME_LENGTH         256 // arb.
#define MAX_ADAPTER_ADDRESS_LENGTH      8   // arb.

typedef struct _IP_ADDR_LIST
{ struct _IP_ADDR_LIST* Next;
  char IpAddress[16];//store an dotted decimal null-terminated  IP address string
  char SubnetMask[16];
  DWORD Context;
}IP_ADDR_LIST;

//ADAPTER_INFO - per-adapter information. All IP addresses are stored as strings
typedef struct _NET_ADAPTER_INFO
{   struct _NET_ADAPTER_INFO* Next;
    DWORD ComboIndex;
    char AdapterName[MAX_ADAPTER_NAME_LENGTH + 4]; //适配器名称，例如{66156DC3-44A4-434C-B8A9-0E5DB4B3EEAD}
    char Description[MAX_ADAPTER_DESCRIPTION_LENGTH + 4];//适配器描述,例如Realtek RTL8139(A) PCI Fast Ethernet Adapter
    UINT AddressLength;
    BYTE Address[MAX_ADAPTER_ADDRESS_LENGTH];
    DWORD Index;
    UINT Type;  /*适配器类型，例如6表示以太网适配器*/
    UINT DhcpEnabled;
    IP_ADDR_LIST *CurrentIpAddress;
    IP_ADDR_LIST IpAddressList;
    IP_ADDR_LIST GatewayList;
    IP_ADDR_LIST DhcpServer;
    BOOL HaveWins;
    IP_ADDR_LIST PrimaryWinsServer;
    IP_ADDR_LIST SecondaryWinsServer;
    long LeaseObtained;
    long LeaseExpires;
}NET_ADAPTER_INFO, *PNET_ADAPTER_INFO;

typedef DWORD (WINAPI* GetAdaptersInfoFunc)
( PNET_ADAPTER_INFO pAdapterInfo,  // buffer to receive data
  PULONG pOutBufLen               // size of data returned
);
GetAdaptersInfoFunc get_adapters_info_func();
BOOL RegSetIP(char *AdapterName, char *pIPAddress, char *pNetMask, char *pNetGate);

typedef DWORD (WINAPI* TArpFunc)
( unsigned long ipaddr,   //I:所查询的目标IP
  unsigned long temp,
  unsigned char *MacBuf,    //I:接收MAC的缓冲地址
  unsigned long *MacBufSize //IO:收MAC的缓冲大小
);
TArpFunc get_arp_func();
/**************cmTimer*******************/
typedef void (*TStaticEvent)(TObject *sender);
class TcmTimer
{ private:
    bool FEnable;
    HWND FNotifyWnd;
    DWORD FInterval;
    //TStaticEvent FOnTimer;
    TNotifyEvent FOnTimer;
    void __fastcall TimerWndProc(TMessage &Msg);
    void __fastcall SetInterval(DWORD value);
    void __fastcall SetEnable(bool value);
  public:
    TcmTimer(DWORD TimerInterval=1000);
    ~TcmTimer(void);
     __property bool Enabled={read=FEnable,write=SetEnable};
     __property DWORD Interval={read=FInterval,write=SetInterval};
     __property TNotifyEvent OnTimer={read=FOnTimer,write=FOnTimer};
};

//------------------------------------------------------------------------------------------
namespace cmSerialCommDriver32 {
//---------------------------------------------------------------------------
enum TFlowControl    { fcNone = 0, fcRtsCts = 3, fcXonXoff = 4, fcTranXonXoff = 5, fcRtsCtsXonXoff = 6 }; //AT&Kn
enum TCommPortNumber { pnCOM1=0, pnCOM2, pnCOM3, pnCOM4, pnCOM5, pnCOM6, pnCOM7, pnCOM8};
enum TCommBaudRate   { br110=0, br300, br600, br1200, br2400, br4800, br9600, br14400, br19200, br38400, br56000, br57600, br115200, br128000, br256000};
enum TCommDataBits   { db5BITS=0, db6BITS, db7BITS, db8BITS };
enum TCommStopBits   { sb1BITS=0, sb1HALFBITS, sb2BITS };
enum TCommParity     { ptNONE=0, ptODD, ptEVEN, ptMARK, ptSPACE };
enum TCommErrorCode  { COMM_NOERROR=0,COMM_NOMEMORY,COMM_INITRDBUF,COMM_INITWRBUF,COMM_OPENPORT,COMM_SETMASK,COMM_BUFSIZE,COMM_GETSTATE,COMM_SETSTATE,COMM_CRRDEVENT,COMM_CRWREVENT,COMM_CRRDTHREAD,COMM_CRWRTHREAD,COMM_CLOSERDT,COMM_CLOSEWRT,COMM_UNKOWN};
typedef void __fastcall (__closure *TCommNotifyEvent) (TObject *Sender, int NotifyType);
typedef void __fastcall (__closure *TCommErrorEvent) (TObject *Sender, int errCode,char *errMsg);
typedef void __fastcall (__closure *TCommReceiveEvent) (TObject *Sender, void *DataPtr, int DataSize);
//------------------------------------------------------------------------------------------
class PACKAGE TcmUart:public TComponent
{  private:
     DCB    _dcb;
     TCommPortNumber    _PortNo;
     bool   _Opened,_bDTR, _bRTS;
     unsigned long   _HwInSize, _HwOutSize,_BaudRate, _TimerInterval;
     HANDLE        _Handle,_hKillComm,_hSyncWrite,_hSyncRead,_hInQueueMutex,_hOutQueueMutex;
     OVERLAPPED    _ReadOS,_WriteOS;
     HWND _NotifyWnd;
     TQueueBuffer  *_InQueue,*_OutQueue;
     TCommErrorEvent  lpCommError;
     TCommReceiveEvent  lpCommReceiveData;
     static void _ReadThread(void *Param);
     static void _WriteThread(void *Param);
     static void _TimerThread(void *Param);
     volatile long _ReadThreadId,_WriteThreadId,_TimerThreadId;
     volatile bool _RunReadThread,_ReadThreadRunning,_RunWriteThread,_WriteThreadRunning,_RunTimerThread,_TimerThreadRunning;
     inline void __fastcall fSetActive(bool value) { if(value!=_Opened){if(value) Open(); else Close();} }
     inline void __fastcall fSetPort(TCommPortNumber value)       { if(_PortNo!= value){_PortNo = value;if(_Opened){Close();Open();}}}
     inline void __fastcall fSetHandle(HANDLE hComm){if(_Handle != hComm)_Handle == hComm;};
     inline void __fastcall fSetParity  (TCommParity  value) {if(_dcb.Parity != (BYTE)value){_dcb.Parity   = (BYTE)value;if(_Opened)ApplyCommSettings();} }
     inline void __fastcall fSetDataBits(TCommDataBits  value ) {if(_dcb.ByteSize != (BYTE)value+5) {_dcb.ByteSize = (BYTE)value+5 ; if(_Opened)ApplyCommSettings();}}
     inline void __fastcall fSetStopBits(TCommStopBits  value ) {if(_dcb.StopBits != (BYTE)value){_dcb.StopBits = (BYTE)value ;if(_Opened)ApplyCommSettings();} }
     inline TCommParity   __fastcall fGetParity(void)   { return (TCommParity)_dcb.Parity  ; }
     inline TCommDataBits __fastcall fGetDataBits(void) { return (TCommDataBits)(_dcb.ByteSize-5); }
     inline TCommStopBits __fastcall fGetStopBits(void) { return (TCommStopBits)_dcb.StopBits; }
     inline long __fastcall fGetInBufSize (void) { return _InQueue ->size; }
     inline long __fastcall fGetOutBufSize(void) { return _OutQueue->size; }
     void __fastcall fSetInBufSize (int n);
     void __fastcall fSetOutBufSize(int n);
     void __fastcall fSetBaudRate(unsigned long value);
     TFlowControl  __fastcall fGetFCtrl(void);
     void          __fastcall fSetFCtrl(TFlowControl);
     bool __fastcall fGetDTR(void); //Computer status, read/write
     bool __fastcall fGetRTS(void); //Computer status, read/write
     void __fastcall fSetDTR(bool); //Computer status, read/write
     void __fastcall fSetRTS(bool); //Computer status, read/write
     inline HANDLE GenCommHaldle(void);
     inline void  CommReset(void);
     inline bool  ApplyCommSettings(void);
     inline void  NotifyCommError(int errCode);
  public:
     __fastcall virtual TcmUart(TComponent* Owner);
     __fastcall virtual ~TcmUart();
     bool __fastcall Open(void);
     void __fastcall Close(void);
     void __fastcall ToggleParity(bool bLowOrHigh);
     int __fastcall RecvData(void *buffer, int bufsize);
     int __fastcall SendData(void *buffer, int bufsize);
     int __fastcall SendString(char *s);
     void __fastcall PurgeRead(bool bAbort=false);
     void __fastcall PurgeWrite(bool bAbort=false);
     bool __fastcall SetHwQueueSize(DWORD dwInQueue,DWORD dwOutQueue);
     inline DWORD __fastcall  DelayForRX(DWORD DataSize){return DataSize*10000/_dcb.BaudRate; }  // = DataSize / (_dcb.BaudRate / 10) * 1000
     BOOL __fastcall EscapeCommFunction(DWORD dwFunc); //dwFunc: one of the following values: CLRDTR,CLRRTS,SETDTR,SETRTS,SETXOFF,SETXON,SETBREAK,CLRBREAK
     void __fastcall TimerWndProc(TMessage &Msg);
     __property TQueueBuffer  *InQueue  = { read = _InQueue };
     __property TQueueBuffer  *OutQueue = { read = _OutQueue};
     __property HANDLE Handle = { read = _Handle, write = fSetHandle };
     __property TFlowControl  FlowControl = { read = fGetFCtrl, write = fSetFCtrl };
   __published:

     __property TCommPortNumber PortNO    = { read = _PortNo, write = fSetPort   };
     __property unsigned long            BaudRate  = { read = _BaudRate , write = fSetBaudRate };
     __property TCommParity     Parity    = { read = fGetParity  , write = fSetParity  };
     __property TCommDataBits   DataBits  = { read = fGetDataBits, write = fSetDataBits};
     __property TCommStopBits   StopBits  = { read = fGetStopBits, write = fSetStopBits};
     __property bool DTR  = { read = fGetDTR , write = fSetDTR  }; //Computer status, read/write
     __property bool RTS  = { read = fGetRTS , write = fSetRTS  }; //Computer status, read/write
     __property int InBufSize  = { read  = fGetInBufSize , write = fSetInBufSize };
     __property int OutBufSize = { read  = fGetOutBufSize, write = fSetOutBufSize};
     __property unsigned long PollingDelay= { read = _TimerInterval    , write = _TimerInterval    };
     __property TCommErrorEvent OnCommError = { read = lpCommError, write=lpCommError };
     __property TCommReceiveEvent OnReceiveData = {read=lpCommReceiveData, write=lpCommReceiveData};
     __property bool Active = { read = _Opened, write = fSetActive  }; //最后载入
 };
//---------------------------------------------------------------------------
} //namespace CommUartDriver32
//---------------------------------------------------------------------------
using namespace cmSerialCommDriver32;


namespace Cmipedit
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TFieldChangeEvent)(System::TObject* Sender, Byte OldField, Byte Value);

class DELPHICLASS TcmIPEdit;
class PASCALIMPLEMENTATION TcmIPEdit : public Controls::TWinControl 
{
	typedef Controls::TWinControl inherited;
	
private:
	unsigned FIP_BigEndian;
	unsigned FIP_LittleEndian;
	Byte FFields[4];
	bool FCreating;
	Classes::TNotifyEvent FOnChange;
	Classes::TNotifyEvent FOnEnter;
	Classes::TNotifyEvent FOnExit;
	TFieldChangeEvent FOnFieldChange;
	void __fastcall SetIP(unsigned Value);
	void __fastcall SetIPstr(AnsiString IPstr);
	AnsiString __fastcall GetIPstr();
	void __fastcall SetIPAddress(void);
	MESSAGE void __fastcall WMNotifyFormat(Messages::TMessage &Message);
	MESSAGE void __fastcall CNNotify(Messages::TWMNotify &Message);
	MESSAGE void __fastcall CNCommand(Messages::TWMCommand &Message);
	MESSAGE void __fastcall WMSetFont(Messages::TWMSetFont &Message);
	
protected:
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	virtual void __fastcall CreateWnd(void);
	virtual void __fastcall DestroyWnd(void);
	MESSAGE void __fastcall CMWantSpecialKey(Messages::TWMKey &Message);
	
public:
	__fastcall virtual TcmIPEdit(Classes::TComponent* AOwner);
	__fastcall virtual ~TcmIPEdit(void);
	bool __fastcall Empty(void);
	void __fastcall Clear(void);
	Byte __fastcall GetField(int Index);
	void __fastcall SetField(int Index, Byte B);
	void __fastcall SetFieldFocus(Byte Field);
	AnsiString __fastcall IPToStr(unsigned IP);
	unsigned __fastcall StrToIP(AnsiString IPstr);
	
__published:
	__property unsigned IPdata = {read=FIP_BigEndian, write=SetIP, nodefault};
	__property AnsiString IP = {read=GetIPstr, write=SetIPstr};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Classes::TNotifyEvent OnEnter = {read=FOnEnter, write=FOnEnter};
	__property Classes::TNotifyEvent OnExit = {read=FOnExit, write=FOnExit};
	__property TFieldChangeEvent OnFieldChange = {read=FOnFieldChange, write=FOnFieldChange};
	__property Color  = {default=-2147483643};
	__property Enabled  = {default=1};
	__property TabOrder  = {default=-1};
	__property TabStop  = {default=0};
	__property ParentShowHint  = {default=1};
	__property ShowHint ;
	__property Hint ;
	__property Visible  = {default=1};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TcmIPEdit(HWND ParentWindow) : Controls::TWinControl(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Cmipedit */
using namespace Cmipedit;



#include <winsock.h>

typedef struct cm_Socket_Node
{ struct cm_Socket_Node *next;
  long socket;
  DWORD IP;
  WORD  Port;
}TcmSocketNode;
typedef struct cm_Server_Connections
{ int count;
  TcmSocketNode *first,*last,*node;
}TcmServerConnections;
typedef void __fastcall (__closure *TErroEvents)(System::TObject* sender, int ErroCode, char * ErrorMsg);
typedef void __fastcall (__closure *TSocketDataEvents)(System::TObject* Sender, int PeerSocket, WORD PeerPort, DWORD PeerIP, char *pBuf, int DataLen);
typedef void __fastcall (__closure *TcmSocketEvents)(System::TObject* sender, int socket,DWORD IP, WORD Port);
enum TcmSocketProtocol{cmICMP,cmIGMP,cmUDP,cmRawIP,cmTcpServer,cmTcpClient};
enum TcmCastMode{cmUnicast,cmBroadcast,cmMulticast};
#ifndef SocketsHPP
enum TServerSocketBlockMode{bmBlocking, bmNonBlocking, bmThreadBlocking};
#endif
class PACKAGE TcmSocket : public TComponent
{ private:
     TQueueBuffer  *_InQueue;
     TErroEvents FOnError;
     TNotifyEvent FOnActiveChange;
     TcmSocketEvents FOnAccept,FOnConnectionsDiscard;
     TSocketDataEvents FOnReceive;
     TServerSocketBlockMode FBlockMode;
     TcmSocketProtocol FProtocol;
     SOCKADDR_IN m_sockaddr;
     HWND FNotifyWnd;
     HANDLE _ReadEvent,_ExitEvent,_ReadThread;
     bool FActive,FBinded;
     String FLocalHost,FRemoteHost;
     int FLocalPort,FRemotePort,FSocket,FRecvBufferSize;
     int ErrorCheck(int rc,char *fail_remark=NULL);
     char* MapErrorCode(int nError);
     void  free_connection_list(TcmServerConnections *head,bool keephead=false);
     void ShowError(char * errCode, int errNum=0);
     void DeclareConnect(bool isActive);
     void reg_connections(long socket,bool add_or_del);
     void ShowMessage(String info);
     void __fastcall SetBufferSize(int size);
     void __fastcall SetActive(bool value);
     void __fastcall OnSocketMessage(TMessage &Msg);
     virtual void __fastcall Loaded();
     static bool wsa_startup(void);
     static DWORD WINAPI ReadThreadProc(LPVOID pParam);
     int  Create(TcmSocketProtocol s_protocol);
     int  Accept(void);//建立连接函数，S为监听Socket对象名；
     bool Connect(char* strRemote, unsigned int iPort);//定义连接函数；
     bool Bind(char* strIP, unsigned int iPort);//绑定函数；
     bool AsyncSelect( HWND hWnd, unsigned int wMsg, long lEvent);
     bool Listen(int iQueuedConnections);//监听函数；
  public:
     TcmServerConnections *Connections;
     void Open(void);
     void Close(void);
     int  Receive(char* pbuf, int BufSize, int PeerSocket=INVALID_SOCKET,SOCKADDR* PeerAddr=NULL);//数据接收函数；
     int  Receive(void* pbuf, int BufSize, int *ipdata,int *portdata);//数据接收函数；
     bool SendTo(DWORD peer_IP, WORD peer_port,void *p_buf, int DataLen=0);//数据发送函数；
     bool SendTo(char *peer_IP, WORD peer_port,void *p_buf, int DataLen=0);//数据发送函数；
     bool SendTo(int peer_socket, void *p_buf, int DataLen=0);//数据发送函数；
     bool Send(void *p_buf, int DataLen=0);//数据发送函数；
     void CloseClient(int clientSocket,int msDelay=300);
     static DWORD IP_UnicastToBroadcast(DWORD ipData);
     static DWORD get_ip_data(char *p_host=NULL,TcmCastMode Mode=cmUnicast);  //是网络字节顺序的IP
     static bool isValidIP(char *IPaddr);/*static指明该方法是一个类方法,它可以通过类名::直接调用*/
     static String HostName();
     static String HostIP(DWORD IPdata=INADDR_NONE);
     static String BroadcastIP(char *IPstr=NULL);
     __fastcall TcmSocket(TComponent* Owner);//类的构造函数
     __fastcall ~TcmSocket();//类的析构函数；
     __property TQueueBuffer  *Queue  = { read = _InQueue };
  __published:
     __property TErroEvents OnError = {read=FOnError, write=FOnError};
     __property TSocketDataEvents OnReceive = {read=FOnReceive, write=FOnReceive};
     __property TcmSocketEvents OnAccept={read=FOnAccept,write=FOnAccept};
     __property TNotifyEvent OnActiveChanged={read=FOnActiveChange,write=FOnActiveChange};
     __property TcmSocketEvents OnDiscard={read=FOnConnectionsDiscard,write=FOnConnectionsDiscard};
     __property TcmSocketProtocol Protocol = {read=FProtocol,write=FProtocol};
     __property int Socket = {read=FSocket};
     __property int RemotePort = {read=FRemotePort, write=FRemotePort};
     __property String RemoteHost = {read=FRemoteHost,write=FRemoteHost};
     __property int LocalPort = {read=FLocalPort, write=FLocalPort};
     __property String LocalHost  = {read=FLocalHost,write=FLocalHost};
     __property int InBufSize ={read=FRecvBufferSize,write=SetBufferSize};
     __property bool Active = {read=FActive,write=SetActive};  //该属性尽可能放在最后载入     
};
//---------------------------------------------------------------------------
#define WM_SYSTEM_TRAY_NOTIFY (WM_USER + 7)
typedef DWORD (__stdcall *pRegFunction)(DWORD,DWORD);
/*enum TTrayIconMessage {imClick, imDoubleClick, imMouseDown,
                       imMouseUp, imLeftClickUp, imLeftDoubleClick,
                       imRightClickUp, imRightDoubleClick, imNone};
*/
//---------------------------------------------------------------------------
class PACKAGE TcmTrayIcon : public TComponent
{
private:
   String FHint;
   int FIconIndex;
   bool FVisible,FAnimate,FRestoreOnDBCLick,FOnTaskList,FOnTaskBar;
   HINSTANCE hKernelLib;
   pRegFunction RegisterServiceProcess;
   TNotifyIconData FData;
   TIcon *FIcon;
   TImageList* FIconList;
   TPopupMenu* FPopupMenu;
   TTimer *FTimer;
   TWindowHook FApplicationHook;
   TNotifyEvent FOnMinimize;
   TNotifyEvent FOnRestore;
   TNotifyEvent FOnClick;
   TNotifyEvent FOnDblClick;
   TMouseMoveEvent FOnMouseMove;
   TMouseEvent FOnMouseDown;
   TMouseEvent FOnMouseUp;
   TNotifyEvent FOnAnimate;
   void __fastcall SetHint(String Hint);
   int __fastcall GetAnimateInterval();
   void __fastcall SetAnimateInterval(int Value);
   void __fastcall SetAnimate(bool Value);
   void __fastcall setOnTaskList(bool value);
   void __fastcall setOnTaskBar(bool value);
   void __fastcall SetIcon(TIcon *value);
   TShiftState ShiftState();
protected:
   virtual void __fastcall SetVisible(bool Value);
   virtual void __fastcall DoMessage(TMessage &Message);
   virtual void __fastcall DoOnAnimate(TObject *Sender);
   virtual void __fastcall Notification(TComponent *AComponent, TOperation Operation);
   bool __fastcall ApplicationHookProc(TMessage &Message);
   virtual void __fastcall Loaded();
    __property TNotifyIconData Data = {read=FData};
public:
   __property TIcon *Icon={read=FIcon,write=SetIcon};
   __fastcall TcmTrayIcon(TComponent* Owner);
   __fastcall ~TcmTrayIcon();
   virtual void __fastcall Minimize();
   virtual void __fastcall Restore();
   virtual void __fastcall Update();
   virtual void __fastcall ShowMenu();
   virtual void __fastcall SetIconIndex(int Value);
   virtual void __fastcall SetDefaultIcon();
   HWND __fastcall GetHandle();
__published:
   // Properties
   __property bool  OnTaskBar = {read=FOnTaskBar,write=setOnTaskBar,default=true};
   __property bool  OnTaskList = {read=FOnTaskList,write=setOnTaskList,default=true};
   __property bool  RestoreOnDBCLick={read=FRestoreOnDBCLick,write=FRestoreOnDBCLick};
   __property String Hint = {read=FHint,write=SetHint};
   __property TPopupMenu* PopupMenu = {read=FPopupMenu,write=FPopupMenu};
   __property TImageList* Icons = {read=FIconList,write=FIconList};
   __property int IconIndex = {read=FIconIndex,write=SetIconIndex,default=0};
   __property int  AnimateInterval = {read=GetAnimateInterval,write=SetAnimateInterval,default=1000};
   __property bool Animate = {read=FAnimate,write=SetAnimate,default=false};
   __property bool Handle = {read=GetHandle};
   __property bool Visible = {read=FVisible,write=SetVisible,default=false};
   // Events
    __property TNotifyEvent OnMinimize = {read=FOnMinimize,write=FOnMinimize};
    __property TNotifyEvent OnRestore = {read=FOnRestore,write=FOnRestore};
    __property TNotifyEvent OnDblClick = {read=FOnDblClick,write=FOnDblClick};
    __property TNotifyEvent OnClick = {read=FOnClick,write=FOnClick};
    __property TMouseMoveEvent OnMouseMove = {read=FOnMouseMove,write=FOnMouseMove};
    __property TMouseEvent OnMouseUp = {read=FOnMouseUp,write=FOnMouseUp};
    __property TMouseEvent OnMouseDown = {read=FOnMouseDown,write=FOnMouseDown};
    __property TNotifyEvent OnAnimate = {read=FOnAnimate,write=FOnAnimate};
};
//---------------------------------------------------------------------------
#define  DefaultContextPopupMenuCount 13
//---------------------------------------------------------------------------
class PACKAGE TContextPopupMenu : public TPopupMenu
{   private:
      TMenuItem *mn[13];
      void __fastcall OnClick(TObject *Sender);
    protected:
      virtual void __fastcall DoPopup(TObject* Sender);
      virtual void __fastcall Loaded();
    public:
      static void TxtEditor_SelConverse(TCustomEdit *TxtEditor,int mode);
      __fastcall TContextPopupMenu(TComponent* Owner);
   __published:
};
//---------------------------------------------------------------------------
#define MB_USERBUTTON  0xf
#define MB_ICONAPPLICATION 0x50

//-- end unit ----------------------------------------------------------------
#endif	// cmUartDrv
