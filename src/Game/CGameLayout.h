#ifndef CGAMELAYOUT_H_DEFINED
#define CGAMELAYOUT_H_DEFINED

#include <Game/CGame.h>
#include <Engine/CLayout.h>
#include <Engine/CMenu.h>
#include <Engine/CWindow.h>

class CGame;

/// Layout for CStateGame, defines where all sub-windows
/// should be.
class CGameLayout : public CLayout
	{
	public:
		using CLayout::draw;
		CGameLayout ( CGame * game, int width, int height);
		virtual ~CGameLayout ();

		void window_init ();
		void window_exit ();

		void draw ( CMenu * menu );  

		/// Contains pause menu.
		CWindow * pause_menu;

	private:
		CGame 	* game;
		/// Contains window with board, etc.
		CWindow * game_wind;
		
	};

	
#endif //CGAMELAYOUT_H_DEFINED
