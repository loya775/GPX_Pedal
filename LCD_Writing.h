/*
 * LCD_Writing.h
 *
 *  Created on: Mar 16, 2018
 *      Author: Jorge Loya
 */
#include "LCDNokia5110.h"
#include "SPI.h"
#include "DatatypeDefinitions.h"
#include "GPIO.h"
#include "GlobalFunctions.h"

#ifndef LCD_WRITING_H_
#define LCD_WRITING_H_

/*!
 	 \brief	 This function prints the inicio menu
 	 \param[in] Needs the value of temperature in Celsius and the actual value of the motor
 	 \return It doesn't have a return
 */
void Inicio_LCD();


#endif /* LCD_WRITING_H_ */
