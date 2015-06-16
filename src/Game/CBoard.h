#ifndef CBOARD_H_DEFINED
#define CBOARD_H_DEFINED

#include <Engine/C2DArray.h>
#include <Engine/CWindow.h>

#include <map>
#include <vector>

class CPlayer;
/// A Board where monsters and player runs.
///
/// Class represents single level loaded from file 
/// where player can play on.
///
/// It basically is a 2D board of tiles (chars),
/// where each can be wall, invisible wall (around
/// blank spaces, so it looks prettier :D), blank
/// space, food or star (to slow down ghosts and 
/// get them into frightened mode).
///
/// Also contains some additional info, like starting
/// positions for player, ghosts and number of total / 
/// eaten dots. 
class CBoard
	{
	public:
		static int WIDTH_SIZE;
		static int HEIGHT_SIZE;

		/// Creates new board
		///
		/// @param width Width of whole level
		/// @param width Width of whole level
		/// @param dots Output parameter with total
		/// count of  dots and stars on whole map
		CBoard (int width, int height, int dots );
		virtual ~CBoard ();

		/// Tells if there is visible wall at `x` `y`
		bool is_wall_hash   ( int x, int y ) const;

		/// Tells if there is invisible wall at `x` `y`
		bool is_wall_x   ( int x, int y ) const;

		/// Tells if there is wall at `x` `y`
		bool is_wall   ( int x, int y ) const;

		/// Tells if there is empty spot at `x` `y`
		bool is_empty_spot   ( int x, int y ) const;

		/// Tells if there is food at `x` `y`
		bool is_dot   ( int x, int y ) const;

		/// Tells if there is visible wall at `x` `y`
		void eat_dot ( int x, int y );

		/// Tells if there is border at `x` `y`
		bool is_border ( int x, int y) const;

		/// Tells if there is star at `x` `y`
		bool is_star ( int x, int y) const;

		/// Tells if all food is eaten (end of stage)
		bool all_dots_eaten ( ) const;

		int get_width () const;
		int get_height() const;

		void draw ( CWindow * wind );

		void teleport ( CPlayer * player);


		/// Makes the whole board empty.
		void clear ();

		/// Sets content of whole board.
		///
		/// @param board 2D std::vector array of chars containing
		/// definition of map.
		void set_board ( const std::vector < std::vector < char > > & board );

		///Returns starting position of player.
		std::pair <int, int> get_start_pos ( ) const;

		/// Sets starting position of player.
		void set_start_pos ( std::pair <int, int> );

		void set_ghost_start_pos ( int x, int y);

		/// Returns starting `x` position of ghost.
		int get_ghost_x ();
		int get_ghost_y ();

	protected:

		/// Array of the actual level on screen.
		/// * `#`, `x` means wall,
		/// * `' '` means empty space, 
		/// * `*` star.
		C2DArray * board;


		/// Initial coordinates for player.
		int player_start_x;
		int player_start_y;

		/// Initial coordinates for ghosts.
		int ghost_start_x;
		int ghost_start_y;


		/// Tells how many food there is on map.
		int dots_total;

		/// Tells how many dots were eaten.
		int dots_eaten;

		/// Contains name of map.
		std::string name;

		
	};
	

#endif //CBOARD_H_DEFINED
