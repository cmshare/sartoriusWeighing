//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include "UnitMain.h"
#include "UnitCatalog.h"
#include "UnitCatalogEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormCatalogEdit *FormCatalogEdit;
int g_CurrentProductID=0;
static saved_ProductID=0;
static bool editor_changed=false;

//---------------------------------------------------------------------------
__fastcall TFormCatalogEdit::TFormCatalogEdit(TComponent* Owner)
        : TForm(Owner)
{ this->Caption=PROJECT_COMPANY;

   MyQuery->SQL->Text="select dev_ctcd from `configs` ";
   MyQuery->Active=true;
   dev_ctcd=MyQuery->FieldByName("dev_ctcd")->AsFloat;
   MyQuery->Active=true;
}
//---------------------------------------------------------------------------
int TFormCatalogEdit::get_next_emptyID(void)
{  int new_id=0;
    MyQuery->SQL->Text="select min(id)  from `catalog` where (name='' or name is null) and id>"+IntToStr(g_CurrentProductID);
    MyQuery->Active=true;
    if(!MyQuery->Eof)
    { new_id=MyQuery->Fields->Fields[0]->AsInteger;
    }
   MyQuery->Active=false;
   return new_id;
}

int TFormCatalogEdit::get_prev_ProductID(void)
{  int new_id=0;
    MyQuery->SQL->Text="select max(id)  from `catalog` where (name<>'' and name is not null) and id<"+IntToStr(g_CurrentProductID);
    MyQuery->Active=true;
    if(!MyQuery->Eof)
    { new_id=MyQuery->Fields->Fields[0]->AsInteger;
    }
   MyQuery->Active=false;
   return new_id;
}
//---------------------------------------------------------------------------
void __fastcall TFormCatalogEdit::FormShow(TObject *Sender)
{  MN_Delete->Enabled=(g_usergrade>USER_GRADE_OPERATOR);

   MN_PrintExcel->Enabled= MN_Delete->Enabled;
   MN_Next->Visible=g_directNewCatalog;
   MN_Previous->Visible=g_directNewCatalog;


   g_directNewCatalog=true;

   if(g_CurrentProductID==0) g_CurrentProductID=get_next_emptyID();

   ShowProduct();
   input_enable((g_usergrade>USER_GRADE_OPERATOR)&&(MN_Next->Visible || Edit_Name->Text.IsEmpty()));

}
//---------------------------------------------------------------------------
void TFormCatalogEdit::ShowProduct(void)
{ if(g_CurrentProductID>0)
  { MyQuery->SQL->Text="select * from `catalog` where id="+IntToStr(g_CurrentProductID);
    MyQuery->Active=true;
    if(!MyQuery->Eof)
    { char strTitle[20];
      sprintf(strTitle,"%03d 产品参数",g_CurrentProductID);
      PanelTop->Caption=strTitle;
      Edit_Name->Text=MyQuery->FieldByName("name")->AsString;
      if(Edit_Name->Text.IsEmpty())
      { Edit_Description->Clear();
        Edit_Code->Clear();
        Edit_ValueTP->Clear();
        Edit_ValueUL->Clear();
        Edit_ValueLL->Clear();
        Edit_StatRange->Clear();
        Edit_PassRate->Clear();
        Edit_PresetTare->Clear();
        Edit_PackLength->Clear();
        Edit_tcWaittime->Clear();
        Edit_tcActiontime->Clear();
        Edit_correctionFactor->Text="1.0";
        Edit_pdsd->Clear();
        ComboBox_mode->ItemIndex=0;
      }
      else
      { Edit_Description->Text=MyQuery->FieldByName("description")->AsString;
        Edit_Code->Text=MyQuery->FieldByName("code")->AsString;
        Edit_ValueTP->Text=FormatFloat("0.#####",MyQuery->FieldByName("value_tp")->AsFloat);
        Edit_ValueUL->Text=FormatFloat("0.#####",MyQuery->FieldByName("value_ul")->AsFloat);
        Edit_ValueLL->Text=FormatFloat("0.#####",MyQuery->FieldByName("value_ll")->AsFloat);
        Edit_StatRange->Text=FormatFloat("0.#####",MyQuery->FieldByName("stat_range")->AsFloat*100);
        Edit_PassRate->Text=FormatFloat("0.##",MyQuery->FieldByName("pass_rate")->AsFloat);
        Edit_PresetTare->Text=FormatFloat("0.#####",MyQuery->FieldByName("preset_tare")->AsFloat);
        Edit_PackLength->Text=FormatFloat("0.#####",MyQuery->FieldByName("pack_length")->AsFloat);
        Edit_correctionFactor->Text=FormatFloat("0.0##",MyQuery->FieldByName("correction_factor")->AsFloat);
        Edit_tcWaittime->Text=MyQuery->FieldByName("tc_waittime")->AsString;
        Edit_tcActiontime->Text=MyQuery->FieldByName("tc_actiontime")->AsString;
        ComboBox_mode->ItemIndex=MyQuery->FieldByName("gross_or_net")->AsInteger;

        Edit_pdsd->Text=FormatFloat("0.###",CALC_PDSU(dev_ctcd,MyQuery->FieldByName("pass_rate")->AsFloat));
      }
      editor_changed=false;
    }
    MyQuery->Active=false;
  }
}


//---------------------------------------------------------------------------
void __fastcall TFormCatalogEdit::MN_SaveClick(TObject *Sender)
{  SaveProduct();
}
//---------------------------------------------------------------------------
void TFormCatalogEdit::input_enable(bool bEnable)
{  Edit_Name->Enabled=bEnable;
   Edit_Description->Enabled=bEnable;
   Edit_Code->Enabled=bEnable;
   Edit_ValueTP->Enabled=bEnable;
   Edit_PresetTare->Enabled=bEnable;
   Edit_ValueLL->Enabled=bEnable;
   Edit_PackLength->Enabled=bEnable;
   Edit_ValueUL->Enabled=bEnable;
   Edit_StatRange->Enabled=bEnable;
   Edit_PassRate->Enabled=bEnable;
   Edit_tcWaittime->Enabled=bEnable;
   Edit_tcActiontime->Enabled=bEnable;
   ComboBox_mode->Enabled=bEnable;
   Edit_correctionFactor->Enabled=bEnable;

   MN_Save->Enabled=bEnable;
   MN_Modify->Enabled=!bEnable && MN_PrintExcel->Enabled;
}
//---------------------------------------------------------------------------
bool  TFormCatalogEdit::SaveProduct(void)
{  if(g_CurrentProductID>0)
  { if(Edit_Name->Text.Trim().IsEmpty())
    { ShowMessage("产品名称为空！");
      Edit_Name->SetFocus();
      return false;
    }
    else if(Edit_ValueTP->Text.IsEmpty())
    { ShowMessage("目标值为空！");
      Edit_ValueTP->SetFocus();
      return false;
    }
    else if(Edit_ValueUL->Text.IsEmpty())
    { ShowMessage("上限值为空！");
      Edit_ValueUL->SetFocus();
      return false;
    }
    else if(Edit_ValueLL->Text.IsEmpty())
    { ShowMessage("下限值为空！");
      Edit_ValueLL->SetFocus();
      return false;
    }
    else if(Edit_StatRange->Text.IsEmpty())
    { ShowMessage("统计范围值为空！");
      Edit_StatRange->SetFocus();
      return false;
    }

    float value_tp=atof(Edit_ValueTP->Text.c_str());
    float value_ul=atof(Edit_ValueUL->Text.c_str());
    float value_ll=atof(Edit_ValueLL->Text.c_str());
    float stat_range=atof(Edit_StatRange->Text.c_str())/100;
    float correction_factor=atof(Edit_correctionFactor->Text.c_str());
    if (correction_factor<=0)
    { ShowMessage("修正系数须大于0");
      Edit_correctionFactor->SetFocus();
      return false;
    }
    else if(value_ul<=value_tp || value_tp<=value_ll)
    { ShowMessage("须满足：上限值>目标值>下限值！");
      Edit_ValueTP->SetFocus();
      return false;
    }
    else if(stat_range<0.1 || stat_range>1.0)
    { ShowMessage("统计范围必须在10%~100%之间！");
      Edit_StatRange->SetFocus();
      return false;
    }

    MyQuery->Active=false;
    MyQuery->SQL->Text="select * from `catalog` where id="+IntToStr(g_CurrentProductID);
    MyQuery->Active=true;
    if(!MyQuery->Eof)
    { MyQuery->Edit();
      MyQuery->FieldByName("name")->AsString=Edit_Name->Text.Trim();
      MyQuery->FieldByName("description")->AsString=Edit_Description->Text.Trim();
      MyQuery->FieldByName("code")->AsString=Edit_Code->Text.Trim();
      MyQuery->FieldByName("value_tp")->AsFloat=value_tp;
      MyQuery->FieldByName("value_ul")->AsFloat=value_ul;
      MyQuery->FieldByName("value_ll")->AsFloat=value_ll;
      MyQuery->FieldByName("stat_range")->AsFloat=stat_range;
      MyQuery->FieldByName("pass_rate")->AsFloat=atof(Edit_PassRate->Text.c_str());
      MyQuery->FieldByName("preset_tare")->AsFloat=atof(Edit_PresetTare->Text.Trim().c_str());
      MyQuery->FieldByName("pack_length")->AsFloat=atof(Edit_PackLength->Text.Trim().c_str());
      MyQuery->FieldByName("tc_waittime")->AsInteger=atoi(Edit_tcWaittime->Text.Trim().c_str());
      MyQuery->FieldByName("tc_actiontime")->AsInteger=atoi(Edit_tcActiontime->Text.Trim().c_str());
      MyQuery->FieldByName("gross_or_net")->AsInteger=ComboBox_mode->ItemIndex;
      MyQuery->FieldByName("correction_factor")->AsFloat=correction_factor;
      MyQuery->FieldByName("updatetime")->AsDateTime=Now();
      MyQuery->Post();
    }
    MyQuery->Active=false;
    ShowMessage("保存成功！");
    saved_ProductID=g_CurrentProductID;
    editor_changed=false;
    input_enable(false);
    return true;
  }
  return false;
}
//---------------------------------------------------------------------------
void __fastcall TFormCatalogEdit::MN_DeleteClick(TObject *Sender)
{  if(g_CurrentProductID>0 && Application->MessageBox("确定要删除本条记录？","提醒",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
   { ExecSQL("update `catalog` set name='',code='',description='',updatetime=null where id=%u",g_CurrentProductID);
     ShowMessage("删除成功！");
     this->Close();
   }
}
//---------------------------------------------------------------------------

void __fastcall TFormCatalogEdit::MN_ExitClick(TObject *Sender)
{ if(editor_changed)
  { if(Application->MessageBox("是否保存当前产品？","提示",MB_YESNO|MB_ICONQUESTION)==IDYES)
    {  if(!SaveProduct())return;
    }
  }
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormCatalogEdit::Edit_Changed(TObject *Sender)
{ editor_changed=true;
  Edit_pdsd->Text=FormatFloat("0.#####",CALC_PDSU(dev_ctcd,atof(Edit_PassRate->Text.c_str())));
}
//---------------------------------------------------------------------------
void __fastcall TFormCatalogEdit::MN_NextClick(TObject *Sender)
{ if(editor_changed)
  { if(Application->MessageBox("是否保存当前产品？","提示",MB_YESNO|MB_ICONQUESTION)==IDYES)
    {  if(!SaveProduct())return;
    }
  }
  g_CurrentProductID=get_next_emptyID();
  if(g_CurrentProductID>0)
  { ShowProduct();
    input_enable(true);
  }
  else
  { ShowMessage("已经下翻至底！");
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormCatalogEdit::MN_PreviousClick(TObject *Sender)
{ if(editor_changed)
  { if(Application->MessageBox("是否保存当前产品？","提示",MB_YESNO|MB_ICONQUESTION)==IDYES)
    {  if(!SaveProduct())return;
    }
  }
  g_CurrentProductID=get_prev_ProductID();
  if(g_CurrentProductID>0)
  { ShowProduct();
    input_enable(false);
  }
  else
  { ShowMessage("已经上翻至顶！");
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormCatalogEdit::MN_ModifyClick(TObject *Sender)
{  input_enable(true);
}

//---------------------------------------------------------------------------
void QueryToExcel_ProductDetail(String  strTitle,String xlsfilepath)
{ FormCatalogEdit->ProductToHTML(strTitle,xlsfilepath);
}
//---------------------------------------------------------------------------
void TFormCatalogEdit::ProductToHTML(String strTitleh,String xlsfilepath)
{ extern char *xlsHead;

  FILE * f=fopen(xlsfilepath.c_str(),"wb");
  fprintf(f,"%s\r\n",xlsHead);
  fprintf(f,"<center><strong><font size=4>%03d 产品参数：</font></strong></center>",g_CurrentProductID);
  fprintf(f,"<table width=640 border=1>\r\n");

  fprintf(f,"<tr><td width=100 align=right>产品名称：</td><td colspan=3 align=left>%s</td></tr>",Edit_Name->Text.c_str());
  fprintf(f,"<tr><td width=100 align=right>产品描述：</td><td colspan=3 align=left>%s</td></tr>",Edit_Description->Text.c_str());
  fprintf(f,"<tr><td width=100 align=right>产品编号：</td><td colspan=3 align=left>%s</td></tr>",Edit_Code->Text.c_str());
  fprintf(f,"<tr><td colspan=4></td></tr>");

  fprintf(f,"<tr align=center><td width=100 align=right>目标值：</td><td>%skg</td><td width=100 align=right>通过率：</td><td>%spcs/min</td></tr>",Edit_ValueTP->Text.c_str(),Edit_PassRate->Text.c_str());
  fprintf(f,"<tr align=center><td width=100 align=right>下限值：</td><td>%skg</td><td width=100 align=right>皮带速度：</td><td>%sm/min</td></tr>",Edit_ValueLL->Text.c_str(),Edit_pdsd->Text.c_str());
  fprintf(f,"<tr align=center><td width=100 align=right>上限值：</td><td>%skg</td><td width=100 align=right>修正系数：</td><td>%s</td></tr>",Edit_ValueUL->Text.c_str(),Edit_correctionFactor->Text.c_str());
  fprintf(f,"<tr><td colspan=4></td></tr>");

  fprintf(f,"<tr align=center><td width=100 align=right>剔除等待时间：</td><td>%ss</td><td width=100 align=right>统计范围：</td><td>%s%%</td></tr>",Edit_tcWaittime->Text.c_str(),Edit_StatRange->Text.c_str());
  fprintf(f,"<tr align=center><td width=100 align=right>剔除动作时间：</td><td>%ss</td><td width=100 align=right>包装长度：</td><td>%smm</td></tr>",Edit_tcActiontime->Text.c_str(),Edit_PackLength->Text.c_str());
  fprintf(f,"<tr align=center><td width=100 align=right>称重显示模式：</td><td>%s</td><td width=100 align=right>预置皮重：</td><td>%skg</td></tr>",ComboBox_mode->Text.c_str(),Edit_PresetTare->Text.c_str());
  fprintf(f,"</table>");

  fprintf(f,"</body></html>");
  fclose(f);
}
//---------------------------------------------------------------------------
void __fastcall TFormCatalogEdit::MN_PrintExcelClick(TObject *Sender)
{ extern void ExcelOpen_ProductDetail(String);
  String  xlsfilepath=ExtractFilePath(Application->ExeName)+DIRECTORY_PRODUCT_PARAMS+"\\P-"+FormatFloat("000",g_CurrentProductID)+".xls";//NewTempXlsFile();
  ExcelOpen_ProductDetail(xlsfilepath);
}
//---------------------------------------------------------------------------

void __fastcall TFormCatalogEdit::EditNum_KeyPress(TObject *Sender,
      char &Key)
{  if ((Key<'0' || Key>'9') && Key!='.' && Key!=8) Key=0;

}
//---------------------------------------------------------------------------

