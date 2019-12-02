//
//  functions.c
//  ESET269Final
//
//  Created by Kris Elers on 11/18/19.
//  Copyright © 2019 Kris Elers. All rights reserved.
//

#include "functions.h"


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


int getChoice(void) {
    char choice[2];
    int i = 0;

    while(1) {
        if((EUSCI_A0->IFG & 1) != 0) {
            choice[i] = EUSCI_A0->RXBUF;    // Place current character in array
            if(choice[i] == '\r') { // Enter key pressed
                choice[i] = '/0';
                return atoi(choice);
            } else {
                i++;
            }
        }
    }
}   // getChoice


void mainMenu(void) {
    Uprint("\n\t\tMSP432 Menu\n\n");
    Uprint("1. RGB Control\n");
    Uprint("2. Digital Input\n");
    Uprint("3. Temperature Reading\n");
}   // mainMenu


void getMenu(void) {
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
                printf("Stopping program...");
                break;
            default:
                printf("\nYou pressed an invalid key. Please try again.");
        }
    }
}   // getMenu


void rgbControl(void) {
    //TO-DO
}   // rgbControl


void digitalInput(void) {
    //TO-DO
    //Lab 7-9
    //
}   // digitalInput


void tempReading(void) {
    //TO-DO (48)
}   // tempReading
