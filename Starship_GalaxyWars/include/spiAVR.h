#ifndef SPIAVR_H
#define SPIAVR_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "helper.h"


//B5 should always be SCK(spi clock) and B3 should always be MOSI. If you are using an
//SPI peripheral that sends data back to the arduino, you will need to use B4 as the MISO pin.
//The SS pin can be any digital pin on the arduino. Right before sending an 8 bit value with
//the SPI_SEND() funtion, you will need to set your SS pin to low. If you have multiple SPI
//devices, they will share the SCK, MOSI and MISO pins but should have different SS pins.
//To send a value to a specific device, set it's SS pin to low and all other SS pins to high.

// [0-7] PORTD (8bit)
// [8-13] PORTB (6bit)
// [A0-A5] PORTC (6bit)
// Output: DDR=1, PORT=0
// PINx: Read Input
// PORTx: Set Output

// Outputs, pin definitions
#define PIN_SCK                   PORTB5 // SHOULD ALWAYS BE B5 (13) ON THE ARDUINO
#define PIN_MOSI                  PORTB3 // SHOULD ALWAYS BE B3 (11) ON THE ARDUINO
#define PIN_SS                    PORTB2 // Always B2 (10)


//If SS is on a different port, make sure to change the init to take that into account.
void SPI_INIT(){
    DDRB |= (1 << PIN_SCK) | (1 << PIN_MOSI) | (1 << PIN_SS); //initialize your pins. 
    SPCR |= (1 << SPE) | (1 << MSTR); //initialize SPI coomunication
}

void SPI_SEND(char data)
{
    PORTB = SetBit(PORTB, PIN_SS, 0);
    
    SPDR = data; //set data that you want to transmit
    while (!(SPSR & (1 << SPIF)));// wait until done transmitting

    PORTB = SetBit(PORTB, PIN_SS, 1);
}

#endif /* SPIAVR_H */