//---------------------------------------------------------------------------

#ifndef c2onfig_mainH
#define c2onfig_mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <IniFiles.hpp>
#include <IOUtils.hpp>
#include <ExtCtrls.hpp>
#include <strutils.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TTreeView *TreeView;
	TButton *btnApply;
	TGroupBox *grpDescription;
	TComboBox *cmbBool;
	TPanel *pnlEdit;
	TSplitter *Splitter1;
	TPanel *pnlKeyTree;
	TSplitter *Splitter2;
	TGroupBox *grpValue;
	TEdit *edtString;
	TPanel *pnlButton;
	TPanel *pnlDescription;
	void __fastcall TreeViewClick(TObject *Sender);
private:	// ユーザー宣言
	String IniDefFile;
	TMemIniFile *ini;

void __fastcall TForm4::LoadIniDef();

public:		// ユーザー宣言
	__fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
