#ifndef CGHOSTMEDIUM_H_DEFINED
#define CGHOSTMEDIUM_H_DEFINED

#include <Game/CPlayer.h>
#include <Game/CGhost.h>
#include <Game/CBoard.h>
#include <Engine/CWindow.h>

/// Ghost that checks if there is player on sight,
/// if so, tries to follow him.
class CGHostMedium : public CGhost
	{
	public:
		CGHostMedium ( int x, int y );
		virtual ~CGHostMedium ();
		
		virtual void draw ( CWindow * window );
		virtual void update ( CBoard * board, CPlayer * player );
		virtual bool player_on_sight ( int player_x, int player_y, CBoard * board, Direction& dir );
	};

	
#endif //CGHOSTMEDIUM_H_DEFINED
