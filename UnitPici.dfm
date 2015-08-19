object FormPici: TFormPici
  Left = 310
  Top = 139
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'FormPici'
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
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label_ValueLL: TLabel
    Left = 208
    Top = 143
    Width = 56
    Height = 13
    Alignment = taRightJustify
    AutoSize = False
    Caption = '11.982kg'
  end
  object Label_ValueTP: TLabel
    Left = 288
    Top = 143
    Width = 89
    Height = 13
    Alignment = taCenter
    AutoSize = False
    Caption = '12.012kg'
  end
  object Label_ValueUL: TLabel
    Left = 387
    Top = 143
    Width = 70
    Height = 13
    AutoSize = False
    Caption = '13.000kg'
  end
  object Label_picitick: TLabel
    Left = 360
    Top = 87
    Width = 182
    Height = 13
    Alignment = taRightJustify
    AutoSize = False
    Caption = '0'
  end
  object Label5: TLabel
    Left = 136
    Top = 88
    Width = 66
    Height = 13
    AutoSize = False
    Caption = #25209#27425#21495#30721#65306'0'
  end
  object Label_PiciNumber: TLabel
    Left = 205
    Top = 88
    Width = 105
    Height = 13
    AutoSize = False
    Caption = '0'
  end
  object Label25: TLabel
    Left = 328
    Top = 132
    Width = 16
    Height = 13
    AutoSize = False
    Caption = #9650
  end
  object Bevel1: TBevel
    Left = 255
    Top = 120
    Width = 10
    Height = 12
    Shape = bsLeftLine
  end
  object Bevel2: TBevel
    Left = 401
    Top = 120
    Width = 10
    Height = 12
    Shape = bsLeftLine
  end
  object Panel2: TPanel
    Left = 138
    Top = -1
    Width = 403
    Height = 75
    BevelInner = bvLowered
    BevelOuter = bvLowered
    Color = 8519679
    TabOrder = 0
    DesignSize = (
      403
      75)
    object Label_Weight: TLabel
      Left = 2
      Top = 2
      Width = 279
      Height = 71
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
    object SpeedButton_grossornet: TSpeedButton
      Left = 8
      Top = 32
      Width = 23
      Height = 22
      Caption = 'G'
      Flat = True
      OnClick = SpeedButton_grossornetClick
    end
    object Label_PiciState: TLabel
      Left = 361
      Top = 8
      Width = 32
      Height = 13
      Anchors = [akTop, akRight]
      AutoSize = False
      Caption = #24320#22987
    end
    object LabelUnit: TStaticText
      Left = 287
      Top = 32
      Width = 30
      Height = 33
      Caption = 'kg'
      Color = 8519679
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = 30
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 0
    end
    object StaticText_ProductID: TStaticText
      Left = 363
      Top = 47
      Width = 31
      Height = 24
      Anchors = [akTop, akRight]
      Caption = '001'
      Color = 8519679
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = 20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 1
    end
  end
  object Panel_LL: TPanel
    Left = 175
    Top = 120
    Width = 80
    Height = 12
    BevelOuter = bvNone
    Color = clRed
    TabOrder = 1
  end
  object Panel_TP: TPanel
    Left = 256
    Top = 120
    Width = 145
    Height = 12
    BevelOuter = bvNone
    Color = clLime
    TabOrder = 2
  end
  object Panel_UL: TPanel
    Left = 402
    Top = 120
    Width = 80
    Height = 12
    BevelOuter = bvNone
    Color = clOlive
    TabOrder = 3
  end
  object GroupBox_Stat1: TGroupBox
    Left = 80
    Top = 164
    Width = 241
    Height = 209
    Caption = #20840#37096#20135#21697
    TabOrder = 4
    Visible = False
    object Label2: TLabel
      Left = 30
      Top = 30
      Width = 72
      Height = 13
      AutoSize = False
      Caption = #963'(n-1)'
    end
    object LabelUnit1: TLabel
      Left = 201
      Top = 30
      Width = 17
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Label4: TLabel
      Left = 30
      Top = 54
      Width = 72
      Height = 13
      AutoSize = False
      Caption = #24179#22343#20540
    end
    object LabelUnit2: TLabel
      Left = 201
      Top = 54
      Width = 17
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Label7: TLabel
      Left = 30
      Top = 78
      Width = 72
      Height = 13
      AutoSize = False
      Caption = #26368#23567#20540
    end
    object LabelUnit3: TLabel
      Left = 201
      Top = 78
      Width = 17
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Label9: TLabel
      Left = 30
      Top = 102
      Width = 72
      Height = 13
      AutoSize = False
      Caption = #26368#22823#20540
    end
    object LabelUnit4: TLabel
      Left = 201
      Top = 102
      Width = 17
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Label11: TLabel
      Left = 30
      Top = 126
      Width = 72
      Height = 13
      AutoSize = False
      Caption = '%'#21512#26684#29575
    end
    object Label13: TLabel
      Left = 30
      Top = 150
      Width = 72
      Height = 13
      AutoSize = False
      Caption = #931#25968#37327#24635#35745
    end
    object Label14: TLabel
      Left = 201
      Top = 150
      Width = 17
      Height = 13
      AutoSize = False
      Caption = 'pcs'
    end
    object Label15: TLabel
      Left = 30
      Top = 174
      Width = 72
      Height = 13
      AutoSize = False
      Caption = #931#37325#37327#24635#35745
    end
    object LabelUnit5: TLabel
      Left = 201
      Top = 174
      Width = 17
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Label12: TLabel
      Left = 201
      Top = 126
      Width = 17
      Height = 13
      AutoSize = False
      Caption = '%'
    end
    object Edit_StandardDeviation: TEdit
      Left = 94
      Top = 26
      Width = 103
      Height = 21
      ReadOnly = True
      TabOrder = 0
      Text = '0'
    end
    object Edit_Average: TEdit
      Left = 94
      Top = 50
      Width = 103
      Height = 21
      ReadOnly = True
      TabOrder = 1
      Text = '0'
    end
    object Edit_MinWeight: TEdit
      Left = 94
      Top = 74
      Width = 103
      Height = 21
      ReadOnly = True
      TabOrder = 2
      Text = '0'
    end
    object Edit_MaxWeight: TEdit
      Left = 94
      Top = 98
      Width = 103
      Height = 21
      ReadOnly = True
      TabOrder = 3
      Text = '0'
    end
    object Edit_QualifiedRate: TEdit
      Left = 94
      Top = 122
      Width = 103
      Height = 21
      ReadOnly = True
      TabOrder = 4
      Text = '0'
    end
    object Edit_totalNum: TEdit
      Left = 94
      Top = 146
      Width = 103
      Height = 21
      ReadOnly = True
      TabOrder = 5
      Text = '0'
    end
    object Edit_totalWeight: TEdit
      Left = 94
      Top = 170
      Width = 103
      Height = 21
      ReadOnly = True
      TabOrder = 6
      Text = '0'
    end
  end
  object GroupBox_Stat2: TGroupBox
    Left = 336
    Top = 164
    Width = 249
    Height = 209
    Caption = #21512#26684#20135#21697
    TabOrder = 5
    Visible = False
    object Label17: TLabel
      Left = 30
      Top = 30
      Width = 72
      Height = 13
      AutoSize = False
      Caption = #963'(n-1)'
    end
    object LabelUnit6: TLabel
      Left = 201
      Top = 30
      Width = 17
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Label19: TLabel
      Left = 30
      Top = 54
      Width = 72
      Height = 13
      AutoSize = False
      Caption = #24179#22343#20540
    end
    object LabelUnit7: TLabel
      Left = 201
      Top = 54
      Width = 17
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Label21: TLabel
      Left = 30
      Top = 78
      Width = 72
      Height = 13
      AutoSize = False
      Caption = #26368#23567#20540
    end
    object LabelUnit8: TLabel
      Left = 201
      Top = 78
      Width = 17
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Label23: TLabel
      Left = 30
      Top = 102
      Width = 72
      Height = 13
      AutoSize = False
      Caption = #26368#22823#20540
    end
    object LabelUnit9: TLabel
      Left = 201
      Top = 102
      Width = 17
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Label27: TLabel
      Left = 30
      Top = 150
      Width = 72
      Height = 13
      AutoSize = False
      Caption = #931#25968#37327#24635#35745
    end
    object Label28: TLabel
      Left = 201
      Top = 150
      Width = 17
      Height = 13
      AutoSize = False
      Caption = 'pcs'
    end
    object Label29: TLabel
      Left = 30
      Top = 174
      Width = 72
      Height = 13
      AutoSize = False
      Caption = #931#37325#37327#24635#35745
    end
    object LabelUnit10: TLabel
      Left = 201
      Top = 174
      Width = 17
      Height = 13
      AutoSize = False
      Caption = 'kg'
    end
    object Edit_StandardDeviation1: TEdit
      Left = 94
      Top = 26
      Width = 103
      Height = 21
      ReadOnly = True
      TabOrder = 0
      Text = '0'
    end
    object Edit_Average1: TEdit
      Left = 94
      Top = 50
      Width = 103
      Height = 21
      ReadOnly = True
      TabOrder = 1
      Text = '0'
    end
    object Edit_MinWeight1: TEdit
      Left = 94
      Top = 74
      Width = 103
      Height = 21
      ReadOnly = True
      TabOrder = 2
      Text = '0'
    end
    object Edit_MaxWeight1: TEdit
      Left = 94
      Top = 98
      Width = 103
      Height = 21
      ReadOnly = True
      TabOrder = 3
      Text = '0'
    end
    object Edit_totalNum1: TEdit
      Left = 94
      Top = 146
      Width = 103
      Height = 21
      ReadOnly = True
      TabOrder = 4
      Text = '0'
    end
    object Edit_totalWeight1: TEdit
      Left = 94
      Top = 170
      Width = 103
      Height = 21
      AutoSize = False
      ReadOnly = True
      TabOrder = 5
      Text = '0'
    end
  end
  object MainMenu1: TMainMenu
    Left = 576
    Top = 40
    object MN_Lock: TMenuItem
      Caption = #25805#20316#35299#38145
      Visible = False
      OnClick = MN_LockClick
    end
    object MN_Action: TMenuItem
      Caption = #25805#20316
      object MN_ResumePici: TMenuItem
        Caption = #32487#32493#25209#27425
        OnClick = MN_ResumePiciClick
      end
      object MN_StopPici: TMenuItem
        Caption = #20572#27490#25209#27425
        OnClick = MN_StopPiciClick
      end
      object MN_LoadProduct: TMenuItem
        Caption = #21152#36733#20135#21697
        Visible = False
        OnClick = MN_LoadProductClick
      end
      object N3: TMenuItem
        Caption = #27983#35272#32479#35745
        object MN_StatMode1: TMenuItem
          Caption = #25968#20540
          OnClick = MN_StatMode1Click
        end
        object MN_StatMode2: TMenuItem
          Caption = #22270#34920
          Enabled = False
        end
        object MN_StatCancel: TMenuItem
          Caption = #21462#28040
          OnClick = MN_StatCancelClick
        end
      end
      object MN_Close: TMenuItem
        Caption = #20851#38381
        OnClick = MN_CloseClick
      end
    end
  end
  object SecondsTimer: TTimer
    OnTimer = SecondsTimerTimer
    Left = 592
    Top = 104
  end
end
