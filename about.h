// ---------------------------------------------------------------------------
#ifndef aboutH
#define aboutH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "main.h"

// ---------------------------------------------------------------------------
class TForm2 : public TForm {
__published: // IDE で管理されるコンポーネント
	TMemo *memAbout;

	void __fastcall memAboutClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

private: // ユーザー宣言
public: // ユーザー宣言
	__fastcall TForm2(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
// ---------------------------------------------------------------------------
#endif
