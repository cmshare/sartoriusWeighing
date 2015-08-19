object FormWeighTest: TFormWeighTest
  Left = 234
  Top = 63
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'FormWeighTest'
  ClientHeight = 574
  ClientWidth = 807
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
    Width = 807
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    Caption = #20135#21697#27979#35797
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
  end
  object ListView1: TListView
    Left = 0
    Top = 115
    Width = 807
    Height = 333
    Align = alClient
    Columns = <
      item
        AutoSize = True
        Caption = #24207#21495
      end
      item
        Caption = #31216#37325#20540
        Width = 200
      end
      item
        Caption = #26102#38388#26085#26399
        Width = 300
      end>
    ReadOnly = True
    RowSelect = True
    TabOrder = 1
    ViewStyle = vsReport
  end
  object Panel1: TPanel
    Left = 0
    Top = 448
    Width = 807
    Height = 126
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 2
    object Label1: TLabel
      Left = 172
      Top = 16
      Width = 70
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #26631#20934#20559#24046#65306
    end
    object Label2: TLabel
      Left = 408
      Top = 16
      Width = 70
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #24179' '#22343' '#20540#65306
    end
    object Label3: TLabel
      Left = 408
      Top = 39
      Width = 70
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #26368' '#22823' '#20540#65306
    end
    object Label4: TLabel
      Left = 408
      Top = 64
      Width = 70
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #26368' '#23567' '#20540#65306
    end
    object LabelUnit5: TLabel
      Left = 578
      Top = 63
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object LabelUnit4: TLabel
      Left = 577
      Top = 40
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object LabelUnit3: TLabel
      Left = 576
      Top = 15
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Label7: TLabel
      Left = 172
      Top = 63
      Width = 70
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #20214#25968#65306
    end
    object Label9: TLabel
      Left = 338
      Top = 63
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'pcs'
    end
    object Label10: TLabel
      Left = 172
      Top = 39
      Width = 70
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #30382#24102#36895#24230#65306
    end
    object Label11: TLabel
      Left = 338
      Top = 39
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'm/min'
    end
    object LabelUnit1: TLabel
      Left = 338
      Top = 15
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Label13: TLabel
      Left = 172
      Top = 87
      Width = 70
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #177#20559#24046#65306
    end
    object LabelUnit2: TLabel
      Left = 338
      Top = 87
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Label15: TLabel
      Left = 408
      Top = 88
      Width = 70
      Height = 13
      Alignment = taRightJustify
      AutoSize = False
      Caption = #38745#24577#37325#37327#65306
    end
    object LabelUnit6: TLabel
      Left = 578
      Top = 87
      Width = 32
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Edit_StandardDeviation: TEdit
      Left = 238
      Top = 10
      Width = 100
      Height = 21
      ReadOnly = True
      TabOrder = 0
    end
    object Edit_Average: TEdit
      Left = 474
      Top = 10
      Width = 100
      Height = 21
      ReadOnly = True
      TabOrder = 1
    end
    object Edit_Maximum: TEdit
      Left = 475
      Top = 33
      Width = 100
      Height = 21
      ReadOnly = True
      TabOrder = 2
    end
    object Edit_Minimum: TEdit
      Left = 475
      Top = 58
      Width = 100
      Height = 21
      ReadOnly = True
      TabOrder = 3
    end
    object Edit_WeightCount: TEdit
      Left = 238
      Top = 57
      Width = 100
      Height = 21
      ReadOnly = True
      TabOrder = 4
      Text = '0'
    end
    object Edit_pdsd: TEdit
      Left = 238
      Top = 33
      Width = 100
      Height = 21
      Enabled = False
      TabOrder = 5
    end
    object Edit1_Deviation1: TEdit
      Left = 238
      Top = 81
      Width = 48
      Height = 21
      ReadOnly = True
      TabOrder = 6
    end
    object Edit_Static: TEdit
      Left = 475
      Top = 82
      Width = 100
      Height = 21
      TabOrder = 7
      OnChange = Edit_StaticChange
      OnKeyPress = Edit_StaticKeyPress
    end
    object Edit1_Deviation2: TEdit
      Left = 289
      Top = 81
      Width = 48
      Height = 21
      ReadOnly = True
      TabOrder = 8
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 41
    Width = 807
    Height = 74
    Align = alTop
    BevelInner = bvLowered
    BevelOuter = bvLowered
    Color = clYellow
    TabOrder = 3
    object Label_Weight: TLabel
      Left = 208
      Top = 5
      Width = 276
      Height = 67
      Alignment = taRightJustify
      AutoSize = False
      Caption = '0.000'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -67
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
    end
    object LabelUnit: TStaticText
      Left = 489
      Top = 35
      Width = 30
      Height = 33
      Caption = 'kg'
      Color = clYellow
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = 30
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 0
    end
  end
  object MainMenu1: TMainMenu
    Left = 24
    Top = 8
    object MN_Lock: TMenuItem
      Caption = #25805#20316#35299#38145
      Visible = False
      OnClick = MN_LockClick
    end
    object MN_Action: TMenuItem
      Caption = #25805#20316
      object MN_Save: TMenuItem
        Caption = #20445#23384#21040'Excel'
        OnClick = MN_SaveClick
      end
      object MN_Clear: TMenuItem
        Caption = #28165#31354
        OnClick = MN_ClearClick
      end
      object MN_Close: TMenuItem
        Caption = #20851#38381
        OnClick = MN_CloseClick
      end
    end
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 552
    Top = 24
  end
end
