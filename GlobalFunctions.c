/*
 * GlobalFunctions.c
 *
 *  Created on: 16/08/2017
 *      Author: jlpe
 */


#include "GlobalFunctions.h"
#include "MK64F12.h"
#include "GPIO.h"
#include "NVIC.h"
#include "PIT.h"
#include "GlobalFunctions.h"
#include "DataTypeDefinitions.h"
#define DELAY .000000000000000000001F
#define SYSTEM_CLOCK 21000000
uint8 pitIntrStatus;
void delay(uint16 delay)
{
	volatile int counter, counter2;

	for(counter2=16; counter2 > 0; counter2--)
	{
		for(counter=delay; counter > 0; counter--);

	}
}

void SpecialDelay()
{
    	pitIntrStatus = PIT_getIntrStutus(PIT_0);
		PIT_delay(PIT_0,(SYSTEM_CLOCK)/2.65,DELAY);
		GPIO_setPIN(GPIO_C, BIT5);
		while(FALSE == pitIntrStatus)
		{
	    	pitIntrStatus = PIT_getIntrStutus(PIT_0);
		}
		PIT_clear(PIT_0);
		PIT_delay(PIT_0,(SYSTEM_CLOCK)/2.65,DELAY);
		GPIO_clearPIN(GPIO_C, BIT5);
		pitIntrStatus = PIT_getIntrStutus(PIT_0);
		while(FALSE == pitIntrStatus)
		{
			pitIntrStatus = PIT_getIntrStutus(PIT_0);
		}
		PIT_clear(PIT_0);
}
