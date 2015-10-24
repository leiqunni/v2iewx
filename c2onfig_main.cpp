//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "c2onfig_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
	IniDefFile = TPath::Combine(ExtractFilePath(Application->ExeName), "viewx++.ini.def");

	LoadIniDef();
}
//---------------------------------------------------------------------------
// INIファイル読込

#pragma region "LoadIni"

void __fastcall TForm4::LoadIniDef()
{
//
	ini = new TMemIniFile(IniDefFile);

	TStringList *sections = new TStringList();
	ini->ReadSections(sections);

	String key, val, param;

	for (int i = 0; i < sections->Count; i++) {
		TStringList *sect = new TStringList();
		TTreeNode *p = TreeView->Items->Add(NULL, sections->Strings[i]);
		ini->ReadSectionValues(sections->Strings[i], sect);
		for (int i = 0; i < sect->Count; i++) {
			String key = sect->Names[i];
			String val = sect->Values[key];
			TreeView->Items->AddChild(p, key);
		}
	}
	TreeView->FullExpand();


//	String key, val, param;
//
//	for (int i = 0; i < sections->Count; i++) {
//		TStringList *sect = new TStringList();
//		ini->ReadSectionValues(sections->Strings[i], sect);
//		TreeView1->Items->Add(NULL, sections->Strings[i]);
//		for (int j = 0; j < sect->Count; j++) {
//			key = sect->Names[j];
//			val = sect->Values[key];
//			TTreeNode *node = TreeView1->Items->Item[i];
////			param = key +　"=";// + val;
////			TreeView1->Items->AddChild(node, key +　"=" + val);
//		}
//
//	}
}
void __fastcall TForm4::TreeViewClick(TObject *Sender)
{
	if (TreeView->Selected->Parent == NULL) {
		return;
	}
//	ShowMessage(TreeView1->Selected->Text);
//	ShowMessage(TreeView1->Selected->Parent->Text);
	String val = ini->ReadString(
		TreeView->Selected->Parent->Text,
		TreeView->Selected->Text,
		"");
	TStringDynArray vals = SplitString(val, ":");
	if (vals.Length == 3) {
		pnlDescription->Caption = vals[2];
//		ShowMessage("!");
	}
}
//---------------------------------------------------------------------------
