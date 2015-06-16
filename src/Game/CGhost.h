#ifndef CGHOST_H_DEFINED
#define CGHOST_H_DEFINED

#include <Game/CBoard.h>
#include <Game/CPlayer.h>
#include <Engine/CWindow.h>

#include <stdlib.h>
#include <set>
#include <algorithm>
#include <utility>

/// Entity of ghost, on crossroads goes random way.
class CGhost
	{
	public:
		/// Enumeration of directions ghost can go.
		enum Direction
				{
					LEFT, DOWN, UP, RIGHT
				};
		CGhost  (int x, int y);
		CGhost  ( ) {}
		virtual ~CGhost ();

		int getX () const;
		int getY () const;

		/// Kills ghost.
		void kill ();

		void set_frightened_mode ( bool option );

		/// Tells if ghost is vulnerable.
		bool is_frightened () const;

		/// Moves ghost to `x` `y` coordinates.
		void move_to ( int x, int y );

		/// Updates ghost on board.
		virtual void update ( CBoard * board, CPlayer * player );

		/// Draws ghost with default colours.
		virtual void draw ( CWindow * window );

		/// Draws ghost with colours you choose.
		virtual void draw ( CWindow * window, int colour_pair );

		/// Checks if ghost is on crossroad, if so, returns set od directions 
		/// where he can go.
		std::pair < bool, std::set < Direction > > on_crossroad ( CBoard * board );

		/// Coordinates where ghost is.
		std::pair < int, int > coords;

		/// Direction where ghost is heading.
		Direction cur_dir;

		/// Tells if ghost is alive.
		bool alive;

		/// Tells if ghost is frightened.
		bool frightened;
	};

	
#endif //CGHOST_H_DEFINED
