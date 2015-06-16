#ifndef CMENUITEM_H_DEFINED
#define CMENUITEM_H_DEFINED

#include <Engine/CWindow.h>

#include <string>

/// Simplest type of menu item, only with `label` and `id`.
class CMenuItem
	{
	public:
		/// Enumeration of posible menu item types.	
		enum ItemType
		{
			ITEM, 
			OPTION
		};

		/// Constructor that creates menu item with
		/// user-defined `id` number and label.
		///
		/// @note not known results if more items
		/// in menu have same `is`s.
		CMenuItem ( std::string label, int id );

		CMenuItem () {};
		virtual ~CMenuItem();

		/// Draws item on window `wind` at `x`, `y`
		/// with `width`.
		///
		/// if this is current item, `highlight` is true.
		///
		/// Height of item is always 1.
		virtual void draw ( CWindow * wind, int x, int y,
							int width, bool highlight = false);

		/// Handles input for menu, same as in 
		/// global CInputManager
		/// 
		/// Inherited classes might have this class implemented 
		/// in different way.
		virtual void HandleInput ();


		/// Type of menu item.
		ItemType type;

		/// Text that will be shown on screen.
		std::string label;

		/// ID to identify this item.
		unsigned int id;	
	};

	
#endif //CMENUITEM_H_DEFINED
