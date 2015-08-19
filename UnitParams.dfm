object FormParams: TFormParams
  Left = 125
  Top = 102
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'FormParams'
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
  object GroupBox1: TGroupBox
    Left = 56
    Top = 45
    Width = 569
    Height = 137
    TabOrder = 0
    object Label1: TLabel
      Left = 20
      Top = 32
      Width = 90
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #31204#21488#38271#24230#65306
    end
    object Label2: TLabel
      Left = 198
      Top = 32
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'mm'
    end
    object Label3: TLabel
      Left = 20
      Top = 64
      Width = 90
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #36724#38388#36317#31163#65306
    end
    object Label4: TLabel
      Left = 198
      Top = 64
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'mm'
    end
    object Label5: TLabel
      Left = 20
      Top = 96
      Width = 90
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #36724#30452#24452#65306
    end
    object Label6: TLabel
      Left = 198
      Top = 96
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'mm'
    end
    object Label7: TLabel
      Left = 285
      Top = 32
      Width = 100
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #36890#36807#29575#65306
    end
    object Label8: TLabel
      Left = 474
      Top = 32
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'pcs/min'
    end
    object Label9: TLabel
      Left = 285
      Top = 64
      Width = 100
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #30382#24102#36895#24230#65306
    end
    object Label10: TLabel
      Left = 474
      Top = 64
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'm/min'
    end
    object Label11: TLabel
      Left = 285
      Top = 96
      Width = 100
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #23454#38469#39057#29575#65306
    end
    object Label12: TLabel
      Left = 474
      Top = 96
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'Hz'
    end
    object Edit_ctcd: TEdit
      Left = 108
      Top = 28
      Width = 89
      Height = 21
      TabOrder = 0
      OnChange = OnCtcdChanged
      OnKeyPress = EditNum_KeyPress
    end
    object Edit_zjjl: TEdit
      Left = 108
      Top = 60
      Width = 89
      Height = 21
      TabOrder = 1
      OnKeyPress = EditNum_KeyPress
    end
    object Edit_zzj: TEdit
      Left = 108
      Top = 92
      Width = 89
      Height = 21
      TabOrder = 2
      OnKeyPress = EditNum_KeyPress
    end
    object Edit_passrate: TEdit
      Left = 384
      Top = 28
      Width = 89
      Height = 21
      TabOrder = 3
      OnChange = OnCtcdChanged
      OnKeyPress = EditNum_KeyPress
    end
    object Edit_pdsd: TEdit
      Left = 384
      Top = 60
      Width = 89
      Height = 21
      Enabled = False
      ReadOnly = True
      TabOrder = 4
    end
    object Edit_sjpl: TEdit
      Left = 384
      Top = 92
      Width = 89
      Height = 21
      Enabled = False
      TabOrder = 5
      OnKeyPress = EditNum_KeyPress
    end
  end
  object GroupBox2: TGroupBox
    Left = 56
    Top = 190
    Width = 569
    Height = 169
    TabOrder = 1
    object Label13: TLabel
      Left = 10
      Top = 32
      Width = 100
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #26368#22823#30382#24102#36895#24230#65306
    end
    object Label14: TLabel
      Left = 198
      Top = 32
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'm/min'
    end
    object Label15: TLabel
      Left = 10
      Top = 64
      Width = 100
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #26368#23567#30382#24102#36895#24230#65306
    end
    object Label16: TLabel
      Left = 198
      Top = 64
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'm/min'
    end
    object Label17: TLabel
      Left = 10
      Top = 96
      Width = 100
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #26368#22823#39057#29575#65306
    end
    object Label18: TLabel
      Left = 198
      Top = 96
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'Hz'
    end
    object Label19: TLabel
      Left = 295
      Top = 32
      Width = 90
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #26368#22823#31216#37325#65306
    end
    object Label20: TLabel
      Left = 474
      Top = 32
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Label21: TLabel
      Left = 295
      Top = 96
      Width = 90
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #26174#31034#20998#24230#65306
    end
    object Label22: TLabel
      Left = 474
      Top = 64
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Label23: TLabel
      Left = 295
      Top = 128
      Width = 90
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #26174#31034#21333#20301#65306
    end
    object Label25: TLabel
      Left = 10
      Top = 128
      Width = 100
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #26368#23567#39057#29575#65306
    end
    object Label26: TLabel
      Left = 198
      Top = 128
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'Hz'
    end
    object Label24: TLabel
      Left = 474
      Top = 96
      Width = 49
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Label27: TLabel
      Left = 295
      Top = 64
      Width = 90
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #26368#23567#31216#37325#65306
    end
    object Edit_zdpdsd: TEdit
      Left = 108
      Top = 28
      Width = 89
      Height = 21
      TabOrder = 0
      OnChange = OnCtcdChanged
      OnKeyPress = EditNum_KeyPress
    end
    object Edit_zxpdsd: TEdit
      Left = 108
      Top = 60
      Width = 89
      Height = 21
      TabOrder = 1
      OnChange = OnCtcdChanged
      OnKeyPress = EditNum_KeyPress
    end
    object Edit_zdpl: TEdit
      Left = 108
      Top = 92
      Width = 89
      Height = 21
      TabOrder = 2
      OnKeyPress = EditNum_KeyPress
    end
    object Edit_zdcz: TEdit
      Left = 384
      Top = 28
      Width = 89
      Height = 21
      TabOrder = 3
      OnKeyPress = EditNum_KeyPress
    end
    object Edit_xsfd: TEdit
      Left = 384
      Top = 92
      Width = 89
      Height = 21
      TabOrder = 4
      OnKeyPress = EditNum_KeyPress
    end
    object Edit_zxpl: TEdit
      Left = 108
      Top = 124
      Width = 89
      Height = 21
      TabOrder = 5
      OnKeyPress = EditNum_KeyPress
    end
    object Edit_zxcz: TEdit
      Left = 384
      Top = 60
      Width = 89
      Height = 21
      TabOrder = 6
      OnKeyPress = EditNum_KeyPress
    end
    object ComboBox_autozero: TComboBox
      Left = 384
      Top = 124
      Width = 89
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 7
      Items.Strings = (
        'kg'
        'g')
    end
  end
  object PanelTop: TPanel
    Left = 0
    Top = 0
    Width = 684
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    Caption = #35774#22791#21442#25968
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
  end
  object MainMenu1: TMainMenu
    Left = 8
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
      object MN_Close: TMenuItem
        Caption = #20851#38381
        OnClick = MN_CloseClick
      end
      object MN_Print: TMenuItem
        Caption = #20445#23384#21040'Excel'
        OnClick = MN_PrintClick
      end
    end
  end
end
