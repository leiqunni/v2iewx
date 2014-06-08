//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "config.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
String IniFilePath = ExtractFilePath(Application->ExeName) + "viewx++.ini"; // 設定ファイルのパス
int KeyConfig[255];
int SelectedRow;

#pragma region " KeyString Init "

// キー初期化
String KeyString[255] = {
	"",
	"マウス左ボタン",
	"マウス右ボタン",
	"",
	"マウス中央ボタン",
	"",
	"",
	"",
	"BackSpace",
	"TABキー",
	"",
	"",
	"",
	"リターン(Enter)",
	"",
	"",
	"Shift",
	"Ctrl",
	"Alt(GRPH)",
	"Pause",
	"CapsLock",
	"カナ",
	"",
	"",
	"",
	"漢字",
	"",
	"ESC",
	"変換",
	"無変換",
	"",
	"",
	"スペースバー",
	"PageUp(RollDown)",
	"PageDown(RollUp)",
	"End(Help)",
	"Home",
	"←",
	"↑",
	"→",
	"↓",
	"",
	"",
	"",
	"PrintScreen(COPY)",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"左Windowsキー",
	"右Windowsキー",
	"アプリケーションキー",
	"",
	"",
	"Num 0",
	"Num 1",
	"Num 2",
	"Num 3",
	"Num 4",
	"Num 5",
	"Num 6",
	"Num 7",
	"Num 8",
	"Num 9",
	"Num *",
	"Num +",
	"Num ,",
	"Num -",
	"Num .",
	"Num /",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
	"F13",
	"F14",
	"F15",
	"F16",
	"F17",
	"F18",
	"F19",
	"F20",
	"F21",
	"F22",
	"F23",
	"F24",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"NumLock",
	"ScrollLock",
	"Num =",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"左Shift",
	"右Shift",
	"左Ctrl",
	"右Ctrl",
	"左Alt",
	"右Alt",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	":",
	";",
	",",
	"-",
	".",
	"/",
	"@",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"[",
	"\\",
	"]",
	"^",
	"_",
	"",
	"",
	"_",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	""
};

#pragma end_region

#pragma region " ToolBar "

// 動作初期化
String ActionString[] = {
	"設定無し",
	"新しいウィンドウを開く",
	"ファイルの削除",
	"ファイルの削除（確認無し）",
	"スライド ショーの実行/停止",
	"終了",
	"前へ戻る",
	"次へ進む",
	"拡大",
	"縮小",
	"メイン メニューの表示切り替え",
	"スクロール バーの表示切り替え",
	"ツール バーの表示切り替え",
	"ステータス バーの表示切り替え",
	"右回転",
	"左回転",
	"ウィンドウに合わせる",
	"ウィンドウに収める",
	"原寸大",
	"名前で並び替え",
	"数値順で並び替え",
	"更新日時で並び替え",
	"種類で並び替え",
	"サイズで並び替え",
	"昇順/降順",
	"画質自動",
	"画質低",
	"画質バイリニア",
	"画質バイキュービック",
	"画質バイリニアHQ",
	"画質バイキュービックHQ",
	"全画面表示"
};

#pragma end_region

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
//	for (int n = 0; n < 31; n ++) cmbAction->Items->Add(ActionString[n]);
	LoadIniFile();
}
//---------------------------------------------------------------------------
//
void __fastcall TForm3::btnOkClick(TObject *Sender)
{
	if (ListBox1->Selected[0]) {
		FileAssociate(".bmp", "viewx.bmpfile", "BMP", ",2");
	}
	if (ListBox1->Selected[1]) {
		FileAssociate(".gif", "viewx.giffile", "GIF", ",3");
	}
	if (ListBox1->Selected[2]) {
		FileAssociate(".ico", "viewx.icofile", "ICON", "");
	}
	if (ListBox1->Selected[3]) {
		FileAssociate(".jpg", "viewx.jpgfile", "JPEG", ",4");
		FileAssociate(".jpeg", "viewx.jpgfile", "JPEG", ",4");
		FileAssociate(".jpe", "viewx.jpgfile", "JPEG", ",4");
	}
	if (ListBox1->Selected[4]) {
		FileAssociate(".png", "viewx.pngfile", "PNG", ",5");
	}
	if (ListBox1->Selected[5]) {
		FileAssociate(".tif", "viewx.tiffile", "TIFF", "");
		FileAssociate(".tiff", "viewx.tiffile", "TIFF", "");
	}
	if (ListBox1->Selected[6]) {
		FileAssociate(".jp2", "viewx.jpeg2000file", "JPEG2000", "");
		FileAssociate(".j2k", "viewx.jpeg2000file", "JPEG2000", "");
	}

	SaveIniFile();
	ShowMessage("設定を反映させるには、アプリケーションを再起動してください。");
	exit(0);
}
//---------------------------------------------------------------------------
//
void __fastcall TForm3::btnCancelClick(TObject *Sender)
{
	exit(0);
}
//---------------------------------------------------------------------------
// ファイルの関連付け
void __fastcall TForm3::FileAssociate(String extension, String fileType, String description, String iclNum)
{
	// 実行するコマンドライン
	String commandLine = "\"" + ExtractFilePath(Application->ExeName) + "viewx++.exe" + "\" \"%1\"";

	// 説明（必要なし）
//	AnsiString description = "viewx++";

	// 動詞の説明（エクスプローラのコンテキストメニューに表示される）
	// （必要なし）
	// Dim verb_description As String = "MyApplicationで開く(&O)"

	// アイコンのパスとインデックス
	String iclPath = ExtractFilePath(Application->ExeName) + "viewx_icon.dll";

	TRegistry *Registry = new TRegistry;
	Registry->RootKey = HKEY_CURRENT_USER;

	// ファイルタイプを登録
	Registry->OpenKey("Software\\Classes\\" + extension, true);
	Registry->WriteString("", fileType);
	Registry->CloseKey();

	// ファイルタイプとその説明を登録
	Registry->OpenKey("Software\\Classes\\" + fileType, true);
	Registry->WriteString("", description + " viewx++");
	Registry->CloseKey();

	// 動詞とその説明とコマンドラインを登録
	Registry->OpenKey("Software\\Classes\\" + fileType + "\\shell\\open\\command\\", true);
	Registry->WriteString("", commandLine);
	Registry->CloseKey();

	// アイコンの登録
	Registry->OpenKey("Software\\Classes\\" + fileType + "\\DefaultIcon", true);
	Registry->WriteString("", iclPath + iclNum);
	Registry->CloseKey();
}
//---------------------------------------------------------------------------
//
void __fastcall TForm3::LoadIniFile()
{
	TMemIniFile *pini = new TMemIniFile(IniFilePath);

	udZoomStep->Position = pini->ReadInteger("GdViewer", "ZoomStep", 10);

	udInterval->Position = pini->ReadInteger("Function", "Interval", 3000);
	edtTitle->Text = pini->ReadString("Function", "Title", "%_filename_ext% [%_position%/%_total%] - viewx++");
	edtStatus->Text = pini->ReadString("Function", "Status", "大きさ: %_width% x %_height% 更新日時: %_last_modified% サイズ: %_filesize_kb% KB 拡大率: %_zoom% %");
	edtExt->Text = pini->ReadString("Function", "Ext", "\\.bmp$|\\.gif$|\\.ico$|\\.jpe$|\\.jpeg$|\\.jpg$|\\.pcx$|\\.png$|\\.tif$|\\.tif$|\\.tiff$|\\.wmf$");

	edtSPI->Text = pini->ReadString("SPI", "Path", "");

	for (int n = 0; n <= 255; n ++) {
//		if (KeyString[n].Length() == 0) continue;
		KeyConfig[n] = pini->ReadInteger("Key", IntToStr(n), 0);
//		if (KeyConfig[n] < 0 || KeyConfig[n] > 9) KeyConfig[n] = 0;
//		ListView1->Items->Add();
//		ListView1->Items->Item[n]->Caption = IntToStr(n);
//		ListView1->Items->Item[n]->SubItems->Add(KeyString[n]);
//		ListView1->Items->Item[n]->SubItems->Add(KeyConfig[n]);
//		ListView1->Items->Item[n]->SubItems->Add(ActionString[KeyConfig[n]]);
	}

	delete pini;
}
//---------------------------------------------------------------------------
//
void __fastcall TForm3::SaveIniFile()
{
	TMemIniFile *pini = new TMemIniFile(IniFilePath);

	pini->WriteInteger("GdViewer", "ZoomStep", StrToInt(edtZoomStep->Text));

	pini->WriteInteger("Function", "Interval", StrToInt(edtInterval->Text));
	pini->WriteString("Function", "Title", edtTitle->Text);
	pini->WriteString("Function", "Status", edtStatus->Text);
	pini->WriteString("Function", "Ext", edtExt->Text);

	pini->WriteString("SPI", "Path", edtSPI->Text);

	for (int n = 0; n <= 255; n ++) {
		if (KeyConfig[n] == 0) {
			pini->DeleteKey("Key", IntToStr(n));
		} else {
			pini->WriteInteger("Key", IntToStr(n), KeyConfig[n]);
		}
	}

	pini->UpdateFile();
	delete pini;
}
//---------------------------------------------------------------------------
//
void __fastcall TForm3::ListView1SelectItem(TObject *Sender, TListItem *Item, bool Selected)
{
//	edtKey->Text = KeyString[Item->Index];
	SelectedRow = Item->Index;
}
//---------------------------------------------------------------------------
//
void __fastcall TForm3::cmbActionChange(TObject *Sender)
{
//	ListView1->Items->Item[SelectedRow]->SubItems->Strings[1] = IntToStr(cmbAction->ItemIndex);
//	ListView1->Items->Item[SelectedRow]->SubItems->Strings[2] = ActionString[cmbAction->ItemIndex];
//	KeyConfig[SelectedRow] = cmbAction->ItemIndex;
}
//---------------------------------------------------------------------------
//
void __fastcall TForm3::btnSendToClick(TObject *Sender)
{
	WinExec("wscript.exe SendTo.vbs", SW_SHOW);
}
//---------------------------------------------------------------------------


