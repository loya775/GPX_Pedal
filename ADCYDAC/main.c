/*
 * Copyright (c) 2017, NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    ADC_FOR_GUITAR.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "MK64F12.h"
#include "ADCDriver.h"
#include "DataTypeDefinitions.h"
#include "FlexTimer.h"
#include "NVIC.h"
#include "DAC.h"
#define SC1FLAG 0x1F
#define SC3FlAG 0x07
	const FTM_ConfigType FTM_Config={
			FTM_0,
			FTM_OutputC_Toogle
	};

	const ADC_ConfigType ADC  = {
			0,
			ADC0Type,
			NORMAL_POWER,
			RATIO1,
			SHORT_SAMPLE,
			CONV12,
			BUSCLK
	};

int main(void) {
	uint16 Sample;
	uint8 SC1cfg = SC1FLAG;
	uint8 SC2cfg = 0;
	uint8 SC3cfg = SC3FlAG;
	ADC_initialize(&ADC,SC1cfg,SC2cfg,SC3cfg);
	FlexTimer_Init(&FTM_Config);
    SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA|GPIO_CLOCK_GATING_PORTC;
	PORTC->PCR[1]   = PORT_PCR_MUX(0x4);
	NVIC_enableInterruptAndPriotity(FTM0_IRQ, PRIORITY_1);
	EnableInterrupts;
	 DAC0_clockGating();
	 DAC0_init();
    while(TRUE)
    {
    	if(getFlexFlag())
    	{
    		Sample = StartConversion(&ADC);
    		clearFlexFlag();
    		DAC0_write(Sample);
    	}
    }
    return 0 ;
}
