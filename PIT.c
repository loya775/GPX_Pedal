/*
 * PIT.c
 *
 *  Created on: Feb 21, 2018
 *      Author: Raymundo Garza
 */
#include "MK64F12.h"
#include "PIT.h"

void PIT0_DriverIRQHandler(void)
{
	PIT->CHANNEL[0].TCTRL &= ~(PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK);
}

void PIT1_DriverIRQHandler(void)
{
	PIT->CHANNEL[1].TCTRL &= ~(PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK);
}

void PIT2_DriverIRQHandler(void)
{
	PIT->CHANNEL[2].TCTRL &= ~(PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK);
}

void PIT3_DriverIRQHandler(void)
{
	PIT->CHANNEL[3].TCTRL &= ~(PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK);
}

void PIT_delay(PIT_Timer_t pitTimer,float systemClock ,float perior)
{
	PIT->MCR &= ~(PIT_MCR_FRZ_SHIFT | PIT_MCR_MDIS_MASK);
	PIT->CHANNEL[pitTimer].LDVAL = (systemClock*perior/2);
	PIT->CHANNEL[pitTimer].TCTRL &=  ~(PIT_TCTRL_CHN_MASK);
	PIT->CHANNEL[pitTimer].TCTRL |= (PIT_TCTRL_TIE_MASK |PIT_TCTRL_TEN_MASK) ;
}

void PIT_clockGating(void)
{
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK ;
}


uint32 PIT_interruptFlagStatus(PIT_Timer_t pitTimer)
{
	return(PIT->CHANNEL[pitTimer].TFLG & PIT_MCR_FRZ_MASK);
}

uint8 PIT_getIntrStutus(PIT_Timer_t pitTimer)
{
	return(PIT->CHANNEL[pitTimer].TFLG & PIT_MCR_FRZ_MASK);
}

void PIT_clear(PIT_Timer_t pitTimer)
{
	PIT->CHANNEL[pitTimer].TFLG |= (PIT_MCR_FRZ_MASK);
}
