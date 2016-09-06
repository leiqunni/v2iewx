//---------------------------------------------------------------------------
#ifndef main_configH
#define main_configH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <XPMan.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <ExtCtrls.hpp>
//#include <GIFImg.hpp>
#include <inifiles.hpp>
#include <registry.hpp>

//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TButton *btnCancel;
	TButton *btnOk;
	TPanel *pnlButton;
	TPageControl *PageControl1;
	TTabSheet *TabSheet6;
	TTabSheet *TabSheet7;
	TTabSheet *TabSheet8;
	TTabSheet *TabSheet9;
	TTabSheet *TabSheet10;
	TGroupBox *GroupBox6;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox3;
	TCheckBox *CheckBox2;
	TGroupBox *GroupBox1;
	TLabel *Label3;
	TEdit *edtInterval;
	TUpDown *udInterval;
	TGroupBox *GroupBox5;
	TLabel *Label1;
	TEdit *edtZoomStep;
	TUpDown *udZoomStep;
	TGroupBox *GroupBox4;
	TLabel *Label4;
	TLabel *Label7;
	TEdit *edtTitle;
	TEdit *edtStatus;
	TGroupBox *GroupBox3;
	TEdit *edtSPI;
	TGroupBox *GroupBox2;
	TEdit *edtExt;
	TListBox *ListBox1;
	TButton *btnSendTo;

	void __fastcall btnOkClick(TObject *Sender);
	void __fastcall btnCancelClick(TObject *Sender);
	void __fastcall ListView1SelectItem(TObject *Sender, TListItem *Item, bool Selected);
	void __fastcall cmbActionChange(TObject *Sender);
	void __fastcall btnSendToClick(TObject *Sender);

private:	// User declarations
	void __fastcall FileAssociate( String extension, String fileType, String description, String iclNum );
	void __fastcall LoadIniFile();
	void __fastcall SaveIniFile();

public:		// User declarations
	__fastcall TForm3(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif

