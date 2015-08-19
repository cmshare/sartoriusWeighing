//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "UnitMain.h"
#include "UnitUsers.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormUsers *FormUsers;

//---------------------------------------------------------------------------
__fastcall TFormUsers::TFormUsers(TComponent* Owner)
        : TForm(Owner)
{  this->Caption=PROJECT_COMPANY;
   EditorMode=emEditorAdd;
   CheckBox_Security->Checked=g_security;
   Edit_MaxIdleTime->Enabled=CheckBox_Security->Checked;
   MN_Add->Click();
}
//---------------------------------------------------------------------------
void  TFormUsers::RefreshUserList(void)
{  ListBoxUsers->Clear();
   MyQuery->SQL->Text="select * from users";
   MyQuery->Active=true;
   while(!MyQuery->Eof)
   { ListBoxUsers->Items->Add(MyQuery->FieldByName("name")->AsString);
     MyQuery->MoveBy(1);
   }
   MyQuery->Active=false;
}
//---------------------------------------------------------------------------
void __fastcall TFormUsers::FormShow(TObject *Sender)
{ Edit_MaxIdleTime->Text=IntToStr(g_MaxIdleTimeMS/60000);
  RefreshUserList();
}
//---------------------------------------------------------------------------
void __fastcall TFormUsers::Button_DeleteClick(TObject *Sender)
{ if(ListBoxUsers->SelCount<1)
  { ShowMessage("请选择待删除的用户！");
    return;
  }
  else if(ListBoxUsers->SelCount>1)
  { ShowMessage("不支持多选！");
    return;
  }
  else if(Application->MessageBox("确认删除选定的用户？","提示",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
  { String strUserName=ListBoxUsers->Items->Strings[ListBoxUsers->ItemIndex];
    if(strUserName=="admin")
    { ShowMessage("系统用户无法删除！");
      return;
    }
    MyQuery->SQL->Text="delete * from users where name='"+strUserName+"'";
    MyQuery->ExecSQL();
    RefreshUserList();
    if(EditorMode==emEditorModify)MN_Add->Click();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormUsers::Button_AddClick(TObject *Sender)
{
  GroupBoxEditor->Caption=((TMenuItem *)Sender)->Caption;
  EditorMode=emEditorAdd;
  editGroupID=0;
  RefreshInputState();
}
//---------------------------------------------------------------------------
void __fastcall TFormUsers::Button_ModifyClick(TObject *Sender)
{ if(ListBoxUsers->SelCount<1)
  { ShowMessage("请选择待修改的用户！");
    return;
  }
  else if(ListBoxUsers->SelCount>1)
  { ShowMessage("不支持多选！");
    return;
  }
  else
  { String strUserName=ListBoxUsers->Items->Strings[ListBoxUsers->ItemIndex];
    MyQuery->SQL->Text="select * from users where name='"+strUserName+"'";
    MyQuery->Active=true;
    editGroupID=(MyQuery->Eof)?0:MyQuery->FieldByName("id")->AsInteger;

    if(editGroupID>0)
    {  GroupBoxEditor->Caption=MN_Modify->Caption;
       EditorMode=emEditorModify;
       Edit_Username->Text=strUserName;
       ComboBox_Grade->ItemIndex=MyQuery->FieldByName("grade")->AsInteger-1;
       //Edit_Password->PasswordChar='*';
       //Edit_Password2->PasswordChar='*';
       Edit_Password->Text=MyQuery->FieldByName("password")->AsString;
       Edit_Password2->Text=MyQuery->FieldByName("password")->AsString;
       Edit_Username->Enabled=(strUserName!="admin");
    }
    MyQuery->Active=false;
    RefreshInputState();
  }

}
//---------------------------------------------------------------------------
void __fastcall TFormUsers::Button_SaveClick(TObject *Sender)
{
  String strUsername=Edit_Username->Text.Trim();
  String strPassword=Edit_Password->Text.Trim();
  int userGrade=ComboBox_Grade->ItemIndex+1;
  if(strUsername.IsEmpty())
  { ShowMessage("用户名不能为空！");
    Edit_Username->SetFocus();
    return;
  }
  else if(userGrade<0)
  { ShowMessage("用户权限为空！");
    ComboBox_Grade->SetFocus();
    return;
  }
  else if(strPassword.IsEmpty())
  { ShowMessage("密码不能为空！");
    Edit_Password->SetFocus();
    return;
  }
  else if(strPassword!=Edit_Password2->Text)
  { ShowMessage("两次输入密码不一致！");
    Edit_Password2->SetFocus();
    return;
  }
  if(EditorMode==emEditorAdd)
  { MyQuery->SQL->Text="select * from users where name='"+strUsername+"'";
    MyQuery->Active=true;
    if(!MyQuery->Eof)
    { MyQuery->Active=false;
      ShowMessage("该用户名已经存在！");
      return;
    }
    else
    { MyQuery->Append();
      MyQuery->FieldByName("name")->AsString=strUsername;
      MyQuery->FieldByName("grade")->AsInteger=userGrade;
      MyQuery->FieldByName("password")->AsString=strPassword;
      MyQuery->Post();
    }
    MyQuery->Active=false;
  }
  else if(EditorMode==emEditorModify)
  { MyQuery->SQL->Text="select * from users where name='"+strUsername+"' and id<>"+IntToStr(editGroupID);
    MyQuery->Active=true;
    if(!MyQuery->Eof)
    { MyQuery->Active=false;
      ShowMessage("该用户名已经存在！");
      return;
    }
    else
    { MyQuery->Active=false;
      MyQuery->SQL->Text="select * from users where id="+IntToStr(editGroupID);
      MyQuery->Active=true;
      if(!MyQuery->Eof)
      { MyQuery->Edit();
        MyQuery->FieldByName("name")->AsString=strUsername;
        MyQuery->FieldByName("grade")->AsInteger=userGrade;
        MyQuery->FieldByName("password")->AsString=strPassword;
        MyQuery->Post();
      }
    }
    MyQuery->Active=false;
  }

  RefreshUserList();
  MN_Save->Enabled=FALSE;
  Edit_Username->Enabled=FALSE;
  GroupBoxEditor->Enabled=FALSE;
  Edit_Password->Enabled=FALSE;
  Edit_Password2->Enabled=FALSE;

  ShowMessage("保存成功！");
  Button_AddClick(MN_Add);
}
//---------------------------------------------------------------------------
void __fastcall TFormUsers::MN_CloseClick(TObject *Sender)
{ this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormUsers::Edit_MaxIdleTimeKeyPress(TObject *Sender, char &Key)
{ if (Key>1&&Key<3 || (Key>3 && Key<8) || (Key>8 && Key<22)|| (Key>22 && Key<'0') || Key>'9')
    Key=0;
}
//---------------------------------------------------------------------------
void __fastcall TFormUsers::FormClose(TObject *Sender,
      TCloseAction &Action)
{  int new_idletime=atoi(Edit_MaxIdleTime->Text.c_str());
   if(new_idletime)
   { new_idletime=new_idletime*1000*60;
     if( new_idletime!= g_MaxIdleTimeMS)
     { g_MaxIdleTimeMS=new_idletime;
       ExecSQL("update configs set MaxIdleTime=%u",g_MaxIdleTimeMS);
     }
   }
   if(g_security!=CheckBox_Security->Checked)
   { g_security=CheckBox_Security->Checked;
     ExecSQL("update configs set security=%d",g_security);
   }
}
//---------------------------------------------------------------------------
void __fastcall TFormUsers::CheckBox_SecurityClick(TObject *Sender)
{  Edit_MaxIdleTime->Enabled=CheckBox_Security->Checked;
}
//---------------------------------------------------------------------------
void TFormUsers::RefreshInputState(void)
{  if(EditorMode==emEditorAdd)
   { MN_Add->Enabled=FALSE;
     MN_Modify->Enabled=TRUE;
     MN_Delete->Enabled=FALSE;
     MN_Save->Enabled=TRUE;
     Edit_Username->Clear();
     ComboBox_Grade->ItemIndex=-1;
     Edit_Password->Clear();
     Edit_Password2->Clear();
     Edit_Password->PasswordChar='\0';
     Edit_Password2->PasswordChar='\0';
   }
   else if(EditorMode==emEditorModify)
   { MN_Add->Enabled=TRUE;
     MN_Modify->Enabled=TRUE;
     MN_Delete->Enabled=TRUE;
     MN_Save->Enabled=TRUE;
   }
  MN_Save->Enabled=TRUE;
  Edit_Username->Enabled=TRUE;
  GroupBoxEditor->Enabled=TRUE;
  Edit_Password->Enabled=TRUE;
  Edit_Password2->Enabled=TRUE;

}

