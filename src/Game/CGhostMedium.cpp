#include <Game/CGhostMedium.h>

#include <stdlib.h>
#include <set>
#include <algorithm>
#include <utility>


CGHostMedium::CGHostMedium ( int x, int y ):
	CGhost ( x, y )
	{

	}
CGHostMedium::~CGHostMedium ()
	{

	}
void CGHostMedium::draw ( CWindow * window )
	{
		window -> print ( (int) 'M', coords.first, coords.second, COLOR_PAIR(PAIR_GREEN_BLACK));
	}
bool CGHostMedium::player_on_sight ( int player_x, int player_y, CBoard * board, Direction& dir)
	{
		if ( player_x == coords . first )
			{
				//player on same X axis
 				for (int i = std::min (player_y, coords . second); i < std::max (player_y, coords . second); ++i)
					if ( board -> is_wall ( player_x, i ))
						return false;

				if ( player_y > coords . second ) dir = CGhost::DOWN;
				if ( player_y < coords . second ) dir = CGhost::UP;
				return true;
			}

		else if ( player_y == coords . second )
			{
				//player on same Y axis
				for (int i = std::min (player_x, coords . first); i < std::max (player_x, coords . first); ++i)
					if ( board -> is_wall ( i, player_y ))
						return false;

				if ( player_x > coords . first ) dir = CGhost::RIGHT;
				if ( player_x < coords . first ) dir = CGhost::LEFT;
				return true;
			}

		else return false;
	}

void CGHostMedium::update ( CBoard * board, CPlayer * player )
	{
		Direction next_dir;
		std::pair < bool, std::set < CGhost::Direction > > dirs = on_crossroad ( board );
		bool player_is_on_sight = player_on_sight ( player -> getX (), player -> getY (), board, next_dir);
		

		if ( player_is_on_sight ) // if ghost sees player
			{
				std::pair < int, int > tmp_coords ( coords );
			
				switch ( next_dir )
					{
						case CPlayer::LEFT:
							tmp_coords.first--;
							break;
						case CPlayer::RIGHT:
							tmp_coords.first++;
							break;
						case CPlayer::UP:
							tmp_coords.second--;
							break;
						case CPlayer::DOWN:
							tmp_coords.second++;
							break;

					}

				if ( ! board -> is_wall (tmp_coords.first, tmp_coords.second) )
					{
						coords = tmp_coords;
						return;
					}
				else next_dir = *(dirs . second . begin ());

			}
		else if ( dirs . first ) // if is on crossroad
			{	
		  	std::set < CGhost::Direction > ::const_iterator it ( dirs . second . begin() );
			  std::advance ( it, rand () % dirs . second . size () );
				next_dir = *it;
			}

		// goes to the only direction in set
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
