object FormWeighLogs: TFormWeighLogs
  Left = 164
  Top = 190
  BorderStyle = bsDialog
  Caption = 'FormWeighLogs'
  ClientHeight = 424
  ClientWidth = 670
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 670
    Height = 41
    Align = alTop
    BevelOuter = bvNone
    Caption = #20135#21697#35760#24405
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    DesignSize = (
      670
      41)
    object SpeedButton1: TSpeedButton
      Left = 608
      Top = 0
      Width = 63
      Height = 22
      Anchors = [akTop, akRight]
      Caption = #23548#20986'...'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
  end
  object DBGrid1: TDBGrid
    Left = 0
    Top = 41
    Width = 670
    Height = 342
    Align = alClient
    DataSource = DataSource1
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
  end
  object Panel2: TPanel
    Left = 0
    Top = 383
    Width = 670
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 2
    DesignSize = (
      670
      41)
    object Label1: TLabel
      Left = 10
      Top = 13
      Width = 57
      Height = 13
      AutoSize = False
      Caption = #26816#32034#65306' '#20174
    end
    object Label2: TLabel
      Left = 263
      Top = 14
      Width = 19
      Height = 13
      AutoSize = False
      Caption = '~'#33267
    end
    object Button_Refresh: TSpeedButton
      Left = 488
      Top = 8
      Width = 49
      Height = 22
      Caption = #21047#26032
      OnClick = Button_RefreshClick
    end
    object DatePickerBegin: TDateTimePicker
      Left = 69
      Top = 9
      Width = 112
      Height = 21
      CalAlignment = dtaLeft
      Date = 42025
      Time = 42025
      DateFormat = dfLong
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 0
    end
    object TimePickerBegin: TDateTimePicker
      Left = 181
      Top = 9
      Width = 78
      Height = 21
      CalAlignment = dtaLeft
      Date = 42025
      Time = 42025
      DateFormat = dfLong
      DateMode = dmComboBox
      Kind = dtkTime
      ParseInput = False
      TabOrder = 1
    end
    object DatePickerEnd: TDateTimePicker
      Left = 288
      Top = 9
      Width = 112
      Height = 21
      CalAlignment = dtaLeft
      Date = 42025
      Time = 42025
      DateFormat = dfLong
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 2
    end
    object TimePickerEnd: TDateTimePicker
      Left = 400
      Top = 9
      Width = 78
      Height = 21
      CalAlignment = dtaLeft
      Date = 42025
      Time = 42025
      DateFormat = dfLong
      DateMode = dmComboBox
      Kind = dtkTime
      ParseInput = False
      TabOrder = 3
    end
    object Button_Return: TButton
      Left = 590
      Top = 5
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #36820#22238
      TabOrder = 4
      OnClick = Button_ReturnClick
    end
  end
  object DataSource1: TDataSource
    Left = 200
    Top = 56
  end
end
