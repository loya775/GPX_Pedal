/*
 * ADCDriver.h
 *
 *  Created on: Mar 16, 2018
 *      Author: d
 */

#ifndef ADCDRIVER_H_
#define ADCDRIVER_H_

#include "DataTypeDefinitions.h"
#include "GPIO.h"

#define AVERAGE_ENABLE_MASK 0x04
#define AVERAGE_DISABLE_MASK 0

typedef enum {ADC0Type, ADC1Type} ADCNoType;

typedef enum {NORMAL_POWER,LOW_POWER} LowPowerCfgType;
/*Type for polarity configuration*/
typedef enum {RATIO1,RATIO2,RATIO4,RATIO8} ClkDvdType;
/*Type for phase configuration*/
typedef enum {SHORT_SAMPLE,LONG_SAMPLE} SampleTimeCfgType;
/*Type for the star of the frame, either MSB o LSM */
typedef enum {CONV8,CONV12,CONV10,CONV16} ConvModeType;
/*Type for SPI modules*/
typedef enum {BUSCLK, ALTCLK2,ALTCLK,ADACK} InputClkType;

typedef enum {SAMP4,SAMP8,SAMP16,SAMP32} AverageSampType;

typedef struct
{
	GPIO_pinControlRegisterType pinConttrolRegisterPORTB;
	ADCNoType ADCNo;
	LowPowerCfgType LowPowerCfg;
	ClkDvdType ClkDvd;
	SampleTimeCfgType SampleTimeCfg;
	ConvModeType ConvMode;
	InputClkType InputClk;
} ADC_ConfigType;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It enables the ADC clock gating depending on the ADCNoType

 	 \param[in] It receives the ADC number
 	 \return It doesn't have a return
 */

void ADC_clk(ADCNoType);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It configures the SC1,SC2 and SC3 registers to specify modes of operation and other specifications

 	 \param[in] It receives the ADC number and the configurations of SC1, SC2 and SC3
 	 \return It doesn't have a return
 */

void ADC_StatusControl(ADCNoType,uint8,uint8,uint8);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It configures the initial values of SC1,SC2 and SC3 registers to specify modes of operation and other specifications

 	 \param[in] It receives the ADC number and the configurations of SC1, SC2 and SC3
 	 \return It doesn't have a return
 */

void ADC_initialize(const ADC_ConfigType*,uint8,uint8,uint8);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function returns an average value of n total of ADC samples depending on a flex timer flag
 	 \param[in] It doesn't receive a variable
 	 \return It returns a value between 0 and 65535; it is the voltage read in bits
 */

uint32 ADC_getValue(void);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function reads the ADC and returns the average value of n samples determined on the ADC Configuration
 	 \param[in]  It receives the ADC Configuration
 	 \return It returns the converted ADC value
 */

uint16 StartConversion(const ADC_ConfigType* ADC_Config);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function modifies the value of CFG1, CFG2 and CFG3 registers
 	 \param[in]  It receives every parameter included in the ADC_ConfigType struct
 	 \return It doesn't have a return
 */

void ADC_Configuration(ADCNoType, LowPowerCfgType, ClkDvdType, SampleTimeCfgType, ConvModeType, InputClkType);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function converts bits read to Celsius
 	 \param[in] This function receives the average value from n ADC samples
 	 \return This function returns the temperature read in Celsius
 */

uint32 getTemperatureCelsius(uint16 AVGADC_value);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function converts bits read to Fahrenheit
 	 \param[in] This function receives the average value from n ADC samples
 	 \return This function returns the temperature read in Fahrenheit
 */

flo32 getTemperatureFahrenheit(uint16 AVGADC_value);

#endif /* ADCDRIVER_H_ */
