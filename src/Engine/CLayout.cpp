#include <Engine/CLayout.h>
#include <Engine/CNCurses.h>

#include <iostream>
#include <cstdlib>

template<typename T> void safe_delete(T*& a) 
	{
	  delete a;
	  a = NULL;
	}

CLayout::CLayout (int width, int height)
	{
		main_wind = NULL;
		CLayout::inteded_w = width;
		CLayout::inteded_h = height;

	}
CLayout::~CLayout ()
	{
		window_exit ();
	}
void CLayout::window_init ()
	{
		clear ();

		int cur_h, cur_w;
		getmaxyx ( stdscr, cur_h, cur_w );

		if ( cur_w < CLayout::inteded_w || cur_h < CLayout::inteded_h )
			{
				CNCurses::exit ();
				std::cerr << "console window is too small." << std::endl
						  << "has to be atleast 80x24." << std::endl;
				exit ( EXIT_FAILURE );
			}
		CLayout::screen_height = CLayout::inteded_h;
		CLayout::screen_width  = CLayout::inteded_w;

		int ax_x = cur_w / 2 - CLayout::inteded_w / 2;
		int ax_y = cur_h / 2 - CLayout::inteded_h / 2;

		main_wind = new CWindow ( ax_x, ax_y, CLayout::inteded_w, CLayout::inteded_h, true, "nCurses PAC-MAN" );

		main_wind -> refresh ();

	}
void CLayout::window_exit ()
	{
		safe_delete ( main_wind );
	}
void CLayout::draw ()
	{

	}
