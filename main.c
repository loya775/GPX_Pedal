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
#include "S25FLXXX.h"
#include "SPI.h"
#include "LCD_Writing.h"
#include "FunctionRotate.h"
#define SC1FLAG 0x1F
#define SC3FlAG 0x07
#define SPI_CHANNEL		SPI_0
#define SPI_PORT		GPIO_D
#define SPI_MOSI_BIT	BIT2
#define SPI_MISO_BIT 	BIT3
#define SPI_CLK			BIT1
#define SPI_PIN_CONFIG  GPIO_MUX2|GPIO_DSE


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



uint8 MMU_waitingFunction()
{

	MemoryPortType SPIChannelForMemory = {
					SPI_CHANNEL,
					SPI_CS_PORT,
					SPI_CS_BIT,
			};

	uint8 status;


	do {
		status = S25FLXXX_readStatusRegister(STATUS_REGISTER_1,&SPIChannelForMemory);
		status = status & 0x01;

	}
	while(status);

	return(FALSE);

}

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
	uint8 Memory_Write_Flag = 0;
	uint16 Counter=0;
	uint8 FlagLooper=0;
	uint16 Counter2=0;
	uint8 Value=0;
	uint8 Value2=0;
	uint8 SC1cfg = SC1FLAG;
	uint8 SC2cfg = 0;
	uint32 Top=0x1FFFFF;
	uint8 SC3cfg = SC3FlAG;
	GUITAR_DATA Data_Bits = {0};
	GPIO_pinControlRegisterType pinControlRegisterGPIOCPortC = GPIO_MUX1|INTR_FALLING_EDGE;
	GPIO_pinControlRegisterType pinControlRegisterGPIOBPortB = GPIO_MUX1;
	GPIO_clockGating(GPIO_C);
	GPIO_clockGating(GPIO_D);
	GPIO_pinControlRegister(GPIO_C,BIT5,&pinControlRegisterGPIOCPortC);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_INPUT, BIT5);
	GPIO_pinControlRegister(GPIO_D,BIT0,&pinControlRegisterGPIOBPortB);
	GPIO_dataDirectionPIN(GPIO_D, GPIO_OUTPUT, BIT0);
	GPIO_pinControlRegister(GPIO_C,BIT1,&pinControlRegisterGPIOBPortB);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_INPUT, BIT1);
	GPIO_pinControlRegister(GPIO_C,BIT11,&pinControlRegisterGPIOBPortB);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_INPUT, BIT11);
	GPIO_pinControlRegister(GPIO_C,BIT16,&pinControlRegisterGPIOBPortB);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_INPUT, BIT16);
	GPIO_pinControlRegister(GPIO_C,BIT17,&pinControlRegisterGPIOBPortB);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_INPUT, BIT17);
	GPIO_clockGating(GPIO_B);
	GPIO_pinControlRegister(GPIO_B,BIT18,&pinControlRegisterGPIOBPortB);
	GPIO_dataDirectionPIN(GPIO_B, GPIO_INPUT, BIT18);
	GPIO_pinControlRegister(GPIO_B,BIT23,&pinControlRegisterGPIOBPortB);
	GPIO_dataDirectionPIN(GPIO_B, GPIO_INPUT, BIT23);
	GPIO_pinControlRegister(GPIO_B,BIT19,&pinControlRegisterGPIOBPortB);
	GPIO_dataDirectionPIN(GPIO_B, GPIO_INPUT, BIT19);
	NVIC_enableInterruptAndPriotity(PORTC_IRQ, PRIORITY_5);
	ADC_initialize(&ADC,SC1cfg,SC2cfg,SC3cfg);
	FlexTimer_Init(&FTM_Config);
	GPIO_setPIN(GPIO_D, BIT0);
    //SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA|GPIO_CLOCK_GATING_PORTC;
	//PORTC->PCR[1]   = PORT_PCR_MUX(0x4);
	NVIC_enableInterruptAndPriotity(FTM0_IRQ, PRIORITY_1);
	DAC0_clockGating();
	DAC0_init();
	EnableInterrupts;
	S25FLXXX_MemoryAddressType S25FLXXX_MemoryAddress = {0};
	S25FLXXX_MemoryAddress.address = 0;
	SPI_init(&SPI_ConfigMemory);
	LCDNokia_init();
	LCDNokia_clear();
	Inicio_LCD();
	SPI_init(&SPI_ConfigMemory);
    while(TRUE)
    {

    	/**If the interruptions is activated we start to save value from the ADC in the Memory*/
    	if(GPIO_getIRQStatus(GPIO_C) && !Memory_Write_Flag)
    	{
    		GPIO_clearIRQStatus(GPIO_C);
    		Saving_Memory_LCD();
    		SPI_init(&SPI_ConfigMemory);
    		Counter=0;
    			while(!GPIO_getIRQStatus(GPIO_C) && S25FLXXX_MemoryAddress.address <= Top)
    			{
    				if(getFlexFlag())
    				{

    					Sample = StartConversion(&ADC);
    					Data_Bits.address = Sample;
    					S25FLXXX_writeByte(Data_Bits.addressByByte.addressByte0,&S25FLXXX_MemoryAddress,&SPIChannelForMemory);
    					MMU_waitingFunction();
    					S25FLXXX_MemoryAddress.address += 1;
    					S25FLXXX_writeByte(Data_Bits.addressByByte.addressByte1,&S25FLXXX_MemoryAddress,&SPIChannelForMemory);
    					MMU_waitingFunction();
    					S25FLXXX_MemoryAddress.address += 1;
    					clearFlexFlag();
    				}

    			}
    			Saving_Finish_LCD();
    			Memory_Write_Flag = TRUE;
    			SPI_init(&SPI_ConfigMemory);
    			Counter=S25FLXXX_MemoryAddress.address;
    			S25FLXXX_MemoryAddress.address = 0;
    			GPIO_clearIRQStatus(GPIO_C);
    	}else if(GPIO_getIRQStatus(GPIO_C))
    	{
    		GPIO_clearIRQStatus(GPIO_C);
    		Memory_Is_Full_LCD();
    		SPI_init(&SPI_ConfigMemory);
    		delay(20000);
    	}



/**Activate or deactivate LOOPER MODE*/
    	if(GPIO_readPIN(GPIO_B, BIT19))
    	{
    		if(FlagLooper==0)
    		{
    			FlagLooper=1;
    			LOOPER_ON_LCD();
    			SPI_init(&SPI_ConfigMemory);
    		}else
    		{
    			FlagLooper=0;
    			LOOPER_OFF_LCD();
    			SPI_init(&SPI_ConfigMemory);
    		}
    	}

    	/**If FlagLooper is in TRUE we read the memory and we take it out by the DAC */

    	if(FlagLooper == TRUE)
    	{
    	S25FLXXX_MemoryAddress.address = Looper_Memory(S25FLXXX_MemoryAddress, Counter, SPIChannelForMemory);
    	Value = S25FLXXX_readByte(&S25FLXXX_MemoryAddress,&SPIChannelForMemory);
    	S25FLXXX_MemoryAddress.address += 1;
    	Value2 = S25FLXXX_readByte(&S25FLXXX_MemoryAddress,&SPIChannelForMemory);
    	S25FLXXX_MemoryAddress.address += 1;
    	Data_Bits.addressByByte.addressByte0=Value;
    	Data_Bits.addressByByte.addressByte1=Value2;
    	DAC0_write(Data_Bits.address);
    	/*If Counter2 is in his Max Value we restarted */
    	if (S25FLXXX_MemoryAddress.address >= Counter)
    		S25FLXXX_MemoryAddress.address=0;
    	}

    	/**Choose wich Effect you want depending how many times you push it*/
    	if(GPIO_readPIN(GPIO_C, BIT11))
    	{
    		choose_function(FlagLooper, S25FLXXX_MemoryAddress, Counter, SPIChannelForMemory);
    		SPI_init(&SPI_ConfigMemory);
    		S25FLXXX_MemoryAddress.address=0;
    	}


    	if(GPIO_readPIN(GPIO_B, BIT18))
    	{
    		Erasing_Memory_LCD();
    		SPI_init(&SPI_ConfigMemory);
    		S25FLXXX_EraseMemory(&SPIChannelForMemory);
    		MMU_waitingFunction();
    		Memory_Erase_LCD();
    		SPI_init(&SPI_ConfigMemory);
    		Memory_Write_Flag = FALSE;
    		delay(10000);
    	}
    }
    return 0 ;
}
