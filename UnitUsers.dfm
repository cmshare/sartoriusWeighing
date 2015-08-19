object FormUsers: TFormUsers
  Left = 437
  Top = 87
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'FormUsers'
  ClientHeight = 390
  ClientWidth = 462
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label4: TLabel
    Left = 248
    Top = 324
    Width = 121
    Height = 13
    AutoSize = False
    Caption = #20998#38047#26080#25805#20316#38145#23450
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 462
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    Caption = #29992#25143#31649#29702
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
  end
  object GroupBoxEditor: TGroupBox
    Left = 208
    Top = 45
    Width = 241
    Height = 177
    Caption = #28155#21152
    TabOrder = 1
    object Label5: TLabel
      Left = 8
      Top = 32
      Width = 65
      Height = 13
      AutoSize = False
      Caption = #29992'  '#25143' '#21517#65306
    end
    object Label2: TLabel
      Left = 8
      Top = 70
      Width = 65
      Height = 13
      AutoSize = False
      Caption = #29992#25143#26435#38480#65306
    end
    object Label1: TLabel
      Left = 8
      Top = 103
      Width = 65
      Height = 13
      AutoSize = False
      Caption = #36755#20837#23494#30721#65306
    end
    object Label3: TLabel
      Left = 8
      Top = 140
      Width = 65
      Height = 13
      AutoSize = False
      Caption = #30830#35748#23494#30721#65306
    end
    object Edit_Username: TEdit
      Left = 72
      Top = 26
      Width = 145
      Height = 21
      MaxLength = 32
      TabOrder = 0
    end
    object ComboBox_Grade: TComboBox
      Left = 72
      Top = 62
      Width = 145
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 1
      Items.Strings = (
        #25805#20316#21592
        #36127#36131#20154
        #31649#29702#21592)
    end
    object Edit_Password: TEdit
      Left = 72
      Top = 101
      Width = 145
      Height = 21
      MaxLength = 32
      TabOrder = 2
    end
    object Edit_Password2: TEdit
      Left = 72
      Top = 138
      Width = 145
      Height = 21
      MaxLength = 32
      TabOrder = 3
    end
  end
  object CheckBox_Security: TCheckBox
    Left = 224
    Top = 360
    Width = 105
    Height = 17
    Caption = #28608#27963#23494#30721
    TabOrder = 2
    OnClick = CheckBox_SecurityClick
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 45
    Width = 193
    Height = 337
    Caption = #29992#25143#21015#34920
    TabOrder = 3
    object ListBoxUsers: TListBox
      Left = 8
      Top = 15
      Width = 178
      Height = 314
      ItemHeight = 13
      MultiSelect = True
      TabOrder = 0
      OnDblClick = Button_ModifyClick
    end
  end
  object Edit_MaxIdleTime: TEdit
    Left = 224
    Top = 320
    Width = 25
    Height = 21
    TabOrder = 4
    Text = '3'
    OnKeyPress = Edit_MaxIdleTimeKeyPress
  end
  object MainMenu1: TMainMenu
    AutoHotkeys = maManual
    Left = 376
    Top = 336
    object N1: TMenuItem
      Caption = #25805#20316
      object MN_Add: TMenuItem
        Caption = #28155#21152
        OnClick = Button_AddClick
      end
      object MN_Modify: TMenuItem
        Caption = #20462#25913
        OnClick = Button_ModifyClick
      end
      object MN_Delete: TMenuItem
        Caption = #21024#38500
        OnClick = Button_DeleteClick
      end
      object MN_Save: TMenuItem
        Caption = #20445#23384
        OnClick = Button_SaveClick
      end
      object MN_Close: TMenuItem
        Caption = #20851#38381
        OnClick = MN_CloseClick
      end
    end
  end
end
