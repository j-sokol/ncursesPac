#ifndef CGHOSTMANAGER_H_DEFINED
#define CGHOSTMANAGER_H_DEFINED

#include <vector>
#include <Game/CGhost.h>
#include <Game/CBoard.h>
#include <Game/CPlayer.h>
#include <Engine/CWindow.h>


/// Enumeriation of game difficulties.
enum CGameDifficulty
	{
		EASY,
		MEDIUM, 
		HARD
	};

/// Manages ghosts for certain difficulty.
class CGhostManager
	{
	public:
		CGhostManager ( int x, int y, int difficulty, int & points );
		~CGhostManager ();
		void update ( CBoard * board, CPlayer * player );
		void draw ( CWindow * window );

		/// Tells if something at  collides with Player,
		/// if so and ghosts are frightened, adds score
		/// and moves ghost to starting position, otherwise
		/// kills player.
		void check_collisions ( CPlayer * player );

		/// Tells if ghosts are frightened.
		bool are_frightened ()  const;

		/// Sets frightened mode for all ghosts a restarts
		/// counter for it.
		void set_frightened_mode ( bool );

	private:

		/// Vector structure of all ghosts in the game
		std::vector < CGhost * > ghosts;

		/// Counter after how many updates shoud released.
		int loose_ghost_timer;

		/// How many active ghosts there is in the game.
		int active_ghosts;
		bool frightened_mode;
		int frightened_counter;

		/// Starting position of ghosts.
		int starting_x;
		int starting_y;

		int ghost_moves;
		
		/// How many ghosts were eaten.
		int ghosts_eaten;

		/// Reference to game score.
		int & points;
	};


#endif //CGHOSTMANAGER_H_DEFINED
