//---------------------------------------------------------------------------

#ifndef infoH
#define infoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include <SysUtils.hpp>

#include "main.h"

//---------------------------------------------------------------------------
class TForm3 : public TForm {
   __published:  // IDE で管理されるコンポーネント
	TListView* ListView1;
	TButton* Button1;
	void __fastcall FormShow(TObject* Sender);
	void __fastcall FormDestroy(TObject* Sender);

   private:  // ユーザー宣言
	void __fastcall TForm3::AddListItem(String name, String value);

	//	TsearchRec sr;

	class TFI : public TObject {
	   public:
		String FullName;
		String Name;
		String Ext;
		TDateTime Date;
		int Size;
		int Time;
	};

   public:  // ユーザー宣言
	__fastcall TForm3(TComponent* Owner);

	TSearchRec sr;

	void __fastcall TForm3::ReadInfo(String fileName);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3* Form3;
//---------------------------------------------------------------------------
#endif
