/*
 * WriteConsole.h
 *
 *  Created on: May 7, 2018
 *      Author: Jorge Loya
 */
#include "UART.h"
#include "DataTypeDefinitions.h"

#ifndef WRITECONSOLE_H_
#define WRITECONSOLE_H_


void FirstMenu(void);
void Wah_wah_Menu(uint8 Percent);
void MenuForLooper();
void MenuForEffect();
void MenuForEraseMemory();
void Resonator_Menu(uint8 Percent);
void Chorus_Menu(uint8 Percent);
void Flanger_Menu(uint8 Percent);
void Tremolo_Menu(uint8 Percent);
void Distorsion_Menu(uint8 Percent);

#endif /* WRITECONSOLE_H_ */
