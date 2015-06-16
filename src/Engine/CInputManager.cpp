#include <Engine/CInputManager.h>
#include <Engine/CNCurses.h>

#include <ncurses.h>

//using namespace CInputManager;
//CInputManager::pressed_key = 1;


bool CInputManager::is_pressed ( int key )
	{
		return (CNCurses::pressed_key == key);
	}

bool CInputManager::any_key_pressed ()
	{
		return ( CNCurses::pressed_key != ERR );
	}
bool CInputManager::no_key_pressed ()
	{
		return ( CNCurses::pressed_key == ERR );
	}
void CInputManager::update ( int time_delay )
	{
		CNCurses::pressed_key = CNCurses::get_input ( time_delay );
	}
