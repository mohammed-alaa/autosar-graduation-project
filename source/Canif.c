/*
 * Canif.c
 *
 *  Created on: Oct 21, 2021
 *      Author: Mohamed
 */
#include <stdbool.h>
#include <stdint.h>
#include "include/Can_User.h"
#include "include/ComStack_Types.h"
#include "include/Can_GeneralTypes.h"
#include "include/Com_Types.h"
#include "include/PduR.h"

void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr)
{
    //should convert Mainbox id to PduID type
    PduIdType Pdu_ID = (Mailbox->hoh) - 1;
    PduInfoType Pdu_Info;
    Pdu_Info.SduDataPtr = PduInfoPtr->SduDataPtr;
    Pdu_Info.SduLength = PduInfoPtr->SduLength;
    PduR_CanIfRxIndication(Pdu_ID, &Pdu_Info);
}

Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    return Can_Write(TxPduId, PduInfoPtr);
}
