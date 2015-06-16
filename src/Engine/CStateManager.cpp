#include <Engine/CStateManager.h>
#include <Engine/CTime.h>
#include <Engine/CInputManager.h>
#include <stdlib.h>

template<typename T> void safe_delete(T*& a) 
	{
	  delete a;
	  a = NULL;
	}

CStateManager::CStateManager ():
	current_state ( NULL )
	{

	}
CStateManager::~CStateManager()
	{
		if ( current_state) current_state -> unload ();
		safe_delete ( current_state );
	}
void CStateManager::change ( CState * new_state )
	{
		throw CStateManagerChangeExeption (new_state);
	}
void CStateManager::quit ()
	{
		throw CStateManagerQuitExeption();
	}
void CStateManager::run ( CState * init_state )
	{
		if ( ! init_state)
			throw "no init state";
		current_state = init_state;
		current_state -> load ();

		while ( true )
			{
				try 
					{
						CInputManager::update ();
						current_state -> update ();

						if ( current_state) current_state -> draw ();

						CTime::delay_ms (100);
					}
				catch ( CStateManagerChangeExeption & e )
					{
						current_state -> unload ();
						safe_delete ( current_state );
						current_state = e.new_state;
						current_state -> load ();
					}
				catch ( CStateManagerQuitExeption & e)
					{
						current_state -> unload ();
						safe_delete ( current_state );
						break;
					}
			}
	}
