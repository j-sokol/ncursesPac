#ifndef CLAYOUT_H_DEFINED
#define CLAYOUT_H_DEFINED

#include <Engine/CWindow.h>


/// Main Layout for things how are shown on screen.
class CLayout
	{
	public:
		CLayout (int width, int height);
		~CLayout ();
		virtual void window_init ();
		virtual void window_exit ();
		virtual void draw ();


		/// Layout's main window, all other windows are inside.
		CWindow * main_wind;

		/// Width of terminal window at this time.
		int screen_width;
		
		/// Width of terminal window at this time.
		int screen_height;
		int inteded_w;
		int inteded_h;
		
	};

	
#endif //CLAYOUT_H_DEFINED
