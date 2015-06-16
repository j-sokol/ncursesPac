#ifndef CTIMER_H_DEFINED
#define CTIMER_H_DEFINED

#include <sys/time.h>


/// Timer to measure game ticks.
class CTimer
	{
	public:
		CTimer();
		~CTimer();

		/// Sets starting point for timer.
		/// If called multiple times, will
		/// restart.
		void start ();

		/// Stops the timer.
		void stop ();

		/// Temporarily stops the timer.
		void pause ();

		/// If timer was unpaused, restarts it.
		void unpause ();

		/// Tells if timer is running.
		bool is_running () const;

		/// Tells if times is paused.
		bool is_paused () const;


		/// Returns difference time in microseconds.
		suseconds_t d_us ();

		/// Returns difference time in miliseconds.
		suseconds_t d_ms ();

		/// Returns difference time in seconds.
		suseconds_t d_s ();

	protected:
		/// Start mark
		suseconds_t start_m;

		/// Stop mark
		suseconds_t stop_m;

		/// Pause mark
		suseconds_t pause_m;

		bool running;
		bool paused;
		
	};

	
#endif //CTIMER_H_DEFINED
