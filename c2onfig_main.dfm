object Form4: TForm4
  Left = 0
  Top = 0
  Caption = 'Form4'
  ClientHeight = 447
  ClientWidth = 710
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 177
    Top = 0
    Width = 4
    Height = 447
    ExplicitHeight = 333
  end
  object pnlEdit: TPanel
    Left = 181
    Top = 0
    Width = 529
    Height = 447
    Align = alClient
    ShowCaption = False
    TabOrder = 0
    ExplicitLeft = 182
    ExplicitTop = 8
    DesignSize = (
      529
      447)
    object Splitter2: TSplitter
      Left = 1
      Top = 339
      Width = 527
      Height = 4
      Cursor = crVSplit
      Align = alBottom
      Beveled = True
      ExplicitTop = 113
    end
    object grpValue: TGroupBox
      Left = 1
      Top = 343
      Width = 527
      Height = 103
      Align = alBottom
      Caption = 'Value'
      TabOrder = 1
      ExplicitLeft = 6
      ExplicitTop = 349
      DesignSize = (
        527
        103)
      object edtString: TEdit
        Left = 14
        Top = 23
        Width = 459
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 0
      end
      object cmbBool: TComboBox
        Left = 14
        Top = 50
        Width = 120
        Height = 21
        Style = csDropDownList
        TabOrder = 1
        Items.Strings = (
          'True'
          'False')
      end
    end
    object btnApply: TButton
      Left = 368
      Top = 413
      Width = 73
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = '&Apply'
      TabOrder = 2
    end
    object btnOK: TButton
      Left = 447
      Top = 413
      Width = 73
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = '&OK'
      TabOrder = 3
    end
    object grpDescription: TGroupBox
      Left = 1
      Top = 1
      Width = 527
      Height = 338
      Align = alClient
      Caption = 'Description'
      TabOrder = 0
      ExplicitLeft = 2
      ExplicitTop = -1
      object pnlDescription: TPanel
        AlignWithMargins = True
        Left = 5
        Top = 18
        Width = 517
        Height = 315
        Align = alClient
        Alignment = taLeftJustify
        BevelOuter = bvNone
        TabOrder = 0
        VerticalAlignment = taAlignTop
        ExplicitHeight = 88
        object ValueListEditor1: TValueListEditor
          Left = 32
          Top = 24
          Width = 329
          Height = 209
          Strings.Strings = (
            'abc=123'
            'def=789'
            '')
          TabOrder = 0
          ColWidths = (
            150
            173)
        end
      end
    end
    object UpDown1: TUpDown
      Left = 480
      Top = 365
      Width = 17
      Height = 22
      TabOrder = 4
    end
  end
  object pnlKeyTree: TPanel
    Left = 0
    Top = 0
    Width = 177
    Height = 447
    Align = alLeft
    Caption = 'pnlDescription'
    ShowCaption = False
    TabOrder = 1
    ExplicitHeight = 367
    object TreeView: TTreeView
      Left = 1
      Top = 1
      Width = 175
      Height = 445
      Align = alClient
      Indent = 19
      ReadOnly = True
      TabOrder = 0
      OnClick = TreeViewClick
      ExplicitHeight = 365
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 350
    Top = 399
  end
  object PopupMenu2: TPopupMenu
    Left = 430
    Top = 399
  end
end
