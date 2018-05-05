/*
 * ADCDriver.c
 *
 *  Created on: Mar 16, 2018
 *      Author: d
 */

#include "ADCDriver.h"
#include "MK64F12.h"
#include "GPIO.h"
#include "DataTypeDefinitions.h"
#include "FlexTimer.h"
#define INITIALCFG1 0x14
#define INITIALSC3 0x07
#define INITIALSC1 0x0C
#define ADC_LOWRESULT 1
#define ADCPIN 2
#define MAXVOLTAGE 3.3
#define MAXBITS 65535
#define TEMPSLOPE 0.01F
#define FAHRENHEITFACTOR 1.8F
#define FAHRENHEITCONST 32.2F
#define DECIMALFACTOR 100
#define CLKSHIFT 5
#define CONVSHIFT 2
#define LOWPOWERSHIFT 6
#define SAMPSHIFT 4

static float64 ReturnTemp;
static uint32 TemperatureC;
static float64 TemperatureF;

ADC_ConfigType* ADC_Config;

void ADC_clk(ADCNoType ADCNumber){
	/*This function turns on the clock gating on each ADC*/
	switch(ADCNumber){
	case ADC0Type:
		SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
		break;
	case ADC1Type:
		SIM->SCGC3 |= SIM_SCGC3_ADC1_MASK;
		break;
	default:
		break;
	}
}

void ADC_Configuration(ADCNoType ADCNumber, LowPowerCfgType LowPower, ClkDvdType ClkD, SampleTimeCfgType Samp, ConvModeType Conv, InputClkType InputC){
	switch(ADCNumber){
	/*This function writes the CFG1 and CFG2 depending on the entries*/
	case ADC0Type:
		ADC0->CFG1=((ClkD<<CLKSHIFT)|(Conv<<CONVSHIFT)|InputC|(LowPower<<LOWPOWERSHIFT)|(Samp<<SAMPSHIFT));
		ADC0->CFG2=0;
		break;
	case ADC1Type:
		ADC1->CFG1=((ClkD<<CLKSHIFT)|(Conv<<CONVSHIFT)|InputC|(LowPower<<LOWPOWERSHIFT)|(Samp<<SAMPSHIFT));
		ADC1->CFG2=0;
		break;
	default:
		break;
	}
}

void ADC_StatusControl(ADCNoType ADCNumber,uint8 SC1_Config,uint8 SC2_Config, uint8 SC3_Config){
	switch(ADCNumber){
	/*This function writes the SC1,SC2 and SC3 depending on the entries*/
		case ADC0Type:
			ADC0->SC1[0]=SC1_Config;
			ADC0->SC2=SC2_Config;
			ADC0->SC3=SC3_Config;
			break;
		case ADC1Type:
			ADC1->SC1[0]=SC1_Config;
			ADC1->SC2=SC2_Config;
			ADC1->SC3=SC3_Config;
			break;
		default:
			break;
		}
}

void ADC_initialize(const ADC_ConfigType* ADC_Config, uint8 SC1_Conf,uint8 SC2_Conf, uint8 SC3_Conf){
	/*This function initializes the GPIO pin used for the ADC; it also activates the clock gating
	 * and configures each element of the ADC_ConfigType struct*/
	GPIO_clockGating(GPIO_B);
	GPIO_dataDirectionPIN(GPIO_B, GPIO_INPUT, ADCPIN);
	GPIO_pinControlRegister(GPIO_B, ADCPIN, &(ADC_Config->pinConttrolRegisterPORTB));
	ADC_clk(ADC_Config->ADCNo);
	ADC_Configuration(ADC_Config->ADCNo, ADC_Config->LowPowerCfg, ADC_Config->ClkDvd, ADC_Config->SampleTimeCfg, ADC_Config->ConvMode, ADC_Config->InputClk);
	ADC_StatusControl(ADC_Config->ADCNo,SC1_Conf,SC2_Conf,SC3_Conf);
}

uint16 StartConversion(const ADC_ConfigType* ADC_Config){
	/*This function reads the value of the ADC; it waits until the conversion and average value are completed*/
	ADC0->SC1[0] = INITIALSC1 & ADC_SC1_ADCH_MASK;
	while(ADC0->SC2 & ADC_SC2_ADACT_MASK);
	while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK));
	return ADC0->R[0];
}


uint32 getTemperatureCelsius(uint16 AVGADC_value){
	/*This function converts bits into Temperature in Celsius using a slope of 10mV/C*/
	TemperatureC=(MAXVOLTAGE*AVGADC_value)/(MAXBITS*TEMPSLOPE);
	if(TRUE == getFlexFlag()){
		ReturnTemp = TemperatureC;

		clearFlexFlag();
	}
	else if (FALSE == getFlexFlag()){
		ReturnTemp = ReturnTemp;
	}
	return ReturnTemp;
}

uflo32 getTemperatureFahrenheit(uint16 AVGADC_value){
	/*This function converts bits into Temperature in Celsius using a slope of 10mV/C and multiplying it by 1.8 and adding 32.2*/
	TemperatureF=((MAXVOLTAGE*AVGADC_value) / (MAXBITS*TEMPSLOPE)) * FAHRENHEITFACTOR + FAHRENHEITCONST;
		if(TRUE == getFlexFlag()){
			ReturnTemp = TemperatureF;
			clearFlexFlag();
		}
		else if (FALSE == getFlexFlag()){
			ReturnTemp = ReturnTemp;
		}
		return ReturnTemp;
}
