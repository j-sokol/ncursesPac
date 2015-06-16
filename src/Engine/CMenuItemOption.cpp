#include <Engine/CMenuItem.h>
#include <Engine/CMenuItemOption.h>
#include <Engine/CInputManager.h>

CMenuItemOption::CMenuItemOption( std::string label, int id , unsigned int & asigned_value ):
	CMenuItem (label, id ),
	asigned_value ( asigned_value )
	//CMenuItem ( )
	{
		label = label;
		id = id;
		type = CMenuItem::OPTION;
	}
CMenuItemOption::~CMenuItemOption()
	{

	}
void CMenuItemOption::draw ( CWindow * wind, int x, int y, int width, bool highlight)
	{
		if ( id == asigned_value )
			{
				std::string printsring ( label );
				printsring . resize ( width , ' ');
				if ( highlight ) wind -> print_str ( printsring , x, y , COLOR_PAIR ( PAIR_RED_WHITE ));
				else wind -> print_str ( printsring , x, y , COLOR_PAIR ( PAIR_BLACK_WHITE ));
			}
		else
			{
				if ( highlight ) wind -> print_str ( label , x, y , COLOR_PAIR ( PAIR_RED_BLACK ));
				else wind -> print_str ( label , x, y );	
			}
	}
