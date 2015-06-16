#ifndef CPLAYER_H_DEFINED
#define CPLAYER_H_DEFINED

#include <utility>
#include <Engine/CWindow.h>
#include <Game/CBoard.h>

///
class CPlayer
	{
	public:
		/// Enumeriation of directions where player 
		/// can go.
		enum Direction
			{
				LEFT, DOWN, UP, RIGHT
			};

		/// Constructs player, `x` `y` are starting
		/// coordinates.
		CPlayer ( int x, int y );
		CPlayer ( std::pair < int, int > coords );
		~CPlayer ();
		int getX () const;
		int getY () const;

		/// moves player one tile to direction where 
		/// he heads.
		void move ( Direction dir);

		/// Moves player to `x` `y` coordinates.
		void move_to ( int x, int y);
		void kill ();

		/// Tells if player is alive.
		bool is_alive () const;
		void update (CBoard * board);

		/// Draws player to `window`.
		void draw (CWindow * window);


	/// pair of coodinates where player is.
	std::pair < int, int > coords;
	std::pair < int, int > next_coords;
	bool alive;

	/// Direction where player is going.
	Direction cur_dir;
	Direction next_dir;

		
	};

	
#endif //CPLAYER_H_DEFINED
