/*




*/
#include "Timer.h"


using HiResClock = std::chrono::high_resolution_clock;




Timer::Timer()
	: is_started(false)
{

}



void Timer::startTimer()
{
	if(is_started)
	{
		return;
	}
	else
	{
		start_time = HiResClock::now();
		is_started = true;
	}
}



void Timer::stopTimer()
{
	fin_time = HiResClock::now();
	is_started = false;
	updateDeltaTime();
}



void Timer::updateDeltaTime()
{
	if (!is_started)
	{		
		dt = std::chrono::duration<float>(fin_time - start_time).count() / 0.1;
	}
}



const float Timer::getTime() const
{
	return dt;
}
