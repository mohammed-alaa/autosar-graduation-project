/*
 * PduR.c
 *
 *  Created on: Oct 21, 2021
 *      Author: Mohamed
 */

#include <stdint.h>
#include "include/ComStack_Types.h"
#include "include/Can_GeneralTypes.h"
#include "include/Com_Types.h"
#include "include/Canif.h"
#include "include/PduR.h"

void PduR_CanIfRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
    Com_RxIndication(RxPduId, PduInfoPtr);
}

Std_ReturnType PduR_ComTransmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    return CanIf_Transmit(TxPduId, PduInfoPtr);
}
