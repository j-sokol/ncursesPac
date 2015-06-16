#ifndef CGAME_H_DEFINED
#define CGAME_H_DEFINED

#include <Game/CGhostManager.h>
#include <Game/CGameLayout.h>
#include <Game/CBoard.h>
#include <Game/CPlayer.h>
#include <Engine/CWindow.h>
#include <Engine/CTimer.h>
#include <Engine/CMenu.h>

class CGameLayout;

class CGame
	{
		

	public:
		CGame ();
		CGame ( std::string map, int difficulty );
		virtual ~CGame();

		/// Starts a game, loading `map` from parameter.
		///
		/// loads map from file, @see CBoardUtils::load_file
		void start ( );

		/// Restarts game, loads only new mosters, leaves same 
		/// score and same board with eaten dots.
		void restart ();
		void update ();
		void draw ();

		/// Handles input for game.
		void handle_input ();

		/// Returns time player / monsters need to wait until
		/// next update. `speed` is stage of game player is in.
		int get_delay ( int speed = 1) const;

		/// Checks if in last update was food eaten, if so,
		/// adds score to `points`
		bool is_food_eaten ();

		/// Checks if in last update was star eaten, if so,
		/// adds score to `points` and sets ghosts to 
		/// frightened mode.
		bool is_star_eaten ();
		bool is_paused () const;
		bool is_over () const;

		/// Tells if will exit game straight away.
		bool will_exit () const;

		/// Tells if will go to main menu
		/// next update.
		bool will_go_to_menu () const;

		/// Loads highscore from file named
		/// `map`.pacmap in ./examples/scores.
		void load_high_score ();

		/// Saves highscore to file.
		void save_high_score ();



		CBoard * board;
		CPlayer * player;
		CGameLayout * layout;
		CGhostManager * ghost;

		/// Menu that is shown when player presses 'p'
		CMenu * pause_menu;

		/// High score for current level.
		int high_score;

		/// Current score for current level.
		int points;
		int lives;

	protected:
		/// Timer that tells when to move player.
		CTimer timer_player;

		/// Timer that tells when to move and update monsters.
		CTimer timer_ghost;

		/// Shows how long is player playing the game.
		CTimer timer;

		/// Tells if game is over.
		bool game_over;
		bool show_pause_menu;
		bool paused;
		bool bool_exit;
		bool bool_menu;

		/// Difficulty of game (EASY, MEDIUM, HARD).
		int difficulty;

		/// name of level, same as name of file.
		std::string map;

		/// Tells what stage player is in.
		int stage;


	};


#endif //CGAME_H_DEFINED
