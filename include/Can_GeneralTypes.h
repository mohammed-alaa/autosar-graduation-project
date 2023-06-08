/*
 * Can_GeneralTypes.h
 *
 *  Created on: Oct 21, 2021
 *      Author: Mohamed
 */

#ifndef INCLUDE_CAN_GENERALTYPES_H_
#define INCLUDE_CAN_GENERALTYPES_H_

typedef uint32_t Can_IdType;
typedef uint32_t Can_HwHandleType;

typedef struct Can_HwType
{
    Can_IdType id;
    Can_HwHandleType hoh;
    uint8_t controllerlId;
} Can_HwType;

#endif /* INCLUDE_CAN_GENERALTYPES_H_ */
