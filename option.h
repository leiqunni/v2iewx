//---------------------------------------------------------------------------

#ifndef optionH
#define optionH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>

#include "main.h"

//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE �ŊǗ������R���|�[�l���g
	TTabControl *tabOption;
	TButton *btnApply;
	TButton *btnOk;
	TButton *btnCancel;
	TGroupBox *grpTextFormat;
	TEdit *edtTitle;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *edtStatus;
	TGroupBox *GroupBox1;
	TEdit *Edit3;
private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
	__fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
