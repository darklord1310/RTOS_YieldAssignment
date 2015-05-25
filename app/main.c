#include "ConfigureLED.h"
#include "LEDsStateMachine.h"


typedef struct
{
	State state;
}TaskBlock;


#define yield(x) (x)->state = __LINE__; break; case __LINE__ : ;
#define startTask(x) switch( (x)->state) { case 0: ;
#define initTaskBlock(x) (x)->state = 0;
#define endTask(x) } ;


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

void testingSwitchCase(TaskBlock *tb)
{
	static int here = 0;

	startTask(tb);

	here = 0;
	yield(tb);
	here = 1;
	yield(tb);
	here = 2;
	yield(tb);
	here = 3;
	yield(tb);

	endTask(tb);
}



int main(void)
{
	initLED();
	State state_LED3 = initial;  //initialize state for LED3
	State state_LED4 = initial;  //initialize state for LED4
	State state_LED5 = initial;  //initialize state for LED5

	int *blinkRate = LED4blinkRate;

	while(1)
	{
		//SD_LED3(&state_LED3 , LED3blinkRate);	// state machine function for LED3
		//SD_LED4(&state_LED4 , &blinkRate);   	// state machine function for LED4
		SD_LED5(&state_LED5 , LED5blinkRate);   // state machine function for LED5
	}

	return 0;
}
