#ifndef CINPUTMANAGER_H_DEFINED
#define CINPUTMANAGER_H_DEFINED

#include <ncurses.h>
/// Handles input from keyboard all over the game.
///
/// Colection of global functions to know, if 
/// keys were pressed or not.
namespace CInputManager
	{
		/// Returns true if #key was pressed.
		/// @note #key is internal ncurses value.
		bool is_pressed ( int key );

		/// returns true if any key was pressed.
		bool any_key_pressed ();
		
		/// returns true if no key was pressed.
		bool no_key_pressed ();

		/// Gets the input.
		/// @param time_delay
		/// * if positive, will wait #time_delay
		/// miliseconds,
		/// * if zero, will update imediately,
		/// * if negative, will wait for input
		/// indefinetely.
		void update ( int time_delay = 0);
	}

#endif //CINPUTMANAGER_H_DEFINED
