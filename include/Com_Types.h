/*
 * Com_Types.h
 *
 *  Created on: Oct 25, 2021
 *      Author: Mohamed
 */

#ifndef INCLUDE_COM_TYPES_H_
#define INCLUDE_COM_TYPES_H_

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    E_NOT_OK,
    E_OK
} Std_ReturnType;

#define NULL 0

/* Signal object identifier */
typedef uint16_t Com_SignalIdType;

/* The direction defines if this I-PDU, shall be sent or received */
typedef enum
{
    RECEIVE,
    SEND
} ComIPduDirection_type;

typedef enum
{
    DEFERRED,
    IMMEDIATE
} ComIPduSignalProcessing_type;

typedef enum
{
    BOOLEAN,
    FLOAT32,
    FLOAT64,
    UINT8,
    UINT16,
    UINT32,
    UINT8_N,
    UINT8_DYN,
    SINT8,
    SINT16,
    SINT32,
    SINT64,
    UINT64
} ComSignalType_type;

/* Defines if a write access to this signal can trigger the transmission of the correspon-ding I-PDU. */
typedef enum
{
    PENDING,
    TRIGGERED,
    TRIGGERED_ON_CHANGE
} ComTransferProperty_type;

/* Available Transmission modes for I-PDU */
typedef enum
{
    DIRECT,
    MIXED,
    NONE,
    PERIODIC
} ComTxModeMode_type;

/* Contains the configuration parameters of the AUTOSAR COM module's signals. */
typedef struct
{
    /*  This parameter refers to the position in the I-PDU and not in the shadow buffer.*/
    uint32_t ComBitPosition;

    /* The numerical value used as the ID. */
    uint16_t ComHandleId;

    /* Size in bits, for integer signal types. */
    uint8_t ComBitSize;

    /*  The AUTOSAR type of the signal.*/
    const ComSignalType_type ComSignalType;

    /*  Defines if a write access to this signal can trigger the transmission of the correspon-ding I-PDU.*/
    const ComTransferProperty_type ComTransferProperty;

    /* IPDU id of the IPDU that this signal belongs to. */
    const uint16_t ComIPduHandleId;

    /* Defines whether the signal new data recieved or not*/
    uint8_t ComSignalUpdated;

    /* Pointer to Signal data buffer*/
    void *const ComSignalDataPtr;

    /* notification function for signal. */
    void (*ComNotification)(void);

} ComSignal_type;

typedef struct
{
    /* size of the Pdu in bytes */
    uint8_t ComIPduSize; /* violation of the sws container */

    /* sent or received */
    ComIPduDirection_type ComIPduDirection;

    /* The numerical value used as the ID of this I-PDU */
    uint16_t ComIPduHandleId;

    /* Define the PDU periodicity on the bus this value shouldn't be changed  */
    const uint16_t ComTxModeTimePeriod;

    /* Define the PDU periodicity on the bus this value can be changed  */
    uint16_t ComTxModeTimePeriod_Processing;

    /* Define the Tx mode for PDU*/
    const ComTxModeMode_type ComTxModeMode;

    /* Define whether the PDU processing is IMMEDIATE or DEFERRED*/
    ComIPduSignalProcessing_type ComIPduSignalProcessing;

    /* Reference to the actual pdu data storage */
    uint8_t *const ComIPduDataPtr;

    /* References to all signals contained in this IPDU.*/
    ComSignal_type *const *ComIPduSignalRef;

} ComIPdu_type;

typedef struct
{

    /* The period between successive calls to Com_MainFunctionRx in ms */
    uint16_t ComRxTimeBase;

    /* The period between successive calls to Com_MainFunctionTx in ms */
    uint16_t ComTxTimeBase;

} ComTimeBase_type;

/* contains the configuration parameters and sub containers of the AUTOSAR COM module */
typedef struct
{
    const ComTimeBase_type ComTimeBase;

    /* IPDU definitions */
    const ComIPdu_type *ComIPdu;

    /* Signal definitions */
    const ComSignal_type *ComSignal;

} ComConfig_type;

#endif /* INCLUDE_COM_TYPES_H_ */
