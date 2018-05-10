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
#include "SoundFX.h"

#define DEBOUNCER 15000
#define INITIALVALUEPOT 50
#define INITIALVALUE 0
#define STEPPOT 10
#define TOPPOTVAL 100
#define STEPONE 1
#define LOWPOTVAL 0
#define TOP 0x1FFFF0
#define SC1FLAG 0x1F
#define SC3FlAG 0x07
#define SPI_CHANNEL		SPI_0
#define SPI_PORT		GPIO_D
#define SPI_MOSI_BIT	BIT2
#define SPI_MISO_BIT 	BIT3
#define SPI_CLK			BIT1
#define SPI_PIN_CONFIG  GPIO_MUX2|GPIO_DSE
#define STEPADDRESS 0x1000

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
uint16 processedSample;
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

/***/
void Menu_For_Erase_Memory(S25FLXXX_MemoryAddressType address, MemoryPortType SPIChannel, ADC_ConfigType ADC)
{
	delay(DEBOUNCER);
	MenuForEraseMemory();
	while(!GPIO_readPIN(GPIO_C, BIT7))
	{
		LooperActivated(SPIChannel);
		Dac_Working(ADC, CLEAN);
		if(GPIO_readPIN(GPIO_C, BIT5))
		{
			delay(DEBOUNCER);
			Eliminando_Aviso();
			address.address = INITIALVALUE;
			//Elminando_Aviso();
			while(address.address < 0x1FFFFF)
			{
				S25FLXXX_erase4KbSector(&address, &SPIChannel);
				address.address += STEPADDRESS;
				MMU_waitingFunction();
			}
			Memory_Write_Flag = FALSE;
			MemoryReadyFlag = FALSE;
			Elminado_Aviso();
		}

	}
	FirstMenu();
	delay(DEBOUNCER);
}
/**This function prints all effect and depending the push button applied a respective Effect*/
void Menu_For_Effect(S25FLXXX_MemoryAddressType address, MemoryPortType SPIChannel, ADC_ConfigType ADC)
{
	MenuForEffect();
	while(!GPIO_readPIN(GPIO_B, BIT19))
	{
		LooperActivated(SPIChannel);
		if(GPIO_readPIN(GPIO_C, BIT5))
		{
			delay(DEBOUNCER);
			Potencia = INITIALVALUEPOT;
			Resonator_Menu(Potencia);
			while(!GPIO_readPIN(GPIO_C, BIT0))
			{
				LooperActivated(SPIChannel);
				Dac_Working(ADC, SLAPBACK);
				if(GPIO_readPIN(GPIO_C, BIT5))
				{
					if(Potencia != TOPPOTVAL)
					Potencia += STEPPOT;
					Resonator_Menu(Potencia);
					delay(DEBOUNCER);
				}
				if(GPIO_readPIN(GPIO_C, BIT7))
				{
					if(Potencia != LOWPOTVAL)
					Potencia -= STEPPOT;
					Resonator_Menu(Potencia);
					delay(DEBOUNCER);
				}

			}
			delay(DEBOUNCER);
			MenuForEffect();
		}else if(GPIO_readPIN(GPIO_C, BIT7))
		{
			delay(DEBOUNCER);
			Potencia = INITIALVALUEPOT;
			Chorus_Menu(Potencia);
			while(!GPIO_readPIN(GPIO_C, BIT0))
			{
				LooperActivated(SPIChannel);
				Dac_Working(ADC, CHORUS);
				if(GPIO_readPIN(GPIO_C, BIT5))
				{
					if(Potencia != TOPPOTVAL)
					Potencia += STEPPOT;
					Chorus_Menu(Potencia);
					delay(DEBOUNCER);
				}
				if(GPIO_readPIN(GPIO_C, BIT7))
				{
					if(Potencia != LOWPOTVAL)
					Potencia -= STEPPOT;
					Chorus_Menu(Potencia);
					delay(DEBOUNCER);
				}
			}
			delay(DEBOUNCER);
			MenuForEffect();
		}else if(GPIO_readPIN(GPIO_C, BIT0))
		{
			delay(DEBOUNCER);
			Potencia = INITIALVALUEPOT;
			Flanger_Menu(Potencia);
			while(!GPIO_readPIN(GPIO_C, BIT0))
			{
				LooperActivated(SPIChannel);
				Dac_Working(ADC, FLANGER);
				if(GPIO_readPIN(GPIO_C, BIT5))
				{
					if(Potencia != TOPPOTVAL)
					Potencia += STEPPOT;
					Flanger_Menu(Potencia);
					delay(DEBOUNCER);
				}
				if(GPIO_readPIN(GPIO_C, BIT7))
				{
					if(Potencia != LOWPOTVAL)
					Potencia -= STEPPOT;
					Flanger_Menu(Potencia);
					delay(DEBOUNCER);
				}
			}
			delay(DEBOUNCER);
			MenuForEffect();
		}else if(GPIO_readPIN(GPIO_C, BIT9))
		{
			delay(DEBOUNCER);
			Potencia = INITIALVALUEPOT;
			Wah_wah_Menu(Potencia);
			while(!GPIO_readPIN(GPIO_C, BIT0))
			{
				LooperActivated(SPIChannel);
				Dac_Working(ADC, CLEAN);
				if(GPIO_readPIN(GPIO_C, BIT5))
				{
					if(Potencia != TOPPOTVAL)
					Potencia += STEPPOT;
					Wah_wah_Menu(Potencia);
					delay(DEBOUNCER);
				}
				if(GPIO_readPIN(GPIO_C, BIT7))
				{
					if(Potencia != LOWPOTVAL)
					Potencia -= STEPPOT;
					Wah_wah_Menu(Potencia);
					delay(DEBOUNCER);
				}
			}
			delay(DEBOUNCER);
			MenuForEffect();
		}else if(GPIO_readPIN(GPIO_C, BIT8))
		{
			delay(DEBOUNCER);
			Potencia = INITIALVALUEPOT;
			Tremolo_Menu(Potencia);
			while(!GPIO_readPIN(GPIO_C, BIT0))
			{
				LooperActivated(SPIChannel);
				Dac_Working(ADC, TREMOLO);
				if(GPIO_readPIN(GPIO_C, BIT5))
				{
					if(Potencia != TOPPOTVAL)
					Potencia += STEPPOT;
					Tremolo_Menu(Potencia);
					delay(DEBOUNCER);
				}
				if(GPIO_readPIN(GPIO_C, BIT7))
				{
					if(Potencia != LOWPOTVAL)
					Potencia -= STEPPOT;
					Tremolo_Menu(Potencia);
					delay(DEBOUNCER);
				}
			}
			delay(DEBOUNCER);
			MenuForEffect();
		}else if(GPIO_readPIN(GPIO_C, BIT1))
		{
			delay(DEBOUNCER);
			Potencia = INITIALVALUEPOT;
			Distorsion_Menu(Potencia);
			while(!GPIO_readPIN(GPIO_C, BIT0))
			{
				LooperActivated(SPIChannel);
				Dac_Working(ADC, DISTORTION);
				if(GPIO_readPIN(GPIO_C, BIT5))
				{
					if(Potencia != TOPPOTVAL)
					Potencia += STEPPOT;
					Distorsion_Menu(Potencia);
					delay(DEBOUNCER);
				}
				if(GPIO_readPIN(GPIO_C, BIT7))
				{
					if(Potencia != LOWPOTVAL)
					Potencia -= STEPPOT;
					Distorsion_Menu(Potencia);
					delay(DEBOUNCER);
				}
			}
			delay(DEBOUNCER);
			MenuForEffect();
		}
	}

	FirstMenu();
	delay(DEBOUNCER);
}
/**This function save values from the ADC in the memory until a push button is activated*/
void Menu_For_Looper(S25FLXXX_MemoryAddressType address, MemoryPortType SPIChannel, ADC_ConfigType ADC)
{
	MenuForLooper();
	while(!GPIO_readPIN(GPIO_C, BIT7))
	{
		delay(DEBOUNCER);
		LooperActivated(SPIChannel);
		Dac_Working(ADC, CLEAN);
		if(GPIO_readPIN(GPIO_C, BIT5) && !Memory_Write_Flag)
		{
	    		Counter=0;
	    		address.address = INITIALVALUE;
	    		Guardando_Aviso();
	    			while(!GPIO_readPIN(GPIO_C, BIT5) && address.address <= TOP)
	    			{
	    				if(getFlexFlag())
	    				{
	    					Sample = StartConversion(&ADC);
	    					Data_Bits.address = Sample;
	    					S25FLXXX_writeByte(Data_Bits.addressByByte.addressByte0,Data_Bits.addressByByte.addressByte1,&address,&SPIChannel);
	    					MMU_waitingFunction();
	    					address.address += STEPONE;
	    					S25FLXXX_writeByte(Data_Bits.addressByByte.addressByte1,Data_Bits.addressByByte.addressByte0,&address,&SPIChannel);
	    					MMU_waitingFunction();
	    					address.address += STEPONE;
	    					clearFlexFlag();
	    				}
	    			}
	    			delay(DEBOUNCER);
	    			Memory_Write_Flag = TRUE;
	    			MemoryReadyFlag = TRUE;
	    			Counter=address.address;
	    			address.address = INITIALVALUE;
	    			Guardado_Aviso();
	    	}else if(GPIO_readPIN(GPIO_C, BIT5))
	    	{

	    	}
	}
	delay(DEBOUNCER);
}
/**This Function Read The memory and put the value in the DAC*/
void LooperActivated(MemoryPortType SPIChannel)
{
	if(MemoryReadyFlag == TRUE  && getFlexFlag())
	{
	Data_Bits.addressByByte.addressByte0 = S25FLXXX_readByte(&AddresLooper,&SPIChannel);
	AddresLooper.address += STEPONE;
	Data_Bits.addressByByte.addressByte1 = S25FLXXX_readByte(&AddresLooper,&SPIChannel);
	AddresLooper.address += STEPONE;
	DAC0_write(Data_Bits.address);
	/*If Counter2 is in his Max Value we restarted */
	if (AddresLooper.address >= Counter)
		AddresLooper.address = INITIALVALUE;
	}
}
/**This Function reads the ADC and put it a effect and then put it in the DAC*/
void Dac_Working(ADC_ConfigType ADC, FXType Effect)
{
	if(getFlexFlag())
	{
		Sample = StartConversion(&ADC);
		setSampleArray(Sample);
		processedSample = FXPercentage(Effect, Sample, Potencia, 0.9);
		DAC0_write(processedSample);
		clearFlexFlag();
	}
}

/**This is a pointer to function depending of the value of Function*/
void choose_function(uint8 Function, S25FLXXX_MemoryAddressType address, MemoryPortType SPIChannel, ADC_ConfigType ADC)
{
	 FSMMoore[Function].fptr(address, SPIChannel, ADC);

}
