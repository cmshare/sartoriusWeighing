object FormControlPici: TFormControlPici
  Left = 736
  Top = 246
  BorderIcons = [biMinimize, biMaximize]
  BorderStyle = bsSingle
  Caption = 'FormControlPici'
  ClientHeight = 374
  ClientWidth = 494
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
  object Bevel1: TBevel
    Left = 32
    Top = 56
    Width = 401
    Height = 297
  end
  object Label1: TLabel
    Left = 64
    Top = 88
    Width = 60
    Height = 13
    AutoSize = False
    Caption = #20135#21697#21517#31216#65306
  end
  object Label2: TLabel
    Left = 64
    Top = 312
    Width = 60
    Height = 13
    AutoSize = False
    Caption = #20214'    '#25968#65306
  end
  object Label3: TLabel
    Left = 64
    Top = 120
    Width = 60
    Height = 13
    AutoSize = False
    Caption = #20135#21697#25551#36848#65306
  end
  object Label4: TLabel
    Left = 64
    Top = 152
    Width = 60
    Height = 13
    AutoSize = False
    Caption = #20135#21697#32534#21495#65306
  end
  object Label5: TLabel
    Left = 64
    Top = 184
    Width = 60
    Height = 13
    AutoSize = False
    Caption = #29983#20135#32447#21495#65306
  end
  object Label6: TLabel
    Left = 64
    Top = 216
    Width = 60
    Height = 13
    AutoSize = False
    Caption = #26816#37325#31204#21495#65306
  end
  object Label7: TLabel
    Left = 64
    Top = 248
    Width = 60
    Height = 13
    AutoSize = False
    Caption = #25209' '#27425' '#21495#65306
  end
  object Label8: TLabel
    Left = 64
    Top = 280
    Width = 60
    Height = 13
    AutoSize = False
    Caption = #25805' '#20316' '#21592#65306
  end
  object Label9: TLabel
    Left = 344
    Top = 312
    Width = 60
    Height = 13
    AutoSize = False
    Caption = 'PCS'
  end
  object PanelTop: TPanel
    Left = 0
    Top = 0
    Width = 494
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    Caption = #24320#22987#25209#27425
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
  end
  object Edit_ProductName: TEdit
    Left = 144
    Top = 82
    Width = 249
    Height = 21
    Enabled = False
    TabOrder = 1
  end
  object Edit_PiciCapacity: TEdit
    Left = 144
    Top = 307
    Width = 193
    Height = 21
    MaxLength = 32
    TabOrder = 8
  end
  object Edit_ProductDesc: TEdit
    Left = 144
    Top = 115
    Width = 249
    Height = 21
    Enabled = False
    MaxLength = 32
    TabOrder = 2
  end
  object Edit_ProductCode: TEdit
    Left = 144
    Top = 147
    Width = 249
    Height = 21
    Enabled = False
    MaxLength = 32
    TabOrder = 3
  end
  object Edit_ProductLine: TEdit
    Left = 144
    Top = 179
    Width = 249
    Height = 21
    MaxLength = 32
    TabOrder = 4
  end
  object Edit_Checkweigher: TEdit
    Left = 144
    Top = 211
    Width = 249
    Height = 21
    MaxLength = 32
    TabOrder = 5
  end
  object Edit_PiciNumber: TEdit
    Left = 144
    Top = 243
    Width = 193
    Height = 21
    MaxLength = 32
    TabOrder = 6
  end
  object Edit_PiciOperator: TEdit
    Left = 144
    Top = 275
    Width = 193
    Height = 21
    MaxLength = 32
    TabOrder = 7
  end
  object MainMenu1: TMainMenu
    Left = 336
    Top = 16
    object N1: TMenuItem
      Caption = #25805#20316
      object MN_OK: TMenuItem
        Caption = #30830#23450
        OnClick = MN_OKClick
      end
      object MN_Cancel: TMenuItem
        Caption = #21462#28040
        OnClick = MN_CancelClick
      end
    end
  end
end
