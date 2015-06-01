#ifndef RunningLED_H
#define RunningLED_H

#include "stm32f4xx_hal.h"
#include "State.h"
#include "Yield.h"
#include "TimerAndDelay.h"

#define turnOnLED3() HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
#define turnOffLED3() HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);

#define turnOnLED4() HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
#define turnOffLED4() HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);

#define turnOnLED5() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
#define turnOffLED5() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

#define turnOnLED6() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
#define turnOffLED6() HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);

void LED3(TaskBlock *tb);
void LED4(TaskBlock *tb);
void LED5(TaskBlock *tb);
void LED6(TaskBlock *tb);

#endif // RunningLED_H
