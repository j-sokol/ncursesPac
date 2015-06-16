#ifndef CWINDOW_H_DEFINED
#define CWINDOW_H_DEFINED

#include <Engine/CNCurses.h>

#include <string>
#include <vector>
#include <ncurses.h>


/// Alias for filling whole parent window with child window.
#define FILL_WINDOW 0


/// A wrap around class for ncurses WINDOW. 
class CWindow
	{
	public:
		CWindow ( int x, int y, int w, int h);
		CWindow ( int x, int y, int w, int h, bool border, std::string label );
		CWindow ( CWindow * parent, int x, int y, int width, int height);
		CWindow ( CWindow * parent, int x, int y,
				  int width, int height, bool border, std::string label);

		virtual ~CWindow();

		/// shows char #c at #x #y coordinates.
		/// @note White font on black background
		void print_char ( int c, int x, int y );
		
		/// shows char #c at #x #y coordinates with #colour_pair.
		void print ( int c, int x, int y, int colour_pair);

		/// Shows text #str at #x #y on the window..
		/// @note White font on black background
		void print_str ( std::string str, int x, int y );

		/// Shows text #str at #x #y on the window with color #pair.		
		void print_str ( std::string str, int x, int y, int colour_pair );

		/// Sets text that will appear at the bottom of the window.
		void set_lower_text ( std::string );
		void clear ();
		void refresh ();
		int get_height () const;
		int get_width () const;
		int get_x () const;
		int get_y () const;

	protected:

		/// ncurses internal data structure.
		WINDOW * wind;

		int x;
		int y;
		int width;
		int height;

		/// Tells if window has a border.
		bool border;

		///	String containing label of window, shown at upper-left
		/// side of window.
		std::string label;

		///	String containing text shown at lower-left side of window.
		std::string lower_text;
		
	};
	
	
#endif //CWINDOW_H_DEFINED
