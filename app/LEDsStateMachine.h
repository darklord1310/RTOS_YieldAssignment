#ifndef LEDsStateMachine_H
#define LEDsStateMachine_H

#include "ConfigureLED.h"

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
#define LED5blinkRate	1000
#define LED6blinkRate   35


typedef enum { initial, ON, OFF, CheckButton, CheckCount, isButtonHold} State;

typedef enum { LED3, LED4, LED5 } LEDSelection;


void SD_LED3(State *state,int BlinkRate);
void SD_LED4(State *state,int *BlinkRate);
void SD_LED5(State *state,int BlinkRate);



#endif // LEDsStateMachine_H
