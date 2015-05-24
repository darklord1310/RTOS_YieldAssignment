#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

#define turnOnLED3() HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
#define turnOffLED3() HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);

#define turnOnLED4() HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
#define turnOffLED4() HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);

#define turnOnLED5() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
#define turnOffLED5() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

#define turnOnLED6() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
#define turnOffLED6() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);



#define LED3blinkRate	120
#define LED4blinkRate   1000
#define LED5blinkRate   80
#define LED6blinkRate   35


typedef enum { initial, ON, OFF, CheckButton, CheckCount} State;

typedef enum { LED3, LED4, LED5 , LED6} LEDSelection;

void initLED()	// Initialization for LEDs
{
	GPIO_InitTypeDef GpioInfo_PortG ;
	GPIO_InitTypeDef GpioInfo_PortB ;
	GPIO_InitTypeDef GpioInfo_PortC ;
	GPIO_InitTypeDef GpioInfo_PortA ;

	__GPIOG_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();
	__GPIOA_CLK_ENABLE();


	// Init for the Port G
	GpioInfo_PortG.Mode = GPIO_MODE_OUTPUT_PP ;
	GpioInfo_PortG.Pin = GPIO_PIN_13 | GPIO_PIN_14; // Enable LED3 and LED4
	GpioInfo_PortG.Pull = GPIO_NOPULL ;
	GpioInfo_PortG.Speed = GPIO_SPEED_HIGH ;
	//GpioInfo.Alternate = GPIO_MODE_AF_PP ;

	// Init for the Port B
	GpioInfo_PortB.Mode = GPIO_MODE_OUTPUT_PP ;
	GpioInfo_PortB.Pin = GPIO_PIN_13;				// Enable LED5
	GpioInfo_PortB.Pull = GPIO_NOPULL ;
	GpioInfo_PortB.Speed = GPIO_SPEED_HIGH ;


	// Init for the Port C
	GpioInfo_PortC.Mode = GPIO_MODE_OUTPUT_PP ;
	GpioInfo_PortC.Pin = GPIO_PIN_5; 				// Enable LED6
	GpioInfo_PortC.Pull = GPIO_NOPULL ;
	GpioInfo_PortC.Speed = GPIO_SPEED_HIGH ;

	// Init for the Port A
	GpioInfo_PortA.Mode = GPIO_MODE_INPUT;
	GpioInfo_PortA.Pin = GPIO_PIN_0; 				// Enable User Push Button
	GpioInfo_PortA.Pull = GPIO_NOPULL ;
	GpioInfo_PortA.Speed = GPIO_SPEED_HIGH ;


	//Init LED on PG13 and PG14
	HAL_GPIO_Init(GPIOG,&GpioInfo_PortG);

	//Init LED on PB13
	HAL_GPIO_Init(GPIOB,&GpioInfo_PortB);

	//Init LED on PC5
	HAL_GPIO_Init(GPIOC,&GpioInfo_PortC);

	//Init Push Button on PA0
	HAL_GPIO_Init(GPIOA,&GpioInfo_PortA);
}


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


void SD_LED3(State *state,int BlinkRate)
{
	static uint32_t previousTime = 0;

	switch(*state)
	{
		case initial: *state = ON;
					  break;

		case ON : if( getCurrentTime() - previousTime == BlinkRate )
				   {
					 previousTime = getCurrentTime();
					 turnOnLED3();
					 *state = OFF;
				   }
				   break;

		case OFF : if( getCurrentTime() - previousTime == BlinkRate)
				  {
					previousTime = getCurrentTime();
					turnOffLED3();
					*state = ON;
				  }
				  break;
	}
}



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

		case OFF : if( getCurrentTime() - previousTime == *BlinkRate )
				   {
					 previousTime = getCurrentTime();
					 turnOffLED4();
					 *state = ON;
				   }
				   break;

		case ON : if( getCurrentTime() - previousTime == *BlinkRate)
				  {
					previousTime = getCurrentTime();
					turnOnLED4();
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
					               *state = OFF;
						   break;

		case OFF : if( getCurrentTime() - previousTime == BlinkRate )
				   {
					 previousTime = getCurrentTime();
					 turnOffLED5();
					 *state = ON;
				   }
				   break;

		case ON : if( getCurrentTime() - previousTime == BlinkRate)
				  {
					previousTime = getCurrentTime();
					turnOnLED5();
					*state = CheckCount;
					count++;
				  }
				  break;
		case CheckCount : if(count <= 5)
							 *state = OFF;
						  else
						  {
							  if( !( HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) ) )		//not sure about this line, have to test on board to verify
								  *state = initial;
						  }
	}
}



void SD_LED6(State *state,int BlinkRate )
{
	static uint32_t previousTime = 0;

	switch(*state)
	{
		case initial: *state = ON;
					  break;

		case OFF : if( getCurrentTime() - previousTime == BlinkRate)
				   {
					 previousTime = getCurrentTime();
					 turnOffLED6();
					 *state = ON;
				   }
				   break;

		case ON : if( getCurrentTime() - previousTime == BlinkRate)
				  {
					previousTime = getCurrentTime();
					turnOnLED6();
					*state = OFF;
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
void UMLStateDiagramExmaple()
{

	State state_LED3 = initial;  //initialize state for LED3
	State state_LED4 = initial;  //initialize state for LED4
	State state_LED5 = initial;  //initialize state for LED5
	State state_LED6 = initial;  //initialize state for LED6

	int *blinkRate = LED4blinkRate;

	while(1)
	{
			SD_LED3(&state_LED3 , LED3blinkRate);	// state machine function for LED3
			SD_LED4(&state_LED4 , &blinkRate);   	// state machine function for LED4
			SD_LED5(&state_LED5 , LED5blinkRate);   // state machine function for LED5
			SD_LED6(&state_LED6 , LED6blinkRate);   // state machine function for LED6
	}

}



int main(void)
{
	initLED();


	while(1)
	{
		UMLStateDiagramExmaple();
	}

	return 0;
}
