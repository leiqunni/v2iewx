object Form3: TForm3
  Left = 0
  Top = 0
  Caption = 'Options'
  ClientHeight = 328
  ClientWidth = 630
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    630
    328)
  PixelsPerInch = 96
  TextHeight = 13
  object tabOption: TTabControl
    Left = 8
    Top = 8
    Width = 617
    Height = 282
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 0
    Tabs.Strings = (
      'General'
      'Key Config')
    TabIndex = 0
    DesignSize = (
      617
      282)
    object grpTextFormat: TGroupBox
      Left = 16
      Top = 32
      Width = 585
      Height = 81
      Anchors = [akLeft, akTop, akRight]
      Caption = 'Text Format'
      TabOrder = 0
      DesignSize = (
        585
        81)
      object Label1: TLabel
        Left = 16
        Top = 24
        Width = 33
        Height = 13
        Caption = 'Title'
      end
      object Label2: TLabel
        Left = 16
        Top = 48
        Width = 31
        Height = 13
        Caption = 'Status'
      end
      object edtTitle: TEdit
        Left = 64
        Top = 21
        Width = 505
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 0
      end
      object edtStatus: TEdit
        Left = 64
        Top = 48
        Width = 505
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 1
      end
    end
    object GroupBox1: TGroupBox
      Left = 16
      Top = 119
      Width = 585
      Height = 58
      Anchors = [akLeft, akTop, akRight]
      Caption = 'File Extention'
      TabOrder = 1
      DesignSize = (
        585
        58)
      object Edit3: TEdit
        Left = 64
        Top = 24
        Width = 505
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 0
        Text = 'Edit1'
      end
    end
  end
  object btnApply: TButton
    Left = 346
    Top = 296
    Width = 88
    Height = 24
    Anchors = [akRight, akBottom]
    Caption = '&Apply'
    Enabled = False
    TabOrder = 1
  end
  object btnOk: TButton
    Left = 440
    Top = 296
    Width = 88
    Height = 24
    Anchors = [akRight, akBottom]
    Caption = '&Ok'
    TabOrder = 2
  end
  object btnCancel: TButton
    Left = 534
    Top = 296
    Width = 88
    Height = 24
    Anchors = [akRight, akBottom]
    Caption = '&Cancel'
    TabOrder = 3
  end
end
