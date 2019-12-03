//
//  functions.c
//  ESET269Final
//
//  Created by Kris Elers on 11/18/19.
//  Copyright © 2019 Kris Elers. All rights reserved.
//

#include "functions.h"
#include "MSP.h"
#include <stdio.h>
#include <stdlib.h>


/*
*   Function for initializing UART
*   Returns: void
*   Author: Kristopher Elers
*/
void UARTinit(void) {
    EUSCI_A0->CTLW0 |= 1;   // Put into reset state
    EUSCI_A0->MCTLW = 0;
    EUSCI_A0->CTLW0 = 0x0081;   // 1 stop bit, no parity, SMCLK, 8-BIT DATA
    EUSCI_A0->BRW = 26; // Baud rate
    P1->SEL0 |= 0x0C;   // SEL0 value
    P1->SEL1 &= ~0x0C;  // SEL1 value
    EUSCI_A0->CTLW0 &= ~1;  // Take out for reset state
}


/*
*   Function for initializing UART
*   Returns: void
*   Author: Alex Liu
*/
void Pininit(void){	
	P2 ->SEL0 &= ~0xEE; //activate every pin in port 2
	P2 ->SEL1 &= ~0xEE;
	P2 ->DIR |= 0xEE; //set every pin to output

	P1 ->SEL0 = 0x00; //setup port 1 pin 0 for systick timer
	P1 ->SEL1 = 0x00;
	P1 ->DIR |= 0x01;	
}


/*
*   Function for printing a string to the console
*   Returns: void
*   Author: Kristopher Elers
*/
void Uprint(char string[]) {
    int i = 0;

    while(string[i] != 0) {
        EUSCI_A0->TXBUF = string[i];
        while((EUSCI_A0->IFG & 2) == 0) {
            //do nothing
        }
        i++;
    }
}   // Uprint


/*
*   Function for initializing ADC
*   Returns: void
*   Author: Kristopher Elers
*/
void ADCinit(void)  {
    ADC14->CTL0 =  0x00000010;    // power on and disable during configuration
    ADC14->CTL0 |= 0x04080300;    // sample and hold mode, sysclk, 32 sample clocks, software trigger
    ADC14->CTL1 =  0x00000030;    // 14-bit resolution 
    ADC14->MCTL[2] = 1;           // A1 input, single-ended, Vref=AVCC 
    P5->SEL1 |= 0x10;             // Configure P5.4 for A1
    P5->SEL0 |= 0x10;
    ADC14->CTL1 |= 0x00020000;    // convert for memory reg. 2
    ADC14->CTL0 |= 2;             // enable ADC
}


/*
*   Function for reading ADC
*   Returns: int
*   Author: Kristopher Elers
*/
int ADCRead(void)   {
    int z = 0;
    ADC14->CTL0 |= 1;         // start a conversion
    while (!ADC14->IFGR0);    // wait till conversion complete
    z = ADC14->MEM[2];       // read conversion result
    return z;
}


/*
*   Function for getting the users choice
*   Returns: int
*   Author: Kristopher Elers
*/
int getChoice(void) {
    char choice[2];
    int i = 0;

    while(1) {
        if((EUSCI_A0->IFG & 1) != 0) {  // Check if if character is receive buffer
            choice[i] = EUSCI_A0->RXBUF;    // Place current character in array
			EUSCI_A0->TXBUF = choice[i];
            if(choice[i] == '\r') { // Enter key pressed
				choice[i] = '\0';
                break;
            } else {
                i++;
            }
        }
    }
		return atoi(choice);
}   // getChoice


/*
*   Function for printing the main menu text
*   Returns: void
*   Author: Kristopher Elers
*/
void mainMenu(void) {
    Uprint("\n\r\n\tMSP432 Menu\n\r");
    Uprint("1. RGB Control\n\r");
    Uprint("2. Digital Input\n\r");
    Uprint("3. Temperature Reading\n\r");
	Uprint("4. Quit\n\r");
}   // mainMenu


/*
*   Function for handling the main menu and main function calls
*   Returns: void
*   Author: Kristopher Elers
*/
void getMenu(void) {
	int option = 0;
	
    while(option != 4) {
        mainMenu();
        Uprint("Select Option: ");
        int option = getChoice();
        switch(option) {
            case 1:
                rgbControl();
                break;
            case 2:
                digitalInput();
                break;
            case 3:
                tempReading();
                break;
            case 4:
                Uprint("\n\rStopping program...");
                while(1);
            default:
                Uprint("\n\rYou pressed an invalid key. Please try again.\n\r");
        }
    }
}   // getMenu


/*
*   Function for RGB Control
*   Returns: void
*   Author: Alex Liu
*/
void rgbControl(void) {
    int rgb;    // RGB combination character array
    int tog;    // Toggle time
    int blink;  // Number of blinks

    Uprint("\n\r\n\rEnter a combination of RGB (1-7): ");
    rgb = getChoice();
    Uprint("\n\rEnter the toggle time: ");
    tog = getChoice();
    Uprint("\n\rEnter the number of blinks: ");
    blink = getChoice();
	Uprint("\n\rBlinking LED...");
	
    int togCount = (tog / 0.000000333) - 1;
    SysTick->LOAD = togCount;   // Set user input delay time
    SysTick->CTRL |= 0x04;
    P1->OUT |= 0x01;

    for(int i = 0; i <= (blink - 1); i++) { // Blink RGB combo 'blink' times
        SysTick->CTRL |= 0x01;
        P2->OUT |= 0x00 + rgb;
        while((SysTick->CTRL & 0x10000) == 0) {
            // Do nothing
        }
        P2->OUT &= ~(0x00 + rgb);
    }
		
	Uprint("\n\rDone");
    P1->OUT &= ~0xEE;   // Turn off all pins
    SysTick->CTRL &= ~0x1;  // Disable SysTick
}   // rgbControl


/*
*   Function for detecting digital input
*   Returns: void
*   Author: Kristopher Elers
*/
void digitalInput(void) {
    
}   // digitalInput


/*
*   Function for getting the temperature reading of the board
*   Returns: void
*   Author: Maksym Sury
*/
void tempReading(void) {
    int x = 0; //iteration value for char array (string)
    int choice;
    double ans; //variable for math answer

    SysTick->LOAD = 3000000-1;
    SysTick->CTRL |= 0x4;
    P1->OUT |= 0x01;
    SysTick->CTRL |= 0x1;

    Uprint("\n\r\n\rEnter the number of temperature readings (1-5): ");
    choice = getChoice();

    //set red turn off green
    
    for(int i = 1; i <= ans; i++) {   
        int y = 0;
        int temp = ADCRead() - 500;
        float tempC = (float)temp / 10;
        float tempF = (tempC * (9.0 / 5.0) + 32.0);
        while((SysTick->CTRL & 0x10000) == 0) {
            // Do nothing
        }

        char numlist[50];
        sprintf(numlist,"Reading %d: %.2f C & %.2f F \n\r", i, tempC, tempF); 
        int x = 0;

        while(numlist[x] != 0) {
            EUSCI_A0->TXBUF = numlist[x];
            while((EUSCI_A0->IFG & 2)==0) {
                // Do nothing
            }
            x++;
        }
    }
}
