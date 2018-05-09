/*
 * FunctionRotate.h
 *
 *  Created on: Apr 14, 2018
 *      Author: Jorge Loya
 */

#ifndef FUNCTIONROTATE_H_
#define FUNCTIONROTATE_H_

#include "DataTypeDefinitions.h"
#include "GPIO.h"
#include "GlobalFunctions.h"
#include "S25FLXXX.h"
#include "ADCDriver.h"
#include "SoundFX.h"

typedef void(*const fptroToFunctions[9])(void);
typedef float* (pftG)(const uint8*);


/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This Function prints the menu to choose function and give you the option to choose.
 	 \param[in] address Direction to read in memory.
 	 \param[in] SPIChannel Is the SPI Channel configurated previously
 	 \param[in] ADC Is the ADC Input
 	 \return void
 */
void choose_function(uint8 Function, S25FLXXX_MemoryAddressType address, MemoryPortType SPIChannel, ADC_ConfigType ADC);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This Function prints the menu to erase memory and give you the option to choose.
  	 \param[in] address Direction to read in memory.
 	 \param[in] SPIChannel Is the SPI Channel configurated previously
 	 \param[in] ADC Is the ADC Input
 	 \return void
 */
void Menu_For_Erase_Memory(S25FLXXX_MemoryAddressType address, MemoryPortType SPIChannel, ADC_ConfigType ADC);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This Function prints the menu for  effect menu and give you the option to choose.
  	 \param[in] address Direction to read in memory.
 	 \param[in] SPIChannel Is the SPI Channel configurated previously
 	 \param[in] ADC Is the ADC Input
 	 \return void
 */
void Menu_For_Effect(S25FLXXX_MemoryAddressType address, MemoryPortType SPIChannel, ADC_ConfigType ADC);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This Function Reads the DAC and pass it across.
 	 \param[in] address Direction to read in memory.
 	 \param[in] SPIChannel Is the SPI Channel configurated previously
 	 \param[in] ADC Is the ADC Input
 	 \return void
 */
void Menu_For_Looper(S25FLXXX_MemoryAddressType address, MemoryPortType SPIChannel,ADC_ConfigType ADC);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This Function pass a value from the DAC to ADC and implement an effect.
 	 \param[in] ADC Is the ADC Input
 	 \param[in] Effect Is the SPI selected for Transfer
 	 \return void
 */
void Dac_Working(ADC_ConfigType ADC, FXType Effect);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief This Function Generate a Looper in the A0 pin.
 	 \param[in] SPIChannel Is the SPI Channel configurated previously
 	 \return void
 */
void LooperActivated(MemoryPortType SPIChannel);

#endif /* FUNCTIONROTATE_H_ */
