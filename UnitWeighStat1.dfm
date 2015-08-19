object FormWeighStat1: TFormWeighStat1
  Left = 598
  Top = 368
  BorderStyle = bsDialog
  Caption = 'FormWeighStat1'
  ClientHeight = 329
  ClientWidth = 571
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  DesignSize = (
    571
    329)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 30
    Top = 64
    Width = 63
    Height = 13
    AutoSize = False
    Caption = #20135#21697#21517#31216#65306
  end
  object Label2: TLabel
    Left = 326
    Top = 62
    Width = 62
    Height = 13
    AutoSize = False
    Caption = #20135#21697#25209#27425#65306
  end
  object Label3: TLabel
    Left = 23
    Top = 119
    Width = 82
    Height = 13
    AutoSize = False
    Caption = #8721#21512#26684#20135#21697#65306
  end
  object Label4: TLabel
    Left = 230
    Top = 119
    Width = 25
    Height = 13
    AutoSize = False
    Caption = 'pcs'
  end
  object Label5: TLabel
    Left = 44
    Top = 157
    Width = 64
    Height = 13
    AutoSize = False
    Caption = #26368#22823#20540#65306
  end
  object Label6: TLabel
    Left = 230
    Top = 157
    Width = 25
    Height = 13
    AutoSize = False
    Caption = 'pcs'
  end
  object Label7: TLabel
    Left = 44
    Top = 196
    Width = 64
    Height = 13
    AutoSize = False
    Caption = #26368#23567#20540#65306
  end
  object Label8: TLabel
    Left = 230
    Top = 196
    Width = 25
    Height = 13
    AutoSize = False
    Caption = 'pcs'
  end
  object Label9: TLabel
    Left = 44
    Top = 236
    Width = 64
    Height = 13
    AutoSize = False
    Caption = #24179#22343#20540#65306
  end
  object Label10: TLabel
    Left = 230
    Top = 236
    Width = 25
    Height = 13
    AutoSize = False
    Caption = 'pcs'
  end
  object Label11: TLabel
    Left = 304
    Top = 119
    Width = 87
    Height = 13
    AutoSize = False
    Caption = #8721#19981#21512#26684#20135#21697#65306
  end
  object Label12: TLabel
    Left = 518
    Top = 119
    Width = 25
    Height = 13
    AutoSize = False
    Caption = 'pcs'
  end
  object Label13: TLabel
    Left = 339
    Top = 157
    Width = 61
    Height = 13
    AutoSize = False
    Caption = #26368#22823#20540#65306
  end
  object Label14: TLabel
    Left = 518
    Top = 157
    Width = 25
    Height = 13
    AutoSize = False
    Caption = 'pcs'
  end
  object Label15: TLabel
    Left = 340
    Top = 196
    Width = 63
    Height = 13
    AutoSize = False
    Caption = #26368#23567#20540#65306
  end
  object Label16: TLabel
    Left = 518
    Top = 196
    Width = 25
    Height = 13
    AutoSize = False
    Caption = 'pcs'
  end
  object Label17: TLabel
    Left = 340
    Top = 236
    Width = 63
    Height = 13
    AutoSize = False
    Caption = #24179#22343#20540#65306
  end
  object Label18: TLabel
    Left = 518
    Top = 236
    Width = 25
    Height = 13
    AutoSize = False
    Caption = 'pcs'
  end
  object Label_StatPeriod: TLabel
    Left = 32
    Top = 291
    Width = 393
    Height = 13
    Anchors = [akLeft, akBottom]
    AutoSize = False
    Caption = #24320#22987#26102#38388#65306'2015-03-05 08:10:09  '#32467#26463#26102#38388#65306' 2015-03-05 18:15:10'
  end
  object Bevel1: TBevel
    Left = 32
    Top = 271
    Width = 510
    Height = 9
    Shape = bsTopLine
  end
  object Bevel2: TBevel
    Left = 32
    Top = 96
    Width = 510
    Height = 9
    Shape = bsTopLine
  end
  object Button_Return: TButton
    Left = 474
    Top = 282
    Width = 75
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = #36820#22238
    TabOrder = 0
    OnClick = Button_ReturnClick
  end
  object PanelTop: TPanel
    Left = 0
    Top = 0
    Width = 571
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    Caption = #20135#21697#32479#35745
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    DesignSize = (
      571
      41)
    object Label_StatID: TLabel
      Left = 8
      Top = 16
      Width = 89
      Height = 13
      AutoSize = False
      Caption = '001'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object SpeedButton1: TSpeedButton
      Left = 521
      Top = 7
      Width = 39
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #19978#32763
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
  end
  object Edit_PiciName: TEdit
    Left = 392
    Top = 57
    Width = 113
    Height = 21
    MaxLength = 32
    TabOrder = 2
  end
  object Edit_ProductName: TEdit
    Left = 100
    Top = 58
    Width = 205
    Height = 21
    Enabled = False
    TabOrder = 3
  end
  object Edit1: TEdit
    Left = 100
    Top = 114
    Width = 113
    Height = 21
    MaxLength = 32
    TabOrder = 4
  end
  object Edit2: TEdit
    Left = 100
    Top = 152
    Width = 113
    Height = 21
    MaxLength = 32
    TabOrder = 5
  end
  object Edit3: TEdit
    Left = 100
    Top = 191
    Width = 113
    Height = 21
    MaxLength = 32
    TabOrder = 6
  end
  object Edit4: TEdit
    Left = 100
    Top = 231
    Width = 113
    Height = 21
    MaxLength = 32
    TabOrder = 7
  end
  object Edit5: TEdit
    Left = 394
    Top = 114
    Width = 113
    Height = 21
    MaxLength = 32
    TabOrder = 8
  end
  object Edit6: TEdit
    Left = 394
    Top = 152
    Width = 113
    Height = 21
    MaxLength = 32
    TabOrder = 9
  end
  object Edit7: TEdit
    Left = 394
    Top = 191
    Width = 113
    Height = 21
    MaxLength = 32
    TabOrder = 10
  end
  object Edit8: TEdit
    Left = 394
    Top = 231
    Width = 113
    Height = 21
    MaxLength = 32
    TabOrder = 11
  end
end
