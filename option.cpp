//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "option.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
	edtTitle->Text = Form1->ini->ReadString("Function", "Title", "");
}
//---------------------------------------------------------------------------
