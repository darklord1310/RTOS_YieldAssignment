#include "LEDsStateMachine.h"


/*
 *	Describe blinking of LEDs independently
 *
 *	LED3 blinks at 240ms
 *	LED4 blinks at 1 s
 *
 */
void SD_LED3(State *state,int BlinkRate)
{
	static uint32_t previousTime = 0;
	static int here = 0;

	switch(*state)
	{
		case initial: *state = ON;
					  break;

		case ON : turnOnLED3();
				  if( getCurrentTime() - previousTime == BlinkRate )
				  {
					 previousTime = getCurrentTime();
					 *state = OFF;
				   }
				   break;

		case OFF : turnOffLED3();
				   if( getCurrentTime() - previousTime == BlinkRate)
				   {
						previousTime = getCurrentTime();
						*state = ON;
				   }
				  break;
	}
}




/*
 *	Describe blinking of LEDs independently
 *
 *	LED3 blinks at 240ms
 *	LED4 blinks at 1 s
 *
 *	The above case is by default, but when user button is pressed
 *	Then,
 *			LED3 blink rate remains same
 *			LED4 blinks at 50ms which is faster than LED3
 *
 */
void SD_LED4(State *state,int *BlinkRate)
{
	static uint32_t previousTime = 0;

	switch(*state)
	{
		case initial: *state = CheckButton;
					  break;

		case CheckButton : if( HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) )
			                   *BlinkRate = 50;
						   else
							   *BlinkRate = LED4blinkRate;
			               *state = OFF;
						   break;

		case OFF : turnOffLED4();
			       if( getCurrentTime() - previousTime == *BlinkRate )
				   {
					 previousTime = getCurrentTime();
					 *state = ON;
				   }
				   break;

		case ON : turnOnLED4();
				  if( getCurrentTime() - previousTime == *BlinkRate)
				  {
					previousTime = getCurrentTime();
					*state = CheckButton;
				  }
				  break;
	}
}



/*
 *  LED5 will blinks 5 times when user button is press
 *  Even if user hold the button, it will still blinks 5 times only
 *  After release and press again, then will only blinks for another 5 times
 *
 */
void SD_LED5(State *state,int BlinkRate)
{
	static uint32_t previousTime = 0;
	static int count = 0;

	switch(*state)
	{
		case initial: *state = CheckButton;
					  break;

		case CheckButton : if( HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) )
					            *state = ON;
						   break;

		case ON : turnOnLED5();
				   if( getCurrentTime() - previousTime == BlinkRate )
				   {
					 previousTime = getCurrentTime();
					 *state = OFF;
				   }
				   break;

		case OFF : turnOffLED5();
				  if( getCurrentTime() - previousTime == BlinkRate)
				  {
					previousTime = getCurrentTime();
					*state = CheckCount;
					count++;
				  }
				  break;
		case CheckCount : if(count < 5)
							 *state = ON;
						  else
							  *state = isButtonHold;
						  break;

		case isButtonHold : if( !( HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) ) )
							{
								  *state = CheckButton;
								  count = 0;
							}
							else
								 *state = isButtonHold;
							break;
	}
}
