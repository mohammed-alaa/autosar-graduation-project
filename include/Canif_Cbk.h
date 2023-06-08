/*
 * Canif_Cbk.h
 *
 *  Created on: Oct 21, 2021
 *      Author: Mohamed
 */

#ifndef INCLUDE_CANIF_CBK_H_
#define INCLUDE_CANIF_CBK_H_

void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr);

#endif /* INCLUDE_CANIF_CBK_H_ */
