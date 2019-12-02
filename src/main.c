//
//  main.c
//  ESET269Final
//
//  Created by Kris Elers on 11/18/19.
//  Copyright © 2019 Kris Elers. All rights reserved.
//

/*Include files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(void) {
	EUSCI_A0->CTLW0 |= 1;	// Put into reset state
	EUSCI_A0->MCTLW = 0;
	EUSCI_A0->CTLW0 = 0x0081;	// 1 stop bit, no parity, SMCLK, 8-BIT DATA
	EUSCI_A0->BRW = 26;	// Baud rate
	P1->SEL0 |= 0x0C;	// SEL0 value
	P1->SEL1 &= ~0x0C;	// SEL1 value
	EUSCI_A0->CTLW0 &= -1;	// Take out for reset state

    getMenu();
    
    /* Go in waiting state. Will modify in later labs */
    while(1);
}	// main
