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
  object btnApply: TButton
    Left = 346
    Top = 296
    Width = 88
    Height = 24
    Anchors = [akRight, akBottom]
    Caption = '&Apply'
    Enabled = False
    TabOrder = 0
  end
  object btnOk: TButton
    Left = 440
    Top = 296
    Width = 88
    Height = 24
    Anchors = [akRight, akBottom]
    Caption = '&Ok'
    TabOrder = 1
  end
  object btnCancel: TButton
    Left = 534
    Top = 296
    Width = 88
    Height = 24
    Anchors = [akRight, akBottom]
    Caption = '&Cancel'
    TabOrder = 2
  end
  object PageControl1: TPageControl
    Left = 8
    Top = 8
    Width = 614
    Height = 282
    ActivePage = TabSheet1
    TabOrder = 3
    object TabSheet1: TTabSheet
      Caption = 'General'
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 609
      ExplicitHeight = 0
      DesignSize = (
        606
        254)
      object grpTextFormat: TGroupBox
        Left = 3
        Top = 3
        Width = 600
        Height = 81
        Anchors = [akLeft, akTop, akRight]
        Caption = 'Text Format'
        TabOrder = 0
        DesignSize = (
          600
          81)
        object Label1: TLabel
          Left = 16
          Top = 24
          Width = 20
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
          Width = 520
          Height = 21
          Anchors = [akLeft, akTop, akRight]
          TabOrder = 0
          ExplicitWidth = 505
        end
        object edtStatus: TEdit
          Left = 64
          Top = 48
          Width = 520
          Height = 21
          Anchors = [akLeft, akTop, akRight]
          TabOrder = 1
          ExplicitWidth = 505
        end
      end
      object GroupBox1: TGroupBox
        Left = 0
        Top = 90
        Width = 603
        Height = 58
        Anchors = [akLeft, akTop, akRight]
        Caption = 'File Extention'
        TabOrder = 1
        DesignSize = (
          603
          58)
        object edtExt: TEdit
          Left = 67
          Top = 24
          Width = 520
          Height = 21
          Anchors = [akLeft, akTop, akRight]
          TabOrder = 0
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Key config'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 609
      ExplicitHeight = 0
    end
  end
end