/*
 * Rte_OS.c
 *
 *  Created on: Nov 6, 2021
 *      Author: Mohamed
 */

//T7.A: Implement the needed tasks for application (e.g. tasks to call application runnables).
//T7.A: Implement the needed tasks for BSW (e.g. tasks to call Com_MainfucntionTx and RX).

#include "FreeRtos/FreeRTOS.h"
#include "FreeRtos/task.h"
#include "include/Com.h"
#include "include/Rte_Door_SWC.h"
#include "include/Rte_Light_SWC.h"

void Task_DoorCheck_10ms(void *pvParameters)
{
    while (1)
    {
        Door_UpdateState10ms();
        vTaskDelay(10);
    }
}

void Task_ButtonPressed_10ms(void *pvParameters)
{
    while (1)
    {
        Door_CheckState10ms();
        vTaskDelay(10);
    }
}

void Task_ButtonHeld_10ms(void *pvParameters)
{
    while (1)
    {
        Door_CheckColor3s();
        vTaskDelay(10);
    }
}

void Task_LedCheck_10ms(void *pvParameters)
{
    while (1)
    {
        Led_CheckState10ms();
        vTaskDelay(10);
    }
}

void Task_SendIPUs_10ms(void *pvParameters)
{
    while (1)
    {
        Com_MainFunctionTx();
        vTaskDelay(10);
    }
}

void Task_ReceiveIPUs_10ms(void *pvParameters)
{
    while (1)
    {
        Com_MainFunctionRx();
        vTaskDelay(10);
    }
}
