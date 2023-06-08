/*
 * Com_Cfg.c
 *
 *  Created on: Oct 25, 2021
 *      Author: Mohamed
 */
#include "include/Com_Types.h"
#include "include/Com_Cfg.h"

uint8_t ComSignalBuffer_1[4];
uint8_t ComSignalBuffer_2[4];
uint8_t ComSignalBuffer_Tx[4];
uint8_t ComSignalBuffer_Tx_2[4];

ComSignal_type ComSignal[] =
    {
        {//signal0_Rx
         .ComBitPosition = 0,
         .ComHandleId = 0,
         .ComBitSize = 32,
         .ComSignalType = UINT32,
         .ComIPduHandleId = 1,
         .ComSignalUpdated = 0,
         .ComSignalDataPtr = ComSignalBuffer_1},
        {//signal0_Tx
         .ComBitPosition = 0,
         .ComHandleId = 1,
         .ComBitSize = 32,
         .ComSignalType = UINT32,
         .ComTransferProperty = PENDING,
         .ComIPduHandleId = 1,
         .ComSignalUpdated = 0,
         .ComSignalDataPtr = ComSignalBuffer_Tx},
        {//signal0_Rx2
         .ComBitPosition = 0,
         .ComHandleId = 0,
         .ComBitSize = 32,
         .ComSignalType = UINT32,
         .ComIPduHandleId = 1,
         .ComSignalUpdated = 0,
         .ComSignalDataPtr = ComSignalBuffer_2},
        {//signal0_Tx2
         .ComBitPosition = 0,
         .ComHandleId = 1,
         .ComBitSize = 32,
         .ComSignalType = UINT32,
         .ComTransferProperty = PENDING,
         .ComIPduHandleId = 1,
         .ComSignalUpdated = 0,
         .ComSignalDataPtr = ComSignalBuffer_Tx_2}};

/* IPdu signal lists. */
ComSignal_type *ComIPduSignalRefs_Can_Message_RX_1[] = {
    &ComSignal[0]};
ComSignal_type *ComIPduSignalRefs_Can_Message_RX_2[] = {
    &ComSignal[2]};
ComSignal_type *ComIPduSignalRefs_Can_Message_Tx_1[] = {
    &ComSignal[1]};
ComSignal_type *ComIPduSignalRefs_Can_Message_Tx_2[] = {
    &ComSignal[3]};

uint8_t ComIPduBuffer_RX_1[4];
uint8_t ComIPduBuffer_RX_2[4];
uint8_t ComIPduBuffer_TX_1[4];
uint8_t ComIPduBuffer_TX_2[4];

/* Com Ipdu */
ComIPdu_type ComIPdu[] =
    {
        {
            // Message_RX_1
            .ComIPduDirection = RECEIVE,
            .ComIPduSize = 4,
            .ComIPduSignalProcessing = DEFERRED,
            .ComIPduHandleId = 1,
            .ComIPduSignalRef = ComIPduSignalRefs_Can_Message_RX_1,
            .ComIPduDataPtr = ComIPduBuffer_RX_1,
        },
        {// Message_TX_1
         .ComIPduDirection = SEND,
         .ComIPduSize = 4,
         .ComIPduSignalProcessing = IMMEDIATE,
         .ComIPduHandleId = 2,
         .ComIPduSignalRef = ComIPduSignalRefs_Can_Message_Tx_1,
         .ComIPduDataPtr = ComIPduBuffer_TX_1,
         .ComTxModeTimePeriod = 10,
         .ComTxModeTimePeriod_Processing = 100,
         .ComTxModeMode = PERIODIC},
        {
            //Message_RX_2
            .ComIPduDirection = RECEIVE,
            .ComIPduSize = 4,
            .ComIPduSignalProcessing = DEFERRED,
            .ComIPduHandleId = 1,
            .ComIPduSignalRef = ComIPduSignalRefs_Can_Message_RX_2,
            .ComIPduDataPtr = ComIPduBuffer_RX_2,
        },
        {// Message_TX_2
         .ComIPduDirection = SEND,
         .ComIPduSize = 4,
         .ComIPduSignalProcessing = IMMEDIATE,
         .ComIPduHandleId = 2,
         .ComIPduSignalRef = ComIPduSignalRefs_Can_Message_Tx_2,
         .ComIPduDataPtr = ComIPduBuffer_TX_2,
         .ComTxModeTimePeriod = 10,
         .ComTxModeTimePeriod_Processing = 100,
         .ComTxModeMode = PERIODIC}

};
const ComConfig_type ComConfiguration =
    {
        .ComTimeBase = {
            .ComRxTimeBase = 10,
            .ComTxTimeBase = 10},
        .ComIPdu = ComIPdu,
        .ComSignal = ComSignal};
