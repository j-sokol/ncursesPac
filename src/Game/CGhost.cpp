#include <Game/CGhost.h>

#include <Engine/CNCurses.h>

CGhost::CGhost  (int x, int y):
	cur_dir ( CGhost::UP ),
	alive ( true ),
	frightened ( false )
	{
		coords . first = x;
		coords . second = y;
	}
CGhost::~CGhost ()
	{

	}
int CGhost::getX () const
	{
		return coords.first;
	}
int CGhost::getY () const
	{
		return coords.second;
	}
void CGhost::kill ()
	{
		alive = false;
	}
void CGhost::set_frightened_mode ( bool option )
	{
		frightened = option;
	}
bool CGhost::is_frightened () const
	{
		return frightened;
	}

void CGhost::move_to ( int x, int y )
	{
		coords.first = x;
		coords.second = y;
	}
void CGhost::update ( CBoard * board, CPlayer * player )
	{
		Direction next_dir;
		std::pair < bool, std::set < CGhost::Direction > > dirs = on_crossroad ( board );
		if ( dirs . first )
			{	
				  std::set< CGhost::Direction >::const_iterator it( dirs . second . begin() );
				  advance ( it, rand () % dirs . second . size () );
					next_dir = *it;
			}
		else next_dir = *(dirs . second . begin ());

		switch ( next_dir )
			{
				case CPlayer::LEFT:
					coords.first--;
					break;
				case CPlayer::RIGHT:
					coords.first++;
					break;
				case CPlayer::UP:
					coords.second--;
					break;
				case CPlayer::DOWN:
					coords.second++;
					break;
			}
		cur_dir = next_dir;
	}
void CGhost::draw ( CWindow * window )
	{
		window -> print ( (int) 'M', coords.first, coords.second, COLOR_PAIR(PAIR_YELLOW_BLACK));	
	}
void CGhost::draw ( CWindow * window, int colour_pair )
	{
		window -> print ( (int) 'M', coords.first, coords.second, COLOR_PAIR ( colour_pair ));
	}

std::pair < bool, std::set < CGhost::Direction > > CGhost::on_crossroad ( CBoard * board )
	{
		std::set < CGhost::Direction > dirs;

		if ( ! board -> is_wall ( coords . first + 1, coords . second ))
			dirs . insert ( CGhost::RIGHT );
		if ( ! board -> is_wall ( coords . first - 1, coords . second ))
			dirs . insert ( CGhost::LEFT );
		if ( ! board -> is_wall ( coords . first , coords . second + 1))
			dirs . insert ( CGhost::DOWN );
		if ( ! board -> is_wall ( coords . first , coords . second - 1))
			dirs . insert ( CGhost::UP );

		switch ( cur_dir )
			{
				case CGhost::LEFT:
					dirs .  erase ( CGhost::RIGHT );
					break;
				case CGhost::RIGHT:
					dirs .  erase ( CGhost::LEFT );
					break;
				case CGhost::UP:
					dirs .  erase ( CGhost::DOWN );
					break;
				case CGhost::DOWN:
					dirs .  erase ( CGhost::UP );
					break; 
			}

		if ( dirs . size () > 1 )
			return std::pair < bool, std::set < CGhost::Direction > >  ( make_pair ( true, dirs ));
		return std::pair < bool, std::set < CGhost::Direction > >  ( make_pair ( false, dirs ));
	}