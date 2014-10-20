//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "PopupMenu1.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck は、作成したコンポーネントに純粋仮想関数が
// ないことを確認するために使用します。
//

static inline void ValidCtrCheck(TPopupMenuEx *)
{
	new TPopupMenuEx(NULL);
}
//---------------------------------------------------------------------------
__fastcall TPopupMenuEx::TPopupMenuEx(TComponent* Owner)
	: TPopupMenu(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::WndProc(Messages::TMessage &Message)
{
   WNDRMES_TYP *Rdt ;          // ﾒｯｾｰｼﾞ格納構造体ﾎﾟｲﾝﾀwork
   AnsiString   Rcv_Mes ; // 受信ﾃﾞｰﾀ格納work

	switch (Message.Msg) {
	case WM_ENTERMENULOOP:
		break;
	case EXITMENULOOP:
		break;
	case WM_MENUSELECT:
		break;
	}
	TForm::WndProc(Message);
}

// ---------------------------------------------------------------------------
namespace Popupmenu1 {
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TPopupMenuEx)};
		RegisterComponents(L"Ex", classes, 0);
	}
}
//---------------------------------------------------------------------------
