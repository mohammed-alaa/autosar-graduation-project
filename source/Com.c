/*
 * Com.c
 *
 *  Created on: Oct 25, 2021
 *      Author: Mohamed
 */
#include "include/Com.h"
#include "include/PduR.h"

const ComConfig_type *ComConfig;
uint8_t NumberOfPDU_Signals[COM_NUM_OF_IPDU] = {
    COM_NUM_OF_SIGNAL};
void Com_Init(const ComConfig_type *config)
{
    ComConfig = config;
}

void Com_RxIndication(PduIdType PduId, const PduInfoType *PduInfoPtr)
{
    const ComIPdu_type *IPdu = GET_IPdu(PduId);
    memcpy(IPdu->ComIPduDataPtr, PduInfoPtr->SduDataPtr, IPdu->ComIPduSize);
    Com_RxProcessSignals(PduId);
}

void Com_RxProcessSignals(PduIdType PduId)
{
    const ComIPdu_type *IPdu = GET_IPdu(PduId);
    uint8_t signalId = 0;

    //Loop to the signals inside the PDU
    for (signalId = 0; signalId < COM_NUM_OF_SIGNAL; signalId++)
    {
        //T2.A: If the PDU processing is IMMEDIATE do the following:
        //T2.A: Call function Com_UnPackSignalsFromPdu to unpack signal and update signal buffer.
        //T2.A: If ComNotification for signal is not NULL call the corresponding signal notification function.
        //T2.A: If the PDU processing is DEFEERED just mark the signal as updated through ComSignalUpdated object.

        if (IPdu->ComIPduSignalProcessing == IMMEDIATE)
        {
            Com_UnPackSignalsFromPdu(PduId);

            if (IPdu->ComIPduSignalRef[signalId]->ComNotification != NULL)
            {
                IPdu->ComIPduSignalRef[signalId]->ComNotification();
            }
            else
            {
                /* Do nothing */
            }
        }
        else if (IPdu->ComIPduSignalProcessing == DEFERRED)
        {
            IPdu->ComIPduSignalRef[signalId]->ComSignalUpdated = 1;
        }
        else
        {
            /* Do nothing */
        }
    }
}

void Com_MainFunctionRx(void)
{
    const ComIPdu_type *IPdu = NULL;
    ComSignal_type *signal = NULL;
    uint8_t pduUpdated = 0;
    uint16_t pduId, signalID;

    for (pduId = 0; pduId < COM_NUM_OF_IPDU; pduId++)
    {
        IPdu = GET_IPdu(pduId);

        for (signalID = 0; signalID < COM_NUM_OF_SIGNAL; signalID++)
        {
            if ((IPdu->ComIPduSignalRef[signalID]->ComSignalUpdated) == 1)
            {
                pduUpdated = 1;
            }
        }
        if (pduUpdated && (IPdu->ComIPduSignalProcessing == DEFERRED) && (IPdu->ComIPduDirection == RECEIVE))
        {
            Com_UnPackSignalsFromPdu(pduId);
        }

        for (signalID = 0; signalID < NumberOfPDU_Signals[pduId]; signalID++)
        {
            signal = IPdu->ComIPduSignalRef[signalID];
            if (signal->ComSignalUpdated)
            {
                if (signal->ComNotification != NULL)
                {
                    signal->ComNotification();
                }
                signal->ComSignalUpdated = 0;
            }
        }
    }
}

uint8_t Com_SendSignal(const Com_SignalIdType SignalId, const void *SignalDataPtr)
{
    //T3.B: Get the sighal using GET_Signal routine
    //T3.B: Update the signal buffer with the input SignalDataPtr

    const ComSignal_type *signal = GET_Signal(SignalId);
    memcpy(signal->ComSignalDataPtr, SignalDataPtr, (signal->ComBitSize / 8));
    return E_OK;
}

uint8_t Com_RecieveSignal(const Com_SignalIdType SignalId, void *SignalDataPtr)
{
    //T2.C: Get the sighal using GET_Signal routine.
    //T2.C: Update the SignalDataPtr with signal Data, through memcpy routine.

    const ComSignal_type *signal = GET_Signal(SignalId);
    memcpy(SignalDataPtr, signal->ComSignalDataPtr, (signal->ComBitSize / 8));
    return E_OK;
}

void Com_MainFunctionTx(void)
{
    ComIPdu_type *IPdu;
    uint16_t pduId;
    for (pduId = 0; pduId < COM_NUM_OF_IPDU; pduId++)
    {
        IPdu = GET_IPdu(pduId);

        //T3.A: Check PDU ComIPduDirection if SEND do the following:
        //T3.A: Switch on ComTxModeMode case PERIODIC do the following:
        //T3.A: Update ComTxModeTimePeriod_Processing value(Subtract from it ComTxTimeBase).
        //T3.A: If ComTxModeTimePeriod_Processing reached zero, call Com_TriggerIPDUSend and reset it to default ComTxModeTimePeriod.
        if (IPdu->ComIPduDirection == SEND)
        {
            switch (IPdu->ComTxModeMode)
            {
            case PERIODIC:
                IPdu->ComTxModeTimePeriod_Processing -= ComConfig->ComTimeBase.ComTxTimeBase;

                if (IPdu->ComTxModeTimePeriod_Processing == 0)
                {
                    if (Com_TriggerIPDUSend(pduId) == E_OK)
                    {
                        IPdu->ComTxModeTimePeriod_Processing = IPdu->ComTxModeTimePeriod;
                    }
                    else
                    {
                        /* Do nothing */
                    }
                }
                else
                {
                    /* Do nothing */
                }
                break;
            }
        }
    }
}

Std_ReturnType Com_TriggerIPDUSend(PduIdType PduId)
{
    const ComIPdu_type *IPdu = GET_IPdu(PduId);
    PduInfoType PduInfoPackage;
    Com_PackSignalsToPdu(PduId);
    PduInfoPackage.SduDataPtr = (uint8_t *)IPdu->ComIPduDataPtr;
    PduInfoPackage.SduLength = IPdu->ComIPduSize;
    if (PduR_ComTransmit(PduId, &PduInfoPackage) == E_OK)
    {
    }
    else
    {
        return E_NOT_OK;
    }
    return E_OK;
}

void Com_PackSignalsToPdu(PduIdType PduId)
{
    uint8_t signalID = 0;
    ComSignal_type *signal = NULL;
    const ComIPdu_type *IPdu = GET_IPdu(PduId);

    for (signalID = 0; signalID < COM_NUM_OF_SIGNAL; signalID++)
    {
        signal = IPdu->ComIPduSignalRef[signalID];
        memcpy(IPdu->ComIPduDataPtr, signal->ComSignalDataPtr, (signal->ComBitSize) / 8);
    }
}

void Com_UnPackSignalsFromPdu(PduIdType PduId)
{
    uint8_t signalID = 0;
    const ComSignal_type *signal = NULL;
    const ComIPdu_type *IPdu = GET_IPdu(PduId);

    for (signalID = 0; signalID < COM_NUM_OF_SIGNAL; signalID++)
    {
        //T2.B: Get signal pointer from the PDU
        //T2.B: Copy PDU data inside the signal buffer, with number of bytes equal signal size(bits)/8

        signal = IPdu->ComIPduSignalRef[signalID];
        memcpy(signal->ComSignalDataPtr, IPdu->ComIPduDataPtr, (signal->ComBitSize) / 8);
    }
}