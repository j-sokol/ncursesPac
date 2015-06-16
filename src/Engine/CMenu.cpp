#include <Engine/CMenu.h>
#include <Engine/CInputManager.h>
#include <cstdlib>

template<typename T> void safe_delete(T*& a) 
	{
	  delete a;
	  a = NULL;
	}


CMenu::CMenu ( int x, int y, int width, int height ):
	cur_index ( 0 ),
	x ( x ),
	y ( y ),
	width ( width ),
	height ( height ),
	will_exit ( false ),
	selected ( false ),
	current ( NULL ),
	selected_item ( NULL )
	{

	}
CMenu::~CMenu()
	{
		for ( unsigned int i = 0; i < items . size (); ++i )
			safe_delete ( items [ i ] );
		items . clear ();
	}
void CMenu::add ( CMenuItem * item )
	{
		items . push_back ( item );

		if ( items . size () == 1 )
			{
				current = items . back ();
				cur_index = items . size () - 1;
			}
		unsigned int i;
		for ( i = 0; i < items . size () ; ++i )
			if ( items [i] )
				break;

		current = items [i];
		cur_index = i;
	}
void CMenu::add_blank ()
	{
		items . push_back ( NULL );
	}
void CMenu::RemoveByID ( unsigned int id )
	{
		std::vector < CMenuItem *>::iterator it = items . begin ();

		while ( it != items . end () )
			{
				if ( ! * it )
					it ++;

				if (  (*it) -> id == id )
					{
						if ( current == * it )
							{
								GoNextItem ();
								cur_index --;
							}
						safe_delete ( * it );
						items . erase ( it );
						return;
					}
				else it ++;
			}
	}
void CMenu::draw ( CWindow * window )
	{
		unsigned int draw_begin = 0;
		unsigned int draw_end 	= items . size ();

		for ( unsigned int cur_item = draw_begin, yoffset = 0;
					cur_item < draw_end;
					cur_item++, yoffset++ )
			{
				if ( ! items [ cur_item ] )
					{
						for (int i = 0; i < width ; ++i)
							{
								window -> print ( (int) '-', x + i, y + yoffset, COLOR_PAIR ( PAIR_WHITE_BLACK ));
							}
					}
				else
					{
						items [ cur_item ] -> draw ( window, x, y + yoffset, width, items [ cur_item ] == current ); // 	
					}
			}

	}
void CMenu::HandleInput ()
	{
		if ( CInputManager::no_key_pressed () )
			return;

		if ( CInputManager::is_pressed (KEY_UP) )
			GoPrevItem ();

		else if ( CInputManager::is_pressed (KEY_DOWN) )
			GoNextItem ();

		else if ( CInputManager::is_pressed ('\n') )
			{
				if ( current -> type == CMenuItem::OPTION || current -> type == CMenuItem::ITEM )
					{
						selected = true;
						selected_item = current;
					}
				else 
					current -> HandleInput ();
			}
		else 
			{
				if ( current )
					current -> HandleInput ();
			}
	}
void CMenu::GoNextItem ()
	{
		if ( items . size () == 0 )
			return;
		if ( items . size () == 1 )
			{
				current = * ( items . begin () );
				cur_index = 0;
				return;
			}

		if ( current == items . back () )
			{
				if ( cur_index == items . size () - 1 )
					{
						GoFirstItem ();
						return;
					}
			}

		cur_index++;
		current = items [ cur_index ];

		if ( ! current )
			GoNextItem ();
	}
void CMenu::GoPrevItem ()
	{
		if ( items . size () == 0 )
			return;
		if ( items . size () == 1 )
			{
				current = items . front ();
				cur_index = 0;
				return;
			}

		if ( current == items . front () )
			{
				if ( cur_index == 0 )
					{
						GoLastItem ();
						return;
					}
			}

		cur_index--;
		current = items [ cur_index ];

		if ( ! current )
			GoPrevItem ();
	}
void CMenu::GoLastItem ()
	{
		if ( items . size () == 0 )
			return;
		if ( items . size () == 1 )
			{
				current = ( items . front () );
				cur_index = 0;
				return;
			}

		current = items . back ();
		cur_index = items . size () - 1;

		if ( ! current )
			GoPrevItem ();
	}
void CMenu::GoFirstItem ()
	{
		if ( items . size () == 0 )
			return;
		if ( items . size () == 1 )
			{
				current = ( items . front () );
				cur_index = 0;
				return;
			}

		current = items . front ();
		cur_index = 0;

		if ( ! current )
			GoNextItem ();
	}
bool CMenu::WillExit () const
	{
		return ( selected && selected_item );
	}
std::string CMenu::CurrentLabel ()
	{
		if ( ! current )
			GoNextItem ();

		return current -> label;
	}
int CMenu::CurrentID ()
	{
		if ( ! current )
			GoNextItem ();

		return current -> id;

	}
void CMenu::reset ()
	{
		selected_item = NULL;
		selected 	    = false;
	}