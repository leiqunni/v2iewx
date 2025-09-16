//---------------------------------------------------------------------------

#ifndef optionH
#define optionH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.StdCtrls.hpp>

#include "main.h"

//---------------------------------------------------------------------------
class TForm3 : public TForm {
   __published:  // IDE で管理されるコンポーネント
	TButton* btnApply;
	TButton* btnOk;
	TButton* btnCancel;
	TPageControl* PageControl1;
	TTabSheet* TabSheet1;
	TTabSheet* TabSheet2;
	TGroupBox* grpTextFormat;
	TLabel* Label1;
	TLabel* Label2;
	TEdit* edtTitle;
	TEdit* edtStatus;
	TGroupBox* GroupBox1;
	TEdit* edtExt;
	void __fastcall btnCancelClick(TObject* Sender);
	void __fastcall btnOkClick(TObject* Sender);
	void __fastcall btnApplyClick(TObject* Sender);

   private:  // ユーザー宣言
   public:   // ユーザー宣言
	__fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3* Form3;
//---------------------------------------------------------------------------
#endif
