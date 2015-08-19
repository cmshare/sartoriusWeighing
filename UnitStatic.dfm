object FormStatic: TFormStatic
  Left = 320
  Top = 168
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'FormStatic'
  ClientHeight = 210
  ClientWidth = 584
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
  object PanelTop: TPanel
    Left = 0
    Top = 0
    Width = 584
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    Caption = #38745#24577#31216#37325
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
  end
  object Panel2: TPanel
    Left = 0
    Top = 41
    Width = 584
    Height = 74
    Align = alTop
    BevelInner = bvLowered
    BevelOuter = bvLowered
    Color = clYellow
    TabOrder = 1
    object Label_Weight: TLabel
      Left = 112
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
    object LabelNetGross: TLabel
      Left = 395
      Top = 19
      Width = 33
      Height = 13
      AutoSize = False
      Caption = 'NET'
      Visible = False
    end
    object LabelUnit: TStaticText
      Left = 393
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
    Left = 184
    Top = 144
    object MN_Lock: TMenuItem
      Caption = #25805#20316#35299#38145
      Visible = False
      OnClick = MN_LockClick
    end
    object MN_Action: TMenuItem
      Caption = #25805#20316
      object MN_ZeroWeight: TMenuItem
        Caption = #28165#38646
        OnClick = MN_ZeroWeightClick
      end
      object MN_NetWeight: TMenuItem
        Caption = #21435#30382
        OnClick = MN_NetWeightClick
      end
      object MN_GrossWeight: TMenuItem
        Caption = #21462#28040#21435#30382
        Visible = False
        OnClick = MN_GrossWeightClick
      end
      object N5: TMenuItem
        Caption = '-'
      end
      object MN_Close: TMenuItem
        Caption = #20851#38381
        OnClick = MN_CloseClick
      end
    end
  end
  object WeighTimer: TTimer
    Enabled = False
    OnTimer = WeighTimerTimer
    Left = 400
    Top = 144
  end
end
