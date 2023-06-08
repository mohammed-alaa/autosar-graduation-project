/*
 * PduR_Cbk.h
 *
 *  Created on: Oct 21, 2021
 *      Author: Mohamed
 */

#ifndef INCLUDE_PDUR_H_
#define INCLUDE_PDUR_H_
#include "include/Com_Cbk.h"

void PduR_CanIfRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);
Std_ReturnType PduR_ComTransmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);

#endif /* INCLUDE_PDUR_H_ */
