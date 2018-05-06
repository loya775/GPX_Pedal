/**
	\file
	\brief
		This is the header file for the FlexTimer divice driver.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Add configuration structures.
 */

#ifndef FLEXTIMER_H_
#define FLEXTIMER_H_


#include "MK64F12.h"
#include "DataTypeDefinitions.h"


#define FLEX_TIMER_0_CLOCK_GATING 0x01000000

#define FLEX_TIMER_FAULTIE  0x80
#define FLEX_TIMER_FAULTM_0   0x00
#define FLEX_TIMER_FAULTM_1   0x20
#define FLEX_TIMER_FAULTM_2   0x40
#define FLEX_TIMER_FAULTM_3   0x60
#define FLEX_TIMER_CAPTEST  0x10
#define FLEX_TIMER_PWMSYNC  0x08
#define FLEX_TIMER_WPDIS    0x04
#define FLEX_TIMER_INIT     0x02
#define FLEX_TIMER_FTMEN    0x01

#define FLEX_TIMER_TOF     0x80
#define FLEX_TIMER_TOIE    0x40
#define FLEX_TIMER_CPWMS   0x20
#define FLEX_TIMER_CLKS_0  0x00
#define FLEX_TIMER_CLKS_1  0x08
#define FLEX_TIMER_CLKS_2  0x10
#define FLEX_TIMER_CLKS_3  0x18
#define FLEX_TIMER_PS_1    0x00
#define FLEX_TIMER_PS_2    0x01
#define FLEX_TIMER_PS_4    0x02
#define FLEX_TIMER_PS_8    0x03
#define FLEX_TIMER_PS_16    0x04
#define FLEX_TIMER_PS_32    0x05
#define FLEX_TIMER_PS_64    0x06
#define FLEX_TIMER_PS_128    0x07

#define FLEX_TIMER_PWMLOAD_CH0 0x01
#define FLEX_TIMER_PWMLOAD_CH1 0x02
#define FLEX_TIMER_PWMLOAD_CH2 0x04
#define FLEX_TIMER_PWMLOAD_CH3 0x08
#define FLEX_TIMER_PWMLOAD_CH4 0x10
#define FLEX_TIMER_PWMLOAD_CH5 0x20
#define FLEX_TIMER_PWMLOAD_CH6 0x40
#define FLEX_TIMER_PWMLOAD_CH7 0x80
#define FLEX_TIMER_LDOK        0x200


#define  FLEX_TIMER_DMA   0x01
#define  FLEX_TIMER_ELSA  0x04
#define  FLEX_TIMER_ELSB  0x08
#define  FLEX_TIMER_MSA   0x10
#define  FLEX_TIMER_MSB   0x20
#define  FLEX_TIMER_CHIE  0x40
#define  FLEX_TIMER_CHF   0x80

typedef enum{FTM_0, /*!< Definition to select GPIO A */
			 FTM_1, /*!< Definition to select GPIO B */
			 FTM_2 /*!< Definition to select GPIO C */
			} FTM_Number;

typedef enum{FTM_CAPT_RE, /*!< Definition to select GPIO A */
			FTM_OutputC_Toogle, /*!< Definition to select GPIO B */
			FTM_PWM_Edge_Aligned
			} FTM_MODE;

typedef enum{BDMMODE_0, /*!< Definition to select GPIO A */
			BDMMODE_1, /*!< Definition to select GPIO B */
			BDMMODE_2, /*!< Definition to select GPIO C */
			BDMMODE_3
			} FTM_BDMMODE_Type;

			typedef struct
			{
				FTM_Number FTM_CODE;
				FTM_MODE MOD_CODE;
			} FTM_ConfigType;

/*!
	\brief	 This function clears the flag to take temperature value
	\param[in] It doesn´t need parameters
	\return It doesn't have a return
*/
void clearFlexFlag();
/*!
 	 \brief	 Initialize a Flex Timer and depends of the Configuration Type
 	 \param[in] Need the Configuration Type
 	 \return It doesn't have a return
 */
void FlexTimer_Init(const FTM_ConfigType*);
/*!
 	 \brief	 This function give you the Value of the FlexFlag to see if is Activated or Disactivated
 	 \param[in] It doesn´t need parameter
 	 \return The value of the flag
 */
uint8 getFlexFlag(void);
/*!
 	 \brief	 This function update the value of the FlexTimer of the PWM
 	 \param[in] Needs the new value to actualize
 	 \return It doesn't have a return
 */
void FlexTimer_updateCHValue(sint16 channelValue);
/*!
 	 \brief	 Initialize the value of a Flex Timer
 	 \param[in] Need the Mode of the FTM and what Flex Timer you want to activated
 	 \return It doesn't have a return
 */
void FTM_MODE_Config(FTM_Number FTM, FTM_MODE MODE);
/*!
 	 \brief	 This function gives you the value of frequency
 	 \param[in] It doesn´t need parameter
 	 \return The value of Frequency
 */
flo32 FlexTimerConvertVALUE(void);
/*!
 	 \brief	 This function gives you value of count from FTM2 interruptions
 	 \param[in] It doesn´t need parameter
 	 \return The value count of FTM2 interruptions
 */
flo32 FlexTimer_GetCounter(void);
#endif /* FLEXTIMER_H_ */
