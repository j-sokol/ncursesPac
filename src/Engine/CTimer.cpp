#include <Engine/CTimer.h>

#include <iostream>	

#define USEC_IN_SEC 1000000
static suseconds_t get_ticks ()
	{
		struct timeval tmp;
		gettimeofday ( & tmp, NULL );
		return tmp . tv_usec + (tmp.tv_sec * USEC_IN_SEC);
	}
CTimer::CTimer():
	start_m (0),
	stop_m (0),
	pause_m (0),
	running ( false ),
	paused ( false )
	{

	}
CTimer::~CTimer()
	{

	}
void CTimer::start ()
	{
		start_m = get_ticks ();
		stop_m = 0;
		pause_m = 0;
		running = true;
		paused = false;
	}
void CTimer::stop ()
	{
		if ( paused || ! running )
			return;
		pause_m = get_ticks ( ) - start_m;
		running = false;
		paused = true;
	}
void CTimer::pause ()
	{
		if ( paused || ! running )
			return;
		pause_m = get_ticks ( ) - start_m;
		running = false;
		paused = true;
	}
void CTimer::unpause ()
	{
		if ( ! paused || running )
			return;
		start_m = get_ticks ( ) - pause_m;
		running = true;
		paused = false;
	}
bool CTimer::is_running () const
	{
		return running;
	}
bool CTimer::is_paused () const
	{
		return paused;
	}

suseconds_t CTimer::d_us ()
	{
		if (  is_running ())
			return get_ticks () - start_m;
		if ( is_paused ())
			return pause_m;
		return 0;   // never goes here
	}
suseconds_t CTimer::d_ms ()
	{
		return d_us () / 1000;
	}
suseconds_t CTimer::d_s ()
	{
		return d_us () / 1000000;
	}
