object FormCatalogEdit: TFormCatalogEdit
  Left = 276
  Top = 210
  BorderIcons = [biMinimize, biMaximize]
  BorderStyle = bsSingle
  Caption = 'FormCatalogEdit'
  ClientHeight = 392
  ClientWidth = 684
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PanelTop: TPanel
    Left = 0
    Top = 0
    Width = 684
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    Caption = #20135#21697#21442#25968
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
  end
  object GroupBox1: TGroupBox
    Left = 56
    Top = 45
    Width = 569
    Height = 102
    TabOrder = 1
    object Label1: TLabel
      Left = 16
      Top = 24
      Width = 100
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #20135#21697#21517#31216#65306
    end
    object Label11: TLabel
      Left = 16
      Top = 50
      Width = 100
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #20135#21697#25551#36848#65306
    end
    object Label2: TLabel
      Left = 16
      Top = 76
      Width = 100
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #20135#21697#32534#21495#65306
    end
    object Edit_Code: TEdit
      Left = 113
      Top = 71
      Width = 256
      Height = 21
      MaxLength = 20
      TabOrder = 2
      Text = 'Edit_Code'
      OnChange = Edit_Changed
    end
    object Edit_Description: TEdit
      Left = 113
      Top = 45
      Width = 256
      Height = 21
      MaxLength = 100
      TabOrder = 1
      Text = 'Edit_Description'
      OnChange = Edit_Changed
    end
    object Edit_Name: TEdit
      Left = 113
      Top = 19
      Width = 256
      Height = 21
      MaxLength = 50
      TabOrder = 0
      Text = 'Edit_Name'
      OnChange = Edit_Changed
    end
  end
  object GroupBox2: TGroupBox
    Left = 56
    Top = 152
    Width = 569
    Height = 105
    TabOrder = 2
    object Label4: TLabel
      Left = 240
      Top = 24
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Label8: TLabel
      Left = 240
      Top = 50
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Label6: TLabel
      Left = 240
      Top = 76
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Label3: TLabel
      Left = 16
      Top = 24
      Width = 100
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #30446'  '#26631'  '#20540#65306
    end
    object Label7: TLabel
      Left = 16
      Top = 50
      Width = 100
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #19979'  '#38480'  '#20540#65306
    end
    object Label5: TLabel
      Left = 16
      Top = 76
      Width = 100
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #19978'  '#38480'  '#20540#65306
    end
    object Label16: TLabel
      Left = 310
      Top = 24
      Width = 80
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #36890'  '#36807'  '#29575#65306
    end
    object Label17: TLabel
      Left = 513
      Top = 24
      Width = 41
      Height = 13
      AutoSize = False
      Caption = 'pc/min'
    end
    object Label18: TLabel
      Left = 310
      Top = 50
      Width = 80
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #30382#24102#36895#24230#65306
    end
    object Label19: TLabel
      Left = 513
      Top = 50
      Width = 41
      Height = 13
      AutoSize = False
      Caption = 'm/min'
    end
    object Label20: TLabel
      Left = 310
      Top = 76
      Width = 80
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #20462#27491#31995#25968#65306
    end
    object Edit_ValueUL: TEdit
      Left = 113
      Top = 71
      Width = 125
      Height = 21
      MaxLength = 8
      TabOrder = 2
      Text = 'Edit1'
      OnChange = Edit_Changed
      OnKeyPress = EditNum_KeyPress
    end
    object Edit_ValueLL: TEdit
      Left = 113
      Top = 45
      Width = 125
      Height = 21
      MaxLength = 8
      TabOrder = 1
      Text = 'Edit1'
      OnChange = Edit_Changed
      OnKeyPress = EditNum_KeyPress
    end
    object Edit_ValueTP: TEdit
      Left = 113
      Top = 19
      Width = 125
      Height = 21
      MaxLength = 8
      TabOrder = 0
      Text = 'Edit1'
      OnChange = Edit_Changed
      OnKeyPress = EditNum_KeyPress
    end
    object Edit_PassRate: TEdit
      Left = 386
      Top = 19
      Width = 125
      Height = 21
      MaxLength = 8
      TabOrder = 3
      Text = 'Edit1'
      OnChange = Edit_Changed
      OnKeyPress = EditNum_KeyPress
    end
    object Edit_pdsd: TEdit
      Left = 386
      Top = 45
      Width = 125
      Height = 21
      Enabled = False
      MaxLength = 8
      ReadOnly = True
      TabOrder = 4
      Text = 'Edit_pdsd'
      OnChange = Edit_Changed
    end
    object Edit_correctionFactor: TEdit
      Left = 386
      Top = 71
      Width = 125
      Height = 21
      MaxLength = 8
      TabOrder = 5
      Text = 'Edit1'
      OnChange = Edit_Changed
      OnKeyPress = EditNum_KeyPress
    end
  end
  object GroupBox3: TGroupBox
    Left = 56
    Top = 263
    Width = 569
    Height = 105
    TabOrder = 3
    object Label21: TLabel
      Left = 240
      Top = 24
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 's'
    end
    object Label22: TLabel
      Left = 240
      Top = 50
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 's'
    end
    object Label24: TLabel
      Left = 16
      Top = 24
      Width = 100
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #21076#38500#31561#24453#26102#38388#65306
    end
    object Label25: TLabel
      Left = 16
      Top = 50
      Width = 100
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #21076#38500#21160#20316#26102#38388#65306
    end
    object Label26: TLabel
      Left = 16
      Top = 76
      Width = 100
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #31216#37325#26174#31034#27169#24335#65306
    end
    object Label9: TLabel
      Left = 310
      Top = 28
      Width = 80
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #32479#35745#33539#22260#65306
    end
    object Label10: TLabel
      Left = 513
      Top = 28
      Width = 32
      Height = 13
      AutoSize = False
      Caption = '%'
    end
    object Label14: TLabel
      Left = 310
      Top = 50
      Width = 80
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #21253#35013#38271#24230#65306
    end
    object Label15: TLabel
      Left = 513
      Top = 50
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'mm'
    end
    object Label12: TLabel
      Left = 310
      Top = 76
      Width = 80
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #39044#32622#30382#37325#65306
    end
    object Label13: TLabel
      Left = 513
      Top = 76
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Edit_tcActiontime: TEdit
      Left = 113
      Top = 45
      Width = 125
      Height = 21
      MaxLength = 8
      TabOrder = 1
      Text = 'Edit1'
      OnChange = Edit_Changed
      OnKeyPress = EditNum_KeyPress
    end
    object Edit_tcWaittime: TEdit
      Left = 113
      Top = 19
      Width = 125
      Height = 21
      MaxLength = 8
      TabOrder = 0
      Text = 'Edit1'
      OnChange = Edit_Changed
      OnKeyPress = EditNum_KeyPress
    end
    object Edit_StatRange: TEdit
      Left = 386
      Top = 19
      Width = 125
      Height = 21
      MaxLength = 8
      TabOrder = 3
      Text = 'Edit1'
      OnChange = Edit_Changed
      OnKeyPress = EditNum_KeyPress
    end
    object Edit_PackLength: TEdit
      Left = 386
      Top = 45
      Width = 125
      Height = 21
      MaxLength = 8
      TabOrder = 4
      Text = 'Edit1'
      OnChange = Edit_Changed
      OnKeyPress = EditNum_KeyPress
    end
    object Edit_PresetTare: TEdit
      Left = 386
      Top = 71
      Width = 125
      Height = 21
      MaxLength = 8
      TabOrder = 5
      Text = 'Edit_PresetTare'
      OnChange = Edit_Changed
      OnKeyPress = EditNum_KeyPress
    end
    object ComboBox_mode: TComboBox
      Left = 112
      Top = 72
      Width = 125
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 2
      Items.Strings = (
        'Gross'
        'Net')
    end
  end
  object MainMenu1: TMainMenu
    Left = 512
    Top = 16
    object N1: TMenuItem
      Caption = #25805#20316
      object MN_Save: TMenuItem
        Caption = #20445#23384
        OnClick = MN_SaveClick
      end
      object MN_Modify: TMenuItem
        Caption = #20462#25913
        OnClick = MN_ModifyClick
      end
      object MN_Delete: TMenuItem
        Caption = #21024#38500
        OnClick = MN_DeleteClick
      end
      object MN_Exit: TMenuItem
        Caption = #20851#38381
        OnClick = MN_ExitClick
      end
      object MN_Next: TMenuItem
        Caption = #19979#19968#20010
        ShortCut = 16462
        OnClick = MN_NextClick
      end
      object MN_Previous: TMenuItem
        Caption = #19978#19968#20010
        ShortCut = 16464
        OnClick = MN_PreviousClick
      end
      object MN_PrintExcel: TMenuItem
        Caption = #20445#23384#21040'Excel'
        OnClick = MN_PrintExcelClick
      end
    end
  end
end
