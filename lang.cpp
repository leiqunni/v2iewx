//---------------------------------------------------------------------------

#pragma hdrstop

#include "lang.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
// lang.ini loading
void __fastcall LoadLang(TForm1* form, String inifile) {
	if (TFile::Exists(inifile)) {
		TStringList* sect = new TStringList();
		TMemIniFile* ini = new TMemIniFile(inifile);

		ini->ReadSectionValues("Lang.TMenuItem.Caption", sect);
		for (int i = 0; i < sect->Count; ++i) {
			String key = sect->Names[i];
			String val = sect->Values[key];
			TMenuItem* item = static_cast<TMenuItem*>(form->FindComponent(key));
			if (item != NULL) {
				item->Caption = val;
			}
		}

		ini->ReadSectionValues("Lang.TToolButton.Hint", sect);
		for (int i = 0; i < sect->Count; ++i) {
			String key = sect->Names[i];
			String val = sect->Values[key];
			TToolButton* item = static_cast<TToolButton*>(form->FindComponent(key));
			if (item != NULL) {
				item->Hint = val;
			}
		}

		form->SlideShowStart = ini->ReadString("Lang.Etc", "SlideShowStart", "Slide Show Start");
		form->SlideShowStop = ini->ReadString("Lang.Etc", "SlideShowStop", "Slide Show Stop");
		form->mnuPlaySlideShow->Caption = SlideShowStart;

		delete ini;
		delete sect;
	}
}
