/*
 * Utilities.h
 *
 *  Created on: Dec 16, 2020
 *      Author: Mohamed
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#define SET_BIT(VAR, BITNO) (VAR) |= (1 << (BITNO))
#define CLR_BIT(VAR, BITNO) (VAR) &= ~(1 << (BITNO))
#define TOG_BIT(VAR, BITNO) (VAR) ^= (1 << (BITNO))
#define GET_BIT(VAR, BITNO) (((VAR) >> (BITNO)) & 0x01)

#endif /* UTILITIES_H_ */
