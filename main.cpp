//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "msvcrt.lib"
#pragma link "GdViewerPro4_OCX"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	DragAcceptFiles(Handle, true); // ドラッグ&ドロップを有効にする

	Gdv1->LicenseKEY = WideString(L"6223560888372426056441256");

	IniFile = TPath::Combine(ExtractFilePath(Application->ExeName), "viewx++.ini");
	KeyFile = TPath::Combine(ExtractFilePath(Application->ExeName), "key.ini");
	LangFile = TPath::Combine(ExtractFilePath(Application->ExeName), "lang.ini");

	hSPI = new TObjectList();
	fileList = new TObjectList();
	paramStr = new TStringList();

    gFI = new TFI();

	LoadLang();
	LoadIni();
	KeyConf = new TMemIniFile(KeyFile);

	if (ParamCount() > 0) {
		for (int i = 1; i <= ParamCount(); ++i) {
			paramStr->Add(ParamStr(i));
		}
		fn_ParseCmdLine(paramStr);
	}
}
//---------------------------------------------------------------------------
//
void __fastcall TForm1::FormDestroy(TObject *Sender) {
	delete KeyConf;
	delete hSPI;
	delete fileList;
	delete paramStr;
	SaveIni();
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::FormResize(TObject *Sender) {
	if (ToolBar->Visible) {
		ToolBar->Indent = (ToolBar->Width - 359) / 2;
	}
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::AddFile(String dir, TSearchRec sr) {
	TFI *fi = new TFI;
	fi->FullName = TPath::Combine(dir, sr.Name);
	fi->Name = sr.Name;
	fi->Ext = ExtractFileExt(sr.Name);
	fi->Size = sr.Size;
	// fi->Time = sr.Time;
	fi->Date = sr.TimeStamp;
	fileList->Add((TObject*)fi);
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::FindDir(String dir, String name) {
	TSearchRec sr;
	if (FindFirst(TPath::Combine(dir, name), 0, sr) == 0) {
		do {
			if (TRegEx::IsMatch(sr.Name, conf.Ext, TRegExOptions() << roIgnoreCase)) {
				AddFile(dir, sr);
			}
		}
		while (!FindNext(sr));
	}
	FindClose(sr);
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::LoadFiles(TStringList *list) {
	fileList->Clear();

	for (int i = 0; i < list->Count; ++i) {
		if (DirectoryExists(list->Strings[i])) {
			FindDir(list->Strings[i], "*.*");
		} else {
			FindDir(IncludeTrailingPathDelimiter(ExtractFileDir(list->Strings[i])), list->Strings[i]);
		}
	}

	if (fileList->Count > 0) {
		fn_Sort(conf.order, conf.asc);
		ScrollBar->Max = fileList->Count;
		ScrollBar->Position = 1;
		ScrollBarChange(NULL);
	}
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::LoadFiles(String path) {
	fileList->Clear();

	FindDir(IncludeTrailingPathDelimiter(ExtractFileDir(path)), L"*.*");

	if (fileList->Count > 0) {
		fn_Sort(conf.order, conf.asc);
		ScrollBar->Max = fileList->Count;
		for (int i = 0; i < fileList->Count; ++i) {
			if (((TFI*)(fileList->Items[i]))->FullName == path) {
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
void __fastcall TForm1::ScrollBarChange(TObject *Sender) {
	if (fileList->Count == 0) return;
	LoadImage(Gdv1, (TFI*)fileList->Items[ScrollBar->Position - 1]);
}
// ---------------------------------------------------------------------------
// 画像表示
void __fastcall TForm1::LoadImage(TGdViewer *gv, TFI *fi) {
	if (hSPI->Count > 0) { // use SPI
		conf.isSPI = false;
		HBITMAP bmp = SPI_LoadImage(fi->FullName.w_str());
		if (bmp != NULL) {
			gv->DisplayFromHBitmap((long)bmp);
			conf.isSPI = true;
		}
	} else { // not use SPI
		DisplayFromFile(gv, ((TFI*)fi)->FullName);
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

	// ウィンドウサイズの最適化
	if (mnuViewOptimizeWindowSize->Checked && mnuViewActual->Checked) {
		fn_OptimizeWindowSize(true);
	}

	// for 'In Window' of zoom mode
	if (mnuViewInWindow->Checked) {
		fn_ZoomMode(99);
	}

	gv->PlayGif();

	this->Caption = fn_TitleFormatting(conf.TitleText);

	// display text in statusbar.
	fn_StatusText();
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::DropFiles(TWMDropFiles Msg) {
	TStringList *list = new TStringList();
	wchar_t *fn = new wchar_t[MAX_PATH];

	int n = DragQueryFileW((HDROP)Msg.Drop, -1, NULL, 0);

	for (int i = 0; i < n; ++i) {
		DragQueryFileW((HDROP)Msg.Drop, i, fn, MAX_PATH);
		list->Add(String(fn));
	}

	fn_ParseCmdLine(list);

	delete[]fn;
	delete list;

	DragFinish((HDROP)Msg.Drop);
}

#pragma region " mnuFile "

// ---------------------------------------------------------------------------
// [File]-[New Window]
void __fastcall TForm1::mnuFileNewWindowClick(TObject *Sender) {
	fn_NewWindow();
}
// ---------------------------------------------------------------------------
// [ファイル]-[開く...]
void __fastcall TForm1::mnuFileOpenClick(TObject *Sender) {
	fn_FileOpenDialog();
}
// ---------------------------------------------------------------------------
// [ファイル]-[削除]
void __fastcall TForm1::mnuFileDeleteClick(TObject *Sender) {
	fn_DeleteFile(FOF_ALLOWUNDO);
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::mnuFilePropertyClick(TObject *Sender) {
//	Form3->Show();
	HINSTANCE rtn = ShellExecute(this->Handle, L"properties", FullPath.w_str(), L"explorer.exe", NULL, SW_SHOWNORMAL);
	ShowMessage((int)rtn);
}
// ---------------------------------------------------------------------------
// [ファイル]-[スライド ショー]
void __fastcall TForm1::mnuPlaySlideShowClick(TObject *Sender) {
	fn_SlideShow();
}
// ---------------------------------------------------------------------------
// [ファイル]-[終了]
void __fastcall TForm1::mnuFileExitClick(TObject *Sender) {
	exit(0);
}

#pragma end_region

#pragma region " mnuEdit "

// ---------------------------------------------------------------------------
// [編集]-[画像のコピー]
void __fastcall TForm1::mnuEditCopyClick(TObject *Sender) {
	fn_ImageCopy();
}
// ---------------------------------------------------------------------------
// [編集]-[パスのコピー]
void __fastcall TForm1::mnuEditPathClick(TObject *Sender) {
	fn_PathCopy();
}

#pragma end_region

#pragma region  " mnuView "

// ---------------------------------------------------------------------------
// [表示]-[メニュー バー]
void __fastcall TForm1::mnuViewMainMenuClick(TObject *Sender) {
	fn_MainMenu(!MainMenu->Tag);
}
// ---------------------------------------------------------------------------
// [表示]-[スクロール バー]
void __fastcall TForm1::mnuViewScrollBarClick(TObject *Sender) {
	fn_ScrollBar(!ScrollBar->Visible);
}
// ---------------------------------------------------------------------------
// [表示]-[ツール バー]
void __fastcall TForm1::mnuViewToolBarClick(TObject *Sender) {
	fn_ToolBar(!ToolBar->Visible);
}
// ---------------------------------------------------------------------------
// [表示]-[ステータス バー]
void __fastcall TForm1::mnuViewStatusBarClick(TObject *Sender) {
	fn_StatusBar(!StatusBar->Visible);
}
// ---------------------------------------------------------------------------
// [表示]-[左回りに回転]
void __fastcall TForm1::mnuViewRotateLeftClick(TObject *Sender) {
	fn_RotateLeft();
}
// ---------------------------------------------------------------------------
// [表示]-[右回りに回転]
void __fastcall TForm1::mnuViewRotateRightClick(TObject *Sender) {
	fn_RotateRight();
}
// ---------------------------------------------------------------------------
// [表示]-[回転を保つ]
void __fastcall TForm1::mnuViewKeepRotClick(TObject *Sender) {
	fn_KeepRot(!mnuViewKeepRot->Checked);
}
// ---------------------------------------------------------------------------
// [表示]-[原寸大]
void __fastcall TForm1::mnuViewActualClick(TObject *Sender) {
	fn_ZoomMode(1);
}
// ---------------------------------------------------------------------------
// [表示]-[ウィンドウに合わせる]
void __fastcall TForm1::mnuViewBestfitClick(TObject *Sender) {
	fn_ZoomMode(2);
}
// ---------------------------------------------------------------------------
// [表示]-[ウィンドウに収める]
void __fastcall TForm1::mnuViewInWindowClick(TObject *Sender) {
	fn_ZoomMode(99);
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::mnuViewOptimizeWindowSizeClick(TObject *Sender) {
	fn_OptimizeWindowSize(!mnuViewOptimizeWindowSize->Checked);
}
// ---------------------------------------------------------------------------
// [表示]-[並び替え]-[名前]
void __fastcall TForm1::mnuViewOrderNameClick(TObject *Sender) {
	fn_Sort(kByName, conf.asc);
}
// ---------------------------------------------------------------------------
// [表示]-[並び替え]-[数値順]
void __fastcall TForm1::mnuViewOrderNameNumClick(TObject *Sender) {
	fn_Sort(kByNameNum, conf.asc);
}
// ---------------------------------------------------------------------------
// [表示]-[並び替え]-[更新日時]
void __fastcall TForm1::mnuViewOrderDateClick(TObject *Sender) {
	fn_Sort(kByTime, conf.asc);
}
// ---------------------------------------------------------------------------
// [表示]-[並び替え]-[種類]
void __fastcall TForm1::mnuViewOrderTypeClick(TObject *Sender) {
	fn_Sort(kByType, conf.asc);
}
// ---------------------------------------------------------------------------
// [表示]-[並び替え]-[サイズ]
void __fastcall TForm1::mnuViewOrderSizeClick(TObject *Sender) {
	fn_Sort(kBySize, conf.asc);
}
// ---------------------------------------------------------------------------
// [表示]-[並べ替え]-[昇順]
void __fastcall TForm1::mnuViewOrderAscClick(TObject *Sender) {
	fn_Sort(conf.order, true);
}
// ---------------------------------------------------------------------------
// [表示]-[並べ替え]-[降順]
void __fastcall TForm1::mnuViewOrderDescClick(TObject *Sender) {
	fn_Sort(conf.order, false);
}
// ---------------------------------------------------------------------------
// [表示]-[画質]-[自動]
void __fastcall TForm1::mnuViewQualityAutoClick(TObject *Sender) {
	fn_QualityAuto(!Gdv1->ViewerQualityAuto);
}
// ---------------------------------------------------------------------------
// [表示]-[画質]-[低]
void __fastcall TForm1::mnuViewQualityLowClick(TObject *Sender) {
	fn_Quality(0);
}
// ---------------------------------------------------------------------------
// [表示]-[画質]-[バイリニア]
void __fastcall TForm1::mnuViewQualityBilinearClick(TObject *Sender) {
	fn_Quality(1);
}
// ---------------------------------------------------------------------------
// [表示]-[画質]-[バイキュービック]
void __fastcall TForm1::mnuViewQualityBicubicClick(TObject *Sender) {
	fn_Quality(1);
}
// ---------------------------------------------------------------------------
// [表示]-[画質]-[バイリニアHQ]
void __fastcall TForm1::mnuViewQualityBilinearHQClick(TObject *Sender) {
	fn_Quality(2);
}
// ---------------------------------------------------------------------------
// [表示]-[画質]-[バイキュービックHQ]
void __fastcall TForm1::mnuViewQualityBicubicHQClick(TObject *Sender) {
	fn_Quality(4);
}
// ---------------------------------------------------------------------------
// [表示]-[描画速度の最適化]
void __fastcall TForm1::mnuViewOptimizeDrawingSpeedClick(TObject *Sender) {
	fn_OptimizeDrawingSpeed(!Gdv1->OptimizeDrawingSpeed);
}
// ---------------------------------------------------------------------------
// [表示]-[全画面表示]
void __fastcall TForm1::mnuViewFullScreenClick(TObject *Sender) {
	fn_FullScreen();
}

#pragma end_region

#pragma region  " mnuPlay "

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::mnuPlayPrevFrameClick(TObject *Sender) {
	fn_PrevFrame();
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::mnuPlayNextFrameClick(TObject *Sender) {
	fn_NextFrame();
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::mnuPlayPrevClick(TObject *Sender) {
	fn_Prev();
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::mnuPlayNextClick(TObject *Sender) {
	fn_Next();
}

#pragma end_region

#pragma region " mnuTools "

// ---------------------------------------------------------------------------
// [ツール]-[オプション]
void __fastcall TForm1::mnuToolsOptionClick(TObject *Sender) {
	fn_Options();
}

#pragma end_region

#pragma region " mnuHelp "

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::mnuHelpAboutClick(TObject *Sender) {
	Form2->ShowModal();
}

#pragma end_region

#pragma region " ToolBar "

// ---------------------------------------------------------------------------
// [ツールバー]-[前のイメージ]
void __fastcall TForm1::tbtnPrevClick(TObject *Sender) {
	fn_Prev();
}
// ---------------------------------------------------------------------------
// [ツールバー]-[次のイメージ]
void __fastcall TForm1::tbtnNextClick(TObject *Sender) {
	fn_Next();
}
// ---------------------------------------------------------------------------
// [ツール バー]-[ウィンドウに合わせる]
void __fastcall TForm1::tbtnBestfitClick(TObject *Sender) {
	fn_ZoomMode(2);
}
// ---------------------------------------------------------------------------
// [ツール バー]-[ウィンドウに収める]
void __fastcall TForm1::tbtnInWindowClick(TObject *Sender) {
	fn_ZoomMode(99);
}
// ---------------------------------------------------------------------------
// [ツール バー]-[原寸大]
void __fastcall TForm1::tbtnActualClick(TObject *Sender) {
	fn_ZoomMode(1);
}
// ---------------------------------------------------------------------------
// [ツール バー]-[ウィンドウに広げる]
void __fastcall TForm1::tbtnSpreadClick(TObject *Sender) {
	fn_ZoomMode(6);
}
// ---------------------------------------------------------------------------
// [ツール バー]-[スライド ショー]
void __fastcall TForm1::tbtnSlideShowClick(TObject *Sender) {
	fn_SlideShow();
}
// ---------------------------------------------------------------------------
// [ツールバー]-[拡大]
void __fastcall TForm1::tbtnZoomInClick(TObject *Sender) {
	fn_ZoomIn();
}
// ---------------------------------------------------------------------------
// [ツールバー]-[縮小]
void __fastcall TForm1::tbtnZoomOutClick(TObject *Sender) {
	fn_ZoomOut();
}
// ---------------------------------------------------------------------------
// [ツールバー]-[右回りに回転]
void __fastcall TForm1::tbtnRotateLeftClick(TObject *Sender) {
	fn_RotateLeft();
}
// ---------------------------------------------------------------------------
// [ツールバー]-[左りに回転]
void __fastcall TForm1::tbtnRotateRightClick(TObject *Sender) {
	fn_RotateRight();
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::tbtnKeepRotClick(TObject *Sender) {
	fn_KeepRot(!mnuViewKeepRot->Checked);
}
// ---------------------------------------------------------------------------
// [ツールバー]-[削除]
void __fastcall TForm1::tbtnDeleteClick(TObject *Sender) {
	fn_DeleteFile(FOF_ALLOWUNDO);
}

#pragma end_region

#pragma region " Susie Plug-in "

// ---------------------------------------------------------------------------
// Susie Plug-in 読み込み
void __fastcall TForm1::SPI_LoadPlugin(String path) {
	TSearchRec sr;
	if (FindFirst(TPath::Combine(path, L"*.spi"), 0, sr) == 0) {
		do {
			hSPI->Add((TObject*)LoadLibrary(TPath::Combine(path, sr.Name).w_str()));
		}
		while (!FindNext(sr));
		// FindClose(sr);
	}
	FindClose(sr);
}
// ---------------------------------------------------------------------------
//
HBITMAP __fastcall TForm1::SPI_LoadImage(String fileName) {
	/* 対応プラグインの検索 */
	for (int i = 0; i < hSPI->Count; i++) { // プラグイン関数の取得
		SPI_ISSUPPORTED spi_issupported = (SPI_ISSUPPORTED)GetProcAddress((HMODULE)hSPI->Items[i], SPIPROC_ISSUPPORTED);
		SPI_GETPICTURE spi_getpicture = (SPI_GETPICTURE)GetProcAddress((HMODULE)hSPI->Items[i], SPIPROC_GETPICTURE);

		if (spi_issupported == NULL || spi_getpicture == NULL) {
			continue;
		}

		// ファイル内容をロードする
		HANDLE handle; // = NULL;

		if ((handle = CreateFile_Read(fileName.w_str())) == INVALID_HANDLE_VALUE) {
			return NULL;
		}

		DWORD filesize = GetFileSize(handle, NULL), readsize;
		LPSTR data = (LPSTR)Heap_Malloc(filesize);
		SetFilePointer(handle, 0, NULL, FILE_BEGIN);

		if (!ReadFile(handle, data, filesize, &readsize, NULL)) {
			CloseHandle(handle);
		}

		CloseHandle(handle);

		// ロードできる形式かどうかをチェックする
		if (spi_issupported(AnsiString(fileName).c_str(), (DWORD)data) == 0) {
			Heap_Free(data);
			continue;
		}

		// 画像を展開する
		HLOCAL info, bm;
		if (spi_getpicture(data, filesize, 1, &info, &bm, NULL, 0) != 0) {
			Heap_Free(data);
		}

		LPBITMAPINFO bmpinfo = (LPBITMAPINFO)LocalLock(info); // BITMAPINFO構造体
		LPBYTE bmbits = (LPBYTE)LocalLock(bm); // 画像データ

		// 取得した情報からBITMAPハンドルを生成する
		HDC dc = GetDC(0);
		HBITMAP bitmap = CreateDIBitmap(dc, &bmpinfo->bmiHeader, CBM_INIT, bmbits, bmpinfo, DIB_RGB_COLORS);
		ReleaseDC(0, dc);

		// いろいろと開放
		LocalUnlock(info);
		LocalFree(info);
		LocalUnlock(bm);
		LocalFree(bm);
		Heap_Free(data);

		return bitmap;
	}
	return NULL;
}

#pragma end_region

#pragma region " Mouse "

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled) {
	if (mg.enabled) {
		if (WheelDelta > 0) {
			fn_ZoomOut();
		} else {
			fn_ZoomIn();
		}
		fn_StatusText();
	} else {
		if (WheelDelta > 0) {
			fn_Prev();
		} else {
			fn_Next();
		}
	}
	Handled = true;
}
////---------------------------------------------------------------------------
////
// void __fastcall TForm1::Gdv1MouseWheelControl(TObject *Sender, short UpDown)
//
// {
// if (gesture) {
// if (UpDown > 0) Gdv1->ZoomOUT(); else Gdv1->ZoomIN();
// StatusBar->SimpleText = "拡大率: " + FloatToStr(Gdv1->ZOOM * 100) + "%";
// } else {
// if (UpDown > 0) fn_Prev(); else fn_Next();
// }
// }
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::Gdv1DblClickControl(TObject *Sender) {
	if (mnuViewBestfit->Checked) {
		fn_ZoomMode(1);
	} else if (mnuViewActual->Checked) {
		fn_ZoomMode(2);
	}
	fn_StatusText();
}
// ---------------------------------------------------------------------------
// マウスジェスチャ
void __fastcall TForm1::Gdv1MouseDownControl(TObject *Sender, short *Button, short *shift, float *X, float *y) {
	if (conf.MouseGesture && Button[0] == 2) {
		mg.enabled = true;
		mg.strokes = "";
		mg.exx = X[0];
		mg.exy = y[0];
	}
	if (Button[0] == 4) { // ホイールクリック
		fn_Reset();
	}
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::Gdv1MouseUpControl(TObject *Sender, short *Button, short *shift, float *X, float *y) {
	if (conf.MouseGesture && Button[0] == 2) {
		mg.enabled = false;
		ExecAction(KeyConf->ReadString("Mouse", mg.strokes, NULL).LowerCase());
		StatusBar->SimpleText = "";
	}
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::Gdv1MouseMoveControl(TObject *Sender, short *Button, short *shift, float *X, float *y) {
	if (conf.MouseGesture && mg.enabled) { // 右ボタンクリック中なら
		int dirX, dirY, absX, absY;
		float pente;
		String direction;

		// ステータスバーが表示されてるなら情報表示。
		if (StatusBar->Visible) {
			StatusBar->SimpleText = "Mouse Gesture " + mg.strokes;
		}

		dirX = X[0] - mg.exx;
		absX = abs(dirX);
		dirY = y[0] - mg.exy;
		absY = abs(dirY);

		if (absX < 15 && absY < 15) {
			return;
		}

		if (absY <= 5) {
			pente = 100;
		} else {
			pente = absX / absY;
		}
		if (pente < 0.58 || pente > 1.73) {
			if (pente < 0.58) {
				if (dirY > 0) {
					direction = "D";
				} else {
					direction = "U";
				}
			} else {
				if (dirX > 0) {
					direction = "R";
				} else {
					direction = "L";
				}
			}
			if (mg.strokes.LastChar() != direction) {
				mg.strokes += direction;
			}
		}
		mg.exx = X[0];
		mg.exy = y[0];
	}
}

#pragma end_region

#pragma region " KeyDown "

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift) {
	ExecAction(KeyConf->ReadString(L"key", Format("%.1d%.3d", OPENARRAY(TVarRec, (Shift.ToInt(), Key))), NULL).LowerCase());
	Key = NULL;
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::ExecAction(String value) {
	// StatusBar->Panels->Items[0]->Text = value;
	if (value == "exit") {
		exit(0);
	} else if (value == "fileopen") {
		fn_FileOpenDialog();
	}
	// else if (value == "alwaysontop")
	// fn_AlwaysOnTop(!mnuViewAlwaysOnTop->Checked);
	else if (value == "fullscreen") {
		fn_FullScreen();
	}
	// else if (value == "fullscreenrestore")
	// fn_FullScreen(false);
	else if (value == "options") {
		fn_Options();
	} else if (value == "slideshow") {
		fn_SlideShow();
	} else if (value == "mainmenu") {
		fn_MainMenu(!MainMenu->Tag);
	} else if (value == "scrollbar") {
		fn_ScrollBar(!ScrollBar->Visible);
	} else if (value == "toolbar") {
		fn_ToolBar(!ToolBar->Visible);
	} else if (value == "statusbar") {
		fn_StatusBar(!StatusBar->Visible);
	} else if (value == "reset") {
		fn_Reset();
	}

	else if (value == "next") {
		fn_Next();
	} else if (value == "prev") {
		fn_Prev();
	}

	else if (value == "nextframe") {
		fn_NextFrame();
	} else if (value == "prevframe") {
		fn_PrevFrame();
	} else if (value == "first") {
		LoadImage(Gdv1, (TFI*)fileList->Items[0]);
	} else if (value == "last") {
		LoadImage(Gdv1, (TFI*)fileList->Items[ScrollBar->Max - 1]);
	}

	else if (value == "zoomin") {
		fn_ZoomIn();
	} else if (value == "zoomout") {
		fn_ZoomOut();
	} else if (value == "rotateright") {
		fn_RotateRight();
	} else if (value == "rotateleft") {
		fn_RotateLeft();
	} else if (value == "windowmaximize") {
		fn_WindowMaximize();
	} else if (value == "windowminimize") {
		fn_WindowMinimize();
	} else if (value == "fileopendialog") {
		fn_FileOpenDialog();
	} else if (value == "keeprot") {
		fn_KeepRot(!mnuViewKeepRot->Checked);
	} else if (value == "bestfit") {
		fn_ZoomMode(2);
	} else if (value == "spread") {
		fn_ZoomMode(6);
	} else if (value == "inwindow") {
		fn_ZoomMode(99);
	} else if (value == "actual") {
		fn_ZoomMode(1);
	}

	else if (value == "quality_low") {
		fn_Quality(0);
	} else if (value == "quality_bilinear") {
		fn_Quality(1);
	} else if (value == "quality_bicubic") {
		fn_Quality(2);
	} else if (value == "quality_bilinearhq") {
		fn_Quality(3);
	} else if (value == "quality_bicubichq") {
		fn_Quality(4);
	}

	else if (value == "filetotrash") {
		fn_DeleteFile(FOF_ALLOWUNDO);
	} else if (value == "filetotrash_noconfirmation") {
		fn_DeleteFile(FOF_ALLOWUNDO | FOF_NOCONFIRMATION);
	} else if (value == "optimizedrawingspeed") {
		fn_OptimizeDrawingSpeed(!Gdv1->OptimizeDrawingSpeed);
	} else if (value == "quality_auto") {
		fn_QualityAuto(!Gdv1->ViewerQualityAuto);
	}
	// else if (value == "properties")
	// fn_properties();
}

#pragma end_region

// ---------------------------------------------------------------------------
//
void __fastcall TForm1::TimerTimer(TObject *Sender) {
	fn_Next();
}
// ---------------------------------------------------------------------------
//
void __fastcall TForm1::DisplayFromFile(TGdViewer *object, String sFilePath) {
	FullPath = sFilePath;
	TFileStream *fs = new TFileStream(sFilePath, fmShareDenyNone);
	char *buf = new char[fs->Size];
	fs->Read(buf, fs->Size);
	long g = fs->Size;
	object->DisplayFromMemory((long)buf, &g);
	delete fs;
	delete[]buf;
}
// ---------------------------------------------------------------------------



