// ---------------------------------------------------------------------------
#include <vcl.h>
#include "func.h"
#pragma hdrstop
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "shlwapi.lib"

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_ParseCmdLine(TStringList *list) {
	if (list->Count == 1 && FileExists(list->Strings[0])) {
		LoadFiles(list->Strings[0]);
	} else {
		LoadFiles(list);
	}
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_NewWindow() {
	RunProcess(Application->ExeName, NULL);
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::RunProcess(String path, String argv) {
	STARTUPINFOW si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	si.cb = sizeof(STARTUPINFO);

	CreateProcessW(path.c_str(), argv.c_str(), NULL, NULL, NULL, NULL, NULL, NULL, &si, &pi);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_Next() {
	if (fileList->Count == 0) {
		return;
	}

	if (ScrollBar->Position >= fileList->Count) {
		ScrollBar->Position = 1;
	} else {
		ScrollBar->Position += 1;
	}
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_Prev() {
	if (fileList->Count == 0) {
		return;
	}

	if (ScrollBar->Position <= 1) {
		ScrollBar->Position = fileList->Count;
	} else {
		ScrollBar->Position -= 1;
	}
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_FileOpenDialog() {
	TStringBuilder *sb3 = new TStringBuilder();

	TMatchCollection m = TRegEx::Matches(conf.Ext, "\\.(.+?)\\$");
	for (int i = 1; i < m.Count; ++i) {
		String _ext = m.Item[i].Groups[1].Value;
		sb3->Append("*." + _ext + "; ");
	}

	OpenDialog->Filter = "All Image Types (" + sb3->ToString() + ")|" + sb3->ToString() + "|" + "All Files (*.*)|*.*|";

	delete sb3;

	if (OpenDialog->Execute() == true) {
		LoadFiles(OpenDialog->FileName);
	}
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_PrevFrame() {
	Gdv1->DisplayPreviousFrame();
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_NextFrame() {
	Gdv1->DisplayNextFrame();
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_Options() {
	RunProcess(L"config++.exe", NULL);
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_SlideShow() {
	if (Timer->Enabled) {
		Timer->Enabled = false;
		tbtnSlideShow->Down = false;
		mnuPlaySlideShow->Caption = SlideShowStart;
		tbtnSlideShow->Hint = SlideShowStart;
	} else {
		Timer->Enabled = true;
		tbtnSlideShow->Down = true;
		mnuPlaySlideShow->Caption = SlideShowStop;
		tbtnSlideShow->Hint = SlideShowStop;
	}
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_ImageCopy() {
	Gdv1->Copy2Clipboard();
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_PathCopy() {
	Clipboard()->AsText = ((TFI*)(fileList->Items[ScrollBar->Position - 1]))->FullName;
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_MainMenu(bool value) {
	MainMenu->Tag = value;
	mnuViewMainMenu->Checked = value;

	if ((Menu != NULL) && value) {
		MainMenu->Tag = true;
		return;
	}

	if (value) {
		pumMain->Items->Remove(mnuFile);
		pumMain->Items->Remove(mnuEdit);
		pumMain->Items->Remove(mnuView);
		pumMain->Items->Remove(mnuTools);
		pumMain->Items->Remove(mnuHelp);
		MainMenu->Items->Add(mnuFile);
		MainMenu->Items->Add(mnuEdit);
		MainMenu->Items->Add(mnuView);
		MainMenu->Items->Add(mnuTools);
		MainMenu->Items->Add(mnuHelp);
		Menu = MainMenu;
	} else {
		Menu = NULL;
		MainMenu->Items->Remove(mnuFile);
		MainMenu->Items->Remove(mnuEdit);
		MainMenu->Items->Remove(mnuView);
		MainMenu->Items->Remove(mnuTools);
		MainMenu->Items->Remove(mnuHelp);
		pumMain->Items->Add(mnuFile);
		pumMain->Items->Add(mnuEdit);
		pumMain->Items->Add(mnuView);
		pumMain->Items->Add(mnuTools);
		pumMain->Items->Add(mnuHelp);
	}
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_ScrollBar(bool value) {
	ScrollBar->Visible = value;
	mnuViewScrollBar->Checked = value;
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_ToolBar(bool value) {
	ToolBar->Visible = value;
	mnuViewToolBar->Checked = value;
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_StatusBar(bool value) {
	StatusBar->Top = ToolBar->Top + ToolBar->Height;
	StatusBar->Visible = value;
	mnuViewStatusBar->Checked = value;
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_Reset() {
	switch (conf.rot) {
	case 1:
		Gdv1->Rotate270();
		break;
	case 2:
		Gdv1->Rotate180();
		break;
	case 3:
		Gdv1->Rotate90();
		break;
	}

	conf.rot = 0;
	fn_ZoomMode(Gdv1->ZoomMode);
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_RotateRight() {
	Gdv1->Rotate90();
	if (++conf.rot == 4) {
		conf.rot = 0;
	}
	tbtnKeepRot->ImageIndex = 12 + conf.rot;
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_RotateLeft() {
	Gdv1->Rotate270();
	if (--conf.rot == -1) {
		conf.rot = 3;
	}
	tbtnKeepRot->ImageIndex = 12 + conf.rot;
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_KeepRot(bool value) {
	mnuViewKeepRot->Checked = value;
	tbtnKeepRot->Down = value;
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_ZoomMode(int value) {
	switch (value) {
	case 1: // []
		Gdv1->ZoomMode = 1;
		mnuViewActual->Checked = true;
		mnuViewOptimizeWindowSize->Enabled = true;
		tbtnActual->Down = true;
		break;
	case 2: // []
		Gdv1->ZoomMode = 2;
		mnuViewBestfit->Checked = true;
		mnuViewOptimizeWindowSize->Enabled = false;
		tbtnBestfit->Down = true;
		break;
	case 6: // []
		Gdv1->ZoomMode = 6;
		mnuViewSpread->Checked = true;
		mnuViewOptimizeWindowSize->Enabled = false;
		tbtnSpread->Down = true;
		break;
	case 99:
		if (Gdv1->Width > Gdv1->ImageWidth && Gdv1->Height > Gdv1->ImageHeight) {
			Gdv1->ZoomMode = 1;
		} else {
			Gdv1->ZoomMode = 2;
		}
		mnuViewInWindow->Checked = true;
		mnuViewOptimizeWindowSize->Enabled = false;
		tbtnInWindow->Down = true;
		break;
	}
}
// ---------------------------------------------------------------------------
// []
void __fastcall TForm1::fn_OptimizeWindowSize(bool value) {
	this->ClientWidth = Gdv1->ImageWidth;
	this->ClientHeight = Gdv1->ImageHeight - (ScrollBar->Visible ? ScrollBar->Height : 0) - (ToolBar->Visible ? ToolBar->Height : 0) -
		(StatusBar->Visible ? StatusBar->Height : 0);
	mnuViewOptimizeWindowSize->Checked = value;
}
// ---------------------------------------------------------------------------
// Sort
void __fastcall TForm1::fn_Sort(SortOrder order, bool asc) {
	conf.order = order;
	conf.asc = asc;

	if (asc) {
		mnuViewOrderAsc->Checked = true;
	} else {
		mnuViewOrderDesc->Checked = true;
	}

	switch (order) {
	case kByName: // [名前]
		if (asc) {
			fileList->Sort(cmpNameAsc);
		} else {
			fileList->Sort(cmpNameDesc);
		}
		mnuViewOrderName->Checked = true;
		break;
	case kByNameNum: // [数値]
		if (asc) {
			fileList->Sort(cmpNameNumAsc);
		} else {
			fileList->Sort(cmpNameNumDesc);
		}
		mnuViewOrderNameNum->Checked = true;
		break;
	case kByTime: // [更新日時]
		if (asc) {
			fileList->Sort(cmpTimeAsc);
		} else {
			fileList->Sort(cmpTimeDesc);
		}
		mnuViewOrderDate->Checked = true;
		break;
	case kByType: // [種類]
		if (asc) {
			fileList->Sort(cmpTypeAsc);
		} else {
			fileList->Sort(cmpTypeDesc);
		}
		mnuViewOrderType->Checked = true;
		break;
	case kBySize: // [サイズ]
		if (asc) {
			fileList->Sort(cmpSizeAsc);
		} else {
			fileList->Sort(cmpSizeDesc);
		}
		mnuViewOrderSize->Checked = true;
		break;
	}
}
// ---------------------------------------------------------------------------
// [表示]-[画質]-[自動]
void __fastcall TForm1::fn_QualityAuto(bool value) {
	Gdv1->ViewerQualityAuto = value;
	mnuViewQualityAuto->Checked = value;
}
// ---------------------------------------------------------------------------
// [表示]-[画質]-[低]
void __fastcall TForm1::fn_Quality(int value) {
	Gdv1->ViewerQuality = value;
	switch (value) {
	case 0: // 低
		mnuViewQualityLow->Checked = true;
		break;
	case 1: // バイリニア
		mnuViewQualityBilinear->Checked = true;
		break;
	case 2: // バイキュービック
		mnuViewQualityBicubic->Checked = true;
		break;
	case 3: // バイリニアHQ
		mnuViewQualityBilinearHQ->Checked = true;
		break;
	case 4: // バイキュービックHQ
		mnuViewQualityBicubicHQ->Checked = true;
		break;
	}
}
// ---------------------------------------------------------------------------
// [描画時間の最適化]
void __fastcall TForm1::fn_OptimizeDrawingSpeed(bool value) {
	Gdv1->OptimizeDrawingSpeed = value;
	mnuViewOptimizeDrawingSpeed->Checked = value;
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_WindowMaximize() {
	if (this->WindowState == wsNormal) {
		this->WindowState = wsMaximized;
	} else {
		this->WindowState = wsNormal;
	}
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_WindowMinimize() {
	if (this->WindowState == wsNormal) {
		this->WindowState = wsMinimized;
	} else {
		this->WindowState = wsNormal;
	}
}
// ---------------------------------------------------------------------------
// [フルスクリーン]
void __fastcall TForm1::fn_FullScreen() {
	if (mnuViewFullScreen->Checked) {
		BorderStyle = bsSizeable;
		WindowState = wsNormal;
		mnuViewFullScreen->Checked = false;
	} else {
		BorderStyle = bsNone;
		WindowState = wsMaximized;
		mnuViewFullScreen->Checked = true;
	}
}
// ---------------------------------------------------------------------------
// [拡大]
void __fastcall TForm1::fn_ZoomIn() {
	Gdv1->ZoomIN();
	fn_StatusText();
}
// ---------------------------------------------------------------------------
// [縮小]
void __fastcall TForm1::fn_ZoomOut() {
	Gdv1->ZoomOUT();
	fn_StatusText();
}
// ---------------------------------------------------------------------------
// [縮小]
void __fastcall TForm1::fn_ZoomStep(int value) {
	Gdv1->ZoomStep = value;
}
// ---------------------------------------------------------------------------
// [縮小]
void __fastcall TForm1::fn_Glass(TGdViewer *gv, bool value) {
	if (value) {
		gv->BackColor = clBlack; // StringToColor(L"000000");
		Form1->GlassFrame->Enabled = true;
		Form1->GlassFrame->SheetOfGlass = true;
	} else {
		gv->BackColor = clWhite; // StringToColor(L"ffffff");
		Form1->GlassFrame->Enabled = false;
		Form1->GlassFrame->SheetOfGlass = false;
	}
}
// ---------------------------------------------------------------------------
// [ファイル削除]
void __fastcall TForm1::fn_DeleteFile(int flags) {
	if (fileList->Count == 0) {
		return;
	}

	String path = ((TFI*)fileList->Items[ScrollBar->Position - 1])->FullName;
	path.cat_printf(L"%c%c", 0, 0);

	SHFILEOPSTRUCT shfo;
	ZeroMemory(&shfo, sizeof(SHFILEOPSTRUCT));
	shfo.hwnd = Application->Handle;
	shfo.wFunc = FO_DELETE;
	shfo.pFrom = path.w_str();
	shfo.pTo = NULL;
	shfo.fFlags = flags;
	SHFileOperation(&shfo);

	if (shfo.fAnyOperationsAborted != true) {
		fileList->Delete(ScrollBar->Position - 1);
		ScrollBar->Max--;
		fn_Next();
	}
}
// ---------------------------------------------------------------------------
// [ステータス バーの情報表示]
void __fastcall TForm1::fn_StatusText() {
	if (StatusBar->Visible) {
		StatusBar->SimpleText = fn_TitleFormatting(conf.StatusText);
	}
}
// ---------------------------------------------------------------------------
// [タイトル フォーマッティング]
String __fastcall TForm1::fn_TitleFormatting(String value) {
	gFI = (TFI*)(fileList->Items[ScrollBar->Position - 1]);

	value = StringReplace(value, "%_path%", gFI->FullName, TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_filename_ext%", ExtractFileName(gFI->FullName), TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_filesize%", gFI->Size, TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_filesize_kb%", gFI->Size / 1024, TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_filesize_mb%", gFI->Size / 1048576, TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_width%", Gdv1->ImageWidth, TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_height%", Gdv1->ImageHeight, TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_zoom%", int(Gdv1->ZOOM * 100), TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_last_modified%", (gFI->Date).DateTimeString(), TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_position%", ScrollBar->Position, TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_total%", fileList->Count, TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_codec%", Gdv1->GetImageFormat(), TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_isspi%", conf.isSPI ? "SPI" : "GD", TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_errorcode%", IntToStr(conf.errorcode), TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_pagecount%", IntToStr(Gdv1->PageCount), TReplaceFlags() << rfReplaceAll);

	return (value);
}
// ---------------------------------------------------------------------------
//
TColor __fastcall TForm1::fn_IntToColor(int rgb) {
	int r = 255 - (rgb % 256);
	int g = 255 - ((rgb / 256) % 256);
	int b = 255 - (rgb / 65536);
	return RGB(r, g, b);
}
// ---------------------------------------------------------------------------
//
