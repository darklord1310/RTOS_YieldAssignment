#include "ConfigureLEDAndPushButton.h"
#include "LEDBlinking.h"
#include "TimerAndDelay.h"
#include "LEDBlinkRate.h"
#include "Yield.h"




int main(void)
{
	TaskBlock tbLED3, tbLED4, tbLED5, tbLED6, tbFiveTimes;
	initTaskBlock(&tbLED3);													//init TaskBlock LED3
	initTaskBlock(&tbLED4);													//init TaskBlock LED4
	initTaskBlock(&tbLED5);													//init TaskBlock LED5
	initTaskBlock(&tbLED6);													//init TaskBlock LED6
	initTaskBlock(&tbFiveTimes);											//init TaskBlock FiveTimes
	initLED();																//init LED and pushButton

	while(1)
	{

		blinkFiveTimes(&tbFiveTimes);
		LED3(&tbLED3);
		LED4(&tbLED4);
	}
	return 0;
}
