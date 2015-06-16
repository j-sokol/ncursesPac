#ifndef CSTATE_H_DEFINED
#define CSTATE_H_DEFINED

/// Abstract class definition of a game state.
class CState
	{
	public:
		CState() {}
		virtual ~CState() {}

		/// Every state initializes it's resources here.
		virtual void load () = 0;

		/// Every state destroys it's resources here.
		virtual void unload () = 0;

		/// Function called every game frame, states calculate
		/// every change that could happen.
		///
		/// CStateManager checks if something happened here and
		/// has to change state to different one.
		virtual void update () = 0;

		/// Function called every game frame, states draw its
		/// content on screen here.
		virtual void draw () = 0;
		
	};

	
#endif //CSTATE_H_DEFINED
