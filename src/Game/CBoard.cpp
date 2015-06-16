#include <Game/CBoard.h>
#include <Game/CPlayer.h>

#include <ostream>
#include <iostream>


CBoard::CBoard ( int width, int height, int dots ):
	dots_total ( dots ),
	dots_eaten ( 0 )
	{
		board = new C2DArray ( width, height );
		clear ();
	}
CBoard::~CBoard ()
	{
		delete board;
	}
bool CBoard::is_wall_hash   ( int x, int y ) const
	{
		if ( board -> at (x, y) == '#')
			return true;
		return false;
	}
bool CBoard::is_wall_x   ( int x, int y ) const
	{
		if ( board -> at (x, y) == 'x')
			return true;
		return false;
	}
bool CBoard::is_wall   ( int x, int y ) const
	{
		if ( board -> at (x, y) == 'x' || board -> at (x, y) == '#' )
			return true;
		return false;
	}
bool CBoard::all_dots_eaten () const
	{
		return ( dots_eaten >= dots_total );
	}

bool CBoard::is_dot  ( int x, int y ) const
	{
		if ( board -> at (x, y) == '.')
			return true;
		return false;
	}
void CBoard::eat_dot ( int x, int y )
	{
		board -> set ( x, y, ' ' );
		dots_eaten ++;
	}
bool CBoard::is_star ( int x, int y ) const
	{
		if ( board -> at (x, y) == '*')
			return true;
		return false;
	}
bool CBoard::is_empty_spot   ( int x, int y ) const
	{
		if ( board -> at (x, y) == ' ')
			return true;
		return false;
	}
bool CBoard::is_border ( int x, int y) const
	{
		if ((x == 0) || (x == (int) board->width()  - 1) ||
	    	(y == 0) || (y == (int) board->height() - 1))
			return true;

		return false;
	}
int  CBoard::get_width  () const
	{
		return board -> height ();
	}
int  CBoard::get_height () const
	{
		return board -> width ();
	}
void CBoard::draw ( CWindow * wind )
	{

		for (int i = 0; i < get_height (); ++i)
		{
			for (int j = 0; j < get_width (); ++j)
			{
				if ( is_wall_hash (j, i) )
					wind -> print ( (int) '#', j, i, COLOR_PAIR(PAIR_BLUE_BLUE));		

				else if ( is_wall_x (j, i) )
					wind -> print_char ( (int) ' ', j, i);		

				else if ( is_dot ( j, i ))
					wind -> print_char ( (int) '.', j, i);		

				else if ( is_empty_spot ( j, i ))
					wind -> print_char ( (int) ' ', j, i);	

				else if ( is_star 	( j, i ))
					wind -> print_char ( (int) '*', j, i);

			}
		}
	}
void CBoard::teleport ( CPlayer * player)
	{

	}
void CBoard::clear ()
	{
		for (int i = 0; i < get_height (); ++i)
		{
			for (int j = 0; j < get_width (); ++j)
			{
				board -> set ( j, i, ' ');
			}
		}
	}
void CBoard::set_board ( const std::vector < std::vector < char > > & n_board )
	{
		for (int i = 0; i < get_height (); ++i)
		{
			for (int j = 0; j < get_width (); ++j)
			{
				board -> set ( j, i, n_board [i] [j] );
			}
		}
	}
std::pair<int, int> CBoard::get_start_pos ( ) const
	{
		return std::make_pair (player_start_x, player_start_y);
	}
void CBoard::set_start_pos ( std::pair <int, int> pos)
	{
		player_start_x = pos.first;
		player_start_y = pos.second; 
	}
void CBoard::set_ghost_start_pos ( int x, int y)
	{
		ghost_start_x = x;
		ghost_start_y = y;
	}

int CBoard::get_ghost_x ()
	{
		return ghost_start_x;
	}
int CBoard::get_ghost_y ()
	{
		return ghost_start_y;
	}


/*void CBoard::print_board () const
	{
		std::cerr << "height & width of board: " << board -> height () << " x " << board -> width () << std::endl;
		std::cerr << "  ";
		for (int i = 0; i < get_width (); ++i)
		{
			std::cerr << i % 10;
		}
		std::cerr << std::endl;
		for (int i = 0; i < get_height (); ++i) 
		{
			std::cerr << i << "|";
			for (int j = 0; j < get_width(); ++j) 
			{
				std::cerr << board -> at ( j, i);
			}
			std::cerr << std::endl;
		}
	}
*/