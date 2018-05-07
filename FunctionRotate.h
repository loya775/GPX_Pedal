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

typedef void(*const fptroToFunctions[9])(void);
typedef float* (pftG)(const uint8*);

/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function call to ReadMemoryMenu.

 	 \return void
 */
void Menu_Function1(uint8 Flag, S25FLXXX_MemoryAddressType address, uint32 Counter, MemoryPortType SPIChannel);
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function call to WriteMemoryMenu.

 	 \return void
 */
void Menu_Function2(uint8 Flag,S25FLXXX_MemoryAddressType address, uint32 Counter, MemoryPortType SPIChannel);
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function call to Establecer_Hora.

 	 \return void
 */
void Menu_Function3(uint8 Flag, S25FLXXX_MemoryAddressType address, uint32 Counter, MemoryPortType SPIChannel);
/********************************************************************************************/
/********************************************************************************************/
/*!
 	  \brief	 This function call to Establecer_Fecha.

 	 \return void
 */
void Menu_Function4(uint8 Flag, S25FLXXX_MemoryAddressType address, uint32 Counter, MemoryPortType SPIChannel);
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function call to Formato_Hora.

 	 \return void
 */
void Menu_Function5(uint8 Flag, S25FLXXX_MemoryAddressType address, uint32 Counter, MemoryPortType SPIChannel);
/********************************************************************************************/
/********************************************************************************************/
/*!
 	\brief	 This function call to Leer_Hora.

 	 \return void
 */
void Menu_Function6(uint8 Flag, S25FLXXX_MemoryAddressType address, uint32 Counter, MemoryPortType SPIChannel);

void choose_function(uint8 FlagLooper, S25FLXXX_MemoryAddressType address, uint32 Counter, MemoryPortType SPIChannel);



#endif /* FUNCTIONROTATE_H_ */
