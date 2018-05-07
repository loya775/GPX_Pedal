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

void LOOPER_OFF_LCD();

void LOOPER_ON_LCD();

void Saving_Memory_LCD();

void Saving_Finish_LCD();

void Tremolo_LCD(uint8 Value);

void Chorus_LCD(uint8 Value);

void Resonator_LCD(uint8 Value);

void Flanger_LCD(uint8 Value);

void Wah_wah_LCD(uint8 Value);

void Distorsion_LCD(uint8 Value);

void Memory_Erase_LCD();

void Erasing_Memory_LCD();

void Memory_Is_Full_LCD();
#endif /* LCD_WRITING_H_ */
