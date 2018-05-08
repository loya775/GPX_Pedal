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
typedef void(*const fptroToFunctions[9])(void);
typedef float* (pftG)(const uint8*);



void choose_function(uint8 Function, S25FLXXX_MemoryAddressType address, MemoryPortType SPIChannel, ADC_ConfigType ADC);

void Menu_For_Erase_Memory(S25FLXXX_MemoryAddressType address, MemoryPortType SPIChannel, ADC_ConfigType ADC);

void Menu_For_Effect(S25FLXXX_MemoryAddressType address, MemoryPortType SPIChannel, ADC_ConfigType ADC);

void Menu_For_Looper(S25FLXXX_MemoryAddressType address, MemoryPortType SPIChannel,ADC_ConfigType ADC);

void Dac_Working(ADC_ConfigType ADC);

void LooperActivated(MemoryPortType SPIChannel);

#endif /* FUNCTIONROTATE_H_ */
