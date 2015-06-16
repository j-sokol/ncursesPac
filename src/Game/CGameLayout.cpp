#include <Game/CGameLayout.h>
  

#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <ncurses.h> 
#include <cstdlib>

template<typename T> void safe_delete(T*& a) 
	{
	  delete a;
	  a = NULL;
	}
	
CGameLayout::CGameLayout ( CGame * game, int width, int height):
	CLayout ( width, height ),
	game ( game ),
	game_wind ( NULL ),
	pause_menu ( NULL )
	{
		this -> window_init ();
	}
CGameLayout::~CGameLayout ()
	{
		this -> window_exit ();
	}
void CGameLayout::window_init ()
	{
		CLayout::window_init();

		int cur_h, cur_w;
		getmaxyx ( stdscr, cur_h, cur_w );
		int width  = game -> board -> get_width (); 
		int height = game -> board -> get_height ();
		int x = cur_w / 2 - game -> board -> get_width () / 2;
		int y = cur_h / 2 - game -> board -> get_height () / 2;

		this -> game_wind = new CWindow ( main_wind, x, y, width, height); 
		this -> pause_menu = new CWindow ( main_wind, (main_wind -> get_width() * 3) / 8, main_wind -> get_height () / 2 , main_wind -> get_width () / 4, 7, true, "Pause Menu");
	}
void CGameLayout::window_exit ()
	{
		safe_delete ( game_wind );
		safe_delete ( pause_menu );
		CLayout::window_exit ();

	}
void CGameLayout::draw ( CMenu * menu)
	{
		if ( ! game )
			return;

		if ( game -> is_paused () )
			{
				pause_menu -> clear ();
				menu -> draw ( pause_menu );
				pause_menu -> refresh ();

				refresh ();
				return;
			}

		main_wind -> clear ();
		game_wind -> clear ();
		

		game -> board -> draw ( game_wind );
		game -> player -> draw ( game_wind );
		game -> ghost -> draw ( game_wind );

		std::ostringstream ss;
	  ss << "Lives: " << game -> lives << "]_____[Score: " 
	  	 << std::setw ( 6 ) << std::setfill ('0') 
	  	 << game -> points << "]_____[HS: " 
	  	 << std::setw ( 6 ) << std::setfill ('0')
	  	 << game -> high_score << "]_____['p' for menu";

	  std::string info = ss.str();
	  main_wind -> set_lower_text ( info );

		main_wind -> refresh ();
		game_wind -> refresh ();

		
	}
