object Form3: TForm3
  Left = 0
  Top = 0
  Caption = 'Form3'
  ClientHeight = 373
  ClientWidth = 826
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object pnlButton: TPanel
    Left = 0
    Top = 336
    Width = 826
    Height = 37
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    DesignSize = (
      826
      37)
    object btnOk: TButton
      Left = 654
      Top = 7
      Width = 80
      Height = 22
      Anchors = [akRight, akBottom]
      Caption = 'OK'
      TabOrder = 0
      OnClick = btnOkClick
    end
    object btnCancel: TButton
      Left = 740
      Top = 7
      Width = 80
      Height = 22
      Anchors = [akRight, akBottom]
      Caption = 'Cancel'
      TabOrder = 1
      OnClick = btnCancelClick
    end
  end
  object PageControl1: TPageControl
    Left = 216
    Top = 24
    Width = 585
    Height = 297
    ActivePage = TabSheet7
    TabOrder = 1
    object TabSheet6: TTabSheet
      Caption = 'TabSheet6'
    end
    object TabSheet7: TTabSheet
      Caption = 'TabSheet7'
      ImageIndex = 1
      object GroupBox1: TGroupBox
        Left = 11
        Top = 11
        Width = 160
        Height = 46
        Caption = 'Slide Show Interval'
        Padding.Left = 3
        Padding.Top = 3
        Padding.Right = 3
        Padding.Bottom = 3
        TabOrder = 0
        object Label3: TLabel
          Left = 62
          Top = 19
          Width = 31
          Height = 13
          Caption = 'm sec.'
        end
        object edtInterval: TEdit
          Left = 6
          Top = 19
          Width = 36
          Height = 21
          Alignment = taRightJustify
          NumbersOnly = True
          TabOrder = 0
          Text = '3000'
        end
        object udInterval: TUpDown
          Left = 42
          Top = 19
          Width = 15
          Height = 21
          Associate = edtInterval
          Min = 10
          Max = 32000
          Increment = 100
          Position = 3000
          TabOrder = 1
          Thousands = False
        end
      end
      object GroupBox5: TGroupBox
        Left = 169
        Top = 3
        Width = 160
        Height = 46
        Caption = #12474#12540#12512#12398#38291#38548
        Padding.Left = 3
        Padding.Top = 3
        Padding.Right = 3
        Padding.Bottom = 3
        TabOrder = 1
        object Label1: TLabel
          Left = 58
          Top = 22
          Width = 30
          Height = 13
          Caption = '%'#12378#12388
        end
        object edtZoomStep: TEdit
          Left = 5
          Top = 17
          Width = 32
          Height = 21
          NumbersOnly = True
          TabOrder = 0
          Text = '10'
        end
        object udZoomStep: TUpDown
          Left = 37
          Top = 17
          Width = 15
          Height = 21
          Associate = edtZoomStep
          Max = 1000
          Increment = 10
          Position = 10
          TabOrder = 1
          Thousands = False
        end
      end
      object GroupBox4: TGroupBox
        Left = 3
        Top = 159
        Width = 459
        Height = 106
        Caption = 'Title Formatting'
        Padding.Left = 3
        Padding.Top = 3
        Padding.Right = 3
        Padding.Bottom = 3
        TabOrder = 2
        object Label4: TLabel
          Left = 6
          Top = 16
          Width = 39
          Height = 13
          Caption = 'Title Bar'
        end
        object Label7: TLabel
          Left = 6
          Top = 59
          Width = 50
          Height = 13
          Caption = 'Status Bar'
        end
        object edtTitle: TEdit
          Left = 6
          Top = 32
          Width = 447
          Height = 21
          TabOrder = 0
        end
        object edtStatus: TEdit
          Left = 6
          Top = 77
          Width = 447
          Height = 21
          TabOrder = 1
        end
      end
      object GroupBox3: TGroupBox
        Left = 3
        Top = 107
        Width = 459
        Height = 46
        Caption = 'Susie Plug-in Folder (Blank to no use)'
        Padding.Left = 3
        Padding.Top = 3
        Padding.Right = 3
        Padding.Bottom = 3
        TabOrder = 3
        object edtSPI: TEdit
          Left = 6
          Top = 16
          Width = 447
          Height = 21
          TabOrder = 0
        end
      end
      object GroupBox2: TGroupBox
        Left = 3
        Top = 55
        Width = 458
        Height = 46
        Caption = 'Image File Extentions (Regex Format)'
        Padding.Left = 3
        Padding.Top = 3
        Padding.Right = 3
        Padding.Bottom = 3
        TabOrder = 4
        object edtExt: TEdit
          Left = 6
          Top = 18
          Width = 447
          Height = 21
          TabOrder = 0
        end
      end
    end
    object TabSheet8: TTabSheet
      Caption = 'TabSheet8'
      ImageIndex = 2
      object GroupBox6: TGroupBox
        Left = 3
        Top = 3
        Width = 571
        Height = 94
        Caption = 'Window Settings'
        TabOrder = 0
        object CheckBox1: TCheckBox
          Left = 11
          Top = 16
          Width = 177
          Height = 25
          Caption = 'Keep last window position.'
          TabOrder = 0
        end
        object CheckBox3: TCheckBox
          Left = 11
          Top = 64
          Width = 145
          Height = 25
          Caption = 'Enable Window Snap.'
          TabOrder = 1
        end
        object CheckBox2: TCheckBox
          Left = 11
          Top = 39
          Width = 145
          Height = 25
          Caption = 'Keep last window size.'
          TabOrder = 2
        end
      end
    end
    object TabSheet9: TTabSheet
      Caption = 'TabSheet9'
      ImageIndex = 3
    end
    object TabSheet10: TTabSheet
      Caption = 'TabSheet10'
      ImageIndex = 4
      object ListBox1: TListBox
        Left = 0
        Top = 3
        Width = 462
        Height = 182
        ItemHeight = 13
        Items.Strings = (
          '.bmp'
          '.gif'
          '.ico'
          '.jpg'
          '.png'
          '.tif'
          '.jp2'
          '.j2k')
        MultiSelect = True
        TabOrder = 0
      end
      object btnSendTo: TButton
        Left = 0
        Top = 191
        Width = 166
        Height = 22
        Caption = #36865#12427' '#12395#12471#12519#12540#12488#12459#12483#12488#12434#36861#21152#12377#12427
        TabOrder = 1
        OnClick = btnSendToClick
      end
    end
  end
end
