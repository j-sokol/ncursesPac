#ifndef CMENU_H_DEFINED
#define CMENU_H_DEFINED

#include <Engine/CWindow.h>
#include <Engine/CMenuItem.h>
#include <Engine/CMenuItemOption.h>

#include <vector>
#include <string>

/// List of easily to remember menu ids instead
/// of raw numbers.
enum MenuIDs
	{
		START_GAME = 420,
		CHOOSE_LEVEL,
		OPTIONS,
		ABOUT,
		CREDITS,
		EXIT_GAME,
		END_GAME,
		HIGH_SCORES,
		BACK,

		RESUME,
		RESTART,
		MAIN_MENU
	};

/// List of selectable options.
class CMenu
	{
	public:

		/// Constructor that creates menu at #x, #y with
		/// #width and #height.
		CMenu ( int x, int y, int width, int height );
		virtual ~CMenu();

		///  Adds item to menu.
		void add ( CMenuItem * item );

		///  Adds blank item to menu.
		void add_blank ();

		/// Removes specific item with #id from menu. 
		void RemoveByID ( unsigned int id );

		/// draws whole menu on #window.	
		void draw ( CWindow * window );

		/// Handles input for menu, same as in 
		/// global CInputManager
		void HandleInput ();

		/// Selects next in menu. 
		void GoNextItem ();

		/// Selects previous in menu. 
		void GoPrevItem ();

		/// Selects last in menu. 
		void GoLastItem ();

		/// Selects first in menu. 
		void GoFirstItem ();

		/// Returns true if user selected an item that 
		/// will quit menu.
		bool WillExit () const;

		/// Returns string - #label of current selected
		/// item in menu.
		std::string CurrentLabel ();

		/// Returns #id of current selected item in menu.
		int CurrentID ();

		/// Makes menu to be selectable again.	
		void reset ();


		/// std::vector container of all items in menu.
		std::vector < CMenuItem *> items;

		/// pointer to current item in menu.
		CMenuItem * current;

	protected:

		/// Index of currently selected item.
		unsigned int cur_index;

		int x;
		int y;
		int width;
		int height;
		
		/// Is true if will exit from menu.
		bool will_exit;
		/// Is true if user selected an item.
		bool selected;

		/// Pointer to selected item.
		CMenuItem * selected_item;

		
	};
	
#endif //CMENU_H_DEFINED
