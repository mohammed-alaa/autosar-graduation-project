/*
 * Can_User.h
 *
 *  Created on: Oct 21, 2021
 *      Author: Mohamed
 */

#ifndef CAN_USER_H_
#define CAN_USER_H_

#include "include/ComStack_Types.h"
#include "include/Can_GeneralTypes.h"
#include "include/Com_Types.h"

void Can_User_Init(void);
Std_ReturnType Can_Write(Can_HwHandleType HTH, PduInfoType *PduInfo);

#endif /* CAN_USER_H_ */
