/*
 * LCD_Writing.c
 *
 *  Created on: Mar 16, 2018
 *      Author: Jorge Loya
 */
#include "MK64F12.h"
#include "GPIO.h"
#include "LCD_Writing.h"
#define Offset_LCD 48
#define DelayValue 65000
#define Begin_LCD 0
#define SecondLineLCD 1
#define ThirdLineLCD 2
#define FourthLineLCD 3
#define MaxVALUE 100
#define CaseIsA100 0
#define CaseIsA100Offset 49
#define MoveValueToPrint10 10
#define MoveValueToPrint100 100
#define MoveValueToPrint1000 1000
#define MoveValueToPrint10000 10000
#define MoveValueToPrint100000 100000
#define MoveValueToPrint1000000 1000000
#define MoveValueToPrint10000000 10000000
#define MoveValueToPrint100000000 100000000
#define Move10f 10.00f
uint32 IntToString;
uint32 TwoDecimalValues;
uint32 IntToString2;
uint32 IntToString3;
uint32 IntToString4;
uint32 IntToString5;
uint32 IntToString6;
uint32 Prev;
uint32 Resta;
uint32 Resta2;
uint32 Resta3;
uint32 Resta4;
uint32 Resta5;
uint32 Number2;
uint32 Number3;
uint8 Number4;
uint8 Number5;
uint8 porcent0;
uint8 Decimal_1f;
uint8 Decimal_2f;
uint8 porcent1;
uint8 porcent2;


void Inicio_LCD()
{
	uint8 string1[]="1)Resonator "; /*! String to be printed in the LCD*/
	uint8 string2[]="2)Chorus"; /*! String to be printed in the LCD*/
	uint8 string3[]="3)Flangere"; /*! String to be printed in the LCD*/
	uint8 string4[]="4)Wah-wah"; /*! String to be printed in the LCD*/
	uint8 string5[]="5)Tremolo"; /*! String to be printed in the LCD*/
	uint8 string6[]="6)Distorsion"; /*! String to be printed in the LCD*/
	LCDNokia_clear();
	LCDNokia_gotoXY(Begin_LCD,Begin_LCD); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string1); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,SecondLineLCD);
	LCDNokia_sendString(string2);
	LCDNokia_gotoXY(Begin_LCD,ThirdLineLCD);
	LCDNokia_sendString(string3); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,FourthLineLCD);
	LCDNokia_sendString(string4); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,4);
	LCDNokia_sendString(string5); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,5);
	LCDNokia_sendString(string6); /*! It print a string stored in an array*/
	delay(DelayValue);
}




