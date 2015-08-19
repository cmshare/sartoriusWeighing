object FormConnections: TFormConnections
  Left = 509
  Top = 261
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'FormConnections'
  ClientHeight = 271
  ClientWidth = 281
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object RadioGroup1: TRadioGroup
    Left = 16
    Top = 16
    Width = 249
    Height = 41
    Caption = 'Connection'
    Columns = 2
    Items.Strings = (
      'SerialPort'
      'TCP/IP')
    TabOrder = 0
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 72
    Width = 120
    Height = 145
    Caption = 'Seriao Port'
    TabOrder = 1
    object ComboBox_PortNum: TComboBox
      Left = 8
      Top = 23
      Width = 105
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
    end
    object ComboBox1: TComboBox
      Left = 8
      Top = 48
      Width = 105
      Height = 21
      ItemHeight = 13
      TabOrder = 1
      Text = 'ComboBox1'
    end
    object ComboBox2: TComboBox
      Left = 8
      Top = 72
      Width = 105
      Height = 21
      ItemHeight = 13
      TabOrder = 2
      Text = 'ComboBox1'
    end
    object ComboBox3: TComboBox
      Left = 8
      Top = 96
      Width = 105
      Height = 21
      ItemHeight = 13
      TabOrder = 3
      Text = 'ComboBox1'
    end
    object ComboBox4: TComboBox
      Left = 8
      Top = 116
      Width = 105
      Height = 21
      ItemHeight = 13
      TabOrder = 4
      Text = 'ComboBox1'
    end
  end
  object BitBtn1: TBitBtn
    Left = 184
    Top = 192
    Width = 75
    Height = 25
    TabOrder = 2
    Kind = bkOK
  end
  object BitBtn2: TBitBtn
    Left = 184
    Top = 216
    Width = 75
    Height = 25
    TabOrder = 3
    Kind = bkCancel
  end
  object GroupBox2: TGroupBox
    Left = 145
    Top = 73
    Width = 120
    Height = 104
    Caption = 'Remote Server'
    TabOrder = 4
    object Label1: TLabel
      Left = 8
      Top = 24
      Width = 51
      Height = 13
      Caption = 'IP Address'
    end
    object Label2: TLabel
      Left = 8
      Top = 64
      Width = 19
      Height = 13
      Caption = 'Port'
    end
    object Edit1: TEdit
      Left = 8
      Top = 40
      Width = 100
      Height = 21
      TabOrder = 0
      Text = '0.0.0.0'
    end
    object Edit2: TEdit
      Left = 8
      Top = 80
      Width = 100
      Height = 21
      TabOrder = 1
      Text = '8080'
    end
  end
end
