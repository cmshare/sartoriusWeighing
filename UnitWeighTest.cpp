//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include <Math.h>
#include "UnitMain.h"
#include "UnitWeighTest.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormWeighTest *FormWeighTest=NULL;
char *UNIT_CAPTIONS[4]={"?","kg","g","t"};
//---------------------------------------------------------------------------
__fastcall TFormWeighTest::TFormWeighTest(TComponent* Owner)
        : TForm(Owner)
{ this->Caption=PROJECT_COMPANY;
  curUnit=UNIT_KG;
  Timer1->Enabled=false;
  Timer1->Interval=500;

  MyQuery->SQL->Text="select dev_ctcd,dev_passrate from `configs` ";
  MyQuery->Active=true;
  Edit_pdsd->Text=FormatFloat("0.#####",CALC_PDSU(MyQuery->FieldByName("dev_ctcd")->AsFloat,MyQuery->FieldByName("dev_passrate")->AsFloat));
  MyQuery->Active=true;

  weight_static=-1;
}
//---------------------------------------------------------------------------
void __fastcall TFormWeighTest::FormShow(TObject *Sender)
{  MN_Clear->Click();
   connected=FormMain->comm_open(true);
   if(!connected)Timer1->Enabled=true;

   strDefaultUnit=UNIT_CAPTIONS[g_defaultUnit];
   LabelUnit->Caption=strDefaultUnit;
   LabelUnit1->Caption=strDefaultUnit;
   LabelUnit2->Caption=strDefaultUnit;
   LabelUnit3->Caption=strDefaultUnit;
   LabelUnit4->Caption=strDefaultUnit;
   LabelUnit5->Caption=strDefaultUnit;
   LabelUnit6->Caption=strDefaultUnit;
}
//---------------------------------------------------------------------------
void _fastcall TFormWeighTest::Wnd_Proc(TMessage &Msg)
{  switch(Msg.Msg)
  { case WM_QUERYENDSESSION: Msg.Result=true;break;
    case MSG_WEIGH_NOTIFY:
         if(Msg.WParam>=0)
         {  float weight=*((float *)(&Msg.LParam));
            TListItem *item=ListView1->Items->Add();
            char strCounter[8];
            String strWeight=WeightToStr(weight);
            Label_Weight->Caption=strWeight;
            sprintf(strCounter,"%03d",++weight_counter);
            Edit_WeightCount->Text=strCounter;
            if(Msg.WParam!=curUnit)
            { curUnit=Msg.WParam;
              LabelUnit->Caption=UNIT_CAPTIONS[curUnit];
            }

            if(curUnit!=g_defaultUnit)
            { if(g_defaultUnit==UNIT_KG)
              { if(curUnit==UNIT_G) weight/=1000;
                else weight*=1000;
              }
              else if(g_defaultUnit==UNIT_G)
              { if(curUnit==UNIT_KG) weight*=1000;
                else weight*=1000000;
              }
              else// if(g_defaultUnit==UNIT_T)
              { if(curUnit==UNIT_KG) weight/=1000;
                else weight/=1000000;
              }
              strWeight=WeightToStr(weight);
            }

            item->Caption=strCounter;
            item->SubItems->Add(strWeight+strDefaultUnit);
            item->SubItems->Add(Now());
            weight_total+=weight;
            if(weight_counter==1)
            { weight_maximum=weight_minimum=weight;
            }
            else
            { if(weight<weight_minimum)weight_minimum=weight;
              else if(weight>weight_maximum)weight_maximum=weight;
            }
            refresh_stat();
         }
         break;
  }
}
//---------------------------------------------------------------------------
void  TFormWeighTest::refresh_stat(void)
{  float weight_average=(weight_counter)?weight_total/weight_counter:0;
   Edit_Average->Text=WeightToStr(weight_average);
   Edit_Maximum->Text=WeightToStr(weight_maximum);
   Edit_Minimum->Text=WeightToStr(weight_minimum);

   if(weight_counter<=1)Edit_StandardDeviation->Text="0";
   else
   { float variance=0;
     for(int i=0;i<weight_counter;i++)
     { String strFloat=ListView1->Items->Item[i]->SubItems->Strings[0];
       float weight=atof(strFloat.c_str());
       variance=variance+ (weight_average-weight)*(weight_average-weight);
     }
     float standardDeviation=sqrt(variance/(weight_counter-1));
     Edit_StandardDeviation->Text=FormatFloat("0.#####",standardDeviation);
   }

   if(weight_static>=0)
   { Edit1_Deviation1->Text=FormatFloat("0.####",weight_maximum-weight_static);
     if(weight_maximum>weight_static)Edit1_Deviation1->Text="+"+Edit1_Deviation1->Text;
     Edit1_Deviation2->Text=FormatFloat("0.####",weight_minimum-weight_static);
     if(weight_minimum>weight_static)Edit1_Deviation2->Text="+"+Edit1_Deviation2->Text;
   }
   else
   { Edit1_Deviation1->Clear();
     Edit1_Deviation2->Clear();
     Edit_Static->Clear();
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormWeighTest::MN_CloseClick(TObject *Sender)
{  this->Close();

}
//---------------------------------------------------------------------------
void TFormWeighTest::TestWeightToHTML(String  strTitle,String  strPath)
{ extern char *xlsHead;
  int fieldcount=ListView1->Columns->Count;
  int rowcount=ListView1->Items->Count;
  FILE * f=fopen(strPath.c_str(),"wb");
  fprintf(f,"%s\r\n",xlsHead);
  fprintf(f,"<center><strong><font size=4>%s</font></strong></center>",strTitle.c_str());
  fprintf(f,"<table width=640 border=1><tr bgcolor=#DFDFDF>\r\n");
  for(int i=0;i<fieldcount;i++)
  { if(i==2)fprintf(f,"<td colspan=2 align=center><strong>%s</strong></td>\r\n",ListView1->Columns->Items[i]->Caption.c_str());
    else fprintf(f,"<td align=\"center\"><strong>%s</strong></td>\r\n",ListView1->Columns->Items[i]->Caption.c_str());
  }
  fprintf(f,"</tr>\r\n");
  for(int j=0;j<rowcount;j++)
  { fprintf(f,"<tr>\r\n");
    for(int i=0;i<fieldcount;i++)
    { String cellText=(i==0)?ListView1->Items->Item[j]->Caption:ListView1->Items->Item[j]->SubItems->Strings[i-1];
      if(i==2) fprintf(f,"<td align=center colspan=2>%s</td>\r\n",cellText.c_str());    
      else fprintf(f,"<td align=\"center\">%s</td>\r\n",cellText.c_str());
    }
    fprintf(f,"</tr>\r\n");
  }

  fprintf(f,"<tr><td colspan=4></td></tr>");
  fprintf(f,"<tr><td colspan=4></td></tr>");

  fprintf(f,"<tr align=center><td align=right>标准偏差：</td><td>%s%s</td><td align=right>平均值：</td><td>%s%s</td></tr>\r\n",Edit_StandardDeviation->Text.c_str(),strDefaultUnit.c_str(),Edit_Average->Text.c_str(),strDefaultUnit.c_str());
  fprintf(f,"<tr align=center><td align=right>皮带速度：</td><td>%sm/min</td><td align=right>最大值：</td><td>%s%s</td></tr>\r\n",Edit_pdsd->Text.c_str(),Edit_Maximum->Text.c_str(),strDefaultUnit.c_str());
  fprintf(f,"<tr align=center><td align=right>件数：</td><td>%spcs</td><td align=right>最小值：</td><td>%s%s</td></tr>\r\n",Edit_WeightCount->Text.c_str(),Edit_Minimum->Text.c_str(),strDefaultUnit.c_str());
  fprintf(f,"<tr align=center><td align=right>±偏差：</td><td>%s %s%s</td><td align=right>静态重量：</td><td>%s%s</td></tr>\r\n",Edit1_Deviation1->Text.c_str(),Edit1_Deviation2->Text.c_str(),strDefaultUnit.c_str(),Edit_Static->Text.c_str(),strDefaultUnit.c_str());

  fprintf(f,"</table>");

  fprintf(f,"</body></html>");
  fclose(f);
}
//---------------------------------------------------------------------------
void QueryToExcel_TestWeight(String  strTitle,String  strPath)
{ FormWeighTest->TestWeightToHTML(strTitle,strPath);
}
//---------------------------------------------------------------------------
void __fastcall TFormWeighTest::Timer1Timer(TObject *Sender)
{  ((TTimer *)Sender)->Enabled=false;
   if(!connected)
   { Application->MessageBox("通信连接失败，请检查通信接口及参数配置！","提示",MB_OK|MB_ICONSTOP);
     this->Close();
   }
}
//---------------------------------------------------------------------------

void __fastcall TFormWeighTest::MN_SaveClick(TObject *Sender)
{ extern void ExcelOpen_TestWeight(String);
  String xlsfile=ExtractFilePath(Application->ExeName)+DIRECTORY_PRODUCT_TEST+"\\T-"+FormatDateTime("yymmddhhnnss",Now())+".xls";
  ExcelOpen_TestWeight(xlsfile);

}
//---------------------------------------------------------------------------
void __fastcall TFormWeighTest::MN_ClearClick(TObject *Sender)
{  weight_counter=0;
   weight_total=0;
   weight_maximum=0;
   weight_minimum=0;

   weight_static=-1;
   
   refresh_stat();
   ListView1->Clear();
   Edit_WeightCount->Text="0";
}
//---------------------------------------------------------------------------
void TFormWeighTest::LockControl(bool bLockOrNot)
{ if(bLockOrNot==MN_Lock->Visible)return;
   if(!bLockOrNot)
   { if(FormMain->UserLoginCheck("密码验证"))FormMain->TimerIdle->Enabled=true;
     else return;
   }
   MN_Lock->Visible=bLockOrNot;
   MN_Action->Visible=!bLockOrNot;
   FormMain->UI_update_login_state(true);
}
void __fastcall TFormWeighTest::MN_LockClick(TObject *Sender)
{ LockControl(false);
}
//---------------------------------------------------------------------------
void __fastcall TFormWeighTest::Edit_StaticKeyPress(TObject *Sender,
      char &Key)
{ if ((Key<'0' || Key>'9') && Key!='.' && Key!=8) Key=0;

}
//---------------------------------------------------------------------------

void __fastcall TFormWeighTest::Edit_StaticChange(TObject *Sender)
{ String str_static=Edit_Static->Text.Trim();
  if(str_static.IsEmpty())weight_static=-1;
  else weight_static=atof(str_static.c_str());
}
//---------------------------------------------------------------------------

