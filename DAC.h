/*
 * DAC.h
 *
 *  Created on: Feb 24, 2018
 *      Author: Raymundo
 */

#include "DataTypeDefinitions.h"


#ifndef DAC_H_
#define DAC_H_





void DAC0_clockGating(void);

void DAC0_init(void);

void DAC0_write(uint16 data);



#endif /* DAC_H_ */
