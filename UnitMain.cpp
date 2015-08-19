//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include "UnitMain.h"
#include "UnitCatalog.h"
#include "UnitCatalogEdit.h"
#include "UnitWeighTest.h"
#include "UnitWeighStat1.h"
#include "UnitUsers.h"
#include "UnitParams.h"
#include "UnitPici.h"
#include "UnitStatic.h"
#include "UnitConnections.h"
#include "UnitDebug.h"
#include "Registry.hpp"
#include <stdio.h>
//默认的管理员用户密码:admin@sart202122
//世界那么大，我想去看看
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "res/UrtNetDrv.lib"
//#pragma resource "res/cmdlg.res"
#define MAX_COM_COUNT              64
#define IDLETIMER_INTERVAL_MS      1000*30
TFormMain *FormMain;
TADOQuery *MyQuery;
TcmUart *UartDriver=NULL;
TcmSocket *TcpDriver=NULL;
String g_username="";
bool g_security,g_directNewCatalog;
int g_usergrade=0,conn_mode=0,g_MaxIdleTimeMS=1000*60*3,g_defaultUnit=0;
static unsigned int server_ip=0,server_port=0;
static unsigned char SearlCOMM_List[MAX_COM_COUNT],SearlCOMM_Count=0;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{  this->Caption=PROJECT_COMPANY;
  
   #ifdef PRIVATE_APP
   Label_ProjectTitle->Visible=false;
   Image1->Visible=false;   
   Image2->Visible=false;
   #endif


   Application->Title=PROJECT_TITLE;
   Label_ProjectTitle->Caption=PROJECT_TITLE;
   Label_ProjectVersion->Caption=PROJECT_VERSION;
   Edit_Password->PasswordChar='*';

   TimerHb->Interval=30*1000;//30秒
   TimerHb->Enabled=false;
   TimerIdle->Interval=IDLETIMER_INTERVAL_MS;
   TimerIdle->Enabled=false;
   ForceDirectories(ExtractFilePath(Application->ExeName)+DIRECTORY_PICI);
   ForceDirectories(ExtractFilePath(Application->ExeName)+DIRECTORY_PRODUCT_PARAMS);
   ForceDirectories(ExtractFilePath(Application->ExeName)+DIRECTORY_PRODUCT_CATALOG);
   ForceDirectories(ExtractFilePath(Application->ExeName)+DIRECTORY_DEVICE_PARAMS);
   ForceDirectories(ExtractFilePath(Application->ExeName)+DIRECTORY_PRODUCT_TEST);

   String db_file_path;

   #if 0
   //检查数据库文件路径
   HKEY hKey;
   char name_str[255];
   DWORD name_len=255,dwDataType;
   if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion",0,KEY_READ,&hKey) == ERROR_SUCCESS)
   {  if(RegQueryValueEx(hKey, "ProgramFilesDir", 0, &dwDataType, &name_str[0], &name_len)==ERROR_SUCCESS)
      {  db_file_path=(String)name_str+"\\wm35";
         ForceDirectories(db_file_path);
      }
      RegCloseKey(hKey);
   }
   #endif

   if(db_file_path.IsEmpty()) db_file_path=ExtractFileDir(Application->ExeName);
   db_file_path=db_file_path+"\\weigh.dat";

   if(!FileExists(db_file_path)) InstallMDB(db_file_path);

   TcpDriver=new TcmSocket(this);
   TcpDriver->OnReceive=TcpDriverReceiveData;
   TcpDriver->Protocol=cmTcpClient;
   UartDriver=new TcmUart(this);  //default 9600,odd,7,1
   UartDriver->OnReceiveData=UartDriverReceiveData;

   MyQuery=new TADOQuery(NULL);
   MyQuery->ConnectionString="Provider=Microsoft.Jet.OLEDB.4.0;Persist Security Info=False;Jet OLEDB:Database Password=hellowm35;Data Source="+db_file_path;

   //升级数据库////////////////////////////////////

   #if 0
   if(!TableFieldExist("`catalog`","updatetime"))
   {  ExecSQL("alter table `catalog` add COLUMN updatetime datetime");
     //ExecSQL("update `catalog` set updatetime=null");
   }
   #endif
   //////////////////////////////////////

   MyQuery->SQL->Text="select security,MaxIdleTime,communication,dev_autozero,uart_port,uart_baudrate,uart_parity,uart_databits,uart_stopbits,server_ip,server_port from configs";
   MyQuery->Active=true;
   g_defaultUnit=(MyQuery->FieldByName("dev_autozero")->AsInteger)?UNIT_G:UNIT_KG;
   g_security=MyQuery->FieldByName("security")->AsBoolean;
   conn_mode=MyQuery->FieldByName("communication")->AsInteger;
   g_MaxIdleTimeMS=MyQuery->FieldByName("MaxIdleTime")->AsInteger;
   UartDriver->PollingDelay=30;
   UartDriver->PortNO=MyQuery->FieldByName("uart_port")->AsInteger;
   UartDriver->BaudRate=MyQuery->FieldByName("uart_baudrate")->AsInteger;
   UartDriver->Parity=(TCommParity)MyQuery->FieldByName("uart_parity")->AsInteger;
   UartDriver->DataBits=(TCommDataBits)MyQuery->FieldByName("uart_databits")->AsInteger;
   UartDriver->StopBits=(TCommStopBits)MyQuery->FieldByName("uart_stopbits")->AsInteger;
   TcpDriver->RemoteHost=TcmSocket::HostIP(MyQuery->FieldByName("server_ip")->AsInteger);
   TcpDriver->RemotePort=MyQuery->FieldByName("server_port")->AsInteger;
   //if(!g_security)UI_update_login_state(true);
   MyQuery->Active=false;
}
//---------------------------------------------------------------------------
bool  TFormMain::comm_open(bool onOff)
{ if(onOff)
  { if(conn_mode==0)
    { return UartDriver->Open();
    }
    else
    {  TcpDriver->LocalHost=0;
       TcpDriver->LocalPort=0;
       TcpDriver->Active=true;
       for(int i=0;i<10;i++)
       { AsyncSleep(100);
         if(TcpDriver->Active)break;
       }
       if(TcpDriver->Active)TimerHb->Enabled=true;
       return TcpDriver->Active;
    }
    return false;
  }
  else
  { TimerHb->Enabled=false;
    if(conn_mode==0)UartDriver->Close();
    else TcpDriver->Active=false;
    return true;
  }

}
//---------------------------------------------------------------------------
void TFormMain::comm_send(char *sendtext)
{ if(conn_mode==0)
  { if(UartDriver && UartDriver->Active) UartDriver->SendString(sendtext);
  }
  else
  { if(TcpDriver && TcpDriver->Active) TcpDriver->Send(sendtext,strlen(sendtext));
  }
}
//---------------------------------------------------------------------------
void  TFormMain::comm_netweight(void)
{ char cmd_NetWeight[]={0x1B,0x66,0x34,0x5F,'\0'};
  comm_send(cmd_NetWeight);
}
//---------------------------------------------------------------------------
void  TFormMain::comm_zeroweight(void)
{ char cmd_ZeroWeight[]={0x1B,0x66,0x33,0x5F,'\0'};
  comm_send(cmd_ZeroWeight);
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::Edit_PasswordKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{ if(Key==13)  Wnd_CloseDlg(IDOK);
}
//---------------------------------------------------------------------------
bool TFormMain::UserLoginCheck(String dlgTitle)
{  Edit_Password->Clear();
   if(Wnd_ControlDlg(PanelLogin,dlgTitle, MB_OKCANCEL)==IDOK)
   { String strUsername=Edit_Username->Text.Trim();
     if(strUsername.IsEmpty())
     { ShowMessage("用户名为空！");
       return false;
     }
     String strPassword=Edit_Password->Text.Trim();
     if(strPassword.IsEmpty())
     { ShowMessage("密码为空！");
       return false;
     }

     MyQuery->SQL->Text="select grade from `users` where name='"+strUsername+"' and password='"+strPassword+"'";
     MyQuery->Active=true;
     if(!MyQuery->Eof)
     {  g_username=strUsername;
        g_usergrade=MyQuery->FieldByName("grade")->AsInteger;
        MyQuery->Active=false;
        return true;
     }
     else
     { ShowMessage("用户名或密码错误！");
     }
     MyQuery->Active=false;
   }
   return false;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MN_LoginClick(TObject *Sender)
{  static int login_counter=0;
   if(!g_security && login_counter==0)
   { g_usergrade=USER_GRADE_SECURITY;
     UI_update_login_state(true);
     Wnd_MessageDlg("登录成功！","提示",MB_OK);
   }
   else if(UserLoginCheck("登录"))
   { UI_update_login_state(true);
     Wnd_MessageDlg("登录成功！","提示",MB_OK);
   }
   login_counter++;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MN_QuitClick(TObject *Sender)
{ if(MN_Login->Visible)
  { if(Wnd_MessageDlg(("确定要退出【"+String(PROJECT_TITLE)+"】？").c_str(),"提示",MB_YESNO|MB_ICONWARNING)==IDYES)
    { //"关闭"
      Application->Terminate();
    }
  }
  else
  { //注销
     g_username="";
     g_usergrade=0;
     UI_update_login_state(false);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MN_AboutClick(TObject *Sender)
{  char temp_buf[512];
  sprintf(temp_buf,"%s %s\n\n  --- %s！",PROJECT_TITLE,PROJECT_VERSION,PROJECT_COMPANY);
  Wnd_MessageDlg(temp_buf,"关于...",MB_OK | MB_ICONAPPLICATION);
}
//---------------------------------------------------------------------------
void TFormMain::UI_update_login_state(bool bLoginOrNot)
{ MN_Product->Visible=bLoginOrNot;
  MN_Settings->Visible=bLoginOrNot;
  MN_Open->Visible=bLoginOrNot;
  MN_Search->Visible=bLoginOrNot;
  MN_Login->Visible=!bLoginOrNot;
  MN_Usrmgr->Enabled=(g_usergrade==USER_GRADE_ADMIN);
  MN_NewProduct->Enabled=(g_usergrade>USER_GRADE_OPERATOR);
  MN_Quit->Caption=(!bLoginOrNot)?"退出":"注销"; //关闭是注销的意思
  TimerIdle->Enabled=bLoginOrNot;
}
//---------------------------------------------------------------------------
 void ExecSQL(const char *format, ...)
{ char sql_buf[1024];
  va_list arg_ptr;
  va_start(arg_ptr, format);
  vsprintf(sql_buf, format, arg_ptr);
  va_end(arg_ptr);
   try
  { MyQuery->SQL->Text=sql_buf;
    MyQuery->ExecSQL();
  } catch(...){}
}
//---------------------------------------------------------------------------
bool TableFieldExist(String tableName,String fieldName)
{ bool bExist=false;
  MyQuery->SQL->Text="select * from "+tableName+" where 1=2";
  MyQuery->Active=true;
  for(int i=0;i<MyQuery->FieldCount;i++)
  { if(AnsiCompareText (MyQuery->Fields->Fields[i]->FieldName,fieldName)==0)
    { bExist=true;
      break;
    }
  }
  MyQuery->Active=false;
  return bExist;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MN_NewProductClick(TObject *Sender)
{
  this->Hide();
  g_CurrentProductID=0;
  g_directNewCatalog=true;
  FormCatalogEdit=new TFormCatalogEdit(Application);
  FormCatalogEdit->ShowModal();
  FormCatalogEdit=NULL;
  this->Show();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::TcpDriverReceiveData(TObject* Sender, int PeerSocket, WORD PeerPort, DWORD PeerIP, char *pBuf, int DataLen)
{  UartDriverReceiveData(NULL,pBuf,DataLen);
}
//---------------------------------------------------------------------------
#define  DiscreteBufferSize  80
void __fastcall TFormMain::UartDriverReceiveData(TObject *Sender, void *DataPtr, int DataSize)
{ static char discreteBuf[DiscreteBufferSize+1];
  static int  bufpos=0;
  if(DataSize<=0)return;
  char *p_end=(char *)DataPtr;
  
  HWND hNotifyWnd;
  if(FormDebug->Visible)FormDebug->appendData((char *)DataPtr,DataSize);

  if(FormPici)hNotifyWnd=FormPici->Handle;
  else if(FormWeighTest)hNotifyWnd=FormWeighTest->Handle;
  else if(FormStatic)hNotifyWnd=FormStatic->Handle;
  else return;


  if(DataSize<16 || p_end[DataSize-1]!='\n')
  { int remains;
    if(bufpos>0)
    { remains =DiscreteBufferSize-bufpos;
      if(remains<=0)
      { remains=DiscreteBufferSize;
        bufpos=0;
      }
    }else remains=DiscreteBufferSize;
    if(DataSize>remains)DataSize=remains;
    memcpy(&discreteBuf[bufpos],DataPtr,DataSize);
    bufpos+=DataSize;
    if(discreteBuf[bufpos-1]=='\n')
    { p_end=(char *)discreteBuf;
      DataSize=bufpos;
      bufpos=0;
    }else return;
  }

  p_end[DataSize]='\0';
  while(*p_end)
  { char *p_begin=p_end;
    //p_end=strstr(p_begin,"\r\n");
    p_end=MemSearch(p_begin,DataSize,"\r\n",2);
    if(p_end)
    { p_end+=2; //跳过/r/n
      int d_len=(int)(p_end-p_begin);
      if(d_len==22 || d_len==16)
      { if(d_len==22 && *p_begin!='+' && *p_begin!='-'){p_begin+=6;d_len=16;}
        if((p_begin[0]=='+' || p_begin[0]=='-')&& p_begin[1]==' ' && p_begin[10]==' ')
        { float weight=atof(p_begin+2);
          char *str_unit=p_begin+11;
          int curUnit;
          if(p_begin[0]=='-')weight=-weight;
          if(str_unit[0]=='k' && str_unit[1]=='g')curUnit=UNIT_KG;
          else if(str_unit[0]=='g')curUnit=UNIT_G;
          else if (str_unit[0]=='t')curUnit=UNIT_T;
          else curUnit=g_defaultUnit;
          SendMessage(hNotifyWnd,MSG_WEIGH_NOTIFY,curUnit,*(int *)(&weight));
          continue;
        }
      }
      SendMessage(hNotifyWnd,MSG_WEIGH_NOTIFY,-1,0);//错误
    }
    else break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MN_LoadProductClick(TObject *Sender)
{ this->Hide();
  FormCatalog=new TFormCatalog(Application);
  switch(FormCatalog->ShowModal())
  { case RET_EDIT:
           FormCatalogEdit=new TFormCatalogEdit(Application);
           FormCatalogEdit->ShowModal();
           FormCatalogEdit=NULL;
         break;
    case RET_PICI:
           FormPici=new TFormPici(Application);
           FormPici->UpdatePiciState(true);
           FormPici->ShowModal();
           FormPici=NULL;
         break;
  }
  FormCatalog=NULL;
  this->Show();
  /*
   if(ret_mode==RET_EDIT)
  { FormCatalogEdit->Show();
  }
  else
  { FormMain->Show();
    if(ret_mode==RET_PICI)FormMain->StartPici(true);
  }
  */
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MN_UsrmgrClick(TObject *Sender)
{ this->Hide();
  FormUsers=new TFormUsers(Application);
  FormUsers->ShowModal();
  FormUsers=NULL;
  this->Show();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MN_DevParamsClick(TObject *Sender)
{  this->Hide();
  FormParams=new TFormParams(Application);
  FormParams->ShowModal();
  FormParams=NULL;
  this->Show();
}
#include <dir.h>
//---------------------------------------------------------------------------
void __fastcall TFormMain::MN_FinalReportClick(TObject *Sender)
{ TOpenDialog *dlg=new TOpenDialog(this);
  dlg->Title="打开最终报表文件...";
  dlg->Filter = "报表文件|f-*.xls";
  dlg->InitialDir=ExtractFilePath(Application->ExeName)+DIRECTORY_PICI;
  if(dlg->Execute())
  {  ExcelOpen(dlg->FileName.c_str(),1);
  }
  delete dlg;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MN_WeighStatClick(TObject *Sender)
{ TOpenDialog *dlg=new TOpenDialog(this);
  dlg->Title="打开统计报表文件...";
  dlg->Filter = "报表文件|s-*.xls";
  dlg->InitialDir=ExtractFilePath(Application->ExeName)+DIRECTORY_PICI;
  if(dlg->Execute())
  {  ExcelOpen(dlg->FileName.c_str(),1);
  }
  delete dlg;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MN_WeighLogsClick(TObject *Sender)
{ TOpenDialog *dlg=new TOpenDialog(this);
  dlg->Title="打开原始记录文件...";
  dlg->Filter = "记录文件|w-*.xls";
  dlg->InitialDir=ExtractFilePath(Application->ExeName)+DIRECTORY_PICI;
  if(dlg->Execute())
  {  ExcelOpen(dlg->FileName.c_str(),1);
  }
  delete dlg;
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::MN_ProductParamClick(TObject *Sender)
{ TOpenDialog *dlg=new TOpenDialog(this);
  dlg->Title="打开产品参数记录文件...";
  dlg->Filter = "产品参数文件|*.xls";
  dlg->InitialDir=ExtractFilePath(Application->ExeName)+DIRECTORY_PRODUCT_PARAMS;
  if(dlg->Execute())
  { ExcelOpen(dlg->FileName.c_str(),1);
  }
  delete dlg;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MN_ProductCatalogClick(TObject *Sender)
{ TOpenDialog *dlg=new TOpenDialog(this);
  dlg->Title="打开产品目录记录文件...";
  dlg->Filter = "产品目录文件|*.xls";
  dlg->InitialDir=ExtractFilePath(Application->ExeName)+DIRECTORY_PRODUCT_CATALOG;
  if(dlg->Execute())
  { ExcelOpen(dlg->FileName.c_str(),1);
  }
  delete dlg;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MN_ProductTestClick(TObject *Sender)
{ TOpenDialog *dlg=new TOpenDialog(this);
  dlg->Title="打开产品测试记录文件...";
  dlg->Filter ="产品测试记录文件|*.xls";
  dlg->InitialDir=ExtractFilePath(Application->ExeName)+DIRECTORY_PRODUCT_TEST;
  if(dlg->Execute())
  { ExcelOpen(dlg->FileName.c_str(),1);
  }
  delete dlg;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MN_DeviceParamClick(TObject *Sender)
{ TOpenDialog *dlg=new TOpenDialog(this);
  dlg->Title="打开设备参数记录文件...";
  dlg->Filter ="设备参数文件|*.xls";
  dlg->InitialDir=ExtractFilePath(Application->ExeName)+DIRECTORY_DEVICE_PARAMS;
  if(dlg->Execute())
  { ExcelOpen(dlg->FileName.c_str(),1);
  }
  delete dlg;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MN_WeighTestClick(TObject *Sender)
{  if(conn_mode==0 ||comm_open(true))
   { comm_zeroweight();
     this->Hide();
     FormWeighTest=new TFormWeighTest(Application);
     FormWeighTest->ShowModal();
     FormWeighTest=NULL;
     comm_open(false);
     this->Show();
   }
   else
   {  Application->MessageBox("通信连接失败，请检查通信接口及参数配置！","提醒",MB_OK|MB_ICONSTOP);
   }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MN_StaticWeighClick(TObject *Sender)
{  if(conn_mode==0||comm_open(true))
   { this->Hide();
     FormStatic=new TFormStatic(Application);
     FormStatic->ShowModal();
     FormStatic=NULL;
     comm_open(false);
     this->Show();
   }
   else
   {  Application->MessageBox("通信连接失败，请检查通信接口及参数配置！","提醒",MB_OK|MB_ICONSTOP);
   }

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormClose(TObject *Sender,
      TCloseAction &Action)
{ comm_open(false);
}
//------------------------------------------------------------------------------
void __fastcall TFormMain::MN_SearchClick(TObject *Sender)
{ /* this->Hide();
  FormWeighLogs=new TFormWeighLogs(Application);
  FormWeighLogs->ShowModal();
  FormWeighLogs=NULL;
  this->Show();*/
  Edit_searchKey->Clear();
  ListBoxSearch->Clear();
  if(Wnd_ControlDlg(PanelSearch,"文件查找", MB_OKCANCEL)==IDOK)
  {  String filepath=ExtractFilePath(Application->ExeName)+"pici\\"+ListBoxSearch->Items->Strings[ListBoxSearch->ItemIndex];
     ExcelOpen(filepath.c_str(),1);
  }
}


//---------------------------------------------------------------------------
void __fastcall TFormMain::ListBoxSearchDblClick(TObject *Sender)
{  if(ListBoxSearch->SelCount==1)
   {  Wnd_CloseDlg(IDOK);
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Button_SeekClick(TObject *Sender)
{ TSearchRec sr;
  String searchPath=ExtractFilePath(Application->ExeName)+"pici\\";
  ListBoxSearch->Clear();
  if (FindFirst(searchPath+Edit_searchKey->Text.Trim()+"*.xls", faAnyFile , sr) == 0)
  { do
    { ListBoxSearch->AddItem(sr.Name,NULL);
    } while (FindNext(sr) == 0);
    FindClose(sr);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Edit_searchKeyKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{ if(Key==13) Button_Seek->Click();
}
//---------------------------------------------------------------------------
int GetExistSearlCOMM(unsigned char *comlist)
{ int port_count=0;
  TRegistry *Reg = new TRegistry();
  Reg->RootKey = HKEY_LOCAL_MACHINE;
  if(Reg->OpenKeyReadOnly("HARDWARE\\DEVICEMAP\\SERIALCOMM"))
  { TStringList *ts =new  TStringList;
    try
    { Reg->GetValueNames(ts);
      for(int i=0;i<ts->Count && port_count<MAX_COM_COUNT;i++)
      { String strCOM=Reg->ReadString(ts->Strings[i]);
        char *p=strCOM.c_str();
        if(p[0]=='C' && p[1]=='O' && p[2]=='M')
        { int comport=atoi(p+3)-1;
          if(comport>=0 && comport<256)
          { int pi;
            for(pi=0;pi<port_count;pi++)
            { if(comport==comlist[pi])break;
            }
            if(pi==port_count)comlist[port_count++]=comport;
          }
        }
      }
    }catch(...){}
    delete ts;
 }
 Reg->CloseKey();
 Reg->Free();
 if(port_count>0)//排序
 { for(int j=0;j<port_count;j++)
   { for (int i=0;i<port_count-j-1;i++)
     if (comlist[i]>comlist[i+1])
     { unsigned char temp=comlist[i];
       comlist[i]=comlist[i+1];
       comlist[i+1]=temp;
     }
   }
 }
 else
 { port_count=64;
   for(int j=0;j<port_count;j++)comlist[j]=j;
 }
 return  port_count;
}
//---------------------------------------------------------------------------
void TFormMain::RefreshCOMlist(void)
{ unsigned char new_comlist[MAX_COM_COUNT],new_comcount,cur_uart_port=UartDriver->PortNO;
  new_comcount=GetExistSearlCOMM(new_comlist);
  if(new_comcount!=SearlCOMM_Count || memcmp(new_comlist,SearlCOMM_List,new_comcount)!=0)
  { String OriginCOMPort=ComboBox_PortNum->Text;
    memcpy(SearlCOMM_List,new_comlist,new_comcount);
    SearlCOMM_Count=new_comcount;
    ComboBox_PortNum->Clear();
    for(int i=0;i<new_comcount;i++)
    { ComboBox_PortNum->Items->Add("COM"+IntToStr(new_comlist[i]+1));
      if(new_comlist[i]==cur_uart_port)ComboBox_PortNum->ItemIndex=i;
    }

    ComboBox_PortNum->Text=OriginCOMPort;
  }
}
//---------------------------------------------------------------------------
void TFormMain::ShowDeviceSettings()
{ bool uartMode=(RadioGroup_conn->ItemIndex==0);
  ComboBox_PortNum->Enabled=uartMode;
  ComboBox_Baudrate->Enabled=uartMode;
  ComboBox_Parity->Enabled=uartMode;
  ComboBox_Databits->Enabled=uartMode;
  ComboBox_Stopbits->Enabled=uartMode;
  Edit_ServerIP->Enabled=!uartMode;
  Edit_Serverport->Enabled=!uartMode;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RadioGroup_connClick(TObject *Sender)
{ ShowDeviceSettings();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerHbTimer(TObject *Sender)
{ if(TcpDriver->Active)
  { char buf[1]={27};
    TcpDriver->Send(buf,1);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MN_ConnectionsClick(TObject *Sender)
{ RefreshCOMlist();
  RadioGroup_conn->ItemIndex=conn_mode;
  ComboBox_Baudrate->ItemIndex=UartDriver->BaudRate;
  ComboBox_Parity->ItemIndex=UartDriver->Parity;
  ComboBox_Databits->ItemIndex=UartDriver->DataBits;
  ComboBox_Stopbits->ItemIndex=UartDriver->StopBits;
  Edit_ServerIP->Text=TcpDriver->RemoteHost;
  Edit_Serverport->Text=TcpDriver->RemotePort;
  ShowDeviceSettings();
  if(Wnd_ControlDlg(PanelConnections,"通信设置", MB_OKCANCEL)==IDOK)
  {  UartDriver->PortNO=SearlCOMM_List[ComboBox_PortNum->ItemIndex];
     UartDriver->BaudRate=ComboBox_Baudrate->ItemIndex;
     UartDriver->Parity=(TCommParity)ComboBox_Parity->ItemIndex;
     UartDriver->DataBits=(TCommDataBits)ComboBox_Databits->ItemIndex;
     UartDriver->StopBits=(TCommStopBits)ComboBox_Stopbits->ItemIndex;
     TcpDriver->RemoteHost=Edit_ServerIP->Text;
     TcpDriver->RemotePort=atoi(Edit_Serverport->Text.c_str());
     conn_mode=RadioGroup_conn->ItemIndex;
     ExecSQL("update configs set communication=%d,uart_port=%d,uart_baudrate=%d,uart_parity=%d,uart_databits=%d,uart_stopbits=%d,server_ip=%d,server_port=%d",conn_mode,UartDriver->PortNO,UartDriver->BaudRate,UartDriver->Parity,UartDriver->DataBits,UartDriver->StopBits,TcmSocket::get_ip_data(TcpDriver->RemoteHost.c_str()),TcpDriver->RemotePort);
  }
   
}

//---------------------------------------------------------------------------
String WeightToStr(float weight)
{ /*char strbuf[16];
  if(weight==0)return "0.000";
  int len=sprintf(strbuf,"%3.3f",weight);
  if(len>0)
  { for(int dotPos=0;dotPos<len;dotPos++)
    { if(strbuf[dotPos]=='.')
      {  while(--len>dotPos)
         { if(strbuf[len]=='0')strbuf[len]='\0';
           else break;
         }
        break;
      }
    }
  }else return "0";

  return (String)strbuf;  */
  if(weight==0)return "0.000";
  else
  { char strWeight[16];
    sprintf(strWeight,"%g",weight);
    return strWeight;
   // return FormatFloat("0.######",weight);
  }
}
//---------------------------------------------------------------------------
#pragma resource "res/mdb.res"
void TFormMain::InstallMDB(String path)
{  TResourceStream *FStream=new TResourceStream((int)HInstance,"mdb","CM_FILE");
   FStream->SaveToFile(path);
   delete FStream;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerIdleTimer(TObject *Sender)
{ static int idle_counter=0;
#if (DEMO_LIMIT_TIME_M>0)
 idle_counter+= ((TTimer *)Sender)->Interval;
 if(idle_counter>1000*60*DEMO_LIMIT_TIME_M)
 { ((TTimer *)Sender)->Enabled=false;
   if(FormCatalogEdit)SendMessage(FormCatalogEdit->Handle,WM_CLOSE,0,0);
   if(FormCatalog)SendMessage(FormCatalog->Handle,WM_CLOSE,0,0);
   if(FormWeighTest)SendMessage(FormWeighTest->Handle,WM_CLOSE,0,0);
   if(FormUsers)SendMessage(FormUsers->Handle,WM_CLOSE,0,0);
   if(FormStatic)SendMessage(FormStatic->Handle,WM_CLOSE,0,0);
   Application->MessageBox(("演示版本时间限制"+IntToStr(DEMO_LIMIT_TIME_M)+"分钟").c_str(),"提示",MB_OK|MB_ICONSTOP);
   Application->Terminate();
   this->Close();
 }
#else
  if(MN_Login->Visible)return;

  if(Application->Active)
  { TLastInputInfo vLastInputInfo ;
    vLastInputInfo.cbSize = sizeof(TLastInputInfo);
    GetLastInputInfo(&vLastInputInfo);
    idle_counter=GetTickCount() - vLastInputInfo.dwTime;
  }
  else
  { idle_counter+= ((TTimer *)Sender)->Interval;
  }
  if(idle_counter>g_MaxIdleTimeMS ||(!g_security && idle_counter>3*60*1000))
  { //如果没有激活密码，即使以admin账号登录，也有3分钟空闲锁定机制。 
    ((TTimer *)Sender)->Enabled=false;
    Wnd_CloseDlg(mrCancel);
    MN_Quit->Click();//注销
    if(FormPici) FormPici->LockControl(true);
    else if(FormWeighTest)FormWeighTest->LockControl(true);
    else if(FormStatic)FormStatic->LockControl(true);
    else
    {  //if(FormWeighLogs)SendMessage(FormWeighLogs->Handle,WM_CLOSE,0,0);
       if(FormCatalogEdit)SendMessage(FormCatalogEdit->Handle,WM_CLOSE,0,0);
       if(FormCatalog)SendMessage(FormCatalog->Handle,WM_CLOSE,0,0);
       if(FormUsers)SendMessage(FormUsers->Handle,WM_CLOSE,0,0);
       if(FormParams)SendMessage(FormParams->Handle,WM_CLOSE,0,0);
    }
  }
#endif
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MN_debugClick(TObject *Sender)
{ FormDebug->Show();
}
//---------------------------------------------------------------------------
//+ 1234.678 g  crlf

//---------------------------------------------------------------------------

