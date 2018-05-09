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

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function Prints in Tera Term The Menu of the proyect.

 	 \param[in]  Void
 	 \return Nothing
 */
void FirstMenu(void);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function Prints in Tera Term The Menu of the proyect.

 	 \param[in]  Void
 	 \return Nothing
 */
void Wah_wah_Menu(uint8 Percent);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function Prints the menu.

 	 \param[in]  Void
 	 \return Nothing
 */
void MenuForLooper();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function Prints the Menu for the Looper.

 	 \param[in]  Void
 	 \return Nothing
 */
void MenuForEffect();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function Prints all the effects in Tera term.

 	 \param[in]  Void
 	 \return Nothing
 */
void MenuForEraseMemory();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function Prints the menu for memory erase.

 	 \param[in]  Void
 	 \return Nothing
 */
void Resonator_Menu(uint8 Percent);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function Prints in Tera Term The Menu of the proyect.

 	 \param[in]  Percent Is the percent of the effect applied to the signal
 	 \return Nothing
 */
void Chorus_Menu(uint8 Percent);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function Prints in Tera Term The Menu of the proyect.

 	 \param[in]  Percent Is the percent of the effect applied to the signal
 	 \return Nothing
 */
void Flanger_Menu(uint8 Percent);/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function Prints in Tera Term The Menu of the proyect.

 	 \param[in]  Percent Is the percent of the effect applied to the signal
 	 \return Nothing
 */
void Tremolo_Menu(uint8 Percent);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function Prints The menu for distortion.
 	 \param[in]  Percent Is the percent of the effect applied to the signal
 	 \return Nothing
 */
void Distorsion_Menu(uint8 Percent);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function Prints that memory has been erased.

 	 \param[in]  Percent Is the percent of the effect applied to the signal
 	 \return Nothing
 */
void Guardado_Aviso();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function Prints that memory is been saving.

 	 \param[in]  Void
 	 \return Nothing
 */
void Guardando_Aviso();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function Prints that the memory has been erased.

 	 \param[in]  Void
 	 \return Nothing
 */
void Elminado_Aviso();
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This function Prints that Memory is erasing.

 	 \param[in]  Void
 	 \return Nothing
 */
void Elminando_Aviso();
#endif /* WRITECONSOLE_H_ */
