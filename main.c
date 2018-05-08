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
 * @file    MenuProyect.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "DataTypeDefinitions.h"
#include "MK64F12.h"
#include "DAC.h"
#include "ADCDriver.h"
#include "FlexTimer.h"
#include "MCG.h"
#include "NVIC.h"
#include "Button_init.h"
#include "SPI.h"
#include "UART.h"
#include "S25FLXXX.h"
#include "WriteConsole.h"
#include "FunctionRotate.h"

#define SC1FLAG 0x1F
#define SC3FlAG 0x07

#define SC1FLAG 0x1F
#define SC3FlAG 0x07
#define SPI_CHANNEL		SPI_0
#define SPI_PORT		GPIO_D
#define SPI_MOSI_BIT	BIT2
#define SPI_MISO_BIT 	BIT3
#define SPI_CLK			BIT1
#define SPI_PIN_CONFIG  GPIO_MUX2|GPIO_DSE

#define CLK_FREQ_HZ 50000000  /* CLKIN0 frequency */
#define SLOW_IRC_FREQ 32768	/*This is the approximate value for the slow irc*/
#define FAST_IRC_FREQ 4000000 /*This is the approximate value for the fast irc*/
#define EXTERNAL_CLOCK 0 /*It defines an external clock*/
#define PLL_ENABLE 1 /**PLL is enabled*/
#define PLL_DISABLE 0 /**PLL is disabled*/
#define CRYSTAL_OSC 1  /*It defines an crystal oscillator*/
#define LOW_POWER 0     /* Set the oscillator for low power mode */
#define SLOW_IRC 0 		/* Set the slow IRC */
#define CLK0_TYPE 0     /* Crystal or canned oscillator clock input */
#define PLL0_PRDIV 25    /* PLL predivider value */
#define PLL0_VDIV 30    /* PLL multiplier value*/

#define Clock 21000000

#define SPI_CS_PORT		GPIO_D
#define SPI_CS_BIT		BIT0
#define SPI_CS_CONFIG	GPIO_MUX1|GPIO_DSE

/*Beginning of the UID memory*/
#define BEGINNING_OF_FIRST_SECTOR 0x000000
/**End of the first sector of the memory*/
#define END_OF_FIRST_SECTOR   0x000FFF


const SPI_ConfigType SPI_ConfigMemory={
	SPI_DISABLE_FIFO,
	SPI_LOW_POLARITY,
	SPI_LOW_PHASE,
	SPI_MSB,
	SPI_CHANNEL,
	SPI_MASTER,
	SPI_BAUD_RATE_2,// It represent the SPI pre-scaler
	SPI_DOUBLE_BAUD_RATE,// It doubles the baud rate
	SPI_FSIZE_8,
	SPI_CS_HIGH,
	{SPI_PORT,SPI_MOSI_BIT,SPI_MISO_BIT,
	SPI_CLK,SPI_CS_BIT,
	SPI_PIN_CONFIG,SPI_CS_CONFIG}};
		/**This is the bit that is used for the chip select in the SPI*/

MemoryPortType SPIChannelForMemory = {
	SPI_CHANNEL,
	SPI_CS_PORT,
	SPI_CS_BIT,
	};



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

int main(void)
{
	S25FLXXX_MemoryAddressType S25FLXXX_MemoryAddress = {0};
	uint8 SC1cfg = SC1FLAG;
	uint8 SC2cfg = 0;
	uint8 SC3cfg = SC3FlAG;
	uint8 SelectFunction;
	uint8 FlagForFunction = FALSE;
	uint8 Probe;
	uint8 Probe2;
	uint8 Probe3;
	S25FLXXX_MemoryAddress.address = 0;
	GPIO_Initialize();
	DAC0_clockGating();
	DAC0_init();
	ADC_initialize(&ADC,SC1cfg,SC2cfg,SC3cfg);
	FlexTimer_Init(&FTM_Config);
	UART_init (UART_0,  Clock, BD_115200);
	UART0_interruptEnable(UART_0);
	NVIC_enableInterruptAndPriotity(PORTC_IRQ, PRIORITY_5);
	NVIC_enableInterruptAndPriotity(FTM0_IRQ, PRIORITY_1);
	NVIC_enableInterruptAndPriotity(UART0_IRQ, PRIORITY_10);
	EnableInterrupts;
	SPI_init(&SPI_ConfigMemory);
	S25FLXXX_MemoryAddress.address = 0x04;
	Probe = S25FLXXX_readByte(&S25FLXXX_MemoryAddress,&SPIChannelForMemory);
	MMU_waitingFunction();
	S25FLXXX_MemoryAddress.address = 0x05;
	Probe2 = S25FLXXX_readByte(&S25FLXXX_MemoryAddress,&SPIChannelForMemory);
	S25FLXXX_MemoryAddress.address = 0x1FFFF3;
	Probe3 = S25FLXXX_readByte(&S25FLXXX_MemoryAddress,&SPIChannelForMemory);
	S25FLXXX_MemoryAddress.address = 0x04;
	S25FLXXX_writeByte(0x60,0x23,&S25FLXXX_MemoryAddress,&SPIChannelForMemory);
	MMU_waitingFunction();
	S25FLXXX_MemoryAddress.address = 0x04;
	Probe = S25FLXXX_readByte(&S25FLXXX_MemoryAddress,&SPIChannelForMemory);
	MMU_waitingFunction();
	S25FLXXX_MemoryAddress.address = 0x05;
	Probe2 = S25FLXXX_readByte(&S25FLXXX_MemoryAddress,&SPIChannelForMemory);
	S25FLXXX_MemoryAddress.address = 0x1FFFF3;
	Probe3 = S25FLXXX_readByte(&S25FLXXX_MemoryAddress,&SPIChannelForMemory);
	MMU_waitingFunction();
	FirstMenu();
    while(TRUE)
    {

    		if(GPIO_readPIN(GPIO_C, BIT5))
    		{
    			FlagForFunction = TRUE;
    			SelectFunction = 0;
    			delay(15000);
    		}
    		if(GPIO_readPIN(GPIO_C, BIT7))
    		{
    			SelectFunction = 1;
    			FlagForFunction = TRUE;
    			delay(15000);
    		}
    		if(GPIO_readPIN(GPIO_C, BIT0))
    		{
    			FlagForFunction = TRUE;
    			SelectFunction = 2;
    			delay(15000);
    		}


    	if(FlagForFunction == TRUE)
    	{
    		choose_function(SelectFunction, S25FLXXX_MemoryAddress, SPIChannelForMemory, ADC);
    		FlagForFunction = FALSE;
    	}


    }

    LooperActivated(SPIChannelForMemory);
    Dac_Working(ADC);
    return 0 ;
}
