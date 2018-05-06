/*
 * DAC.c
 *
 *  Created on: Feb 24, 2018
 *      Author: Raymundo
 */

#include "DAC.h"
#include "MK64F12.h"

#define DAC_0_CG 0x1000
#define DAC_writeHighMask 0x0F00
#define DAC_writeLowMask  0x00FF
#define DAC_writeOffset 8


void DAC0_clockGating(void)
{
	SIM->SCGC2 |= DAC_0_CG;
}




void DAC0_init(void)
{
	DAC0->C0 &= DAC_C0_DACEN_MASK;			//DAC_Enable
	DAC0->C0 |= ~(DAC_C0_DACRFS_MASK);		//DAC_ReferenceVoltage
	DAC0->C0 |= ~(DAC_C0_DACTRGSEL_MASK);	//DAC_TriggerSelect
	DAC0->C0 |= ~(DAC_C0_DACSWTRG_MASK);	//DAC_SoftwareTrigger
	DAC0->C0 |= ~(DAC_C0_LPEN_MASK);		//DAC_PowerControl
	DAC0->C0 |= ~(DAC_C0_DACBWIEN_MASK);	//DAC_WatermarkIE
	DAC0->C0 |= ~(DAC_C0_DACBTIEN_MASK);	//DAC_BufferReadPointerTopFlagIE
	DAC0->C0 |= ~(DAC_C0_DACBBIEN_MASK);	//DAC_BufferReadPointerBotFlagIE

}


void DAC0_write(uint16 data)
{
	DAC0->DAT->DATH = (data & DAC_writeHighMask) >> DAC_writeOffset;
	DAC0->DAT->DATL = (data & DAC_writeLowMask);
}

