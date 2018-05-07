/*
 * FunctionRotate.c
 *
 *  Created on: Apr 14, 2018
 *      Author: Jorge Loya
 */
#include "FunctionRotate.h"
#include "LCD_Writing.h"
#include "GPIO.h"
#include "S25FLXXX.h"
#include "SPI.h"
#include "DataTypeDefinitions.h"
#include "MK64F12.h"

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
uint8 Effect=0;

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
			void(*fptr)(uint8 FlagLooper, S25FLXXX_MemoryAddressType address, uint32 Counter, MemoryPortType SPIChannel);
			uint32 state;
		}Function;

const Function FSMMoore[6]=
{
		{Menu_Function1,1},
		{Menu_Function2,2},
		{Menu_Function3,3},
		{Menu_Function4,4},
		{Menu_Function5,5},
		{Menu_Function6,6}
};



void Menu_Function1(uint8 Flag, S25FLXXX_MemoryAddressType address, uint32 Counter, MemoryPortType SPIChannel)
{
	uint8 Potencia = 50;
	Resonator_LCD(Potencia);
	SPI_init(&SPI_Config);
	while(!GPIO_readPIN(GPIO_B, BIT23))
	{
		if(Flag==TRUE)
		{
			Looper_Memory( address,  Counter,  SPIChannel);

		}
		if(GPIO_readPIN(GPIO_C, BIT16))
		{
			if(Potencia != 100)
			{
				Potencia +=10;
				Resonator_LCD(Potencia);
				SPI_init(&SPI_Config);
			}
		}else if(GPIO_readPIN(GPIO_C, BIT17))
		{
			if(Potencia != 0)
			{
				Potencia -=10;
				Resonator_LCD(Potencia);
				SPI_init(&SPI_Config);
			}
		}
	}
}

void Menu_Function2(uint8 Flag, S25FLXXX_MemoryAddressType address, uint32 Counter, MemoryPortType SPIChannel)
{
	uint8 Potencia = 50;
	Chorus_LCD(Potencia);
	SPI_init(&SPI_Config);
	while(!GPIO_readPIN(GPIO_B, BIT23))
		{
		if(Flag==TRUE)
		{
			Looper_Memory( address,  Counter,  SPIChannel);
		}
			if(GPIO_readPIN(GPIO_C, BIT16))
			{
				if(Potencia != 100)
				{
					Potencia +=10;
					Chorus_LCD(Potencia);
					SPI_init(&SPI_Config);
				}
			}else if(GPIO_readPIN(GPIO_C, BIT17))
			{
				if(Potencia != 0)
				{
					Potencia -=10;
					Chorus_LCD(Potencia);
					SPI_init(&SPI_Config);
				}
			}
		}
}
void Menu_Function3(uint8 Flag, S25FLXXX_MemoryAddressType address, uint32 Counter, MemoryPortType SPIChannel)
{
	uint8 Potencia = 50;
	Flanger_LCD(Potencia);
	SPI_init(&SPI_Config);
	while(!GPIO_readPIN(GPIO_B, BIT23))
		{
		if(Flag==TRUE)
		{
			Looper_Memory( address,  Counter,  SPIChannel);
		}
			if(GPIO_readPIN(GPIO_C, BIT16))
			{
				if(Potencia != 100)
				{
					Potencia +=10;
					Flanger_LCD(Potencia);
					SPI_init(&SPI_Config);
				}
			}else if(GPIO_readPIN(GPIO_C, BIT17))
			{
				if(Potencia != 0)
				{
					Potencia -=10;
					Flanger_LCD(Potencia);
					SPI_init(&SPI_Config);
				}
			}
		}
}
void Menu_Function4(uint8 Flag, S25FLXXX_MemoryAddressType address, uint32 Counter, MemoryPortType SPIChannel)
{
	uint8 Potencia = 50;
	Wah_wah_LCD(Potencia);
	SPI_init(&SPI_Config);
	while(!GPIO_readPIN(GPIO_B, BIT23))
		{
		if(Flag==TRUE)
		{
			Looper_Memory( address,  Counter,  SPIChannel);
			SPI_init(&SPI_Config);
		}
			if(GPIO_readPIN(GPIO_C, BIT16))
			{
				if(Potencia != 100)
				{
					Potencia +=10;
					Wah_wah_LCD(Potencia);
					SPI_init(&SPI_Config);
				}
			}else if(GPIO_readPIN(GPIO_C, BIT17))
			{
				if(Potencia != 0)
				{
					Potencia -=10;
					Wah_wah_LCD(Potencia);
					SPI_init(&SPI_Config);
				}
			}
		}
}
void Menu_Function5(uint8 Flag, S25FLXXX_MemoryAddressType address, uint32 Counter, MemoryPortType SPIChannel)
{
	uint8 Potencia = 50;
	Tremolo_LCD(Potencia);
	SPI_init(&SPI_Config);
	while(!GPIO_readPIN(GPIO_B, BIT23))
		{
		if(Flag==TRUE)
		{
			Looper_Memory( address,  Counter,  SPIChannel);
		}
			if(GPIO_readPIN(GPIO_C, BIT16))
			{
				if(Potencia != 100)
				{
					Potencia +=10;
					Tremolo_LCD(Potencia);
					SPI_init(&SPI_Config);
				}
			}else if(GPIO_readPIN(GPIO_C, BIT17))
			{
				if(Potencia != 0)
				{
					Potencia -=10;
					Tremolo_LCD(Potencia);
					SPI_init(&SPI_Config);
				}
			}
		}
}
void Menu_Function6(uint8 Flag, S25FLXXX_MemoryAddressType address, uint32 Counter, MemoryPortType SPIChannel)
{
	uint8 Potencia = 50;
	Distorsion_LCD(Potencia);
	SPI_init(&SPI_Config);
	while(!GPIO_readPIN(GPIO_B, BIT23))
		{
			if(Flag==TRUE)
			{
				Looper_Memory( address,  Counter,  SPIChannel);
			}
			if(GPIO_readPIN(GPIO_C, BIT16))
			{
				if(Potencia != 100)
				{
					Potencia +=10;
					Distorsion_LCD(Potencia);
					SPI_init(&SPI_Config);
				}
			}else if(GPIO_readPIN(GPIO_C, BIT17))
			{
				if(Potencia != 0)
				{
					Potencia -=10;
					Distorsion_LCD(Potencia);
					SPI_init(&SPI_Config);
				}
			}
		}
}

void choose_function(uint8 FlagLooper, S25FLXXX_MemoryAddressType address, uint32 Counter, MemoryPortType SPIChannel)
{
	 FSMMoore[Effect].fptr(FlagLooper,address, Counter, SPIChannel);
	Effect += 1;
	if (Effect==6)
	{
		Effect = 0;
	}
}
