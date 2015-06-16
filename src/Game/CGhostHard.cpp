#include <Game/CGhostHard.h>

#include <stdlib.h>
#include <set>
#include <algorithm>
#include <utility>

CGhostHard::CGhostHard ( int x, int y ):
	CGhost ( x, y )
	{

	}
CGhostHard::~CGhostHard ()
 	{

 	}
void CGhostHard::draw ( CWindow * window )
	{
		window -> print ( (int) 'M', coords.first, coords.second, COLOR_PAIR(PAIR_RED_BLACK));		
	}
void CGhostHard::update ( CBoard * board, CPlayer * player )
	{
		Direction next_dir;
		std::pair < bool, std::set < CGhost::Direction > > dirs = on_crossroad ( board );
		if ( dirs . first )
			{	
				std::set < CGhost::Direction >::const_iterator it( dirs . second . begin() );
				if ( abs ( coords . first - player -> getX () ) >  abs ( coords . second - player -> getY () ) )
					{
						if ( coords . first > player -> getX () ) it = dirs . second . find ( CGhost::LEFT );
						if ( coords . first < player -> getX () ) it = dirs . second . find ( CGhost::RIGHT );

						if ( it == dirs . second . end ()) 
							{
								if ( coords . second > player -> getY () ) it = dirs . second . find ( CGhost::UP );
								if ( coords . second < player -> getY () ) it = dirs . second . find ( CGhost::DOWN );
							}
					}
				else 
					{
						if ( coords . second > player -> getY () ) it = dirs . second . find ( CGhost::UP );
						if ( coords . second < player -> getY () ) it = dirs . second . find ( CGhost::DOWN );
						
						if ( it == dirs . second . end ()) 
							{
								if ( coords . first > player -> getX () ) it = dirs . second . find ( CGhost::LEFT );
								if ( coords . first < player -> getX () ) it = dirs . second . find ( CGhost::RIGHT );
							}
					}

			  if ( it == dirs . second . end ()) 
			  	{
			  		it = dirs . second . begin();
			  		advance ( it, rand () % dirs . second . size () );
			  	}
			  
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
