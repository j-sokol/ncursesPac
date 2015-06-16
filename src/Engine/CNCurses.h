#ifndef CNCURSES_H_DEFINED
#define CNCURSES_H_DEFINED

#include <ncurses.h>

/// Enumeration of colour pairs used for printing on
/// stdscr.
/// First colour is text, second is background.
enum ColourPairs
	{
		PAIR_BLUE_BLUE = 30,
		PAIR_RED_BLACK,
		PAIR_YELLOW_BLACK,
		PAIR_BLUE_BLACK,
		PAIR_GREEN_BLACK,
		PAIR_WHITE_BLACK,
		PAIR_RED_WHITE,
		PAIR_BLACK_WHITE
	};

/// Wrapped-around interactions with low-level
/// ncurses functions.
///
/// Point of this is to abstract away direct ncurses use.
namespace CNCurses
	{
		/// Initializes ncurses mode.
		///
		void init ();

		/// Exits ncurses mode.
		/// 
		/// Call this every time you leave the game,
		/// otherwise strange things with terminal 
		/// could happen.
		void exit ();

		/// Returns pressed key within a time of
		/// #time_delay (in miliseconds).
		///
		/// @note If #time_delay is -1, function
		/// will wait for input indefinitely. 
		int  get_input ( int time_delay = -1);	


		/// Key that was pressed last updated frame.
		/// It is ncurses internal value - ASCII
		/// code and some special keys, like 
		///	KEY_RIGHT, KEY_UP, etc.
		extern int pressed_key;
	}
	
#endif //CNCURSES_H_DEFINED
