//---------------------------------------------------------------------------

#ifndef PopupMenu1H
#define PopupMenu1H
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class PACKAGE TPopupMenuEx : public TPopupMenu
{
private:
protected:
	virtual void __fastcall WndProc(TMessage &Message);

public:
	__fastcall TPopupMenuEx(TComponent* Owner);
__published:
	__property TPopupMenuExOnPopDown = { read = FOnPopDown, write = FOnPopDown, default = NULL };
	TPopupMenuExOnPopDown FOnPopDown;
	virtual bool __fastcall PopupMenuExOnPopDown(AnsiString *s);
};
//---------------------------------------------------------------------------
#endif
