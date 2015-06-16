#include <Engine/CNCurses.h>

#include <sys/select.h>			// select()
#include <unistd.h>				// STDIN_FILENO
#include <locale.h>


int CNCurses::pressed_key = ERR;


void CNCurses::init ()
	{
		setlocale(LC_CTYPE, "");
		initscr ();
		curs_set (0);
		cbreak ();
		noecho ();
		nodelay (stdscr, TRUE);
		keypad ( stdscr, TRUE);

		start_color();
		init_pair(PAIR_RED_BLACK, COLOR_RED, COLOR_BLACK);
		init_pair(PAIR_BLUE_BLUE, COLOR_BLUE, COLOR_BLUE);
		init_pair(42, COLOR_BLUE, COLOR_BLUE);
		init_pair(PAIR_YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);
		init_pair(PAIR_YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);
		init_pair(PAIR_BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
		init_pair(PAIR_GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
		init_pair(PAIR_WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
		init_pair(PAIR_RED_WHITE, COLOR_RED, COLOR_WHITE);
		init_pair(PAIR_BLACK_WHITE, COLOR_BLACK, COLOR_WHITE);

		ESCDELAY = 25;
		refresh ();

	}
void CNCurses::exit ()
	{
		erase ();
		refresh ();
		endwin ();
	}
int CNCurses::get_input ( int time_delay ) 
	{
		/* CODE writen Alexandre Dantas taken from his nSnake project*/
		int retval = 0;
		int c      = 0;

		fd_set input;
		struct timeval timeout;

		timeout.tv_sec = 0;
		timeout.tv_usec = time_delay * 1000; // microseconds

		// If #delay_ms is -1, we'll wait infinitely
		// (sending NULL to #select())
		struct timeval* timeout_p = NULL;
		if (time_delay != -1)
			timeout_p = &timeout;

		FD_ZERO(&input);
		FD_SET(STDIN_FILENO, &input);

		// This function is somewhat complex
		// check 'man select' for info
		retval = select(FD_SETSIZE, &input, NULL, NULL, timeout_p);

		// Ncurses' function that works without delay
		// (because we nodelay()'ed)
		c = getch();

		if ((retval == 1) && (c == ERR)) // ERROR
			return -1;

		if (retval == 0)
			return ERR; // Nothing was pressed.
						// This is an Ncurses internal value.

		return c;
	}
