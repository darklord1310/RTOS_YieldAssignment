#include "TimerAndDelay.h"



uint32_t getCurrentTime()
{
	static uint32_t counter = 0 ;
	static uint32_t currentTime = 0 ;

	if (counter++ >= 100)
	{
		counter = 0 ;
		currentTime ++ ;
	}

	return currentTime ;
}


void delay(uint32_t delayCycle)
{

	static uint32_t previousTime = 0 ;

	while ( (getCurrentTime() - previousTime) < delayCycle)
		previousTime = getCurrentTime();
}

/*
int isTimerExpires(int timeConstraint, int LEDSelection)
{
	static uint32_t previousTime[4] = {0,0,0,0};

	if( getCurrentTime() - previousTime[LEDSelection] == timeConstraint)
	{
		previousTime[LEDSelection] = getCurrentTime();
		return 1;
	}
	else
		return 0;
}
*/

int isTimerExpires(int timeConstraint)
{
	static uint32_t previousTime = 0;

	if( getCurrentTime() - previousTime == timeConstraint)
	{
		previousTime = getCurrentTime();
		return 1;
	}
	else
		return 0;
}

int timer1()
{
	static uint32_t previousTime = 0;

	if( getCurrentTime() - previousTime == 1000)
	{
		previousTime = getCurrentTime();
		return 1;
	}
	else
		return 0;
}


int timer2()
{
	static uint32_t previousTime = 0;

	if( getCurrentTime() - previousTime == 1000)
	{
		previousTime = getCurrentTime();
		return 1;
	}
	else
		return 0;
}


int timer3()
{
	static uint32_t previousTime = 0;

	if( getCurrentTime() - previousTime == 1000)
	{
		previousTime = getCurrentTime();
		return 1;
	}
	else
		return 0;
}
