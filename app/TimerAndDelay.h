#ifndef TimerAndDelay_H
#define TimerAndDelay_H

#include "stm32f4xx_hal.h"
#include "LEDSelection.h"

uint32_t getCurrentTime();
void delay(uint32_t delayCycle);
int isTimerExpires(int timeConstraint);
int timer1();
int timer2();
int timer3();

#endif // TimerAndDelay_H
