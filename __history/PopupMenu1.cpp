//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "PopupMenu1.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck �́A�쐬�����R���|�[�l���g�ɏ������z�֐���
// �Ȃ����Ƃ��m�F���邽�߂Ɏg�p���܂��B
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
   WNDRMES_TYP *Rdt ;          // ү���ފi�[�\�����߲��work
   AnsiString   Rcv_Mes ; // ��M�ް��i�[work

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
