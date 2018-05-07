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
	uint8 string3[]="3)Flanger"; /*! String to be printed in the LCD*/
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

void LOOPER_ON_LCD()
{
	uint8 string1[]="LOOPER ACTIVADO"; /*! String to be printed in the LCD*/
	LCDNokia_clear();
	LCDNokia_gotoXY(3,Begin_LCD); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string1); /*! It print a string stored in an array*/
	delay(DelayValue);
}

void LOOPER_OFF_LCD()
{
	uint8 string1[]="LOOPER DESACTIVADO"; /*! String to be printed in the LCD*/
	LCDNokia_clear();
	LCDNokia_gotoXY(3,Begin_LCD); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string1); /*! It print a string stored in an array*/
	delay(DelayValue);
}

void Saving_Memory_LCD()
{
	uint8 string1[]="Saving value"; /*! String to be printed in the LCD*/
	uint8 string2[]=" For Looper"; /*! String to be printed in the LCD*/
	LCDNokia_clear();
	LCDNokia_gotoXY(Begin_LCD,0); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string1); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(2,1); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string2); /*! It print a string stored in an array*/
	delay(DelayValue);
}

void Saving_Finish_LCD()
{
	uint8 string1[]="Values save"; /*! String to be printed in the LCD*/
	uint8 string2[]="  in the "; /*! String to be printed in the LCD*/
	uint8 string3[]="  Memory "; /*! String to be printed in the LCD*/
	LCDNokia_clear();
	LCDNokia_gotoXY(Begin_LCD,1); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string1); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,2); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string2); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,3); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string3); /*! It print a string stored in an array*/
	delay(DelayValue);
}

void Chorus_LCD(uint8 Value)
{
	IntToString = Value/100;
	IntToString2 = ((Value-(IntToString*100))/10);
	IntToString3 = (Value-(IntToString*100)-(IntToString2*10));
	uint8 string1[]="  Chorus"; /*! String to be printed in the LCD*/
	uint8 string2[]="  Effect"; /*! String to be printed in the LCD*/
	uint8 string3[]="B0)+ B1)-"; /*! String to be printed in the LCD*/
	uint8 string4[]="%"; /*! String to be printed in the LCD*/
	LCDNokia_clear();
	LCDNokia_gotoXY(Begin_LCD,Begin_LCD); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string1); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,1); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string2); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,2); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string3); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,3); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendChar(IntToString+48); /*! It print a string stored in an array*/
	LCDNokia_sendChar(IntToString2+48); /*! It print a string stored in an array*/
	LCDNokia_sendChar(IntToString3+48); /*! It print a string stored in an array*/
	LCDNokia_sendString(string4); /*! It print a string stored in an array*/
	delay(DelayValue);
}

void Resonator_LCD(uint8 Value)
{
	IntToString = Value/100;
	IntToString2 = ((Value-(IntToString*100))/10);
	IntToString3 = (Value-(IntToString*100)-(IntToString2*10));
	uint8 string1[]="Resonator "; /*! String to be printed in the LCD*/
	uint8 string2[]=" Effect "; /*! String to be printed in the LCD*/
	uint8 string3[]="B0)+ B1)-"; /*! String to be printed in the LCD*/
	uint8 string4[]="%"; /*! String to be printed in the LCD*/
	LCDNokia_clear();
	LCDNokia_gotoXY(Begin_LCD,Begin_LCD); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string1); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,1); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string2); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,2); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string3); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,3); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendChar(IntToString+48); /*! It print a string stored in an array*/
	LCDNokia_sendChar(IntToString2+48); /*! It print a string stored in an array*/
	LCDNokia_sendChar(IntToString3+48); /*! It print a string stored in an array*/
	LCDNokia_sendString(string4); /*! It print a string stored in an array*/
	delay(DelayValue);
}

void Flanger_LCD(uint8 Value)
{
	IntToString = Value/100;
	IntToString2 = ((Value-(IntToString*100))/10);
	IntToString3 = (Value-(IntToString*100)-(IntToString2*10));
	uint8 string1[]="  Flanger"; /*! String to be printed in the LCD*/
	uint8 string2[]=" Effect "; /*! String to be printed in the LCD*/
	uint8 string3[]="B0)+ B1)-"; /*! String to be printed in the LCD*/
	uint8 string4[]="%"; /*! String to be printed in the LCD*/
	LCDNokia_clear();
	LCDNokia_gotoXY(Begin_LCD,Begin_LCD); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string1); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,1); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string2); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,2); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string3); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,3); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendChar(IntToString+48); /*! It print a string stored in an array*/
	LCDNokia_sendChar(IntToString2+48); /*! It print a string stored in an array*/
	LCDNokia_sendChar(IntToString3+48); /*! It print a string stored in an array*/
	LCDNokia_sendString(string4); /*! It print a string stored in an array*/
	delay(DelayValue);
}

void Wah_wah_LCD(uint8 Value)
{
	IntToString = Value/100;
	IntToString2 = ((Value-(IntToString*100))/10);
	IntToString3 = (Value-(IntToString*100)-(IntToString2*10));
	uint8 string1[]="  Wah-wah "; /*! String to be printed in the LCD*/
	uint8 string2[]="   Effect"; /*! String to be printed in the LCD*/
	uint8 string3[]="B0)+ B1)-"; /*! String to be printed in the LCD*/
	uint8 string4[]="%"; /*! String to be printed in the LCD*/
	LCDNokia_clear();
	LCDNokia_gotoXY(Begin_LCD,Begin_LCD); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string1); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,1); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string2); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,2); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string3); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,3); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendChar(IntToString+48); /*! It print a string stored in an array*/
	LCDNokia_sendChar(IntToString2+48); /*! It print a string stored in an array*/
	LCDNokia_sendChar(IntToString3+48); /*! It print a string stored in an array*/
	LCDNokia_sendString(string4); /*! It print a string stored in an array*/
	delay(DelayValue);

	delay(DelayValue);
}

void Tremolo_LCD(uint8 Value)
{
	IntToString = Value/100;
	IntToString2 = ((Value-(IntToString*100))/10);
	IntToString3 = (Value-(IntToString*100)-(IntToString2*10));
	uint8 string1[]="  Tremolo"; /*! String to be printed in the LCD*/
	uint8 string2[]="  Effect "; /*! String to be printed in the LCD*/
	uint8 string3[]="B0)+ B1)-"; /*! String to be printed in the LCD*/
	uint8 string4[]="%"; /*! String to be printed in the LCD*/
	LCDNokia_clear();
	LCDNokia_gotoXY(Begin_LCD,Begin_LCD); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string1); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,1); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string2); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,2); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string3); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,3); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendChar(IntToString+48); /*! It print a string stored in an array*/
	LCDNokia_sendChar(IntToString2+48); /*! It print a string stored in an array*/
	LCDNokia_sendChar(IntToString3+48); /*! It print a string stored in an array*/
	LCDNokia_sendString(string4); /*! It print a string stored in an array*/
	delay(DelayValue);
}

void Distorsion_LCD(uint8 Value)
{
	IntToString = Value/100;
	IntToString2 = ((Value-(IntToString*100))/10);
	IntToString3 = (Value-(IntToString*100)-(IntToString2*10));
	uint8 string1[]=" Distorsion"; /*! String to be printed in the LCD*/
	uint8 string2[]="  Effect "; /*! String to be printed in the LCD*/
	uint8 string3[]="B0)+ B1)-"; /*! String to be printed in the LCD*/
	uint8 string4[]="%"; /*! String to be printed in the LCD*/
	LCDNokia_clear();
	LCDNokia_gotoXY(Begin_LCD,Begin_LCD); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string1); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,1); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string2); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,2); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string3); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,3); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendChar(IntToString+48); /*! It print a string stored in an array*/
	LCDNokia_sendChar(IntToString2+48); /*! It print a string stored in an array*/
	LCDNokia_sendChar(IntToString3+48); /*! It print a string stored in an array*/
	LCDNokia_sendString(string4); /*! It print a string stored in an array*/
	delay(DelayValue);
}

void Erasing_Memory_LCD()
{
	uint8 string1[]=" Erasing"; /*! String to be printed in the LCD*/
	uint8 string2[]="  Memory "; /*! String to be printed in the LCD*/
	LCDNokia_clear();
	LCDNokia_gotoXY(Begin_LCD,1); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string1); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,2); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string2); /*! It print a string stored in an array*/
	delay(DelayValue);
}

void Memory_Erase_LCD()
{
	uint8 string1[]=" Memory"; /*! String to be printed in the LCD*/
	uint8 string2[]="  Erase "; /*! String to be printed in the LCD*/
	LCDNokia_clear();
	LCDNokia_gotoXY(Begin_LCD,Begin_LCD); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string1); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(Begin_LCD,1); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string2); /*! It print a string stored in an array*/
	delay(DelayValue);
}

void Memory_Is_Full_LCD()
{
	uint8 string1[]=" Memory is"; /*! String to be printed in the LCD*/
	uint8 string2[]="  Full "; /*! String to be printed in the LCD*/
	LCDNokia_clear();
	LCDNokia_gotoXY(Begin_LCD,Begin_LCD); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string1); /*! It print a string stored in an array*/
	LCDNokia_gotoXY(1,Begin_LCD); /*! It establishes the position to print the messages in the LCD*/
	LCDNokia_sendString(string2); /*! It print a string stored in an array*/
	delay(DelayValue);
}
