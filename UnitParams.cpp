//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "UnitMain.h"
#include "UnitParams.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormParams *FormParams;
//---------------------------------------------------------------------------
__fastcall TFormParams::TFormParams(TComponent* Owner)
        : TForm(Owner)
{ this->Caption=PROJECT_COMPANY;
}
/*只有皮带速度是算出来的，
其它都是输入。皮带速度 =   (秤台长度  X 通过率)/1000 X1.1  米/分钟 （m/min）
秤台长度：毫米（mm）  （输入值）
通过率：件数/分钟（ pcs/min）（输入值）*/
//---------------------------------------------------------------------------
void __fastcall TFormParams::MN_CloseClick(TObject *Sender)
{ this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormParams::FormShow(TObject *Sender)
{  MN_Print->Enabled=(g_usergrade>USER_GRADE_OPERATOR);

   MyQuery->SQL->Text="select * from `configs` ";
   MyQuery->Active=true;
   if(!MyQuery->Eof)
   {   Edit_ctcd->Text=FormatFloat("0.###",MyQuery->FieldByName("dev_ctcd")->AsFloat);
       Edit_passrate->Text=FormatFloat("0.###",MyQuery->FieldByName("dev_passrate")->AsFloat);
       Edit_zjjl->Text=FormatFloat("0.###",MyQuery->FieldByName("dev_zjjl")->AsFloat);
       Edit_zzj->Text=FormatFloat("0.###",MyQuery->FieldByName("dev_zzj")->AsFloat);
      // Edit_zxclsj->Text=FormatFloat("0.###",MyQuery->FieldByName("dev_zxclsj")->AsFloat);
       Edit_zdpdsd->Text=FormatFloat("0.###",MyQuery->FieldByName("dev_zdpdsd")->AsFloat);
       Edit_zxpdsd->Text=FormatFloat("0.###",MyQuery->FieldByName("dev_zxpdsd")->AsFloat);
       Edit_zdpl->Text=50.0;//FormatFloat("0.###",MyQuery->FieldByName("dev_zdpl")->AsFloat);
       Edit_zxpl->Text=FormatFloat("0.###",MyQuery->FieldByName("dev_zxpl")->AsFloat);
       Edit_zdcz->Text=FormatFloat("0.###",MyQuery->FieldByName("dev_zdcz")->AsFloat);
       Edit_zxcz->Text=FormatFloat("0.###",MyQuery->FieldByName("dev_zxcz")->AsFloat);
       Edit_xsfd->Text=FormatFloat("0.###",MyQuery->FieldByName("dev_xsfd")->AsFloat);
       ComboBox_autozero->ItemIndex=MyQuery->FieldByName("dev_autozero")->AsInteger;
   }
   MyQuery->Active=false;
   input_enalbe(false);
}
//---------------------------------------------------------------------------
void TFormParams::input_enalbe(bool bEnable)
{  Edit_ctcd->Enabled=bEnable;
   Edit_passrate->Enabled=bEnable;
   Edit_zjjl->Enabled=bEnable;
   Edit_zzj->Enabled=bEnable;
  // Edit_zxclsj->Enabled=bEnable;
   Edit_zdpdsd->Enabled=bEnable;
   Edit_zxpdsd->Enabled=bEnable;
   Edit_zdpl->Enabled=false;
   Edit_zxpl->Enabled=false;
   Edit_zdcz->Enabled=bEnable;
   Edit_zxcz->Enabled=bEnable;
   Edit_xsfd->Enabled=bEnable;
   ComboBox_autozero->Enabled=bEnable;
   MN_Save->Enabled=bEnable;
   MN_Modify->Enabled=!bEnable && MN_Print->Enabled;
}
//---------------------------------------------------------------------------
void __fastcall TFormParams::OnCtcdChanged(TObject *Sender)
{  String ctcd=Edit_ctcd->Text.Trim(),passrate=Edit_passrate->Text.Trim(),zd_pdsd=Edit_zdpdsd->Text.Trim(),zx_pdsd=Edit_zxpdsd->Text.Trim();
   if(!ctcd.IsEmpty() && !passrate.IsEmpty())
   { float pdsd=CALC_PDSU(atof(ctcd.c_str()),atof(passrate.c_str()));
     Edit_pdsd->Text=FormatFloat("0.000",pdsd);
    //  Edit_sjpl->Text=FormatFloat("0.000",50.0*pdsd/87.5);
     if(!zd_pdsd.IsEmpty())Edit_sjpl->Text=FormatFloat("0.000",50.0*pdsd/atof(zd_pdsd.c_str()));
   }

   if(!zd_pdsd.IsEmpty() && !zx_pdsd.IsEmpty())
   { Edit_zxpl->Text=FormatFloat("0.000",50.0*atof(zx_pdsd.c_str())/atof(zd_pdsd.c_str()));
   }

}
//---------------------------------------------------------------------------
void __fastcall TFormParams::MN_SaveClick(TObject *Sender)
{  input_enalbe(false);
   ExecSQL("update configs set dev_ctcd=%f,dev_passrate=%f,dev_zjjl=%f,dev_zzj=%f,dev_zdpdsd=%f, dev_zxpdsd=%f, dev_zdpl=%f, dev_zxpl=%f, dev_zdcz=%f, dev_zxcz=%f, dev_xsfd=%f, dev_autozero=%d",
atof(Edit_ctcd->Text.Trim().c_str()),atof(Edit_passrate->Text.Trim().c_str()),atof(Edit_zjjl->Text.Trim().c_str()),atof(Edit_zzj->Text.Trim().c_str()), atof(Edit_zdpdsd->Text.Trim().c_str()),
   atof(Edit_zxpdsd->Text.Trim().c_str()),atof(Edit_zdpl->Text.Trim().c_str()),atof(Edit_zxpl->Text.Trim().c_str()),atof(Edit_zdcz->Text.Trim().c_str()),atof(Edit_zxcz->Text.Trim().c_str()),atof(Edit_xsfd->Text.Trim().c_str()),ComboBox_autozero->ItemIndex);

   g_defaultUnit=(ComboBox_autozero->ItemIndex)?UNIT_G:UNIT_KG;
   Application->MessageBox("保存成功！","提示",MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TFormParams::MN_ModifyClick(TObject *Sender)
{ input_enalbe(true);
}
//---------------------------------------------------------------------------

void __fastcall TFormParams::EditNum_KeyPress(TObject *Sender, char &Key)
{ if ((Key<'0' || Key>'9') && Key!='.' && Key!=8) Key=0;
}
//---------------------------------------------------------------------------
void QueryToExcel_DevParams(String  strTitle,String  strPath)
{ FormParams->DevParamsToHTML(strTitle,strPath);
}
//---------------------------------------------------------------------------
void TFormParams::DevParamsToHTML(String strTitle,String strPath)
{ extern char *xlsHead;
  FILE *f=fopen(strPath.c_str(),"wb");
  fprintf(f,"%s\r\n",xlsHead);
  fprintf(f,"<center><strong><font size=4>设备参数：</font></strong></center>");
  fprintf(f,"<table width=640 border=1>\r\n");


  fprintf(f,"<tr align=center><td width=100 align=right>秤台长度：</td><td>%smm</td><td width=100 align=right>通过率：</td><td>%spcs/min</td></tr>",Edit_ctcd->Text.c_str(),Edit_passrate->Text.c_str());
  fprintf(f,"<tr align=center><td width=100 align=right>轴间距离：</td><td>%smm</td><td width=100 align=right>皮带速度：</td><td>%sm/min</td></tr>",Edit_zjjl->Text.c_str(),Edit_pdsd->Text.c_str());
  fprintf(f,"<tr align=center><td width=100 align=right>轴直径：</td><td>%smm</td><td width=100 align=right>实际频率：</td><td>%sHz</td></tr>",Edit_zzj->Text.c_str(),Edit_sjpl->Text.c_str());
  fprintf(f,"<tr><td colspan=4></td></tr>");

  fprintf(f,"<tr align=center><td width=100 align=right>最大皮带速度：</td><td>%sm/min</td><td width=100 align=right>最大称重：</td><td>%skg</td></tr>",Edit_zdpdsd->Text.c_str(),Edit_zdcz->Text.c_str());
  fprintf(f,"<tr align=center><td width=100 align=right>最小皮带速度：</td><td>%sm/min</td><td width=100 align=right>最小称重：</td><td>%skg</td></tr>",Edit_zxpdsd->Text.c_str(),Edit_zxcz->Text.c_str());
  fprintf(f,"<tr align=center><td width=100 align=right>最大频率：</td><td>%sHz</td><td width=100 align=right>显示分度：</td><td>%skg</td></tr>",Edit_zdpl->Text.c_str(),Edit_xsfd->Text.c_str());
  fprintf(f,"<tr align=center><td width=100 align=right>最小频率：</td><td>%sHz</td><td width=100 align=right>显示单位：</td><td>%s</td></tr>",Edit_zxpl->Text.c_str(),ComboBox_autozero->Text.c_str());
  fprintf(f,"</table>");

  fprintf(f,"</body></html>");
  fclose(f);
}
//---------------------------------------------------------------------------
void __fastcall TFormParams::MN_PrintClick(TObject *Sender)
{ extern void ExcelOpen_DevParams(String);
  String xlsfile=ExtractFilePath(Application->ExeName)+DIRECTORY_DEVICE_PARAMS+"\\device.xls";
  ExcelOpen_DevParams(xlsfile);

}
//---------------------------------------------------------------------------


