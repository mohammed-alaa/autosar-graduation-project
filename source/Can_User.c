/*
 * Can_User.c
 *
 *  Created on: Oct 21, 2021
 *      Author: Mohamed
 */

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "inc/tm4c123gh6pm.h"
#include "include/ComStack_Types.h"
#include "include/Can_GeneralTypes.h"
#include "include/Canif_Cbk.h"
#include "include/Com_Types.h"

tCANMsgObject sCANMessage_RX_2;
tCANMsgObject sCANMessage_RX_0;
tCANMsgObject sCANMessage_TX;
tCANMsgObject sCANMessage_TX_2;

uint8_t pui8MsgData[4];
uint8_t pui8MsgData_RX_2[8];
uint8_t pui8MsgData_RX_0[8];

uint8_t ui32MsgData_TX[4] = {0, 0, 0, 0};
uint8_t ui32MsgData_TX2[4];

// This function is the interrupt handler for the CAN peripheral.

void CANIntHandler(void)
{
    uint32_t ui32Status;
    PduInfoType Rx_PduInfo0_2;
    Can_HwType Rx_Mailbox0_2;

    // Read the CAN interrupt status to find the cause of the interrupt
    ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);

    // If the cause is a controller status interrupt, then get the status
    if (ui32Status == CAN_INT_INTID_STATUS)
    {
        ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
    }
    else if (ui32Status == 2)
    {
        CANIntClear(CAN0_BASE, 2);
    }
    else if (ui32Status == 4)
    {
        CANIntClear(CAN0_BASE, 4);
    }
    else if (ui32Status == 3)
    {
        CANIntClear(CAN0_BASE, 3);
        sCANMessage_RX_2.pui8MsgData = pui8MsgData_RX_2;
        CANMessageGet(CAN0_BASE, 3, &sCANMessage_RX_2, 0);

        Rx_Mailbox0_2.id = sCANMessage_RX_2.ui32MsgID;
        Rx_Mailbox0_2.hoh = 1;
        Rx_Mailbox0_2.controllerlId = 0; //controller 0

        Rx_PduInfo0_2.SduLength = sCANMessage_RX_2.ui32MsgLen;
        Rx_PduInfo0_2.SduDataPtr = sCANMessage_RX_2.pui8MsgData;
        CanIf_RxIndication(&Rx_Mailbox0_2, &Rx_PduInfo0_2);
    }
    else if (ui32Status == 1)
    {
        //T1.D: Clear Rx mailbox interrupt.
        //T1.D: Get the recieved data through fucntion CANMessageGet
        //T1.D: Define variable of type Can_HwType and assign the right recieved data to it.
        //T1.D: Define variable of type PduInfoType and assign the right recieved data to it.
        //T1.D: Call the function CanIf_RxIdincation and pass to it the two created variables.

        CANIntClear(CAN0_BASE, 1);
        sCANMessage_RX_0.pui8MsgData = pui8MsgData_RX_0;
        CANMessageGet(CAN0_BASE, 1, &sCANMessage_RX_0, 0);

        Rx_Mailbox0_2.id = sCANMessage_RX_0.ui32MsgID;
        Rx_Mailbox0_2.hoh = 3;
        Rx_Mailbox0_2.controllerlId = 0; //controller 0

        Rx_PduInfo0_2.SduLength = sCANMessage_RX_0.ui32MsgLen;
        Rx_PduInfo0_2.SduDataPtr = sCANMessage_RX_0.pui8MsgData;
        CanIf_RxIndication(&Rx_Mailbox0_2, &Rx_PduInfo0_2);
    }
    else
    {
        // Spurious interrupt handling can go here.
    }
}

void Can_User_Init(void)
{
    // For this example CAN0 is used with RX and TX pins on port B4 and B5.

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    // Configure the GPIO pin muxing to select CAN0 functions for these pins.

    GPIOPinConfigure(GPIO_PB4_CAN0RX);
    GPIOPinConfigure(GPIO_PB5_CAN0TX);

    // Enable the alternate function on the GPIO pins.

    GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);

    // The GPIO port and pins have been set up for CAN.  The CAN peripheral must be enabled.

    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
    // Initialize the CAN controller
    CANInit(CAN0_BASE);

    // Set up the bit rate for the CAN bus
    CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
    //Enabling Loopback test mode
    CAN0_CTL_R |= 0x81;
    CAN0_TST_R |= 0x10;

    // Enable interrupts on the CAN peripheral.
    CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

    // Enable the CAN interrupt on the processor (NVIC).
    IntEnable(INT_CAN0);

    // Enable the CAN for operation.
    CANEnable(CAN0_BASE);

    //T1.A: Define message object of type recieve to be used to recieve message ID 0x77.
    //T1.A: the mailbox object should be configured to recieve the message length 4 bytes.

    sCANMessage_RX_0.ui32MsgID = 0x77;
    sCANMessage_RX_0.ui32MsgIDMask = 0x77;
    sCANMessage_RX_0.ui32Flags = (MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER);
    sCANMessage_RX_0.ui32MsgLen = 4;
    CANMessageSet(CAN0_BASE, 1, &sCANMessage_RX_0, MSG_OBJ_TYPE_RX);

    // Initialize a message object to be used for receiving CAN messages with
    // any CAN ID.  In order to receive any CAN ID, the ID and mask must both
    // be set to 0, and the ID filter enabled.
    sCANMessage_RX_2.ui32MsgID = 0x66;
    sCANMessage_RX_2.ui32MsgIDMask = 0xfffff;
    sCANMessage_RX_2.ui32Flags = (MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER);
    sCANMessage_RX_2.ui32MsgLen = 4;

    // Now load the message object into the CAN peripheral.  Once loaded the
    // CAN will receive any message on the bus, and an interrupt will occur.
    // Use message object 1 for receiving messages (this is not the same as
    // the CAN ID which can be any value in this example).
    CANMessageSet(CAN0_BASE, 3, &sCANMessage_RX_2, MSG_OBJ_TYPE_RX);

    ui32MsgData_TX[0] = 0;
    sCANMessage_TX.ui32MsgID = 0x66;
    sCANMessage_TX.ui32MsgIDMask = 0;
    sCANMessage_TX.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage_TX.ui32MsgLen = sizeof(ui32MsgData_TX);
    sCANMessage_TX.pui8MsgData = ui32MsgData_TX;

    //T1.B: Define message object of type Send to be used to Send message ID 0x77.
    //T1.B: the mailbox object should be configured to Send the message length 4 bytes.

    ui32MsgData_TX2[0] = 0;
    sCANMessage_TX_2.ui32MsgID = 0x77;
    sCANMessage_TX_2.ui32MsgIDMask = 0;
    sCANMessage_TX_2.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage_TX_2.ui32MsgLen = sizeof(ui32MsgData_TX2);
    sCANMessage_TX_2.pui8MsgData = ui32MsgData_TX2;
}

Std_ReturnType Can_Write(Can_HwHandleType HTH, const PduInfoType *PduInfo)
{
    //T1.C: Check HTH id, according to the HTH id choose the corresponding mailbox to send PDU data.
    //T1.C: Get the PduInfo lenght and assign it to the corresponding tx mailbox.
    //T1.C: Get the PduInfo Data pointer and pass it to the corresponding tx mailbox data buffer.
    //T1.C: Send the Tx message through fucntion CANMessageSet with the right input parameters.
    //T1.c: Use the ids (2 and 4) for Two configured tx Mailboxs.

    if (HTH == 1)
    {
        sCANMessage_TX_2.ui32MsgLen = PduInfo->SduLength;
        memcpy(ui32MsgData_TX2, PduInfo->SduDataPtr, PduInfo->SduLength);
        CANMessageSet(CAN0_BASE, 2, &sCANMessage_TX_2, MSG_OBJ_TYPE_TX);
        return E_OK;
    }
    else if (HTH == 3)
    {
        sCANMessage_TX.ui32MsgLen = PduInfo->SduLength;
        memcpy(ui32MsgData_TX, PduInfo->SduDataPtr, PduInfo->SduLength);
        CANMessageSet(CAN0_BASE, 4, &sCANMessage_TX, MSG_OBJ_TYPE_TX);
        return E_OK;
    }
    else
    {
        return E_NOT_OK;
    }
}
