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
 * @file    GPX_PEDAL.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "MK64F12.h"
#include "SPI.h"
#include  "GPIO.h"
#include "ADCDriver.h"
#include "S25FLXXX.h"


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

/** Baud rate is calculated as BaudRate= SystemClock/(doubleDataRate*baudRate)
	 * 	In the case of 60 MHz of system clock the SPI baud rate is 15 MHz. It is
	 * 	important to note the the double baud rate needs to be enabled, otherwise is not
	 * 	possible to reach this frequency*/
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
				{SPI_PORT,SPI_MOSI_BIT,SPI_MISO_BIT,SPI_CLK,SPI_CS_BIT,
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
	uint8 status2;

	do {
		status = S25FLXXX_readStatusRegister(STATUS_REGISTER_1,&SPIChannelForMemory);
		status = status & 0x01;
		status = status;
	}
	while(status);

	return(FALSE);

}


int main(void) {

	uint8 data;
	uint16 EraseCounter=0;
	uint16 PageMain;
	uint16 AddressMain;
	uint16 PageCounter = 0;
	uint16 AddressCounter = 0;
	S25FLXXX_MemoryAddressType S25FLXXX_MemoryAddress = {0};

	S25FLXXX_MemoryAddress.address = BEGINNING_OF_FIRST_SECTOR + 4;

	SPI_init(&SPI_ConfigMemory);

	//S25FLXXX_erase4KbSector(&S25FLXXX_MemoryAddress, &SPIChannelForMemory);
	//MMU_waitingFunction();

	//data = S25FLXXX_readByte(&S25FLXXX_MemoryAddress, &SPIChannelForMemory);
	//MMU_waitingFunction();

	//S25FLXXX_writeByte(&S25FLXXX_MemoryAddress,&SPIChannelForMemory);
	S25FLXXX_write(55, &S25FLXXX_MemoryAddress,&SPIChannelForMemory);

	MMU_waitingFunction();
//
	data = S25FLXXX_readByte(&S25FLXXX_MemoryAddress, &SPIChannelForMemory);
	MMU_waitingFunction();
	//Erase Memory

	//S25FLXXX_MemoryAddress.address = 4;
		//data = S25FLXXX_readByte(&S25FLXXX_MemoryAddress, &SPIChannelForMemory);
		//MMU_waitingFunction();
		S25FLXXX_EraseMemory(&SPIChannelForMemory);
	//S25FLXXX_MemoryAddress.address = 0x4;
	MMU_waitingFunction();
	data = S25FLXXX_readByte(&S25FLXXX_MemoryAddress, &SPIChannelForMemory);
    while(TRUE)
    {
    	if(GPIO_getIRQStatus(GPIO_C))
    	{
    		S25FLXXX_writeByte(&S25FLXXX_MemoryAddress,&SPIChannelForMemory);
    		MMU_waitingFunction();
    		GPIO_clearIRQStatus(GPIO_C);
    		PageMain = GetPage();
    		AddressMain = GetAddress();
    	}
    	S25FLXXX_MemoryAddress.address = 1;



    	/*
    	while(PageCounter < PageMain )
    	{
    		while(AddressCounter <= 0xFFF)
    		{
    	    	data = S25FLXXX_readByte(&S25FLXXX_MemoryAddress, &SPIChannelForMemory);
    	    	S25FLXXX_MemoryAddress.address += 1;
    		}
    		PageCounter += 1;
    	}*/

    	//data = S25FLXXX_readByte(&S25FLXXX_MemoryAddress, &SPIChannelForMemory);
    }
    return 0 ;
}

