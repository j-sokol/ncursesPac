#include <Engine/CTime.h>
#include <ctime>        // time()
#include <unistd.h> 	// usleep ()


void CTime::delay_ms(int delay)
	{
		usleep((useconds_t)delay * 100);
	}