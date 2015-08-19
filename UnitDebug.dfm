object FormDebug: TFormDebug
  Left = 192
  Top = 100
  Width = 870
  Height = 500
  Caption = 'FormDebug'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object RichEdit1: TRichEdit
    Left = 0
    Top = 0
    Width = 854
    Height = 421
    Align = alClient
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object Panel1: TPanel
    Left = 0
    Top = 421
    Width = 854
    Height = 41
    Align = alBottom
    TabOrder = 1
    object Button_Clear: TButton
      Left = 16
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Clear'
      TabOrder = 0
      OnClick = Button_ClearClick
    end
  end
end
