

#include "MK64F12.h"
#include "SPI.h"
#include "GPIO.h"
#include "DataTypeDefinitions.h"
#include  "GlobalFunctions.h"


uint8 ErrorFlagSPI = FALSE;


 void SPI_clk(SPI_ChannelType channel)
{
	switch (channel)
	{
		case SPI_0:
			SIM->SCGC6 |= SPI0_CLOCK_GATING;
			break;
		case SPI_1:
			SIM->SCGC6 |= SPI1_CLOCK_GATING;
			break;
		default:
			SIM->SCGC3 |= SPI2_CLOCK_GATING;
			break;
	}
}

 void SPI_setMaster(SPI_ChannelType channel, SPI_MasterType masterOrSlave)
{
	switch(channel)
	{
		case SPI_0:
			if(masterOrSlave)
				SPI0->MCR |= SPI_MCR_MSTR_MASK;
			else
				SPI0->MCR &= ~SPI_MCR_MSTR_MASK;
			break;
		case SPI_1:
			if(masterOrSlave)
				SPI1->MCR |= SPI_MCR_MSTR_MASK;
			else
				SPI1->MCR &= ~SPI_MCR_MSTR_MASK;
			break;
		default:
			if(masterOrSlave)
				SPI2->MCR |= SPI_MCR_MSTR_MASK;
			else
				SPI2->MCR &= ~SPI_MCR_MSTR_MASK;
			break;
	}

}

 void SPI_enable(SPI_ChannelType channel)
{
	switch(channel)
	{
		case SPI_0:
			SPI0->MCR &= ~SPI_MCR_MDIS_MASK;
			break;
		case SPI_1:
			SPI1->MCR &= ~SPI_MCR_MDIS_MASK;
			break;
		default:
			SPI2->MCR &= ~SPI_MCR_MDIS_MASK;
	}

}

 void SPI_fIFO(SPI_ChannelType channel, SPI_EnableFIFOType enableOrDisable)
{
	switch(channel)
	{
		case SPI_0:
			if(!enableOrDisable){
				SPI0->MCR |= SPI_MCR_DIS_RXF_MASK |
							SPI_MCR_DIS_TXF_MASK |
							SPI_MCR_CLR_RXF_MASK |
							SPI_MCR_CLR_TXF_MASK;
			}
			else{
				SPI0->MCR &= ~(SPI_MCR_DIS_RXF_MASK | SPI_MCR_DIS_TXF_MASK)|SPI_MCR_CLR_RXF_MASK|SPI_MCR_CLR_TXF_MASK;}
			break;
		case SPI_1:
			if(!enableOrDisable){
				SPI1->MCR |= SPI_MCR_DIS_RXF_MASK |
							SPI_MCR_DIS_TXF_MASK |
							SPI_MCR_CLR_RXF_MASK |
							SPI_MCR_CLR_TXF_MASK;}
			else{
				SPI1->MCR &= ~(SPI_MCR_DIS_RXF_MASK |
							SPI_MCR_DIS_TXF_MASK)|SPI_MCR_CLR_RXF_MASK|SPI_MCR_CLR_TXF_MASK;}
			break;
		default:
			if(!enableOrDisable){
				SPI2->MCR |= SPI_MCR_DIS_RXF_MASK |
				SPI_MCR_DIS_TXF_MASK |
				SPI_MCR_CLR_RXF_MASK |
				SPI_MCR_CLR_TXF_MASK;}
			else{
				SPI2->MCR &= ~(SPI_MCR_DIS_RXF_MASK |
						SPI_MCR_DIS_TXF_MASK)|SPI_MCR_CLR_RXF_MASK|SPI_MCR_CLR_TXF_MASK;}
			break;

	}


}

 void SPI_clockPolarity(SPI_ChannelType channel, SPI_PolarityType cpol)
{
	switch (channel)
	{
		case SPI_0:
			if(cpol)
				SPI0->CTAR[0] |= SPI_CTAR_CPOL_MASK;
			else
				SPI0->CTAR[0] &= ~SPI_CTAR_CPOL_MASK;
			break;
		case SPI_1:
			if(cpol)
				SPI1->CTAR[0] |= SPI_CTAR_CPOL_MASK;
			else
				SPI1->CTAR[0] &= ~SPI_CTAR_CPOL_MASK;
			break;
		default:
			if(cpol)
				SPI2->CTAR[0] |= SPI_CTAR_CPOL_MASK;
			else
				SPI2->CTAR[0] &= ~SPI_CTAR_CPOL_MASK;
			break;
	}

}

 void SPI_frameSize(SPI_ChannelType channel, uint32 frameSize)
{
	switch (channel)
	{
		case SPI_0:
			SPI0->CTAR[0] &= ~SPI_CTAR_FMSZ_MASK;
			SPI0->CTAR[0] |= frameSize;
			break;
		case SPI_1:
			SPI1->CTAR[0] &= ~SPI_CTAR_FMSZ_MASK;
			SPI1->CTAR[0] |= frameSize;
			break;
		default:
			SPI2->CTAR[0] &= ~SPI_CTAR_FMSZ_MASK;
			SPI2->CTAR[0] |= frameSize;
			break;
	}

}

 void SPI_clockPhase(SPI_ChannelType channel, SPI_PhaseType cpha)
{
	switch (channel)
	{
		case SPI_0:
			if(cpha)
				SPI0->CTAR[0] |= SPI_CTAR_CPHA_MASK;
			else
				SPI0->CTAR[0] &= ~SPI_CTAR_CPHA_MASK;
			break;
		case SPI_1:
			if(cpha)
				SPI1->CTAR[0] |= SPI_CTAR_CPHA_MASK;
			else
				SPI1->CTAR[0] &= ~SPI_CTAR_CPHA_MASK;
			break;
		default:
			if(cpha)
				SPI2->CTAR[0] |= SPI_CTAR_CPHA_MASK;
			else
				SPI2->CTAR[0] &= ~SPI_CTAR_CPHA_MASK;
			break;
	}

}

 void SPI_baudRate(SPI_ChannelType channel, uint32 baudRate,uint8 doubleBaudRate)
{
	switch (channel)
	{
		case SPI_0:
			if(doubleBaudRate)
				SPI0->CTAR[0] |= SPI_CTAR_DBR_MASK|baudRate;
			else
				SPI0->CTAR[0] |= 0|baudRate;
			break;
		case SPI_1:
			if(doubleBaudRate)
				SPI1->CTAR[0] |= SPI_CTAR_DBR_MASK|baudRate;
			else
				SPI1->CTAR[0] |= 0|baudRate;
			break;
		default:
			if(doubleBaudRate)
				SPI2->CTAR[0] |= SPI_CTAR_DBR_MASK|baudRate;
			else
				SPI2->CTAR[0] |= 0|baudRate;
			break;
	}

}

 void SPI_mSBFirst(SPI_ChannelType channel, SPI_LSMorMSBType msb)
{
	switch (channel)
	{
		case SPI_0:
			if(msb)
				SPI0->CTAR[0] |= SPI_CTAR_LSBFE_MASK;
			else
				SPI0->CTAR[0] &= ~SPI_CTAR_LSBFE_MASK;
			break;
		case SPI_1:
			if(msb)
				SPI1->CTAR[0] |= SPI_CTAR_LSBFE_MASK;
			else
				SPI1->CTAR[0] &= ~SPI_CTAR_LSBFE_MASK;
			break;
		default:
			if(msb)
				SPI2->CTAR[0] |= SPI_CTAR_LSBFE_MASK;
			else
				SPI2->CTAR[0] &= ~SPI_CTAR_LSBFE_MASK;
			break;
	}
}

void SPI_startTranference(SPI_ChannelType channel)
{
	switch (channel)
	{
		case SPI_0:
			SPI0->MCR &= ~SPI_MCR_HALT_MASK;
			break;
		case SPI_1:
			SPI1->MCR &= ~SPI_MCR_HALT_MASK;
			break;
		default:
			SPI2->MCR &= ~SPI_MCR_HALT_MASK;
			break;
	}
}

void SPI_stopTranference(SPI_ChannelType channel)
{
	switch (channel)
	{
		case SPI_0:
			SPI0->MCR |= SPI_MCR_HALT_MASK;
			break;
		case SPI_1:
			SPI1->MCR |= SPI_MCR_HALT_MASK;
			break;
		default:
			SPI2->MCR |= SPI_MCR_HALT_MASK;
			break;
	}
}


uint8 SPI_errorFlag(void)
{
	return(ErrorFlagSPI);
}


uint8 SPI_transfer(SPI_ChannelType channel, uint8 Data)
{
	uint8 receivedData=0;

	ErrorFlagSPI = FALSE;

	switch(channel)
	{
		case SPI_0:
			SPI0->MCR &= ~SPI_MCR_HALT_MASK;
			SPI0->PUSHR = (Data) | SPI_PUSHR_EOQ_MASK;

			while((SPI0->SR & SPI_SR_TCF_MASK)==0 && FALSE == ErrorFlagSPI);
			SPI0->SR |= SPI_SR_TCF_MASK;
			receivedData = SPI0->POPR & 0xff;
			SPI0->MCR |= SPI_MCR_HALT_MASK;
			break;
		case SPI_1:
			SPI1->MCR &= ~SPI_MCR_HALT_MASK;
			SPI1->PUSHR = (Data);

			while((SPI1->SR & SPI_SR_TCF_MASK)==0 && FALSE == ErrorFlagSPI);
			SPI1->SR |= SPI_SR_TCF_MASK;
			receivedData = SPI1->POPR&0xff;
			SPI1->MCR |= SPI_MCR_HALT_MASK;
			break;
		default:
			SPI2->MCR &= ~SPI_MCR_HALT_MASK;
			SPI2->PUSHR = (Data);

			while((SPI2->SR & SPI_SR_TCF_MASK)==0 && FALSE == ErrorFlagSPI);
			SPI2->SR |= SPI_SR_TCF_MASK;
			receivedData = SPI2->POPR&0xff;
			SPI2->MCR |= SPI_MCR_HALT_MASK;
			break;
	}
	return receivedData;

}

void SPI_init(const SPI_ConfigType* SPI_Config)
{
	SPI_clk(SPI_Config->SPI_Channel);
	GPIO_clockGating(SPI_Config->GPIOForSPI.GPIO_portName);
	GPIO_pinControlRegister(SPI_Config->GPIOForSPI.GPIO_portName,SPI_Config->GPIOForSPI.SPI_CLK,&(SPI_Config->GPIOForSPI.pinConttrolRegister));
	GPIO_pinControlRegister(SPI_Config->GPIOForSPI.GPIO_portName,SPI_Config->GPIOForSPI.SPI_SOUT,&(SPI_Config->GPIOForSPI.pinConttrolRegister));
	GPIO_pinControlRegister(SPI_Config->GPIOForSPI.GPIO_portName,SPI_Config->GPIOForSPI.SPI_SIN,&(SPI_Config->GPIOForSPI.pinConttrolRegister));

	if (!SPI_Config->SPI_Master)
		GPIO_pinControlRegister(SPI_Config->GPIOForSPI.GPIO_portName,SPI_Config->GPIOForSPI.SPI_CS,&(SPI_Config->GPIOForSPI.pinConttrolRegister));
	else
		GPIO_pinControlRegister(SPI_Config->GPIOForSPI.GPIO_portName,SPI_Config->GPIOForSPI.SPI_CS,&(SPI_Config->GPIOForSPI.pinConttrolRegisterCS));
	SPI_enable(SPI_Config->SPI_Channel);
	SPI_setMaster(SPI_Config->SPI_Channel,SPI_Config->SPI_Master);
	SPI_fIFO(SPI_Config->SPI_Channel,SPI_Config->SPI_EnableFIFO);
	SPI_clockPolarity(SPI_Config->SPI_Channel,SPI_Config->SPI_Polarity);
	SPI_frameSize(SPI_Config->SPI_Channel,SPI_Config->frameSize);
	SPI_clockPhase(SPI_Config->SPI_Channel,SPI_Config->SPI_Phase);
	SPI_baudRate(SPI_Config->SPI_Channel,SPI_Config->baudrate,SPI_Config->doubleBaudRate);
	SPI_mSBFirst(SPI_Config->SPI_Channel,SPI_MSB);
	SPI_CSInactiveState(SPI_Config->SPI_Channel,SPI_Config->idleState);

	if (!SPI_Config->SPI_Master)
		SPI_setSlave(SPI_Config->SPI_Channel, SPI_Config->frameSize, SPI_Config->SPI_Polarity, SPI_Config->SPI_Phase);
	else
		{
			GPIO_setPIN(SPI_Config->GPIOForSPI.GPIO_portName,SPI_Config->GPIOForSPI.SPI_CS);
			GPIO_dataDirectionPIN(SPI_Config->GPIOForSPI.GPIO_portName, GPIO_OUTPUT, SPI_Config->GPIOForSPI.SPI_CS);

		}
}

void SPI_CSInactiveState(SPI_ChannelType channel, SPI_CSInactiveStateType clkInactiveState)
{
	switch(channel)
	{
		case SPI_0:
			if(clkInactiveState)
				SPI0->MCR |= SPI_MCR_PCSIS_MASK;
			else
				SPI0->MCR &= ~(SPI_MCR_PCSIS_MASK);
			break;
		case SPI_1:
			if(clkInactiveState)
				SPI1->MCR |= SPI_MCR_PCSIS_MASK;
			else
				SPI1->MCR &= ~(SPI_MCR_PCSIS_MASK);
			break;
		default:
			if(clkInactiveState)
				SPI2->MCR |= SPI_MCR_PCSIS_MASK;
			else
				SPI2->MCR &= ~(SPI_MCR_PCSIS_MASK);
			break;
	}

}

void SPI_setSlave(SPI_ChannelType channel, uint32 frameSize, SPI_PolarityType cpol, SPI_PhaseType cpha) {
	switch (channel) {
		case SPI_0:
			SPI0->RSER |= SPI_RSER_TCF_RE_MASK;

			SPI0->CTAR_SLAVE[0] = 0;

			SPI0->CTAR_SLAVE[0]|= frameSize;

			if(cpol)
				SPI0->CTAR_SLAVE[0]|= SPI_CTAR_CPOL_MASK;
			else
				SPI0->CTAR_SLAVE[0] &= ~SPI_CTAR_CPOL_MASK;

			if(cpha)
				SPI0->CTAR_SLAVE[0] |= SPI_CTAR_CPHA_MASK;
			else
				SPI0->CTAR_SLAVE[0] &= ~SPI_CTAR_CPHA_MASK;

			break;
		case SPI_1:
			SPI1->RSER |= SPI_RSER_TCF_RE_MASK;

			SPI1->CTAR_SLAVE[0] = 0;

			SPI1->CTAR_SLAVE[0]|= frameSize;

			if(cpol)
				SPI1->CTAR_SLAVE[0] |= SPI_CTAR_CPOL_MASK;
			else
				SPI1->CTAR_SLAVE[0] &= ~SPI_CTAR_CPOL_MASK;

			if(cpha)
				SPI1->CTAR_SLAVE[0]|= SPI_CTAR_CPHA_MASK;
			else
				SPI1->CTAR_SLAVE[0] &= ~SPI_CTAR_CPHA_MASK;

			break;
		default:
			SPI2->RSER |= SPI_RSER_TCF_RE_MASK;

			SPI2->CTAR_SLAVE[0] = 0;

			SPI2->CTAR_SLAVE[0] |= frameSize;

			if(cpol)
				SPI2->CTAR_SLAVE[0] |= SPI_CTAR_CPOL_MASK;
			else
				SPI2->CTAR_SLAVE[0] &= ~SPI_CTAR_CPOL_MASK;

			if(cpha)
				SPI2->CTAR_SLAVE[0] |= SPI_CTAR_CPHA_MASK;
			else
				SPI2->CTAR_SLAVE[0] &= ~SPI_CTAR_CPHA_MASK;

			break;
	}
}

void SPI_startTranference2(SPI_ChannelType channel)
{
	switch (channel)
	{
		case SPI_0:
			SPI0->MCR &= ~SPI_MCR_HALT_MASK;
			break;
		case SPI_1:
			SPI1->MCR &= ~SPI_MCR_HALT_MASK;
			break;
		default:
			SPI2->MCR &= ~SPI_MCR_HALT_MASK;
			break;
	}
}

void SPI_stopTranference2(SPI_ChannelType channel)
{
	switch (channel)
	{
		case SPI_0:
			SPI0->MCR |= SPI_MCR_HALT_MASK;
			break;
		case SPI_1:
			SPI1->MCR |= SPI_MCR_HALT_MASK;
			break;
		default:
			SPI2->MCR |= SPI_MCR_HALT_MASK;
			break;
	}
}
void SPI_sendOneByte(uint8 Data)
{
	SPI0->PUSHR = (Data);
	while(FALSE == (SPI0->SR & SPI_SR_TCF_MASK));
	SPI0->SR |= SPI_SR_TCF_MASK;
}
