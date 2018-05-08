/*
 * Button_Init.c
 *
 *  Created on: May 7, 2018
 *      Author: Jorge Loya
 */
#include "Button_Init.h"
#include "GPIO.h"
void GPIO_Initialize(void)
{
	GPIO_pinControlRegisterType pinControlRegisterInterrupt = GPIO_MUX1|INTR_FALLING_EDGE;
	GPIO_pinControlRegisterType MUXALT = PORT_PCR_MUX(3);
	GPIO_clockGating(GPIO_C);
	GPIO_clockGating(GPIO_B);
	GPIO_pinControlRegister(GPIO_C,BIT5, &pinControlRegisterInterrupt);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_INPUT, BIT5);
	GPIO_pinControlRegister(GPIO_C,BIT7, &pinControlRegisterInterrupt);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_INPUT, BIT7);
	GPIO_pinControlRegister(GPIO_C,BIT0, &pinControlRegisterInterrupt);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_INPUT, BIT0);
	GPIO_pinControlRegister(GPIO_C,BIT9, &pinControlRegisterInterrupt);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_INPUT, BIT9);
	GPIO_pinControlRegister(GPIO_C,BIT8, &pinControlRegisterInterrupt);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_INPUT, BIT8);
	GPIO_pinControlRegister(GPIO_C,BIT1, &pinControlRegisterInterrupt);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_INPUT, BIT1);
	GPIO_pinControlRegister(GPIO_B,BIT19, &pinControlRegisterInterrupt);
	GPIO_dataDirectionPIN(GPIO_B, GPIO_INPUT, BIT19);
	GPIO_pinControlRegister(GPIO_B,BIT18, &pinControlRegisterInterrupt);
	GPIO_dataDirectionPIN(GPIO_B, GPIO_INPUT, BIT18);
	GPIO_pinControlRegister(GPIO_B,BIT16, &MUXALT);
	GPIO_pinControlRegister(GPIO_B,BIT17, &MUXALT);
}
