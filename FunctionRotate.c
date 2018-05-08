/*
 * FunctionRotate.c
 *
 *  Created on: Apr 14, 2018
 *      Author: Jorge Loya
 */
#include "FunctionRotate.h"
#include "GPIO.h"
#include "S25FLXXX.h"
#include "SPI.h"
#include "DataTypeDefinitions.h"
#include "MK64F12.h"
#include "S25FLXXX.h"
#include "WriteConsole.h"
#include "GlobalFunctions.h"
#include "FlexTimer.h"
#include "ADCDriver.h"
#include "DAC.h"

#define TOP 0x1FFFF0
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

S25FLXXX_MemoryAddressType AddresLooper = {0};
uint8 Potencia;
uint8 Prov;
uint8 Prov2;
uint16 Sample;
uint8 MemoryReadyFlag=FALSE;
uint32 Counter = 0;
GUITAR_DATA Data_Bits = {0};
uint8 Memory_Write_Flag = FALSE;
const SPI_ConfigType SPI_Config={
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
typedef const struct Function
		{
			void(*fptr)(S25FLXXX_MemoryAddressType address, MemoryPortType SPIChannel, ADC_ConfigType ADC);
			uint32 state;
		}Function;

const Function FSMMoore[3]=
{
		{Menu_For_Looper,1},
		{Menu_For_Erase_Memory,2},
		{Menu_For_Effect,3},
};


void Menu_For_Erase_Memory(S25FLXXX_MemoryAddressType address, MemoryPortType SPIChannel, ADC_ConfigType ADC)
{
	delay(15000);
	MenuForEraseMemory();
	while(!GPIO_readPIN(GPIO_C, BIT7))
	{
		LooperActivated(SPIChannel);
		Dac_Working(ADC);
		if(GPIO_readPIN(GPIO_C, BIT5))
		{
			delay(15000);
			address.address = 0;
			while(address.address < 0x1FFFFF)
			{
				S25FLXXX_erase4KbSector(&address, &SPIChannel);
				address.address += 0x1000;
				MMU_waitingFunction();
			}
			address.address = 0x1FF004;
			S25FLXXX_erase4KbSector(&address, &SPIChannel);
			MMU_waitingFunction();
			Memory_Write_Flag = FALSE;
			MemoryReadyFlag = FALSE;
		}

	}
	FirstMenu();
	delay(15000);
}

void Menu_For_Effect(S25FLXXX_MemoryAddressType address, MemoryPortType SPIChannel, ADC_ConfigType ADC)
{
	MenuForEffect();
	while(!GPIO_readPIN(GPIO_B, BIT19))
	{
		LooperActivated(SPIChannel);
		if(GPIO_readPIN(GPIO_C, BIT5))
		{
			delay(15000);
			Potencia = 50;
			Resonator_Menu(Potencia);
			while(!GPIO_readPIN(GPIO_C, BIT0))
			{
				LooperActivated(SPIChannel);
				Dac_Working(ADC);
				if(GPIO_readPIN(GPIO_C, BIT5))
				{
					if(Potencia != 100)
					Potencia += 10;
					Resonator_Menu(Potencia);
					delay(15000);
				}
				if(GPIO_readPIN(GPIO_C, BIT7))
				{
					if(Potencia != 0)
					Potencia -= 10;
					Resonator_Menu(Potencia);
					delay(15000);
				}

			}
			delay(15000);
			MenuForEffect();
		}else if(GPIO_readPIN(GPIO_C, BIT7))
		{
			delay(15000);
			Potencia = 50;
			Chorus_Menu(Potencia);
			while(!GPIO_readPIN(GPIO_C, BIT0))
			{
				LooperActivated(SPIChannel);
				Dac_Working(ADC);
				if(GPIO_readPIN(GPIO_C, BIT5))
				{
					if(Potencia != 100)
					Potencia += 10;
					Chorus_Menu(Potencia);
					delay(15000);
				}
				if(GPIO_readPIN(GPIO_C, BIT7))
				{
					if(Potencia != 0)
					Potencia -= 10;
					Chorus_Menu(Potencia);
					delay(15000);
				}
			}
			delay(15000);
			MenuForEffect();
		}else if(GPIO_readPIN(GPIO_C, BIT0))
		{
			delay(15000);
			Potencia = 50;
			Flanger_Menu(Potencia);
			while(!GPIO_readPIN(GPIO_C, BIT0))
			{
				LooperActivated(SPIChannel);
				Dac_Working(ADC);
				if(GPIO_readPIN(GPIO_C, BIT5))
				{
					if(Potencia != 100)
					Potencia += 10;
					Flanger_Menu(Potencia);
					delay(15000);
				}
				if(GPIO_readPIN(GPIO_C, BIT7))
				{
					if(Potencia != 0)
					Potencia -= 10;
					Flanger_Menu(Potencia);
					delay(15000);
				}
			}
			delay(15000);
			MenuForEffect();
		}else if(GPIO_readPIN(GPIO_C, BIT9))
		{
			delay(15000);
			Potencia = 50;
			Wah_wah_Menu(Potencia);
			while(!GPIO_readPIN(GPIO_C, BIT0))
			{
				LooperActivated(SPIChannel);
				Dac_Working(ADC);
				if(GPIO_readPIN(GPIO_C, BIT5))
				{
					if(Potencia != 100)
					Potencia += 10;
					Wah_wah_Menu(Potencia);
					delay(15000);
				}
				if(GPIO_readPIN(GPIO_C, BIT7))
				{
					if(Potencia != 0)
					Potencia -= 10;
					Wah_wah_Menu(Potencia);
					delay(15000);
				}
			}
			delay(15000);
			MenuForEffect();
		}else if(GPIO_readPIN(GPIO_C, BIT8))
		{
			delay(15000);
			Potencia = 50;
			Tremolo_Menu(Potencia);
			while(!GPIO_readPIN(GPIO_C, BIT0))
			{
				LooperActivated(SPIChannel);
				Dac_Working(ADC);
				if(GPIO_readPIN(GPIO_C, BIT5))
				{
					if(Potencia != 100)
					Potencia += 10;
					Tremolo_Menu(Potencia);
					delay(15000);
				}
				if(GPIO_readPIN(GPIO_C, BIT7))
				{
					if(Potencia != 0)
					Potencia -= 10;
					Tremolo_Menu(Potencia);
					delay(15000);
				}
			}
			delay(15000);
			MenuForEffect();
		}else if(GPIO_readPIN(GPIO_C, BIT1))
		{
			delay(15000);
			Potencia = 50;
			Distorsion_Menu(Potencia);
			while(!GPIO_readPIN(GPIO_C, BIT0))
			{
				LooperActivated(SPIChannel);
				Dac_Working(ADC);
				if(GPIO_readPIN(GPIO_C, BIT5))
				{
					if(Potencia != 100)
					Potencia += 10;
					Distorsion_Menu(Potencia);
					delay(15000);
				}
				if(GPIO_readPIN(GPIO_C, BIT7))
				{
					if(Potencia != 0)
					Potencia -= 10;
					Distorsion_Menu(Potencia);
					delay(15000);
				}
			}
			delay(15000);
			MenuForEffect();
		}
	}

	FirstMenu();
	delay(15000);
}

void Menu_For_Looper(S25FLXXX_MemoryAddressType address, MemoryPortType SPIChannel, ADC_ConfigType ADC)
{
	MenuForLooper();
	while(!GPIO_readPIN(GPIO_C, BIT7))
	{
		LooperActivated(SPIChannel);
		Dac_Working(ADC);
		if(GPIO_readPIN(GPIO_C, BIT5) && !Memory_Write_Flag)
		{
			delay(25000);
	    		Counter=0;
	    		address.address = 0;
	    			while(!GPIO_readPIN(GPIO_C, BIT5) && address.address <= TOP)
	    			{
	    				if(getFlexFlag())
	    				{
	    					Sample = StartConversion(&ADC);
	    					Data_Bits.address = Sample;
	    					S25FLXXX_writeByte(Data_Bits.addressByByte.addressByte0,Data_Bits.addressByByte.addressByte1,&address,&SPIChannel);
	    					MMU_waitingFunction();
	    					address.address += 2;
	    					clearFlexFlag();
	    				}

	    			}
	    			delay(25000);
	    			Memory_Write_Flag = TRUE;
	    			MemoryReadyFlag = TRUE;
	    			Counter=address.address;
	    			address.address = 0x1FF001;
	    			S25FLXXX_writeByte(Counter>>16,(Counter&0xFFFF)>>8,&address,&SPIChannel);
	    			address.address = 0x1FF003;
	    			MMU_waitingFunction();
	    			S25FLXXX_writeByte((Counter&0xFF),0,&address,&SPIChannel);
	    			address.address = 0x1FF001;
	    			MMU_waitingFunction();
	    			Counter =S25FLXXX_readByte(&address,&SPIChannel);
	    			address.address = 0x1FF002;
	    			MMU_waitingFunction();
	    			Counter =S25FLXXX_readByte(&address,&SPIChannel);
	    			address.address = 0x1FF003;
	    			MMU_waitingFunction();
	    			Counter =S25FLXXX_readByte(&address,&SPIChannel);
	    			MMU_waitingFunction();
	    			address.address = 0;
	    	}else if(GPIO_readPIN(GPIO_C, BIT5))
	    	{

	    	}
	}

}



void LooperActivated(MemoryPortType SPIChannel)
{
	if(MemoryReadyFlag == TRUE)
	{
	Data_Bits.addressByByte.addressByte0 = S25FLXXX_readByte(&AddresLooper,&SPIChannel);
	AddresLooper.address += 1;
	Data_Bits.addressByByte.addressByte1 = S25FLXXX_readByte(&AddresLooper,&SPIChannel);
	AddresLooper.address += 1;
	DAC0_write(Data_Bits.address);
	/*If Counter2 is in his Max Value we restarted */
	if (AddresLooper.address >= Counter)
		AddresLooper.address=0;
	}
}

void Dac_Working(ADC_ConfigType ADC)
{
	if(getFlexFlag())
	{
		DAC0_write(StartConversion(&ADC));
		clearFlexFlag();
	}
}

void choose_function(uint8 Function, S25FLXXX_MemoryAddressType address, MemoryPortType SPIChannel, ADC_ConfigType ADC)
{
	 FSMMoore[Function].fptr(address, SPIChannel, ADC);

}
