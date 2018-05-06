/**
	\file
	\brief
		This is the starter file of FlexTimer.
		In this file the FlexTimer is configured in overflow mode.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Add configuration structures.
 */



#include "FlexTimer.h"
#include "MK64F12.h"
//#include "LCD_Writing.h"
#define FirstValueinArray 0
#define ValuMODPWM 0x00FF
#define ValuMODOutput 0x01
#define ValueMODInputCapture 0xFFFE
#define DutyCycle50 2
#define Clock 21000000
#define ConvertPeriodo 0.000006103f
flo32 i;
uint8 FlexFlag;
flo32 Frecuencia;
uint32 PreviousValue;
uint32 Total;
uint32 Value;
uint32 dummie;
uint8 Flag;
/*This function activates when the FTM1_IRQHandler is activated we turn on a flag who say us when we got a take a value from our temperature sensor*/
void FTM0_IRQHandler()
{
	FTM0->SC &= ~FLEX_TIMER_TOF;
	FlexFlag = TRUE;
}

/*This function is use to get the diference between interruption how many times the flextimer count*/
void FTM2_IRQHandler()
{
	PreviousValue = Value;
	Value = FTM2->CONTROLS[0].CnV;
	Total = Value - PreviousValue;
	dummie = FTM2->CONTROLS[0].CnSC;
	FTM2->SC &= ~FTM_SC_TOF_MASK;
	FTM2->CONTROLS[0].CnSC &= ~FTM_CnSC_CHF_MASK;
}
/*In this function we update the value of ther motor is use in control_manual menu*/
void FlexTimer_updateCHValue(sint16 channelValue)
{
	//delay(1000);
	/**Assigns a new value for the duty cycle*/
	FTM0->CONTROLS[FirstValueinArray].CnV = channelValue;
}

/*Return the value of flexflag wich is assigned in the FTM1 interruption*/
uint8 getFlexFlag(void){

	return FlexFlag;
}
/*We send our specification to activated a determinate Flextimer*/
void FlexTimer_Init(const FTM_ConfigType* Config)
{
	FTM_MODE_Config(Config->FTM_CODE, Config->MOD_CODE);
}
/*We clean the value of FlexFlag*/
void clearFlexFlag(void)
{
	FlexFlag = FALSE;
}
/*We put a configuration for a FTM*/
void FTM_MODE_Config(FTM_Number FTM, FTM_MODE MODE)
{
	switch(FTM)
	{
		case(FTM_0):
				SIM->SCGC6 |= SIM_SCGC6_FTM0_MASK;
				switch(MODE)
				{
					case(FTM_CAPT_RE):
					FTM0->MODE |= FLEX_TIMER_WPDIS;
					FTM2->MODE |= FLEX_TIMER_FTMEN;
					FTM2->CONF |= FTM_CONF_BDMMODE(BDMMODE_3);
					FTM2->MOD |= ValueMODInputCapture;
					FTM2->CONTROLS[FirstValueinArray].CnSC |= FTM_CnSC_CHIE_MASK;
					FTM2->CONTROLS[FirstValueinArray].CnSC |= FLEX_TIMER_ELSA;
					FTM2->SC |= FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_128;
				break;
				case(FTM_OutputC_Toogle):
					FTM0->MODE |= FLEX_TIMER_WPDIS;
					FTM0->MODE |= FLEX_TIMER_FTMEN;
					FTM0->CONF |= FTM_CONF_BDMMODE(BDMMODE_3);
					FTM0->MOD = ValuMODOutput;
					FTM0->CONTROLS[FirstValueinArray].CnSC = FLEX_TIMER_MSA | FLEX_TIMER_ELSA;
					FTM0->CONTROLS[FirstValueinArray].CnV = ValuMODOutput;
					FTM0->SC |= FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_128|FLEX_TIMER_TOIE;
				break;
				case(FTM_PWM_Edge_Aligned):
					FTM0->MODE |= FLEX_TIMER_WPDIS;
					FTM0->MODE &= ~FLEX_TIMER_FTMEN;
					FTM0->MOD = ValuMODPWM;
					FTM0->CONTROLS[FirstValueinArray].CnSC = FLEX_TIMER_MSB | FLEX_TIMER_ELSB;
					FTM0->CONTROLS[FirstValueinArray].CnV = FTM0->MOD/DutyCycle50;
					FTM0->SC = FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_128;
					break;
				default:
				break;
			}
		break;
		case(FTM_1):
			SIM->SCGC6 |= SIM_SCGC6_FTM1_MASK;
			switch(MODE)
			{
				case(FTM_CAPT_RE):
					FTM1->MODE |= FLEX_TIMER_WPDIS;
					FTM1->MODE |= FLEX_TIMER_FTMEN;
					FTM1->CONF |= FTM_CONF_BDMMODE(BDMMODE_3);
					FTM1->MOD |= ValueMODInputCapture;
					FTM1->CONTROLS[FirstValueinArray].CnSC |= FTM_CnSC_CHIE_MASK;
					FTM1->CONTROLS[FirstValueinArray].CnSC |= FLEX_TIMER_ELSA;
					FTM1->SC |= FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_128;
			break;
				case(FTM_OutputC_Toogle):
					FTM1->MODE |= FLEX_TIMER_WPDIS;
					FTM1->MODE &= ~FLEX_TIMER_FTMEN;
					FTM1->CONF |= FTM_CONF_BDMMODE(BDMMODE_3);
					FTM1->MOD = ValuMODOutput;
					FTM1->CONTROLS[FirstValueinArray].CnSC = FLEX_TIMER_MSA | FLEX_TIMER_ELSA;
					FTM1->CONTROLS[FirstValueinArray].CnV = ValuMODOutput;
					FTM1->SC |= FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_128|FLEX_TIMER_TOIE;
			break;
				case(FTM_PWM_Edge_Aligned):
					FTM1->MODE |= FLEX_TIMER_WPDIS;
					FTM1->MODE &= ~FLEX_TIMER_FTMEN;
					FTM1->MOD = ValuMODPWM;
					FTM1->CONTROLS[FirstValueinArray].CnSC = FLEX_TIMER_MSB | FLEX_TIMER_ELSB;
					FTM1->CONTROLS[FirstValueinArray].CnV = FTM1->MOD/DutyCycle50;
					FTM1->SC = FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_128;
			break;
		default:
			break;
	}
	break;

	case(FTM_2):
		SIM->SCGC6 |= SIM_SCGC6_FTM2_MASK;
		switch(MODE)
		{
			case(FTM_CAPT_RE):
			FTM2->MODE |= FLEX_TIMER_WPDIS;
			FTM2->MODE |= FLEX_TIMER_FTMEN;
			FTM2->CONF |= FTM_CONF_BDMMODE(BDMMODE_3);
			FTM2->MOD |= 0xFFFE;
			FTM2->CONTROLS[FirstValueinArray].CnSC |= FTM_CnSC_CHIE_MASK;
			FTM2->CONTROLS[FirstValueinArray].CnSC |= FLEX_TIMER_ELSA;
			FTM2->SC |= FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_128;
			break;
			case(FTM_OutputC_Toogle):
			FTM2->MODE |= FLEX_TIMER_WPDIS;
			FTM2->MODE |= FLEX_TIMER_FTMEN;
			FTM2->CONF |= FTM_CONF_BDMMODE(BDMMODE_3);
			FTM2->MOD = ValuMODOutput;
			FTM2->CONTROLS[FirstValueinArray].CnSC = FLEX_TIMER_MSA | FLEX_TIMER_ELSA;
			FTM2->CONTROLS[FirstValueinArray].CnV = ValuMODOutput;
			FTM2->SC |= FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_128|FLEX_TIMER_TOIE;
			break;
		case(FTM_PWM_Edge_Aligned):
			FTM2->MODE |= FLEX_TIMER_WPDIS;
			FTM2->MODE &= ~FLEX_TIMER_FTMEN;
			FTM2->MOD = ValuMODPWM;
			FTM2->CONTROLS[FirstValueinArray].CnSC = FLEX_TIMER_MSB | FLEX_TIMER_ELSB;
			FTM2->CONTROLS[FirstValueinArray].CnV = FTM0->MOD/DutyCycle50;
			FTM2->SC = FLEX_TIMER_CLKS_1|FLEX_TIMER_PS_128;
			break;
		default:
			break;
	}
			break;
		default:
			break;
	}
}
/*We do the convertion to frequency from the value obtained from FTM2 interruption*/
flo32 FlexTimerConvertVALUE()
{
	i=FlexTimer_GetCounter();
	Frecuencia=(Clock/128)*i;
	Frecuencia=i*ConvertPeriodo;
	Frecuencia=1/Frecuencia;
	return Frecuencia;
}
/*Assign the value of number of count from FTM2 interruptions*/

flo32 FlexTimer_GetCounter(void)
{
	return Total;
}
