/*
 * S25FLXXX.h
 *
 *  Created on: 11/10/2017
 *      Author: jlpe
 */

#ifndef S25FLXXX_H_
#define S25FLXXX_H_
#include "DataTypeDefinitions.h"
#include "SPI.h"
#include "GPIO.h"

#define READ_CMD 0x03
#define WREN_CMD 0x06
#define PP_CDM 0x02
#define READ_ID_CMD 0x90
#define FATS_READ_CMD 0x0B
#define READ_SR1_CMD 0x05
#define READ_SR2_CMD 0x35
#define READ_SR3_CMD 0x33
#define RCR_CMD 0x35

#define CHIP_ERASE_CMD 0x60
#define WRR_CMD 0x01
#define P8E_CMD 0x40
#define SECTOR_4KB_ERASE 0X20

#define STATUS_REGISTER_1 0x01
#define STATUS_REGISTER_2 0x02
#define STATUS_REGISTER_3 0x03

#define MEMORY_IS_BUSY 0x01



typedef union
{
	uint32 uid;
	struct
	{
		uint32 uidByte0 : 8;
		uint32 uidByte1 : 8;
		uint32 uidByte2 : 8;
		uint32 uidByte3 : 8;
	}uidBytes;
}UID_Type;

typedef struct
{
	uint8 schedule;
	UID_Type userUID;
	uint8 date;
	uint8 month;
	uint8 year;
	//uint8 CRC;
}UID_MemoryType;

typedef struct
{
	uint8 UID_Byte3;
	uint8 UID_Byte2;
	uint8 UID_Byte1;
	uint8 UID_Byte0;
	uint8 hours;
	uint8 minutes;
	uint8 seconds;
	uint8 day;
	uint8 date;
	uint8 month;
	uint8 year;
	uint8 source;
}S25FLXXX_EventType;


typedef union
{
	uint32 date;
	struct
	{
		uint32 date  : 8;
		uint32 month : 8;
		uint32 year  : 8;

	}dateStructType;
}dateUnionType;

typedef struct
{
	dateUnionType initalDate;
	dateUnionType finalDate;
} holidayPeriodType;



typedef const struct
{
	SPI_ChannelType SPI_channel;
	GPIO_portNameType PortName;
	uint8 chipEnableBit;

} MemoryPortType;


typedef union {
	uint32 address;
	struct
	{
		uint32 addressByte0   :8;
		uint32 addressByte1   :8;
		uint32 addressByte2   :8;
		uint32 addressByte3   :8;
	}addressByByte;
}S25FLXXX_MemoryAddressType;

typedef union {
	uint32 address;
	struct
	{
		uint8 addressByte0   :8;
		uint8 addressByte1   :8;
	}addressByByte;
}GUITAR_DATA;

typedef union
{
	uint16 address;
	struct
	{
		uint16 addressByte0 :8;
		uint16 addressByte1 :8;
	}addressByByte;

}S25FLXXX_AddressPointerType;

typedef union
{
	uint32 address;
	struct
	{
		uint16 scheduleByte0 :8;
		uint16 scheduleByte1 :8;
		uint16 scheduleByte2 :8;
		uint16 scheduleByte3 :8;
	}scheduleAddress;

}S25FLXXX_ScheduleAddressType;

void S25FLXXX_writeBytes(uint8 *,S25FLXXX_MemoryAddressType* address, MemoryPortType*, uint32 numberOfBytes);
void S25FLXXX_writeByte(uint8 byteToWrite, uint8 byteToWrite2, S25FLXXX_MemoryAddressType* address, MemoryPortType* SPIChannel);



void S25FLXXX_readBytes(uint8 *,S25FLXXX_MemoryAddressType*, MemoryPortType*, uint32);
uint8 S25FLXXX_readByte(S25FLXXX_MemoryAddressType* address, MemoryPortType*);

uint8 S25FLXXX_readStatusRegister(uint8 statusRegister,MemoryPortType* SPIChannel);
void S25FLXXX_writeStatusRegister(uint8 data,MemoryPortType* SPIChannel);

void S25FLXXX_erase4KbSector(S25FLXXX_MemoryAddressType*,MemoryPortType* SPIChannel);


uint8 S25FLXXX_ConfigurationRegister(void);

void S25FLXXX_chipErase(MemoryPortType* SPIChannel);

 void S25FLXXX_EraseMemory(MemoryPortType* SPIChannel);
 void S25FLXXX_write(uint8 byteToWrite,S25FLXXX_MemoryAddressType* address, MemoryPortType* SPIChannel);
 uint32 Looper_Memory(S25FLXXX_MemoryAddressType address, uint32 Counter, MemoryPortType SPIChannel);
 uint8 MMU_waitingFunction();
#endif /* S25FLXXX_H_ */
