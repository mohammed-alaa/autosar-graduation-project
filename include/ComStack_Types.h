/*
 * ComStack_Types.h
 *
 *  Created on: Oct 21, 2021
 *      Author: Mohamed
 */

#ifndef INCLUDE_COMSTACK_TYPES_H_
#define INCLUDE_COMSTACK_TYPES_H_

typedef uint32_t PduLengthType;
typedef uint32_t PduIdType;

typedef struct
{
    uint8_t *SduDataPtr;
    PduLengthType SduLength;
} PduInfoType;

#endif /* INCLUDE_COMSTACK_TYPES_H_ */
