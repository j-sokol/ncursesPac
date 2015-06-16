#include <Engine/CMenuItem.h>
#include <Engine/CInputManager.h>

CMenuItem::CMenuItem ( std::string label, int id ):
	type ( CMenuItem::ITEM ),
	label ( label ),
	id ( id )
	{

	}
CMenuItem::~CMenuItem ()
	{

	}
void CMenuItem::draw ( CWindow * wind, int x, int y, int width, bool highlight ) 
	{
		if ( ! highlight )
			wind -> print_str ( label , x, y );	
		else wind -> print_str ( label , x, y , COLOR_PAIR ( PAIR_RED_BLACK ));
	}
void CMenuItem::HandleInput ()
	{

	}