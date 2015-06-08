#include "LEDBlinking.h"



/*
 *	Describe blinking of LED 3
 *
 *	LED3 blinks at 1s
 *
 */
void LED3(TaskBlock *tb )
{
	startTask(tb);
	while(1)
	{
		turnOffLED3();

		while( !timer1() ){
			yield(tb);
		}
		turnOnLED3();

		while( !timer1() ){
			yield(tb);
		}
	}
	endTask(tb);
}


/*
 *	Describe blinking of LED 4
 *
 *	LED4 blinks at 1s
 *
 */
void LED4(TaskBlock *tb)
{
	startTask(tb);

	while(1)
	{
		turnOnLED4();

		while( !timer2() ){
			yield(tb);
		}
		turnOffLED4();

		while( !timer2() ){
			yield(tb);
		}
	}
	endTask(tb);
}



void blinkFiveTimes(TaskBlock *tb)
{
	static int i = 0;
	startTask(tb);

	while(1)
	{
		while( !( HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) ) ){
			yield(tb);
		}

			while( i < 5)
			{
				turnOnLED5();
				while( !timer3() ){
					yield(tb);
				}

				turnOffLED5();

				while( !timer3()  ){
					yield(tb);
				}
				i++;
			}
			i = 0;

			while( (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) ) ){
				yield(tb);
		}
	}
	endTask(tb);

}
