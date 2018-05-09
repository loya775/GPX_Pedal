/*
 * WriteConsole.c
 *
 *  Created on: May 7, 2018
 *      Author: Jorge Loya
 */
#include "DataTypeDefinitions.h"
#include "WriteConsole.h"
#include "MK64F12.h"
#include "NVIC.h"
#include "GPIO.h"
#define OFFSET 48
uint8 ToChar1;
uint8 ToChar2;
uint8 ToChar3;

void FirstMenu(){
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	UART_putString(UART_0,"\033[0;32;46m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(UART_0,"\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[1;0H");
	UART_putString(UART_0, "B0) Guardar un Looper\r");
	UART_putString(UART_0,"\033[2;0H");
	UART_putString(UART_0, "B1) Eliminar Memoria\r");
	UART_putString(UART_0,"\033[3;0H");
	UART_putString(UART_0, "B2) Efectos\r");
	return;
}

void Guardando_Aviso(){
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	UART_putString(UART_0,"\033[0;32;46m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(UART_0,"\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[1;0H");
	UART_putString(UART_0, "B0) Guardando......\r");
	return;
}

void Eliminando_Aviso(){
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	UART_putString(UART_0,"\033[0;32;46m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(UART_0,"\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[1;0H");
	UART_putString(UART_0, "Eliminando....\r");
	return;
}

void Elminado_Aviso(){
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	UART_putString(UART_0,"\033[0;32;46m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(UART_0,"\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[1;0H");
	UART_putString(UART_0, "Eliminado\r");
	UART_putString(UART_0,"\033[2;0H");
	UART_putString(UART_0, "B1) Salir\r");
	return;
}

void Guardado_Aviso(){
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	UART_putString(UART_0,"\033[0;32;46m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(UART_0,"\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[1;0H");
	UART_putString(UART_0, "B0) Guardado Terminado\r");
	UART_putString(UART_0,"\033[2;0H");
	UART_putString(UART_0, "B1) Salir\r");
	return;
}

void MenuForLooper(){
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	UART_putString(UART_0,"\033[0;32;46m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(UART_0,"\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[1;0H");
	UART_putString(UART_0, "Menu de Looper\r");
	UART_putString(UART_0,"\033[2;0H");
	UART_putString(UART_0, "B0) Guardar un Looper\r");
	UART_putString(UART_0,"\033[3;0H");
	UART_putString(UART_0, "B1) Salir\r");
	return;
}

void MenuForEffect(){
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	UART_putString(UART_0,"\033[0;32;46m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(UART_0,"\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[1;0H");
	UART_putString(UART_0, "Menu de Efectos\r");
	UART_putString(UART_0,"\033[2;0H");
	UART_putString(UART_0, "B0) Slap Back\r");
	UART_putString(UART_0,"\033[3;0H");
	UART_putString(UART_0, "B1) Chorus\r");
	UART_putString(UART_0,"\033[4;0H");
	UART_putString(UART_0, "B2) Flanger\r");
	UART_putString(UART_0,"\033[5;0H");
	UART_putString(UART_0, "B3) Clean\r");
	UART_putString(UART_0,"\033[6;0H");
	UART_putString(UART_0, "B4) Tremolo\r");
	UART_putString(UART_0,"\033[7;0H");
	UART_putString(UART_0, "B5) Distorsion\r");
	UART_putString(UART_0,"\033[8;0H");
	UART_putString(UART_0, "B6) Salir\r");
	return;
}

void MenuForEraseMemory(){
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	UART_putString(UART_0,"\033[0;32;46m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(UART_0,"\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[1;0H");
	UART_putString(UART_0, "Menu para Borrar Memoria\r");
	UART_putString(UART_0,"\033[2;0H");
	UART_putString(UART_0, "B0) Borrar Memoria\r");
	UART_putString(UART_0,"\033[3;0H");
	UART_putString(UART_0, "B1) Regresar\r");
	return;
}

void Resonator_Menu(uint8 Percent){
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	ToChar1 = Percent/100;
	ToChar2 = (Percent-(ToChar1*100))/10;
	ToChar3 = (Percent-(ToChar1*100)-(ToChar2*10));
	UART_putString(UART_0,"\033[0;32;46m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(UART_0,"\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[1;0H");
	UART_putString(UART_0, " SLAP_BACK Effect\r");
	UART_putString(UART_0,"\033[2;0H");
	UART_putString(UART_0, "B0)+ B1)- \r");
	UART_putString(UART_0,"\033[3;0H");
	UART_putChar (UART_0, ToChar1 + 48);
	UART_putChar (UART_0, ToChar2 + 48);
	UART_putChar (UART_0, ToChar3 + 48);
	UART_putString(UART_0,"\033[4;0H");
	UART_putString(UART_0, "B2) Regresar\r");
	return;
}
void Chorus_Menu(uint8 Percent){
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	ToChar1 = Percent/100;
	ToChar2 = (Percent-(ToChar1*100))/10;
	ToChar3 = (Percent-(ToChar1*100)-(ToChar2*10));
	UART_putString(UART_0,"\033[0;32;46m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(UART_0,"\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[1;0H");
	UART_putString(UART_0, " Chorus Effect\r");
	UART_putString(UART_0,"\033[2;0H");
	UART_putString(UART_0, "B0)+ B1)- \r");
	UART_putString(UART_0,"\033[3;0H");
	UART_putChar (UART_0, ToChar1 + 48);
	UART_putChar (UART_0, ToChar2 + 48);
	UART_putChar (UART_0, ToChar3 + 48);
	UART_putString(UART_0,"\033[4;0H");
	UART_putString(UART_0, "B2) Regresar\r");
	return;
}
void Flanger_Menu(uint8 Percent){
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	ToChar1 = Percent/100;
	ToChar2 = (Percent-(ToChar1*100))/10;
	ToChar3 = (Percent-(ToChar1*100)-(ToChar2*10));
	UART_putString(UART_0,"\033[0;32;46m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(UART_0,"\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[1;0H");
	UART_putString(UART_0, " Flanger Effect\r");
	UART_putString(UART_0,"\033[2;0H");
	UART_putString(UART_0, "B0)+ B1)- \r");
	UART_putString(UART_0,"\033[3;0H");
	UART_putChar (UART_0, ToChar1 + 48);
	UART_putChar (UART_0, ToChar2 + 48);
	UART_putChar (UART_0, ToChar3 + 48);
	UART_putString(UART_0,"\033[4;0H");
	UART_putString(UART_0, "B2) Regresar\r");
	return;
}
void Wah_wah_Menu(uint8 Percent){
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	ToChar1 = Percent/100;
	ToChar2 = (Percent-(ToChar1*100))/10;
	ToChar3 = (Percent-(ToChar1*100)-(ToChar2*10));
	UART_putString(UART_0,"\033[0;32;46m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(UART_0,"\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[1;0H");
	UART_putString(UART_0, " Wah-Wah Effect\r");
	UART_putString(UART_0,"\033[2;0H");
	UART_putString(UART_0, "B0)+ B1)- \r");
	UART_putString(UART_0,"\033[3;0H");
	UART_putChar (UART_0, ToChar1 + 48);
	UART_putChar (UART_0, ToChar2 + 48);
	UART_putChar (UART_0, ToChar3 + 48);
	UART_putString(UART_0,"\033[4;0H");
	UART_putString(UART_0, "B2) Regresar\r");
	return;
}
void Tremolo_Menu(uint8 Percent){
	/**The following sentences send strings to PC using the UART_putString function. Also, the string
	 * is coded with terminal code*/
	/** VT100 command for text in red and background in cyan*/
	ToChar1 = Percent/100;
	ToChar2 = (Percent-(ToChar1*100))/10;
	ToChar3 = (Percent-(ToChar1*100)-(ToChar2*10));
	UART_putString(UART_0,"\033[0;32;46m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(UART_0,"\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[1;0H");
	UART_putString(UART_0, " Tremolo Effect\r");
	UART_putString(UART_0,"\033[2;0H");
	UART_putString(UART_0, "B0)+ B1)- \r");
	UART_putString(UART_0,"\033[3;0H");
	UART_putChar (UART_0, ToChar1 + 48);
	UART_putChar (UART_0, ToChar2 + 48);
	UART_putChar (UART_0, ToChar3 + 48);
	UART_putString(UART_0,"\033[4;0H");
	UART_putString(UART_0, "B2) Regresar\r");
	return;
}
void Distorsion_Menu(uint8 Percent)
{
	ToChar1 = Percent/100;
	ToChar2 = (Percent-(ToChar1*100))/10;
	ToChar3 = (Percent-(ToChar1*100)-(ToChar2*10));
	UART_putString(UART_0,"\033[0;32;46m");
	/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[2J");
	/** VT100 command for text in red and background in green*/
	UART_putString(UART_0,"\033[0;32;41m");
	/** VT100 command for positioning the cursor in x and y position*/
	/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0,"\033[1;0H");
	UART_putString(UART_0, " Distorsion Effect\r");
	UART_putString(UART_0,"\033[2;0H");
	UART_putString(UART_0, "B0)+ B1)- \r");
	UART_putString(UART_0,"\033[3;0H");
	UART_putChar (UART_0, ToChar1 + 48);
	UART_putChar (UART_0, ToChar2 + 48);
	UART_putChar (UART_0, ToChar3 + 48);
	UART_putString(UART_0,"\033[4;0H");
	UART_putString(UART_0, "B2) Regresar\r");
	return;
}

