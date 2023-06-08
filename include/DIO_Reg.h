/*
 * DIO_Reg.h
 *
 *  Created on: Nov 6, 2021
 *      Author: Mohamed
 */

#ifndef DIO_REG_H_
#define DIO_REG_H_

#define RCGCGPIO *((volatile uint32_t *)0x400FE608)       // General-Purpose Input/Output Run Mode Clock Gating Control, base 0x400FE000, offset 0x608
#define GPIODEN_PORTF *((volatile uint32_t *)0x4002551C)  // Enable DIO functionality for PORTF
#define GPIODIR_PORTF *((volatile uint32_t *)0x40025400)  // Control PORTF Direction I/O
#define GPIODATA_PORTF *((volatile uint32_t *)0x400253FC) // GPIO DATA, Enable the corresponding bits from (2-9) in the address bus, BASE + 0x3FC
#define GPIOPUR_PORTF *((volatile uint32_t *)0x40025510)  // GPIO Pull-Up Select

#endif /* DIO_REG_H_ */
