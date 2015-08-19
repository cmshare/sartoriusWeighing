object FormCatalog: TFormCatalog
  Left = 307
  Top = 73
  Width = 823
  Height = 632
  Caption = 'FormCatalog'
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
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 807
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    Caption = #20135#21697#30446#24405
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
  end
  object DBGrid1: TDBGrid
    Left = 0
    Top = 41
    Width = 807
    Height = 533
    Align = alClient
    DataSource = DataSource1
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
    ReadOnly = True
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnDblClick = DBGrid1DblClick
  end
  object DataSource1: TDataSource
    Left = 200
    Top = 56
  end
  object MainMenu1: TMainMenu
    Left = 120
    Top = 8
    object N1: TMenuItem
      Caption = #25805#20316
      object MN_Print: TMenuItem
        Caption = #20445#23384#21040'Excel'
        OnClick = MN_PrintClick
      end
      object MN_Clear: TMenuItem
        Caption = #28165#31354
        OnClick = MN_ClearClick
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object MN_Close: TMenuItem
        Caption = #20851#38381
        OnClick = MN_CloseClick
      end
    end
  end
end
