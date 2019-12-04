//
//  functions.h
//  ESET269Final
//
//  Created by Kris Elers on 11/18/19.
//  Copyright © 2019 Kris Elers. All rights reserved.
//

#ifndef functions_h
#define functions_h

#include <stdio.h>

//Structs

//Functions
void UARTinit(void);
void ADCinit(void);
void PINinitDigital(void);
void PINinitRGB(void);

void getMenu(void);
void Uprint(char string[]);
void mainMenu(void);
void delay(int x);

void rgbControl(void);
void digitalInput(void);
void tempReading(void);

int ADCRead(void);
int getChoice(void);

//Constants

#endif /* functions_h */
