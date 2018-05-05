/*
 * SPI.h
 *
 *  Created on: 11/10/2017
 *      Author: jlpe
 */

#ifndef SPI_H_
#define SPI_H_

#include "DataTypeDefinitions.h"
#include "GPIO.h"

#define SPI0_CLOCK_GATING 0x1000
#define SPI1_CLOCK_GATING 0x2000
#define SPI2_CLOCK_GATING 0x1000

#define SPI_FSIZE_4 SPI_CTAR_FMSZ(3)
#define SPI_FSIZE_5 SPI_CTAR_FMSZ(4)
#define SPI_FSIZE_6 SPI_CTAR_FMSZ(5)
#define SPI_FSIZE_7 SPI_CTAR_FMSZ(6)
#define SPI_FSIZE_8 SPI_CTAR_FMSZ(7)
#define SPI_FSIZE_9 SPI_CTAR_FMSZ(8)
#define SPI_FSIZE_10 SPI_CTAR_FMSZ(9)
#define SPI_FSIZE_11 SPI_CTAR_FMSZ(10)
#define SPI_FSIZE_12 SPI_CTAR_FMSZ(11)
#define SPI_FSIZE_13 SPI_CTAR_FMSZ(12)
#define SPI_FSIZE_14 SPI_CTAR_FMSZ(13)
#define SPI_FSIZE_15 SPI_CTAR_FMSZ(14)
#define SPI_FSIZE_16 SPI_CTAR_FMSZ(15)


#define SPI_DOUBLE_BAUD_RATE 1
#define SPI_NON_DOUBLE_BAUD_RATE 0

#define SPI_BAUD_RATE_2     0x00
#define SPI_BAUD_RATE_4     0x01
#define SPI_BAUD_RATE_6     0x02
#define SPI_BAUD_RATE_8     0x03
#define SPI_BAUD_RATE_16    0x04
#define SPI_BAUD_RATE_32    0x05
#define SPI_BAUD_RATE_64    0x06
#define SPI_BAUD_RATE_128   0x07
#define SPI_BAUD_RATE_256   0x08
#define SPI_BAUD_RATE_512   0x09
#define SPI_BAUD_RATE_1024  0x0A
#define SPI_BAUD_RATE_2048  0x0B
#define SPI_BAUD_RATE_4096  0x0C
#define SPI_BAUD_RATE_8192  0x0D

#define SPI_PCSIS_0 0x100
#define SPI_PCSIS_1 0x200
#define SPI_PCSIS_2 0x400
#define SPI_PCSIS_3 0x800
#define SPI_PCSIS_4 0x1000
#define SPI_PCSIS_5 0x2000

/*Type for FIFO configuration*/
typedef enum {SPI_DISABLE_FIFO, SPI_ENABLE_FIFO} SPI_EnableFIFOType;
typedef enum {SPI_CS_LOW, SPI_CS_HIGH} SPI_CSInactiveStateType;
/*Type for polarity configuration*/
typedef enum {SPI_LOW_POLARITY,SPI_HIGH_POLARITY} SPI_PolarityType;
/*Type for phase configuration*/
typedef enum {SPI_LOW_PHASE,SPI_HIGH_PHASE} SPI_PhaseType;
/*Type for the star of the frame, either MSB o LSM */
typedef enum {SPI_MSB, SPI_LSM} SPI_LSMorMSBType;
/*Type for SPI modules*/
typedef enum {SPI_0,
			  SPI_1,
			  SPI_2
			  } SPI_ChannelType;
/*Type for master or slave configuration*/
typedef enum{SPI_SLAVE,SPI_MASTER} SPI_MasterType;
/*Type for GPIO configuration that activates the GPIO for SPI*/
typedef struct{
	GPIO_portNameType GPIO_portName;
	uint8 SPI_SOUT;
	uint8 SPI_SIN;
	uint8 SPI_CLK;
	uint8 SPI_CS;
	GPIO_pinControlRegisterType pinConttrolRegister;
	GPIO_pinControlRegisterType pinConttrolRegisterCS;
}GPIOForSPIType;
/*Type that is used for SPI configuration, It contains all the information needed for a SPI module*/
typedef struct
{
	SPI_EnableFIFOType SPI_EnableFIFO;
	SPI_PolarityType SPI_Polarity;
	SPI_PhaseType SPI_Phase;
	SPI_LSMorMSBType SPI_LSMorMSB;
	SPI_ChannelType SPI_Channel;
	SPI_MasterType SPI_Master;
	uint8 baudrate;
	uint8 doubleBaudRate;
	uint32 frameSize;
	SPI_CSInactiveStateType idleState;
	GPIOForSPIType GPIOForSPI;
} SPI_ConfigType;



uint8 SPI_errorFlag(void);

/*it enable the clock module of the SPI by modifying the MDIS bits*/
 void SPI_enable(SPI_ChannelType);
/*It activate the clock gating*/
 void SPI_clk(SPI_ChannelType);
/*It configure the SPI as a master or slave depending on the value of masterOrslave*/
 void SPI_setMaster(SPI_ChannelType channel, SPI_MasterType masterOrSlave);
/*It activate the TX and RX FIFOs of the SPI depending on the value of enableOrdisable*/
 void SPI_fIFO(SPI_ChannelType channel, SPI_EnableFIFOType enableOrDisable);
/*It selects the clock polarity depending on the value of cpol*/
 void SPI_clockPolarity(SPI_ChannelType channel, SPI_PolarityType cpol);
/*It selects the frame size depending on the value of frameSize and the macros that are defined above*/
 void SPI_frameSize(SPI_ChannelType channel, uint32 frameSize);
/*It selects the clock phase depending on the value of cpha*/
 void SPI_clockPhase(SPI_ChannelType channel, SPI_PhaseType cpha);
/*It selects the baud rate depending on the value of baudRate and the macros that are defined above*/
 void SPI_baudRate(SPI_ChannelType channel, uint32 baudRate,uint8 doubleBaudRate);
/*It selects if MSB or LSM bits is first transmitted*/
 void SPI_mSBFirst(SPI_ChannelType channel, SPI_LSMorMSBType msb);
/*It stars the SPI transmission by modifying the value of HALT bit*/
void SPI_startTranference(SPI_ChannelType channel);
/*It stops the SPI transmission by modifying the value of HALT bit*/
void SPI_stopTranference(SPI_ChannelType channel);
/*It transmits the information contained in data*/
uint8 SPI_transfer(SPI_ChannelType channel, uint8 Data);
/*It configures the SPI for transmission, this function as arguments receives a pointer to a constant structure where are all
 * the configuration parameters*/
void SPI_init(const SPI_ConfigType*);
void SPI_CSInactiveState(SPI_ChannelType channel,SPI_CSInactiveStateType csInactiveState);

/**
 * \brief Configuracion adicional del SPI en modo esclavo
 *
 * \param channel Canal SPI
 * \param frameSize Tamaño del frame
 * \param cpol Polaridad
 * \param cpha Fase
 */
void SPI_setSlave(SPI_ChannelType channel, uint32 frameSize, SPI_PolarityType cpol, SPI_PhaseType cpha);


#endif /* SPI_H_ */
