//
//  functions.c
//  ESET269Final
//
//  Created by Kris Elers on 11/18/19.
//  Copyright © 2019 Kris Elers. All rights reserved.
//

#include "functions.h"

//void ADCInit(void) {
//    ADC14->CTL0 =  0x00000010;    // power on and disable during configuration
//    ADC14->CTL0 |= 0x04080300;    // sample and hold mode, sysclk, 32 sample clocks, software trigger
//    ADC14->CTL1 =  0x00000030;    // 14-bit resolution
//    ADC14->MCTL[2] = 1;           // A1 input, single-ended, Vref=AVCC
//    P5->SEL1 |= 0x10;             // Configure P5.4 for A1
//    P5->SEL0 |= 0x10;
//    ADC14->CTL1 |= 0x00020000;    // convert for memory reg. 2
//    ADC14->CTL0 |= 2;             // enable ADC
//    return;
//}

//int ADCRead(void) {
//    int z = 0;
//    ADC14->CTL0 |= 1;         // start a conversion
//    while (!ADC14->IFGR0);    // wait till conversion complete
//    z = ADC14->MEM[2];       // read conversion result
//    return z;
//}

void mainMenu(void) {
    printf("\n\t\tMSP432 Menu\n\n");
    printf("1. RGB Control\n");
    printf("2. Digital Input\n");
    printf("3. Temperature Reading\n");
}

void getMenu(void) {
    char option = '0';
    
    while(option != '4') {
        mainMenu();
        printf("Select Option: ");
        scanf(" %c", &option);
        switch(option) {
            case '1':
                rgbControl();
                break;
            case '2':
                digitalInput();
                break;
            case '3':
                tempReading();
                break;
            case '4':
                printf("Stopping program...");
                break;
            default:
                printf("\nYou pressed an invalid key. Please try again.");
        }
    }
}

void rgbControl(void) {
    //TO-DO
}

void digitalInput(void) {
    //TO-DO
    //Lab 7-9
    //
}

void tempReading(void) {
    //TO-DO (48)
}
