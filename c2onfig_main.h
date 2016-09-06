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
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ValEdit.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TTreeView *TreeView;
	TGroupBox *grpDescription;
	TComboBox *cmbBool;
	TPanel *pnlEdit;
	TSplitter *Splitter1;
	TPanel *pnlKeyTree;
	TSplitter *Splitter2;
	TGroupBox *grpValue;
	TEdit *edtString;
	TPanel *pnlDescription;
	TButton *btnApply;
	TButton *btnOK;
	TPopupMenu *PopupMenu1;
	TPopupMenu *PopupMenu2;
	TUpDown *UpDown1;
	TValueListEditor *ValueListEditor1;
	void __fastcall TreeViewClick(TObject *Sender);

private:	// ユーザー宣言
	String IniFile, IniDefFile;
	TMemIniFile *ini, *def;

void __fastcall TForm4::LoadIni();
void __fastcall TForm4::LoadIniDef();

public:		// ユーザー宣言
	__fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
