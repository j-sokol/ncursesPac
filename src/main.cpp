#include <Engine/CNCurses.h>
#include <Engine/CStateManager.h>
#include <Game/CStateMenu.h>
 


int main(int argc, char const *argv[])
	{
		CNCurses::init();
		
		CStateManager states;
		states . run ( new CStateMenu );
		
		CNCurses::exit();
		
		return 0;
	}
