/*
 * S25FLXXX.c
 *
 *  Created on: Dec 16, 2014
 *      Author: Luis
 */



#include "S25FLXXX.h"
#include "FlexTimer.h"
#include "ADCDriver.h"
#include "GPIO.h"
#include "DAC.h"
uint16 PageValue;
uint16 AddressValue;
uint16 DacValue;
uint16 DacValue2;
uint16 Dac;
GUITAR_DATA Data_Bit = {0};
//#include "GlobalFunctions.h"
const ADC_ConfigType ADC_Memory  = {
		0,
		ADC0Type,
		NORMAL_POWER,
		RATIO1,
		SHORT_SAMPLE,
		CONV16,
		BUSCLK
};
void S25FLXXX_writeEvent(S25FLXXX_EventType* event, S25FLXXX_MemoryAddressType* address,MemoryPortType* SPIChannel)
{
	GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	SPI_transfer(SPIChannel->SPI_channel, WREN_CMD);
	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	SPI_transfer(SPIChannel->SPI_channel, PP_CDM);

	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte2);
	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte1);
	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte0);

	SPI_transfer(SPIChannel->SPI_channel, event->UID_Byte3);
	SPI_transfer(SPIChannel->SPI_channel, event->UID_Byte2);
	SPI_transfer(SPIChannel->SPI_channel, event->UID_Byte1);
	SPI_transfer(SPIChannel->SPI_channel, event->UID_Byte0);

	SPI_transfer(SPIChannel->SPI_channel, event->hours);
	SPI_transfer(SPIChannel->SPI_channel, event->minutes);
	SPI_transfer(SPIChannel->SPI_channel, event->seconds);
	SPI_transfer(SPIChannel->SPI_channel, event->day);
	SPI_transfer(SPIChannel->SPI_channel, event->date);
	SPI_transfer(SPIChannel->SPI_channel, event->month);
	SPI_transfer(SPIChannel->SPI_channel, event->year);
	SPI_transfer(SPIChannel->SPI_channel, event->source);


	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
}







void S25FLXXX_writeSchedule(S25FLXXX_ScheduleAddressType* pointer,S25FLXXX_MemoryAddressType* address, MemoryPortType* SPIChannel)
{
	GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	SPI_transfer(SPIChannel->SPI_channel, WREN_CMD);
	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	SPI_transfer(SPIChannel->SPI_channel, PP_CDM);
	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte2);
	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte1);
	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte0);

	SPI_transfer(SPIChannel->SPI_channel, pointer->scheduleAddress.scheduleByte0);
	SPI_transfer(SPIChannel->SPI_channel, pointer->scheduleAddress.scheduleByte1);
	SPI_transfer(SPIChannel->SPI_channel, pointer->scheduleAddress.scheduleByte2);
	SPI_transfer(SPIChannel->SPI_channel, pointer->scheduleAddress.scheduleByte3);

	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
}

void S25FLXXX_writePointer(S25FLXXX_AddressPointerType* pointer,S25FLXXX_MemoryAddressType* address, MemoryPortType* SPIChannel)
{
	GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	SPI_transfer(SPIChannel->SPI_channel, WREN_CMD);
	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	SPI_transfer(SPIChannel->SPI_channel, PP_CDM);
	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte2);
	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte1);
	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte0);

	SPI_transfer(SPIChannel->SPI_channel, pointer->addressByByte.addressByte0);
	SPI_transfer(SPIChannel->SPI_channel, pointer->addressByByte.addressByte1);

	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
}

void S25FLXXX_erase4KbSector(S25FLXXX_MemoryAddressType* address,MemoryPortType* SPIChannel)
{
	GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	SPI_transfer(SPIChannel->SPI_channel, WREN_CMD);
	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	SPI_transfer(SPIChannel->SPI_channel, SECTOR_4KB_ERASE);

	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte2);
	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte1);
	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte0);
	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
}

void S25FLXXX_writeStatusRegister(uint8 data,MemoryPortType* SPIChannel)
{
/*This function only writes the status register number 1*/
    GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
    SPI_transfer(SPIChannel->SPI_channel, WREN_CMD);
	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);

    GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
    SPI_transfer(SPIChannel->SPI_channel, WRR_CMD);

    SPI_transfer(SPIChannel->SPI_channel, data);
	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
}

void S25FLXXX_chipErase(MemoryPortType* SPIChannel)
{

    GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
    SPI_transfer(SPIChannel->SPI_channel, WREN_CMD);
	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
    GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
    SPI_transfer(SPIChannel->SPI_channel, CHIP_ERASE_CMD);
	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
}

uint8 S25FLXXX_ConfigurationRegister(void)
{
	uint8 recivedData;
		GPIO_clearPIN(GPIO_B, BIT5);
		SPI_transfer(SPI_2, RCR_CMD);

		recivedData = SPI_transfer(SPI_2, 0x00);
		GPIO_setPIN(GPIO_B, BIT5);
		return(recivedData);
}

uint8 S25FLXXX_readStatusRegister(uint8 statusRegister, MemoryPortType* SPIChannel)
{
	uint8 recivedData;

	switch(statusRegister)
	{
		case STATUS_REGISTER_1:
			GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
			recivedData = SPI_transfer(SPIChannel->SPI_channel, READ_SR1_CMD);

			recivedData = SPI_transfer(SPIChannel->SPI_channel, 0x00);
			GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
			break;
		case STATUS_REGISTER_2:
			GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
			recivedData = SPI_transfer(SPIChannel->SPI_channel, READ_SR2_CMD);

			recivedData = SPI_transfer(SPIChannel->SPI_channel, 0x00);
			GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
			break;
		default:
			GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
			recivedData = SPI_transfer(SPIChannel->SPI_channel, READ_SR3_CMD);

			recivedData = SPI_transfer(SPIChannel->SPI_channel, 0x00);
			GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
			break;
	}

	return(recivedData);
}

void S25FLXXX_readID(uint8* mfgAndID)
{
	uint8 recivedData;
	GPIO_clearPIN(GPIO_B, BIT5);
	SPI_transfer(SPI_2, READ_ID_CMD);
	SPI_transfer(SPI_2, 0x00);
	SPI_transfer(SPI_2, 0x00);
	SPI_transfer(SPI_2, 0x00);
	recivedData = SPI_transfer(SPI_2, 0x00);
	recivedData = SPI_transfer(SPI_2, 0x00);
	mfgAndID[0] =recivedData;
	recivedData = SPI_transfer(SPI_2, 0x00);
	mfgAndID[1] = recivedData;
	GPIO_setPIN(GPIO_B, BIT5);

}

void S25FLXXX_writeByte(uint8 byteToWrite,S25FLXXX_MemoryAddressType* address, MemoryPortType* SPIChannel)
{
	GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	SPI_transfer(SPIChannel->SPI_channel, WREN_CMD);
	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	GPIO_clearPIN(SPIChannel->PortName,SPIChannel->chipEnableBit);
	SPI_transfer(SPIChannel->SPI_channel, PP_CDM);
	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte2);
	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte1);
	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte0);
	SPI_transfer(SPIChannel->SPI_channel, byteToWrite);
	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
}


void S25FLXXX_writeBytes(uint8* bytesToWrite,S25FLXXX_MemoryAddressType* address, MemoryPortType* SPIChannel, uint32 numberOfBytes)
{
	uint32 index=0;
    GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
    SPI_transfer(SPIChannel->SPI_channel, WREN_CMD);
	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	GPIO_clearPIN(SPIChannel->PortName,SPIChannel->chipEnableBit);
	SPI_transfer(SPIChannel->SPI_channel, PP_CDM);
	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte2);
	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte1);
	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte0);
	for(index=0;index <=numberOfBytes-1; index++ )
	{
		SPI_transfer(SPIChannel->SPI_channel, bytesToWrite[index]);
	}
	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
}


void S25FLXXX_writeUID(UID_MemoryType* uid ,S25FLXXX_MemoryAddressType* address, MemoryPortType* SPIChannel)
{
	GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	SPI_transfer(SPIChannel->SPI_channel, WREN_CMD);
	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	SPI_transfer(SPIChannel->SPI_channel, PP_CDM);
	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte2);
	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte1);
	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte0);

	SPI_transfer(SPIChannel->SPI_channel, uid->year);
	SPI_transfer(SPIChannel->SPI_channel, uid->month);
	SPI_transfer(SPIChannel->SPI_channel, uid->date);
	SPI_transfer(SPIChannel->SPI_channel, uid->schedule);
	SPI_transfer(SPIChannel->SPI_channel, uid->userUID.uidBytes.uidByte0);
	SPI_transfer(SPIChannel->SPI_channel, uid->userUID.uidBytes.uidByte1);
	SPI_transfer(SPIChannel->SPI_channel, uid->userUID.uidBytes.uidByte2);
	SPI_transfer(SPIChannel->SPI_channel, uid->userUID.uidBytes.uidByte3);

	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
}


uint8 S25FLXXX_readByte(S25FLXXX_MemoryAddressType* address, MemoryPortType* SPIChannel)
{
	uint8 receivedData=0;

	GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	SPI_transfer(SPIChannel->SPI_channel, READ_CMD);
	receivedData=SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte2);
	receivedData=SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte1);
	receivedData=SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte0);
	receivedData= SPI_transfer(SPIChannel->SPI_channel, 0x00);
	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	return receivedData;
}

void S25FLXXX_readBytes(uint8* bytesToRead,S25FLXXX_MemoryAddressType* address, MemoryPortType* SPIChannel, uint32 numberOfBytes)
{
	uint32 index=0;
	uint8 receivedData=0;

	GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
	SPI_transfer(SPIChannel->SPI_channel, READ_CMD);
	receivedData=SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte2);
	receivedData=SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte1);
	receivedData=SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte0);
	for(index=0;index <=numberOfBytes-1; index++ )
	{
		receivedData= SPI_transfer(SPIChannel->SPI_channel, 0x00);
		bytesToRead[index] =receivedData;
	}
	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);


}



 uint16 GetPage(void)
{
	return PageValue;
}
 uint16 GetAddress(void)
{
	return AddressValue;
}

 void S25FLXXX_EraseMemory(MemoryPortType* SPIChannel)
 {
 	GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
 	SPI_transfer(SPIChannel->SPI_channel, WREN_CMD);
 	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
 	GPIO_clearPIN(SPIChannel->PortName,SPIChannel->chipEnableBit);
 	SPI_transfer(SPIChannel->SPI_channel, 0xC7);
 	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
 }

 void S25FLXXX_write(uint8 byteToWrite,S25FLXXX_MemoryAddressType* address, MemoryPortType* SPIChannel)
 {
 	GPIO_clearPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
 	SPI_transfer(SPIChannel->SPI_channel, WREN_CMD);
 	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
 	GPIO_clearPIN(SPIChannel->PortName,SPIChannel->chipEnableBit);
 	SPI_transfer(SPIChannel->SPI_channel, PP_CDM);
 	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte2);
 	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte1);
 	SPI_transfer(SPIChannel->SPI_channel, address->addressByByte.addressByte0);
 	SPI_transfer(SPIChannel->SPI_channel, byteToWrite);
 	GPIO_setPIN(SPIChannel->PortName, SPIChannel->chipEnableBit);
 }

 uint32 Looper_Memory(S25FLXXX_MemoryAddressType address, uint32 Counter, MemoryPortType SPIChannel)
 {
	DacValue = S25FLXXX_readByte(&address, &SPIChannel);
	MMU_waitingFunction();
 	address.address += 1;
 	DacValue2 = S25FLXXX_readByte(&address,&SPIChannel);
 	MMU_waitingFunction();
 	address.address += 1;
 	Data_Bit.addressByByte.addressByte0=DacValue;
 	Data_Bit.addressByByte.addressByte1=DacValue2;
 	DAC0_write(Data_Bit.address);
 	/*If Counter2 is in his Max Value we restarted */
 	if (address.address >= Counter)
 		address.address=0;
 	return address.address;
 }

