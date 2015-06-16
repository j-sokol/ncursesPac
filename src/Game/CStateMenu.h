#ifndef CSTATEMENU_H_DEFINED
#define CSTATEMENU_H_DEFINED

#include <Engine/CState.h>
#include <Engine/CMenu.h>
#include <Game/CMenuLayout.h>


class CStateMenu : public CState
	{
		friend class CMenuLayout;
	public:
		CStateMenu( );
		virtual ~CStateMenu();
		void load ();
		void unload ();
		void update ();
		void draw ();

	private:
		CMenuLayout * layout;
		CMenu * menu;
		CMenu * levels;
		CMenu * options;


		bool menu_levels;
		bool menu_options;

		unsigned int difficulty;


		// other menus here ...
		void CreateMainMenu ();
		void DrawAboutMenu ();
		void CreateLevelsMenu ();
		void CreateOptionsMenu ();
	};

	
#endif //CSTATEMENU_H_DEFINED
