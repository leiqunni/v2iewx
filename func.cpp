﻿// ---------------------------------------------------------------------------
#include <vcl.h>
#include "func.h"
#pragma hdrstop
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "shlwapi.lib"

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_ParseFiles(TStringList *list) {
	flst->Clear();

	if (list->Count == 1 && FileExists(list->Strings[0])) {
		fn_LoadFiles(list->Strings[0]);
	} else {
		fn_LoadFiles(list);
	}
}

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_LoadFiles(TStringList *list) {
	for (int i = 0; i < list->Count; ++i) {
		if (DirectoryExists(list->Strings[i])) {
			fn_FindDir(list->Strings[i], "*.*");
		} else {
			fn_FindDir(IncludeTrailingPathDelimiter(ExtractFileDir(list->Strings[i])), list->Strings[i]);
		}
	}

	if (flst->Count > 0) {
		fn_Sort(conf.order, conf.asc);
		ScrollBar->Max = flst->Count;
		ScrollBar->Position = 1;
		ScrollBarChange(NULL);
	}
}

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_LoadFiles(String path) {
	fn_FindDir(IncludeTrailingPathDelimiter(ExtractFileDir(path)), L"*.*");

	if (flst->Count > 0) {
		fn_Sort(conf.order, conf.asc);
		ScrollBar->Max = flst->Count;
		for (int i = 0; i < flst->Count; ++i) {
			if (((TFI*)(flst->Items[i]))->FullName == path) {
				ScrollBar->Position = i + 1;
				if (ScrollBar->Position == 1) {
					ScrollBarChange(NULL);
				}
				break;
			}
		}
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
	if (flst->Count == 0)
		return;

	if (mnuViewSpreadViewNone->Checked) { // Not Spread View
		if (ScrollBar->Position >= flst->Count) {
			ScrollBar->Position = 1;
		} else {
			ScrollBar->Position += 1;
		}
	} else {
		if (ScrollBar->Position >= flst->Count - 2) {
			ScrollBar->Position = 1;
		} else {
			ScrollBar->Position += 2;
		}
	}
}

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_Prev() {
	if (flst->Count == 0)
		return;

	if (mnuViewSpreadViewNone->Checked) {
		if (ScrollBar->Position <= 1) {
			ScrollBar->Position = flst->Count;
		} else {
			ScrollBar->Position -= 1;
		}
	} else {
		if (ScrollBar->Position <= 0) {
			ScrollBar->Position = flst->Count - 2;
		} else {
			ScrollBar->Position -= 2;
		}
	}
}

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_FileOpenDialogEx(bool folder) {
	if (fn_GetVer() < 6.0) {
		fn_OpenDialog();
	} else {
		fn_FileOpenDialog(folder);
	}
}

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_OpenDialog() {
	TStringBuilder *sb = new TStringBuilder();

	TMatchCollection m = TRegEx::Matches(conf.Ext, "\\.(.+?)\\$");
	for (int i = 0; i < m.Count; ++i) {
		String _ext = m.Item[i].Groups[1].Value;
		sb->Append("*." + _ext + "; ");
	}

	OpenDialog->Filter = "All Image Types (" + sb->ToString() + ")|" + sb->ToString() + "|" + "All Files (*.*)|*.*|";

	delete sb;

	if (OpenDialog->Execute() == true) {
		fn_LoadFiles((TStringList *)FileOpenDialog->Files);
	}
}

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_FileOpenDialog(bool folder) {
	TStringBuilder *sb = new TStringBuilder();

	TMatchCollection m = TRegEx::Matches(conf.Ext, "\\.(.+?)\\$");

	for (int i = 0; i < m.Count; ++i) {
		sb->Append("*." + m.Item[i].Groups[1].Value + ";");
	}

	TFileTypeItem *item;

	item = FileOpenDialog->FileTypes->Add();
	item->DisplayName = "All Image Types";
	item->FileMask = sb->ToString();

	for (int i = 0; i < m.Count; ++i) {
		item = FileOpenDialog->FileTypes->Add();
		item->DisplayName = m.Item[i].Groups[1].Value;
		item->FileMask = "*." + m.Item[i].Groups[1].Value;
	}

	item = FileOpenDialog->FileTypes->Add();
	item->DisplayName = "All Files";
	item->FileMask = "*.*";

	if (folder) {
		FileOpenDialog->Options = TFileDialogOptions() << fdoPickFolders << fdoAllowMultiSelect << fdoPathMustExist << fdoFileMustExist;
	} else {
		FileOpenDialog->Options = TFileDialogOptions() << fdoAllowMultiSelect << fdoPathMustExist << fdoFileMustExist;
	}

	if (FileOpenDialog->Execute() == true) {
		fn_ParseFiles((TStringList *)FileOpenDialog->Files);
	}
}

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_PrevFrame() {
	Gdv0->DisplayPreviousFrame();
}

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_NextFrame() {
	Gdv0->DisplayNextFrame();
}

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_Options() {
//	RunProcess(L"c2onfig.exe", NULL);
    Form3->ShowModal();
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
	Gdv0->Copy2Clipboard();
}

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_PathCopy() {
	Clipboard()->AsText = ((TFI*)(flst->Items[ScrollBar->Position - 1]))->FullName;
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
		Gdv0->Rotate270();
		break;
	case 2:
		Gdv0->Rotate180();
		break;
	case 3:
		Gdv0->Rotate90();
		break;
	}

	conf.rot = 0;
	fn_ZoomMode(Gdv0->ZoomMode);
}

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_Reset(TGdViewer *gv) {
	switch (conf.rot) {
	case 1:
		gv->Rotate270();
		break;
	case 2:
		gv->Rotate180();
		break;
	case 3:
		gv->Rotate90();
		break;
	}

	conf.rot = 0;
	fn_ZoomMode(gv, gv->ZoomMode);
}

// ---------------------------------------------------------------------------
// []
void __fastcall TForm1::fn_SpreadView(int value) {
	conf.SpreadView = value;

	// switch (value) {
	// case 0:
	// Splitter->Visible = false;
	// Panel1->Visible = false;
	mnuViewSpreadViewNone->Checked = true;
	tbtnSpreadView->Down = false;
	tbtnSpreadView->ImageIndex = 16;
	return;
	// break;
	// case 1:
	// mnuViewSpreadViewRight->Checked = true;
	// tbtnSpreadView->ImageIndex = 17;
	// break;
	// case 2:
	// mnuViewSpreadViewLeft->Checked = true;
	// tbtnSpreadView->ImageIndex = 18;
	// break;
	// }
	//
	// Panel1->Visible = true;
	// Splitter->Visible = true;
	// // Panel1->Visible = true;
	// tbtnSpreadView->Down = true;
	// Panel1->Width = (Form1->ClientWidth - Splitter->Width) / 2;
}

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_RotateRight() {
	Gdv0->Rotate90();
	if (++conf.rot == 4) {
		conf.rot = 0;
	}
	tbtnKeepRot->ImageIndex = 12 + conf.rot;
}

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_RotateLeft() {
	Gdv0->Rotate270();
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
		Gdv0->ZoomMode = 1;
		mnuViewActual->Checked = true;
		mnuViewOptimizeWindowSize->Enabled = true;
		tbtnActual->Down = true;
		break;
	case 2: // []
		Gdv0->ZoomMode = 2;
		mnuViewBestfit->Checked = true;
		mnuViewOptimizeWindowSize->Enabled = false;
		tbtnBestfit->Down = true;
		break;
	case 6: // []
		Gdv0->ZoomMode = 6;
		mnuViewSpread->Checked = true;
		mnuViewOptimizeWindowSize->Enabled = false;
		tbtnSpread->Down = true;
		break;
	case 99:
		if (Gdv0->Width > Gdv0->ImageWidth && Gdv0->Height > Gdv0->ImageHeight) {
			Gdv0->ZoomMode = 1;
		} else {
			Gdv0->ZoomMode = 2;
		}
		mnuViewInWindow->Checked = true;
		mnuViewOptimizeWindowSize->Enabled = false;
		tbtnInWindow->Down = true;
		break;
	}
}

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_ZoomMode(TGdViewer *gv, int value) {
	switch (value) {
	case 1: // []
		gv->ZoomMode = 1;
		mnuViewActual->Checked = true;
		mnuViewOptimizeWindowSize->Enabled = true;
		tbtnActual->Down = true;
		break;
	case 2: // []
		gv->ZoomMode = 2;
		mnuViewBestfit->Checked = true;
		mnuViewOptimizeWindowSize->Enabled = false;
		tbtnBestfit->Down = true;
		break;
	case 6: // []
		gv->ZoomMode = 6;
		mnuViewSpread->Checked = true;
		mnuViewOptimizeWindowSize->Enabled = false;
		tbtnSpread->Down = true;
		break;
	case 99:
		if (gv->Width > gv->ImageWidth && gv->Height > gv->ImageHeight) {
			gv->ZoomMode = 1;
		} else {
			gv->ZoomMode = 2;
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
	this->ClientWidth = Gdv0->ImageWidth;
	this->ClientHeight = Gdv0->ImageHeight - (ScrollBar->Visible ? ScrollBar->Height : 0) - (ToolBar->Visible ? ToolBar->Height : 0) -
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
	case kByName: // [Name]
		if (asc) {
			flst->Sort(cmpNameAsc);
		} else {
			flst->Sort(cmpNameDesc);
		}
		mnuViewOrderName->Checked = true;
		break;
	case kByNameNum: // [Numeric]
		if (asc) {
			flst->Sort(cmpNameNumAsc);
		} else {
			flst->Sort(cmpNameNumDesc);
		}
		mnuViewOrderNameNum->Checked = true;
		break;
	case kByTime: // [Modify Date]
		if (asc) {
			flst->Sort(cmpTimeAsc);
		} else {
			flst->Sort(cmpTimeDesc);
		}
		mnuViewOrderDate->Checked = true;
		break;
	case kByType: // [Type]
		if (asc) {
			flst->Sort(cmpTypeAsc);
		} else {
			flst->Sort(cmpTypeDesc);
		}
		mnuViewOrderType->Checked = true;
		break;
	case kBySize: // [Size]
		if (asc) {
			flst->Sort(cmpSizeAsc);
		} else {
			flst->Sort(cmpSizeDesc);
		}
		mnuViewOrderSize->Checked = true;
		break;
	}
}

// ---------------------------------------------------------------------------
// [View]-[Quality]
void __fastcall TForm1::fn_Quality(ViewerQuality value) {
	_ViewerQuality = value;

	switch (value) {
	case Auto:
		Gdv0->ViewerQualityAuto = true;
		mnuViewQualityAuto->Checked = true;
		break;
	default:
		Gdv0->ViewerQualityAuto = false;
		Gdv0->ViewerQuality = value;
		break;
	}

	switch (value) {
	case Low: // Low
		mnuViewQualityLow->Checked = true;
		break;
	case Bilinear: // Bilinear
		mnuViewQualityBilinear->Checked = true;
		break;
	case Bicubic: // Bicubic
		mnuViewQualityBicubic->Checked = true;
		break;
	case BilinearHQ: // BilinearHQ
		mnuViewQualityBilinearHQ->Checked = true;
		break;
	case BicubicHQ: // BicubicHQ
		mnuViewQualityBicubicHQ->Checked = true;
		break;
	}
}

// ---------------------------------------------------------------------------
// [描画時間の最適化]
void __fastcall TForm1::fn_OptimizeDrawingSpeed(bool value) {
	Gdv0->OptimizeDrawingSpeed = value;
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
// [Full Screen]
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
// [Zoom In]
void __fastcall TForm1::fn_ZoomIn() {
	fn_ZoomIn(Gdv0);
}

// ---------------------------------------------------------------------------
// [Zoom In]
void __fastcall TForm1::fn_ZoomOut() {
	fn_ZoomOut(Gdv0);
}

// ---------------------------------------------------------------------------
// [Zoom In]
void __fastcall TForm1::fn_ZoomIn(TGdViewer *gv) {
	gv->ZoomIN();
	fn_StatusText();
}

// ---------------------------------------------------------------------------
// [Zoom Out]
void __fastcall TForm1::fn_ZoomOut(TGdViewer *gv) {
	gv->ZoomOUT();
	fn_StatusText();
}

// ---------------------------------------------------------------------------
// [Zoom Step]
void __fastcall TForm1::fn_ZoomStep(int value) {
	Gdv0->ZoomStep = value;
}

// ---------------------------------------------------------------------------
// [Delete File]
void __fastcall TForm1::fn_DeleteFile(int flags) {
	if (flst->Count == 0) {
		return;
	}

	String path = ((TFI*)flst->Items[ScrollBar->Position - 1])->FullName;
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
		flst->Delete(ScrollBar->Position - 1);
		ScrollBar->Max--;
		fn_Next();
	}
}

// ---------------------------------------------------------------------------
// [Show StatusBar text.]
void __fastcall TForm1::fn_StatusText() {
	if (StatusBar->Visible) {
		StatusBar->SimpleText = fn_TitleFormatting(conf.StatusText);
	}
}

// ---------------------------------------------------------------------------
// [Title Formatting]
String __fastcall TForm1::fn_TitleFormatting(String value) {
	if (flst->Count == 0)
		return "";

	TFI *fi = (TFI*)(flst->Items[ScrollBar->Position - 1]);

	value = StringReplace(value, "%_path%", fi->FullName, TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_filename_ext%", ExtractFileName(fi->FullName), TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_filesize%", fi->Size, TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_filesize_kb%", fi->Size / 1024, TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_filesize_mb%", fi->Size / 1048576, TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_width%", Gdv0->ImageWidth, TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_height%", Gdv0->ImageHeight, TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_zoom%", int(Gdv0->ZOOM * 100), TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_last_modified%", (fi->Date).DateTimeString(), TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_position%", ScrollBar->Position, TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_total%", flst->Count, TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_codec%", Gdv0->GetImageFormat(), TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_isspi%", conf.isSPI ? "SPI" : "GDPic", TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_errorcode%", IntToStr(conf.errorcode), TReplaceFlags() << rfReplaceAll);
	value = StringReplace(value, "%_pagecount%", IntToStr(Gdv0->PageCount), TReplaceFlags() << rfReplaceAll);

	return (value);
}

// ---------------------------------------------------------------------------
//
TColor __fastcall TForm1::fn_IntToColor(int rgb) {
	int r = 255 - (rgb % 256);
	int g = 255 - ((rgb / 256) % 256);
	int b = 255 - (rgb / 65536);
	return (TColor)RGB(r, g, b);
}

// ---------------------------------------------------------------------------
//
double __fastcall TForm1::fn_GetVer() {
	OSVERSIONINFO OSver;
	OSver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&OSver);
	return OSver.dwMajorVersion + OSver.dwMinorVersion * 0.1;
}

// ---------------------------------------------------------------------------
// [Delete File]
void __fastcall TForm1::fn_LoadRecent() {
	TStringList *sect = new TStringList();

	// ini->ReadSectionValues("Recent", sect);

	for (int i = 0; i < sect->Count; ++i) {
		String key = sect->Names[i];
		String val = sect->Values[key];
		TMenuItem *item = new TMenuItem(mnuFileRecentFiles);
		item->Caption = val;
		mnuFileRecentFiles->Add(item);
	}
}

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::fn_FindDir(String dir, String name) {
	TSearchRec sr;

	if (FindFirst(TPath::Combine(dir, name), faAnyFile, sr) == 0) {
		do {
			if (sr.Name == "." || sr.Name == "..")
				continue;
			if (TRegEx::IsMatch(sr.Name, conf.Ext, TRegExOptions() << roIgnoreCase)) {
				TFI *fi = new TFI;
				fi->FullName = TPath::Combine(dir, sr.Name);
				fi->Name = sr.Name;
				fi->Ext = ExtractFileExt(sr.Name);
				fi->Size = sr.Size;
				fi->Date = sr.TimeStamp;
				flst->Add((TObject *)fi);
			}
			// Load Sub Directries.
			if (mnuFileLoadSubdirectry->Checked) {
				if (DirectoryExists(TPath::Combine(dir, sr.Name))) {
					fn_FindDir(TPath::Combine(dir, sr.Name), "*.*");
				}
			}
		}
		while (!FindNext(sr));
	}

	FindClose(sr);
}

// ---------------------------------------------------------------------------
// 画像表示
void __fastcall TForm1::fn_LoadImage(TGdViewer *gv, TFI *fi) {
	if (hSPI->Count > 0) { // use SPI
		conf.isSPI = false;
		HBITMAP bmp = SPI_LoadImage(fi->FullName.w_str());
		if (bmp != NULL) {
			gv->DisplayFromHBitmap((long)bmp);
			conf.isSPI = true;
		}
	} else { // not use SPI
		DisplayFromFile(gv, ((TFI *)fi)->FullName);
	}

	if (mnuViewKeepRot->Checked) {
		switch (conf.rot) {
		case 1:
			gv->Rotate90();
			break;
		case 2:
			gv->Rotate180();
			break;
		case 3:
			gv->Rotate270();
			break;
		}
	} else {
		conf.rot = 0;
		tbtnKeepRot->ImageIndex = 12;
	}

	// Optimize Window Size
	if (mnuViewOptimizeWindowSize->Checked && mnuViewActual->Checked) {
		fn_OptimizeWindowSize(true);
	}

	// for 'In Window' of zoom mode
	if (mnuViewInWindow->Checked) {
		fn_ZoomMode(99);
	}

	// Recent->WriteString("Recent", fi->FullName, fi->Name);

	gv->PlayGif();

	this->Caption = fn_TitleFormatting(conf.TitleText);

	// display text in statusbar.
	fn_StatusText();
}

// ---------------------------------------------------------------------------
// Add to recent file list.
void __fastcall TForm1::fn_AddRecent(String path) {
	if (RecentList->Count > 40) {
		RecentList->Delete(RecentList->Count - 1);
	}

	RecentList->Add(path);

}
