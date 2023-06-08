/*
 * Com.h
 *
 *  Created on: Oct 25, 2021
 *      Author: Mohamed
 */

#ifndef INCLUDE_COM_H_
#define INCLUDE_COM_H_

#include "Com_Types.h"
#include "ComStack_Types.h"

#include "Com_Cfg.h"
#include "Com_Helper.h"
#include "Com_Cbk.h"

/*initializes internal and external interfaces and variables of the COM module */
void Com_Init(const ComConfig_type *config);

//process signals if the signal processing mode is IMMEDIATE -> notify the signal callback , else -> mark signal as updated
void Com_RxProcessSignals(PduIdType PduId);

void Com_UnPackSignalsFromPdu(PduIdType PduId);

void Com_MainFunctionRx(void);

void Com_MainFunctionTx(void);

Std_ReturnType Com_TriggerIPDUSend(PduIdType PduId);

void Com_PackSignalsToPdu(PduIdType PduId);

uint8_t Com_SendSignal(const Com_SignalIdType SignalId, const void *SignalDataPtr);
uint8_t Com_RecieveSignal(const Com_SignalIdType SignalId, void *SignalDataPtr);

#endif /* INCLUDE_COM_H_ */
