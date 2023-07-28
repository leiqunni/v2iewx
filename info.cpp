//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "info.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm3* Form3;

//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner) : TForm(Owner) {}

//---------------------------------------------------------------------------
//
void __fastcall TForm3::ReadInfo(String fileName) {}

//---------------------------------------------------------------------------
//
void __fastcall TForm3::AddListItem(String name, String value) {
	TListItem* item = ListView1->Items->Add();
	item->Caption = name;
	item->SubItems->Add(value);
}

//---------------------------------------------------------------------------
//
void __fastcall TForm3::FormShow(TObject* Sender) {
	if (FindFirst(Form1->FullPath, 0, sr) != 0) {
		return;
	}

	AddListItem("File Name", ExtractFileName(Form1->FullPath));
	AddListItem("File Path", Form1->FullPath);
	AddListItem("File Format", Form1->Gdv0->GetImageFormat());
	AddListItem("File Size", sr.Size);
	//
	//	AddListItem("File Format", Form1->Gdv0->GetImageFormat()));
	//
	//	AddListItem("File Format", Form1->Gdv0->GetImageFormat()));
}

//---------------------------------------------------------------------------
//
void __fastcall TForm3::FormDestroy(TObject* Sender) {
	FindClose(sr);
}
