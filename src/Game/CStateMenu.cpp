#include <Game/CStateMenu.h>
#include <Game/CGhostManager.h>
#include <Engine/CStateManager.h>
#include <Game/CBoardUtils.h>
#include <Game/CStateGame.h>
  
#include <Engine/CInputManager.h>
#include <Engine/CDialog.h>
#include <Engine/CMenuItem.h>
#include <Engine/CMenuItemOption.h>
#include <cstdlib>


template<typename T> void safe_delete(T*& a) 
	{
	  delete a;
	  a = NULL;
	}


CStateMenu::CStateMenu ():
	layout ( NULL ),
	menu ( NULL ),
	levels ( NULL ),
	options ( NULL ),
	menu_levels ( false ),
	menu_options ( false ),
	difficulty ( CGameDifficulty::MEDIUM )
	{
		
	}
CStateMenu::~CStateMenu()
	{

	}
void CStateMenu::load ()
	{
		layout = new CMenuLayout ( 80, 24, this );
		CreateMainMenu ();
		CreateLevelsMenu ();
		CreateOptionsMenu ();
	}
void CStateMenu::unload ()
	{
		safe_delete ( menu );
		safe_delete ( layout );
		safe_delete ( levels );
		safe_delete ( options );
	}
void CStateMenu::update ()
	{
		if ( CInputManager::is_pressed ( 'q' )) // ESC KEY  - q
			CStateManager::quit ();

		if ( menu_levels ) // all submenus here
			{
				levels -> HandleInput ();
					if ( levels -> WillExit () ) // if main menu will quit
					{
						auto tmp_ID = levels -> CurrentID ();
						switch ( tmp_ID )
							{
								case BACK:
								menu_levels = false;
								break;

								default:
								CStateManager::change(new CStateGame(levels -> current -> label, difficulty));
								break;
							}
						levels -> reset ();
					}

			}
		else if ( menu_options )
			{
				options -> HandleInput ();
					if ( options -> WillExit () ) // if main menu will quit
					{
						auto tmp_ID = options -> CurrentID ();
						switch ( tmp_ID )
							{
								case BACK:
									menu_options = false;
									break;

								case EASY:
									difficulty = CGameDifficulty::EASY;
									menu_options = false;
									break;

								case MEDIUM:
									difficulty = CGameDifficulty::MEDIUM;
									menu_options = false;
									break;
									
								case HARD:
									difficulty = CGameDifficulty::HARD;
									menu_options = false;
									break;	

								break;
							}
						options -> reset ();
					}
			}
		else
			{
				menu -> HandleInput ();
				if ( menu -> WillExit () ) // if main menu will quit
					{
						auto tmp_ID = menu -> CurrentID ();
						switch ( tmp_ID )
							{
								case START_GAME:
								CStateManager::change ( new CStateGame ( "default", difficulty ) );
								break;
								case CHOOSE_LEVEL:
								menu_levels = true;
								break;
								case OPTIONS:
								menu_options = true;
								break;

								case ABOUT:
								DrawAboutMenu ();
								break;

								case EXIT_GAME:
								CStateManager::quit ();
								break;
							}
						menu -> reset ();
					}
			}	

	}
void CStateMenu::draw ()
	{
		if ( menu_levels ) // others active menus
			{
				layout -> draw ( levels );
			}
		else if ( menu_options )
			layout -> draw ( options );
		else 
			{
				layout -> draw ( menu );
			}
	}
void CStateMenu::CreateMainMenu()
	{
		safe_delete ( menu );

		menu = new CMenu ( 1, 1, layout -> menu -> get_width () - 2, layout -> menu -> get_height () - 2);

		CMenuItem * item_ptr;
		item_ptr = new CMenuItem ( "Arcade Mode", START_GAME);
		menu -> add ( item_ptr );

		item_ptr = new CMenuItem ( "Choose Level", CHOOSE_LEVEL);
		menu -> add ( item_ptr );

		
		menu -> add ( NULL );

		item_ptr = new CMenuItem ( "Set Difficulty", OPTIONS);
		menu -> add ( item_ptr );


		item_ptr = new CMenuItem ( "About Game", ABOUT);
		menu -> add ( item_ptr );

		menu -> add ( NULL );

		item_ptr = new CMenuItem ( "Exit Game", EXIT_GAME);
		menu -> add ( item_ptr );


	}
void CStateMenu::DrawAboutMenu ()
	{
		std::vector<std::string> * v = new  std::vector<std::string> {   "Classic PACMAN game in terminal.",
										 "Written in C++ using ncurses as",
										 "a semester project in PA2.", "",
										 "Jan Sokol 2015" };
		CDialog::show ( *v, "About Game" ); 
		delete v;
	}
void CStateMenu::CreateLevelsMenu ()
	{
		safe_delete ( levels );
		levels = new CMenu ( 1, 1, layout -> menu -> get_width () - 2, layout -> menu -> get_height () - 2 );

		CMenuItem * item_ptr;
		

		std::vector<std::string> level_names = CBoardUtils::list_files ( "pacmap" );

		for (int i = 0; i < std::min ( 18, (int) level_names . size () ); ++i) //  
		{
			item_ptr = new CMenuItem ( level_names [i], i);
			levels -> add ( item_ptr );
		}

		levels -> add_blank ();

		item_ptr = new CMenuItem ( "Back", BACK);
		levels -> add ( item_ptr );
	}
void CStateMenu::CreateOptionsMenu ()
	{
		safe_delete ( options );

		options = new CMenu ( 1, 1, layout -> menu -> get_width () - 2, layout -> menu -> get_height () - 2 );

		CMenuItem * item_ptr;
		item_ptr = new CMenuItemOption ( "Easy", EASY, difficulty);
		options -> add ( item_ptr );

		item_ptr = new CMenuItemOption ( "Medium", MEDIUM, difficulty);
		options -> add ( item_ptr );


		item_ptr = new CMenuItemOption ( "Hard", HARD, difficulty);
		options -> add ( item_ptr );

		options -> add ( NULL );

		item_ptr = new CMenuItem ( "Back", BACK);
		options -> add ( item_ptr );

		
	}
