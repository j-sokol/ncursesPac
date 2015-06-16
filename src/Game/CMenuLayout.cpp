#include <Game/CMenuLayout.h>
#include <Engine/CNCurses.h>
#include <Engine/CWindow.h>

#include <vector>
#include <string>
#include <cstdlib>

template<typename T> void safe_delete(T*& a) 
	{
	  delete a;
	  a = NULL;
	}

CMenuLayout::CMenuLayout( int width, int height, CStateMenu * CState):
	CLayout ( width, height ),
	CState ( CState ),
	menu ( NULL ),
	logo ( NULL )
	{
		window_init ();
	}
CMenuLayout::~CMenuLayout()
	{
		window_exit ();
	}
void CMenuLayout::window_init ()
	{
		CLayout::window_init ();

		logo = new CWindow ( main_wind, 0, 0, 52, 16);
		menu = new CWindow ( main_wind, 55, 0, 24, FILL_WINDOW, true, "MENU");

		menu -> refresh ();
	}
void CMenuLayout::window_exit ()
	{
		safe_delete ( menu );
		safe_delete ( logo );

		CLayout::window_exit ();
	}

void CMenuLayout::draw (CMenu * _menu)
	{
		main_wind -> clear ();
		logo 	    -> clear ();

		std::vector<std::string> pac_ascii = { "================================================.", 
									 "     .-.   .-.     .--.                         |", 
									 "    | OO| | OO|   / _.-' .-.   .-.  .-.   .''.  |", 
									 "    |   | |   |   \\  '-. '-'   '-'  '-'   '..'  |", 
									 "    '^^^' '^^^'    '--'                         |", 
									 "===============.  .-.  .================.  .-.  |", 
									 "               | |   | |                |  '-'  |", 
									 "               | |   | |                |       |", 
									 "               | ':-:' |                |  .-.  |", 
									 "l42            |  '-'  |                |  '-'  |", 
									 "==============='       '================'       |",
									 "    ___________    ____   _____ _____    ____  ", 
									 "    \\____ \\__  \\ _/ ___\\ /      \\__  \\  /    \\", 
									 "    |  |_> > __ \\\\  \\___|  Y Y  \\/ __ \\|   |  \\", 
									 "    |   __(____  /\\___  >__|_|  (____  /___|  /", 
									 "    |__|       \\/     \\/      \\/     \\/     \\/ "};

		for ( unsigned int i = 0; i < pac_ascii . size (); ++i )
			logo ->  	print_str ( pac_ascii[i], 3, i, COLOR_PAIR ( PAIR_RED_BLACK ));


		logo -> refresh ();

		menu -> clear ();
		_menu -> draw ( menu );

		main_wind -> refresh ();
		menu 			-> refresh ();
		refresh ();


	}
void CMenuLayout::redraw ()
	{

	}
