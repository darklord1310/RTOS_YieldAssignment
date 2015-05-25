#include "ConfigureLED.h"

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