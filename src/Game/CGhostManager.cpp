#include <Game/CGhostManager.h>
  
#include <Game/CGhostMedium.h>
#include <Game/CGhostHard.h>
#include <stdlib.h>


template<typename T> void safe_delete(T*& a) 
	{
	  delete a;
	  a = NULL;
	}

CGhostManager::CGhostManager ( int x, int y, int difficulty, int & points ):
	active_ghosts ( 1 ),
	frightened_mode ( false ),
	starting_x ( x ),
	starting_y ( y ), 
	ghost_moves ( 0 ),
	frightened_counter ( 0 ),
	ghosts_eaten ( 0 ),
	points ( points )
	{
		CGhost * ghost;
		if ( difficulty == EASY )
			{
				ghost = new CGhost ( x, y );
				ghosts . push_back (  ghost );

				ghost = new CGHostMedium ( x, y );
				ghosts . push_back (  ghost );

				ghost = new CGhost ( x, y );
				ghosts . push_back (  ghost );

				ghost = new CGHostMedium ( x, y );
				ghosts . push_back (  ghost );
				
				loose_ghost_timer = 30;
			}
		if ( difficulty == MEDIUM )
			{
				ghost = new CGhost ( x, y );
				ghosts . push_back (  ghost );

				ghost = new CGHostMedium ( x, y );
				ghosts . push_back (  ghost );

				ghost = new CGhostHard ( x, y );
				ghosts . push_back (  ghost );

				ghost = new CGHostMedium ( x, y );
				ghosts . push_back (  ghost );


				loose_ghost_timer = 22;
			}
		if ( difficulty == HARD )
			{
				ghost = new CGHostMedium ( x, y );
				ghosts . push_back (  ghost );

				ghost = new CGhostHard ( x, y );
				ghosts . push_back (  ghost );

				ghost = new CGhostHard ( x, y );
				ghosts . push_back (  ghost );

				ghost = new CGhostHard ( x, y );
				ghosts . push_back (  ghost );

				loose_ghost_timer = 15;
			}


	}
CGhostManager::~CGhostManager()
	{
		for (std::vector<CGhost *>::iterator i = ghosts.begin(); i != ghosts.end(); ++i)
			safe_delete (*i);
	}
void CGhostManager::update ( CBoard * board, CPlayer * player )
	{
		if ( frightened_mode )
			frightened_counter++;

		if (frightened_counter >= 70 )
			{
				frightened_counter = 0;
				frightened_mode = false;

				for (int i = 0; i < active_ghosts; ++i)
					{
						ghosts [i] -> set_frightened_mode ( false );
					}
			} 

		ghost_moves++;
		if ( (ghost_moves % loose_ghost_timer) == 0 && active_ghosts < (int) ghosts . size () )
			active_ghosts++;

		for (int i = 0; i < active_ghosts; ++i)
		{
			ghosts [i] -> update ( board, player ); 
		}
	}
void CGhostManager::draw ( CWindow * window )
	{
		for (int i = 0; i < active_ghosts; ++i)
			{
				if ( ! ghosts [i] -> is_frightened () ) ghosts [i] -> draw ( window ); 
				else 
					{
						if ( frightened_counter > 60 && frightened_counter % 2 == 0 )
							ghosts [i] -> draw ( window, PAIR_WHITE_BLACK );
						else ghosts [i] -> draw ( window, PAIR_BLUE_BLACK );
					}
			}
	}
void CGhostManager::check_collisions ( CPlayer * player )
	{
		for (int i = 0; i < active_ghosts; ++i)
		{
			if ( ghosts [i] -> getX () == player -> getX () &&
					 ghosts [i] -> getY () == player -> getY () )
				{
					if ( ghosts [i] -> is_frightened () )
						{
							ghosts [i] -> set_frightened_mode ( false );
							ghosts [i] -> move_to ( starting_x, starting_y );
							ghosts_eaten++;
							switch ( ghosts_eaten )
								{
									case 1:
										points += 200;
										break;
									case 2:
										points += 400;
										break;
									case 3:
										points += 800;
										break;
									case 4:
										points += 1600;
										break;
								}

						}
					else player -> kill ();
				}
		}
	}
bool CGhostManager::are_frightened ()  const
	{
		return frightened_mode;
	}
void CGhostManager::set_frightened_mode ( bool mode )
	{
		frightened_mode = mode;
		for (int i = 0; i < active_ghosts; ++i)
			{
				ghosts [i] -> set_frightened_mode ( mode );  
			}
		if ( mode )
			frightened_counter = 0;
	}

