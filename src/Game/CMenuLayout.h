#ifndef CMENULAYOUT_H_DEFINED
#define CMENULAYOUT_H_DEFINED

//#include <Game/CStateMenu.h>
#include <Engine/CWindow.h>
#include <Engine/CLayout.h>
#include <Engine/CMenu.h>

class CStateMenu;

/// Layout of what will be drawn at CStateMenu.
class CMenuLayout : public CLayout
	{
	public:
		// For compiler, hiding parent's virtual function.
		using CLayout::draw;

		CMenuLayout( int width, int height, CStateMenu * CState);
		virtual ~CMenuLayout();
		void window_init ();
		void window_exit ();


		/// Shows the main menu screen with exact `menu` passed
		/// as parameter.
		void draw (CMenu * menu);
		void redraw ();

		CStateMenu * CState;
		CWindow * menu;
		CWindow * logo;
	};


	
#endif //CMENULAYOUT_H_DEFINED
