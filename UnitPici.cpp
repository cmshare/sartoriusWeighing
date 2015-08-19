//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "UnitMain.h"
#include "UnitPici.h"
#include "UnitCatalog.h"
#include "UnitUsers.h"
#include "UnitCatalogEdit.h"
#include "UnitWeighStat1.h"
#include "UnitWeighTest.h"
#include "UnitWeighLogs.h"
#include "UnitControlPici.h"
#include <stdio.h>
#include <Math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormPici *FormPici=NULL;
static int grayColors[3]={clWhite, clWhite,clWhite};
static int lightColors[3]={clRed,clLime,0x00dfdf};
extern int g_PiciCapacity,g_LastPiciProductID;
extern char *UNIT_CAPTIONS[4];
//---------------------------------------------------------------------------
__fastcall TFormPici::TFormPici(TComponent* Owner)
        : TForm(Owner)
{  this->Caption=PROJECT_COMPANY;
   MN_Lock->Visible=false;
   mark_panels[0]=Panel_LL;
   mark_panels[1]=Panel_TP;
   mark_panels[2]=Panel_UL;
   if(g_PiciCapacity<=0)
   { g_PiciCapacity=DefaultPiciCapacity;
   }
   bNetWeight=false;
   SecondsTimer->Interval=1000;
   Label_picitick->Caption=Now();
   qualified_counter=0;
   read_weight=0;
   totalweight=weight_maximum=weight_minimum=totalweight1=weight_minimum1=weight_maximum1=0;
   weight_values=(float *)malloc(g_PiciCapacity *sizeof(float));
   weight_times=(TDateTime *)malloc(g_PiciCapacity *sizeof(TDateTime));
   for(int i=0;i<3;i++)
   { mark_panels[i]->Color=grayColors[i];
   }
   refresh_stat();
}
//---------------------------------------------------------------------------
float weight_kg2default(float weight)
{ if(g_defaultUnit==UNIT_KG)return weight;
  else if(g_defaultUnit==UNIT_G)return weight*1000;
  else return  weight/1000;
}
//---------------------------------------------------------------------------
void __fastcall TFormPici::FormShow(TObject *Sender)
{  if(!g_CurPiciProductID)return;
   strDefaultUnit=UNIT_CAPTIONS[g_defaultUnit];

   MyQuery->SQL->Text="select * from `catalog` where id="+IntToStr(g_CurPiciProductID);
   MyQuery->Active=true;
   if(!MyQuery->Eof)
   {  correction_factor=MyQuery->FieldByName("correction_factor")->AsFloat;
      weight_tp=weight_kg2default(MyQuery->FieldByName("value_tp")->AsFloat);
      weight_ul=weight_kg2default(MyQuery->FieldByName("value_ul")->AsFloat);
      weight_ll=weight_kg2default(MyQuery->FieldByName("value_ll")->AsFloat);
      float stat_range=MyQuery->FieldByName("stat_range")->AsFloat;
      weight_range_ul=weight_ul*(stat_range+1);
      weight_range_ll=weight_ll*stat_range;
      weight_tare=weight_kg2default(MyQuery->FieldByName("preset_tare")->AsFloat);
      Label_ValueTP->Caption=WeightToStr(weight_tp)+strDefaultUnit;
      Label_ValueUL->Caption=WeightToStr(weight_ul)+strDefaultUnit;
      Label_ValueLL->Caption=WeightToStr(weight_ll)+strDefaultUnit;
      bNetWeight=MyQuery->FieldByName("gross_or_net")->AsInteger;
      SpeedButton_grossornet->Caption=bNetWeight?"N":"G";

      //  Edit_StatRange->Text=WeightToStr(MyQuery->FieldByName("stat_range")->AsFloat*100);
      //  Edit_PassRate->Text=WeightToStr(MyQuery->FieldByName("pass_rate")->AsFloat*100);
      //  Edit_PresetTare->Text=WeightToStr(MyQuery->FieldByName("preset_tare")->AsFloat);
      //->Text=FormatFloat("0.0",MyQuery->FieldByName("pack_length")->AsFloat);
   }
   MyQuery->Active=false;

   if(weight_tare)
   {
   }

   char strProductID[8];
   sprintf(strProductID,"%03d",g_CurPiciProductID);
   StaticText_ProductID->Caption=strProductID;

   Label_PiciNumber->Caption=g_piciNumber;
   refresh_stat();

   connected=FormMain->comm_open(true);
   SecondsTimer->Enabled=true;

   LabelUnit->Caption=strDefaultUnit;
   LabelUnit1->Caption=strDefaultUnit;
   LabelUnit2->Caption=strDefaultUnit;
   LabelUnit3->Caption=strDefaultUnit;
   LabelUnit4->Caption=strDefaultUnit;
   LabelUnit5->Caption=strDefaultUnit;
   LabelUnit6->Caption=strDefaultUnit;
   LabelUnit7->Caption=strDefaultUnit;
   LabelUnit8->Caption=strDefaultUnit;
   LabelUnit9->Caption=strDefaultUnit;
   LabelUnit10->Caption=strDefaultUnit;
}
//---------------------------------------------------------------------------
void TFormPici::forceCalcStat(void)
{  float average_weight=0,average_weight1=0,standardDeviation=0,standardDeviation1=0,variance=0,variance1=0;
    average_weight=(g_PiciCounter>0)?totalweight/g_PiciCounter:0.0;
    average_weight1=(qualified_counter>0)?totalweight1/qualified_counter:0.0;


     for(int i=0;i<g_PiciCounter;i++)
     {  float weight=weight_values[i];
        variance += ((average_weight-weight)*(average_weight-weight));
        if(weight>weight_ll &&  weight<weight_ul)
        { variance1+=((average_weight1-weight)*(average_weight1-weight));
        }

     }
     if(g_PiciCounter>1)standardDeviation=sqrt(variance/(g_PiciCounter-1));
     if(qualified_counter>1)standardDeviation1=sqrt(variance1/(qualified_counter-1));
     Edit_StandardDeviation->Text=FormatFloat("0.000##",standardDeviation);
     Edit_MinWeight->Text=WeightToStr(weight_minimum);
     Edit_MaxWeight->Text=WeightToStr(weight_maximum);
     Edit_totalWeight->Text=WeightToStr(totalweight);
     Edit_totalNum->Text=IntToStr(g_PiciCounter);
     Edit_QualifiedRate->Text=(g_PiciCounter>0)?FormatFloat("0.0##",100.0*qualified_counter/g_PiciCounter):(String)"0";
     Edit_Average->Text=FormatFloat("0.000##",average_weight);
     Edit_StandardDeviation1->Text=FormatFloat("0.000##",standardDeviation1);
     Edit_MinWeight1->Text=WeightToStr(weight_minimum1);
     Edit_MaxWeight1->Text=WeightToStr(weight_maximum1);
     Edit_totalWeight1->Text=WeightToStr(totalweight1);
     Edit_totalNum1->Text=IntToStr(qualified_counter);
     Edit_Average1->Text=FormatFloat("0.000##",average_weight1);
}
//---------------------------------------------------------------------------
void TFormPici::refresh_stat(void)
{ if(GroupBox_Stat1->Visible)
  { forceCalcStat();
  }
}
//---------------------------------------------------------------------------
/*void TFormPici::update_show(bool bSaveRecored)
{ String strWeight=WeightToStr(read_weight);
} */
//---------------------------------------------------------------------------
void __fastcall TFormPici::FormClose(TObject *Sender, TCloseAction &Action)
{ if(weight_values){free(weight_values);weight_values=NULL;}
  FormPici=NULL;
  SecondsTimer->Enabled=false;
}
//---------------------------------------------------------------------------
void TFormPici::UpdatePiciState(bool piciOnOff)
{  MN_StopPici->Enabled=piciOnOff;
   MN_LoadProduct->Enabled=!piciOnOff;
   MN_ResumePici->Enabled=!piciOnOff;
   MN_Close->Enabled=!piciOnOff;
   Label_PiciState->Caption=(piciOnOff)?"开始":"停止";
   FormMain->MN_WeighTest->Enabled=!piciOnOff;
 //  if(piciOnOff)FormMain->comm_zeroweight();
}
//---------------------------------------------------------------------------
void _fastcall TFormPici::Wnd_Proc(TMessage &Msg)
{  switch(Msg.Msg)
  { case WM_QUERYENDSESSION: Msg.Result=true;break;
    case MSG_WEIGH_NOTIFY:if(Msg.WParam>=0 && g_CurPiciProductID)
            { if(g_PiciCounter<g_PiciCapacity)
              { read_weight=*((float *)(&Msg.LParam));
                if(correction_factor!=1.0)
                { unsigned long int_weight=(unsigned long)(read_weight*correction_factor*1000);
                  read_weight=(float)int_weight/1000;
                }
                if(Msg.WParam!=g_defaultUnit)
                { if(g_defaultUnit==UNIT_KG)
                  { if(Msg.WParam==UNIT_G) read_weight/=1000;
                    else read_weight*=1000;
                  }
                  else if(g_defaultUnit==UNIT_G)
                  { if(Msg.WParam==UNIT_KG) read_weight*=1000;
                    else read_weight*=1000000;
                  }
                  else// if(g_defaultUnit==UNIT_T)
                  { if(Msg.WParam==UNIT_KG) read_weight/=1000;
                    else read_weight/=1000000;
                  }
                }

                if(bNetWeight && weight_tare!=0)
                {  Label_Weight->Caption=WeightToStr(read_weight-weight_tare);
                }
                else
                {  Label_Weight->Caption=WeightToStr(read_weight);
                }

                if(read_weight<weight_range_ul && read_weight>weight_range_ll)
                { weight_values[g_PiciCounter]=read_weight;
                  weight_times[g_PiciCounter]=Now();
                  g_PiciCounter++;
                  if(g_PiciCounter==1)
                  { weight_maximum=weight_minimum=read_weight;
                  }
                  else
                  { if(read_weight<weight_minimum)weight_minimum=read_weight;
                     else if(read_weight>weight_maximum)weight_maximum=read_weight;
                  }
                  totalweight+=read_weight;
                }

                int weight_level;
                if(read_weight<weight_ll)weight_level=0;
                else if(read_weight>weight_ul)weight_level=2;
                else
                { weight_level=1;
                  if(++qualified_counter==1)
                  { weight_maximum1=weight_minimum1=read_weight;
                  }
                  else
                  { if(read_weight<weight_minimum1)weight_minimum1=read_weight;
                    else if(read_weight>weight_maximum1)weight_maximum1=read_weight;
                  }
                  totalweight1+=read_weight;
                }
                for(int i=0;i<3;i++)
                { mark_panels[i]->Color=(i==weight_level)?lightColors[i]:grayColors[i];
                }
                refresh_stat();
              }
              else if(g_PiciCounter==g_PiciCapacity)
              { ShowMessage("已经连续称重完成"+IntToStr(g_PiciCounter)+"次！");
                MN_StopPici->Click();
              }
            }
            break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPici::MN_StopPiciClick(TObject *Sender)
{ if(Query_StopPici())
  { UpdatePiciState(false);
    if(!g_piciNumber.IsEmpty())
    { forceCalcStat();
      GenOriginalRecordFile();
      GenStatFile();
      GenFinalReportFile();
    }
    g_CurPiciProductID=0;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPici::MN_ResumePiciClick(TObject *Sender)
{ if(FormMain->comm_open(true))
  { //断点恢复之前的批次
    g_CurPiciProductID=g_LastPiciProductID;
    UpdatePiciState(true);
  }
  else  ShowMessage("通信连接失败，请检查通信接口及参数配置！");
}
//---------------------------------------------------------------------------
void __fastcall TFormPici::MN_CloseClick(TObject *Sender)
{  if(Application->MessageBox(("确定结束批次"+g_piciNumber).c_str(),"提醒",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
     this->Close();
}
//---------------------------------------------------------------------------
void TextAppendBlank(char *str,int len)
{ int origin_len=strlen(str);
  if(origin_len<len)
  { for(int i=origin_len;i<len;i++)
    {  str[i]=' ';
    }
    str[len]='\0';
  }
}

#define HALF_LINE_WIDTH  40
void TFormPici::GenStatFile(void)
{ extern char *xlsHead;
  char pbuf[128];
  extern String g_curStatFile,g_piciNumber,g_piciOperator,g_piciProductLine,g_piciProductCode,g_piciCheckweigher,g_piciProductName;
  extern TDateTime piciStartTime,piciOverTime;
  if(FileExists(g_curStatFile))
  { int fileAttr= FileGetAttr(g_curStatFile);
    if((fileAttr & faReadOnly)!=0)FileSetAttr(g_curStatFile,fileAttr&~faReadOnly);
  }
  FILE *f=fopen(g_curStatFile.c_str(),"wb");
  if(!f)return;

  fprintf(f,"%s\r\n",xlsHead);
  fprintf(f,"<center><strong><font size=4>%03d统计报表</font></strong></center>",g_CurPiciProductID);
  fprintf(f,"<table width=640 border=1>\r\n");
  fprintf(f,"<tr align=center><td align=right bgcolor=#DFDFDF>生产线号：</td><td>%s</td><td align=right bgcolor=#DFDFDF>产品编号：</td><td>%s</td><td bgcolor=#DFDFDF align=right>批次号：</td><td>%s</td></tr>\r\n",g_piciProductLine.c_str(),g_piciProductCode.c_str(),g_piciNumber.c_str());
  fprintf(f,"<tr align=center><td align=right bgcolor=#DFDFDF>检重秤号：</td><td>%s</td><td align=right bgcolor=#DFDFDF>产品名称：</td><td>%s</td><td bgcolor=#DFDFDF align=right>操作员：</td><td>%s</td></tr>\r\n",g_piciCheckweigher.c_str() ,g_piciProductName.c_str() ,g_piciOperator.c_str());

  fprintf(f,"<tr><td colspan=6></td></tr>");
  fprintf(f,"<tr bgcolor=#DFDFDF align=center><td colspan=2>全部产品</td><td colspan=2>合格产品</td><td colspan=2>不合格产品</td></tr>\r\n");
  fprintf(f,"<tr align=center><td align=right>数量合计：</td><td>%dpcs</td><td align=right>数量合计：</td><td>%dpcs</td><td align=right>数量合计：</td><td>%dpcs</td></tr>\r\n",g_PiciCounter,qualified_counter,g_PiciCounter-qualified_counter);
  fprintf(f,"<tr align=center><td align=right>重量总计：</td><td>%s%s</td><td align=right>重量总计：</td><td>%s%s</td><td align=right>重量总计：</td><td>%s%s</td></tr>\r\n",Edit_totalWeight->Text.c_str(),strDefaultUnit.c_str(),Edit_totalWeight1->Text.c_str(),strDefaultUnit.c_str(),WeightToStr(totalweight-totalweight1).c_str(),strDefaultUnit.c_str());

  int ll_count=0;
  for(int i=0;i<g_PiciCounter;i++){if(weight_values[i]<weight_ll)ll_count++;}
  fprintf(f,"<tr align=center><td align=right>标准偏差：</td><td>%s%s</td><td align=right>标准偏差：</td><td>%s%s</td><td align=right>超下限数量合计：</td><td>%dpcs</td></tr>\r\n",Edit_StandardDeviation->Text.c_str(),strDefaultUnit.c_str(),Edit_StandardDeviation1->Text.c_str(),strDefaultUnit.c_str(),ll_count);
  fprintf(f,"<tr align=center><td align=right>平均值：</td><td>%s%s</td><td align=right>平均值：</td><td>%s%s</td><td align=right>超上限数量合计：</td><td>%dpcs</td></tr>\r\n",Edit_Average->Text.c_str(),strDefaultUnit.c_str(),Edit_Average1->Text.c_str(),strDefaultUnit.c_str(),g_PiciCounter-qualified_counter-ll_count);

  fprintf(f,"<tr  align=center><td align=right>最小值：</td><td>%s%s</td><td align=right>最小值：</td><td>%s%s</td><td colspan=2></td></tr>\r\n",Edit_MinWeight->Text.c_str(),strDefaultUnit.c_str(),Edit_MinWeight1->Text.c_str(),strDefaultUnit.c_str());
  fprintf(f,"<tr align=center><td align=right>最大值：</td><td>%s%s</td><td align=right>最大值：</td><td>%s%s</td><td colspan=2></td></tr>\r\n",Edit_MaxWeight->Text.c_str(),strDefaultUnit.c_str(),Edit_MaxWeight1->Text.c_str(),strDefaultUnit.c_str());
  fprintf(f,"<tr align=center><td align=right>合格率：</td><td>%s%%</td><td colspan=4></td></tr>\r\n",Edit_QualifiedRate->Text.c_str());

  fprintf(f,"<tr><td colspan=6></td></tr>");
  fprintf(f,"<tr align=center><td align=right>批次开始时间：</td><td>%s</td><td colspan=4></td></tr>\r\n",DateTimeToStr(piciStartTime).c_str());
  fprintf(f,"<tr align=center><td align=right>批次结束时间：</td><td>%s</td><td colspan=4></td></tr>\r\n",DateTimeToStr(piciOverTime).c_str());

  fprintf(f,"</table></body></html>");
  fclose(f);

  FileSetAttr(g_curStatFile, faReadOnly);
}
//---------------------------------------------------------------------------
void TFormPici::GenOriginalRecordFile(void)
{ extern char *xlsHead;
  extern String g_curPiciFile,g_piciProductDesc,g_piciNumber,g_piciOperator,g_piciProductLine,g_piciProductCode,g_piciCheckweigher,g_piciProductName;
  extern TDateTime piciStartTime,piciOverTime;
  if(FileExists(g_curPiciFile))
  { int fileAttr= FileGetAttr(g_curPiciFile);
    if((fileAttr & faReadOnly)!=0)FileSetAttr(g_curPiciFile,fileAttr&~faReadOnly);
  }
  FILE *f=fopen(g_curPiciFile.c_str(),"wb");
  if(!f)return;
  fprintf(f,"%s\r\n",xlsHead);
  fprintf(f,"<center><strong><font size=4>%03d原始记录</font></strong></center>",g_CurPiciProductID);

  fprintf(f,"<table width=640 border=1>\r\n");
  fprintf(f,"<tr align=left><td>产品编号：</td><td colspan=2>%s</td></tr>",g_piciProductCode.c_str());
  fprintf(f,"<tr align=left><td>产品名称：</td><td colspan=2>%s</td></tr>",g_piciProductName.c_str());
  fprintf(f,"<tr align=left><td>产品描述：</td><td colspan=2>%s</td></tr>",g_piciProductDesc.c_str());
  fprintf(f,"<tr align=left><td>生产线号：</td><td colspan=2>%s</td></tr>",g_piciProductLine.c_str());
  fprintf(f,"<tr align=left><td>检重秤号：</td><td colspan=2>%s</td></tr>",g_piciCheckweigher.c_str());
  fprintf(f,"<tr align=left><td>批次号：</td><td colspan=2>%s</td></tr>",g_piciNumber.c_str());
  fprintf(f,"<tr align=left><td>操作员：</td><td colspan=2>%s</td></tr>",g_piciOperator.c_str());
  #if 0
  fprintf(f,"<tr align=left><td>件数：</td><td colspan=2>%d</td></tr>",g_PiciCounter);
  #else
  if(g_PiciCapacity==DefaultPiciCapacity)
  {  fprintf(f,"<tr align=left><td>件数：</td><td colspan=2></td></tr>");
  }
  else
  { fprintf(f,"<tr align=left><td>件数：</td><td colspan=2>%d</td></tr>",g_PiciCapacity);
  }
  #endif
  fprintf(f,"<tr align=left><td>批次开始时间：</td><td colspan=2>%s</td></tr>",DateTimeToStr(piciStartTime).c_str());
  fprintf(f,"<tr align=left><td>批次结束时间：</td><td colspan=2>%s</td></tr>",DateTimeToStr(piciOverTime).c_str());
  if(g_PiciCounter>0)
  { fprintf(f,"<tr><td colspan=3></td></tr>");
    fprintf(f,"<tr bgcolor=#DFDFDF align=center><td>序号</td><td>称重值</td><td>时间</td></tr>\r\n");
    for(int i=0;i<g_PiciCounter;i++)
    { fprintf(f,"<tr align=center><td>%03d</td><td>%3.03f%s</td><td>%s</td></tr>\r\n",i+1,weight_values[i],strDefaultUnit.c_str(),DateTimeToStr(weight_times[i]).c_str());
    }
  }
  fprintf(f,"</table></body></html>");
  fclose(f);
  FileSetAttr(g_curPiciFile, faReadOnly);
}
//---------------------------------------------------------------------------
void TFormPici::GenFinalReportFile(void)
{ extern char *xlsHead;
  extern String g_curFinalReport,g_piciProductDesc,g_piciNumber,g_piciOperator,g_piciProductLine,g_piciProductCode,g_piciCheckweigher,g_piciProductName;
  extern TDateTime piciStartTime,piciOverTime;
  if(FileExists(g_curFinalReport))
  { int fileAttr= FileGetAttr(g_curFinalReport);
    if((fileAttr & faReadOnly)!=0)FileSetAttr(g_curFinalReport,fileAttr&~faReadOnly);
  }
  FILE *f=fopen(g_curFinalReport.c_str(),"wb");
  if(!f)return;
  fprintf(f,"%s\r\n",xlsHead);
  fprintf(f,"<center><strong><font size=4>%03d最终报表</font></strong></center>\r\n",g_CurPiciProductID);

  fprintf(f,"<table width=640 border=1>\r\n");
  fprintf(f,"<tr align=left><td colspan=2>产品编号：</td><td colspan=4>%s</td></tr>\r\n",g_piciProductCode.c_str());
  fprintf(f,"<tr align=left><td colspan=2>产品名称：</td><td colspan=4>%s</td></tr>\r\n",g_piciProductCode.c_str());
  fprintf(f,"<tr align=left><td colspan=2>产品描述：</td><td colspan=4>%s</td></tr>\r\n",g_piciProductDesc.c_str());
  fprintf(f,"<tr align=left><td colspan=2>生产线号：</td><td colspan=4>%s</td></tr>\r\n",g_piciProductLine.c_str());
  fprintf(f,"<tr align=left><td colspan=2>检重秤号：</td><td colspan=4>%s</td></tr>\r\n",g_piciCheckweigher.c_str());
  fprintf(f,"<tr align=left><td colspan=2>批次号：</td><td colspan=4>%s</td></tr>\r\n",g_piciNumber.c_str());
  fprintf(f,"<tr align=left><td colspan=2>操作员：</td><td colspan=4>%s</td></tr>\r\n",g_piciOperator.c_str());

  #if 0
  fprintf(f,"<tr align=left><td colspan=2>件数：</td><td colspan=4>%d</td></tr>",g_PiciCounter);
  #else
  if(g_PiciCapacity==DefaultPiciCapacity)
  {  fprintf(f,"<tr align=left><td colspan=2>件数：</td><td colspan=4></td></tr>");
  }
  else
  { fprintf(f,"<tr align=left><td colspan=2>件数：</td><td colspan=4>%d</td></tr>",g_PiciCapacity);
  }
  #endif
  fprintf(f,"<tr align=left><td colspan=2>批次开始时间：</td><td colspan=4>%s</td></tr>",DateTimeToStr(piciStartTime).c_str());
  fprintf(f,"<tr align=left><td colspan=2>批次结束时间：</td><td colspan=4>%s</td></tr>",DateTimeToStr(piciOverTime).c_str());
  fprintf(f,"<tr><td colspan=6></td></tr>");


  MyQuery->SQL->Text="select `configs`.*,`catalog`.* from `configs`,`catalog` where `catalog`.id="+IntToStr(g_CurPiciProductID);
  MyQuery->Active=true;

  float f_pdsd_1=CALC_PDSU(MyQuery->FieldByName("dev_ctcd")->AsFloat,MyQuery->FieldByName("dev_passrate")->AsFloat);
  float f_pdsd_2=CALC_PDSU(MyQuery->FieldByName("dev_ctcd")->AsFloat,MyQuery->FieldByName("pass_rate")->AsFloat);

  fprintf(f,"<tr align=center><td width=100 align=right>秤台长度：</td><td colspan=2>%0.03fmm</td><td width=100 align=right>通过率：</td><td colspan=2>%0.03fpcs/min</td></tr>",MyQuery->FieldByName("dev_ctcd")->AsFloat,MyQuery->FieldByName("dev_passrate")->AsFloat);
  fprintf(f,"<tr align=center><td width=100 align=right>轴间距离：</td><td colspan=2>%0.03fmm</td><td width=100 align=right>皮带速度：</td><td colspan=2>%0.3fm/min</td></tr>",MyQuery->FieldByName("dev_zjjl")->AsFloat,f_pdsd_1);
  fprintf(f,"<tr align=center><td width=100 align=right>轴直径：</td><td colspan=2>%0.03fmm</td><td width=100 align=right>实际频率：</td><td colspan=2>%0.03fHz</td></tr>",MyQuery->FieldByName("dev_zzj")->AsFloat,50.0*f_pdsd_1/MyQuery->FieldByName("dev_zdpdsd")->AsFloat);
  fprintf(f,"<tr><td colspan=6></td></tr>");

  fprintf(f,"<tr align=center><td width=100 align=right>最大皮带速度：</td><td colspan=2>%0.03fm/min</td><td width=100 align=right>最大称重：</td><td colspan=2>%0.03f%s</td></tr>",MyQuery->FieldByName("dev_zdpdsd")->AsFloat,weight_kg2default(MyQuery->FieldByName("dev_zdcz")->AsFloat),strDefaultUnit.c_str());
  fprintf(f,"<tr align=center><td width=100 align=right>最小皮带速度：</td><td colspan=2>%0.03fm/min</td><td width=100 align=right>最小称重：</td><td colspan=2>%0.03f%s</td></tr>",MyQuery->FieldByName("dev_zxpdsd")->AsFloat,weight_kg2default(MyQuery->FieldByName("dev_zxcz")->AsFloat),strDefaultUnit.c_str());
  fprintf(f,"<tr align=center><td width=100 align=right>最大频率：</td><td colspan=2>%0.03fHz</td><td width=100 align=right>显示分度：</td><td colspan=2>%0.03f%s</td></tr>",MyQuery->FieldByName("dev_zdpl")->AsFloat,weight_kg2default(MyQuery->FieldByName("dev_xsfd")->AsFloat),strDefaultUnit.c_str());
  fprintf(f,"<tr align=center><td width=100 align=right>最小频率：</td><td colspan=2>%0.03fHz</td><td width=100 align=right>显示单位：</td><td colspan=2>%s</td></tr>",MyQuery->FieldByName("dev_zxpl")->AsFloat,(MyQuery->FieldByName("dev_autozero")->AsInteger)?"g":"kg");
  fprintf(f,"<tr><td colspan=6></td></tr>");

  fprintf(f,"<tr align=center><td align=right>目标值：</td><td colspan=2>%0.03f%s</td><td align=right>通过率：</td><td colspan=2>%0.03fpcs/min</td></tr>\r\n",weight_tp,strDefaultUnit.c_str(),MyQuery->FieldByName("pass_rate")->AsFloat);
  fprintf(f,"<tr align=center><td align=right>下限值：</td><td colspan=2>%0.03f%s</td><td align=right>皮带速度：</td><td colspan=2>%0.03fm/min</td></tr>\r\n",weight_ll,strDefaultUnit.c_str(),f_pdsd_2);
  fprintf(f,"<tr align=center><td align=right>上限值：</td><td colspan=2>%0.03f%s</td><td align=right>修正系数：</td><td colspan=2>%0.03fm/min</td></tr>\r\n",weight_ul,strDefaultUnit.c_str(),MyQuery->FieldByName("correction_factor")->AsFloat);
  fprintf(f,"<tr><td colspan=6></td></tr>");

  fprintf(f,"<tr align=center><td align=right>剔除等待时间：</td><td colspan=2>%ds</td><td align=right>统计范围：</td><td colspan=2>%0.03f%%</td></tr>\r\n",MyQuery->FieldByName("tc_waittime")->AsInteger,MyQuery->FieldByName("stat_range")->AsFloat*100);
  fprintf(f,"<tr align=center><td align=right>剔除动作时间：</td><td colspan=2>%ds<td align=right>包装长度：</td><td colspan=2>%0.03fmm</td></tr>\r\n",MyQuery->FieldByName("tc_actiontime")->AsInteger,MyQuery->FieldByName("pack_length")->AsFloat);
  fprintf(f,"<tr align=center><td align=right>称重显示模式：</td><td colspan=2>%s<td align=right>预置皮重：</td><td colspan=2>%0.03f%s</td></tr>\r\n",(MyQuery->FieldByName("gross_or_net")->AsInteger==0)?"Gross":"Net",weight_kg2default(MyQuery->FieldByName("preset_tare")->AsFloat),strDefaultUnit.c_str());
  fprintf(f,"<tr><td colspan=6></td></tr>");

  fprintf(f,"<tr bgcolor=#DFDFDF align=center><td colspan=2>全部产品</td><td colspan=2>合格产品</td><td colspan=2>不合格产品</td></tr>\r\n");
  fprintf(f,"<tr align=center><td align=right>数量合计：</td><td>%dpcs</td><td align=right>数量合计：</td><td>%dpcs</td><td align=right>数量合计：</td><td>%dpcs</td></tr>\r\n",g_PiciCounter,qualified_counter,g_PiciCounter-qualified_counter);
  fprintf(f,"<tr align=center><td align=right>重量总计：</td><td>%s%s</td><td align=right>重量总计：</td><td>%s%s</td><td align=right>重量总计：</td><td>%s%s</td></tr>\r\n",Edit_totalWeight->Text.c_str(),strDefaultUnit.c_str(),Edit_totalWeight1->Text.c_str(),strDefaultUnit.c_str(),WeightToStr(totalweight-totalweight1).c_str(),strDefaultUnit.c_str());

  int ll_count=0;
  for(int i=0;i<g_PiciCounter;i++){if(weight_values[i]<weight_ll)ll_count++;}
  fprintf(f,"<tr align=center><td align=right>标准偏差：</td><td>%s%s</td><td align=right>标准偏差：</td><td>%s%s</td><td align=right>超下限数量合计：</td><td>%dpcs</td></tr>\r\n",Edit_StandardDeviation->Text.c_str(),strDefaultUnit.c_str(),Edit_StandardDeviation1->Text.c_str(),strDefaultUnit.c_str(),ll_count);
  fprintf(f,"<tr align=center><td align=right>平均值：</td><td>%s%s</td><td align=right>平均值：</td><td>%s%s</td><td align=right>超上限数量合计：</td><td>%dpcs</td></tr>\r\n",Edit_Average->Text.c_str(),strDefaultUnit.c_str(),Edit_Average1->Text.c_str(),strDefaultUnit.c_str(),g_PiciCounter-qualified_counter-ll_count);

  fprintf(f,"<tr  align=center><td align=right>最小值：</td><td>%s%s</td><td align=right>最小值：</td><td>%s%s</td><td colspan=2></td></tr>\r\n",Edit_MinWeight->Text.c_str(),strDefaultUnit.c_str(),Edit_MinWeight1->Text.c_str(),strDefaultUnit.c_str());
  fprintf(f,"<tr align=center><td align=right>最大值：</td><td>%s%s</td><td align=right>最大值：</td><td>%s%s</td><td colspan=2></td></tr>\r\n",Edit_MaxWeight->Text.c_str(),strDefaultUnit.c_str(),Edit_MaxWeight1->Text.c_str(),strDefaultUnit.c_str());
  fprintf(f,"<tr align=center><td align=right>合格率：</td><td>%s%%</td><td colspan=4></td></tr>\r\n",Edit_QualifiedRate->Text.c_str());
  fprintf(f,"<tr><td colspan=6></td></tr>");


  MyQuery->Active=false;

   
  fprintf(f,"</table></body></html>");
  fclose(f);
  FileSetAttr(g_curFinalReport, faReadOnly);

}
//---------------------------------------------------------------------------
void __fastcall TFormPici::MN_StatMode1Click(TObject *Sender)
{ if(!GroupBox_Stat1->Visible)
  {  GroupBox_Stat1->Visible=true;
     GroupBox_Stat2->Visible=true;
     refresh_stat();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormPici::MN_StatCancelClick(TObject *Sender)
{  GroupBox_Stat1->Visible=false;
   GroupBox_Stat2->Visible=false;
}
//---------------------------------------------------------------------------
void __fastcall TFormPici::MN_LoadProductClick(TObject *Sender)
{ this->Hide();
  FormCatalog=new TFormCatalog(Application);
  switch(FormCatalog->ShowModal())
  { case RET_EDIT:
           FormCatalogEdit=new TFormCatalogEdit(Application);
           FormCatalogEdit->ShowModal();
           FormCatalogEdit=NULL;
         break;
    case RET_PICI:
           UpdatePiciState(true);
         break;
  }
  FormCatalog=NULL;
  this->Show();
}
//---------------------------------------------------------------------------
void __fastcall TFormPici::SpeedButton_PiciControlClick(TObject *Sender)
{ if(g_CurPiciProductID>0)  MN_StopPici->Click();
  else MN_ResumePici->Click();
}
//---------------------------------------------------------------------------
void __fastcall TFormPici::MN_LockClick(TObject *Sender)
{  LockControl(false);
}
//---------------------------------------------------------------------------
void TFormPici::LockControl(bool bLockOrNot)
{ if(bLockOrNot==MN_Lock->Visible)return;
   if(!bLockOrNot)
   { if(FormMain->UserLoginCheck("密码验证"))FormMain->TimerIdle->Enabled=true;
     else return;
   }
   MN_Lock->Visible=bLockOrNot;
   MN_Action->Visible=!bLockOrNot;
   FormMain->UI_update_login_state(true);
}
//---------------------------------------------------------------------------
void __fastcall TFormPici::SpeedButton_grossornetClick(TObject *Sender)
{ bNetWeight=!bNetWeight;
  ((TSpeedButton *)Sender)->Caption=bNetWeight?"N":"G";
  Label_Weight->Caption=WeightToStr((bNetWeight)?read_weight-weight_tare:read_weight);
}

//---------------------------------------------------------------------------
void __fastcall TFormPici::SecondsTimerTimer(TObject *Sender)
{  if(!connected)
   { ((TTimer *)Sender)->Enabled=false;
     UpdatePiciState(false);
     Application->MessageBox("通信连接失败，请检查通信接口及参数配置！","提示",MB_OK|MB_ICONSTOP);
     g_CurPiciProductID=0;
     this->Close();
   }
   else Label_picitick->Caption=Now();
}
//---------------------------------------------------------------------------

