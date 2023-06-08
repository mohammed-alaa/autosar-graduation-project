/*
 * Light_SWC.c
 *
 *  Created on: Nov 6, 2021
 *      Author: Mohamed
 */

//T5.A: Design the Light_SWC with the following specifications:
//T5.A: The SWC should have a runnable to Read Door State and Light Color every 10ms.
//T5.A: correct action should be taken upon receiving the two signals.
//T5.A: The SWC shuoldn't access Com_ReceiveSignal directly, it should be accessed through RTE module(e.g. RTE_Read_Signalname).

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "include/Rte_Light_SWC.h"

extern void RTE_Receive_ButtonPress(uint32_t *au32ButtonState);
extern void RTE_Receive_ButtonHold(uint32_t *au32ButtonHold);

static uint32_t au32LightColor = LIGHT_COLOR_RED;
static uint32_t gu32IsSinglePress = 0;
static uint32_t gu32IsHoldPress = 0;
static uint8_t gu8LightValue = LIGHT_ON_RED;
static uint8_t au8IsLightOn = 0;
static uint8_t au8SkipToggle = 0;

void Led_CheckState10ms(void)
{
    RTE_Receive_ButtonPress(&gu32IsSinglePress);
    RTE_Receive_ButtonHold(&gu32IsHoldPress);

    if (gu32IsHoldPress)
    {
        gu32IsHoldPress = 0;
        au8SkipToggle = 1;
        GPIOPinWrite(LIGHT_PORT, au32LightColor, LIGHT_ON_NONE);

        if (au32LightColor == LIGHT_COLOR_RED)
        {
            au32LightColor = LIGHT_COLOR_GREEN;
            gu8LightValue = LIGHT_ON_GREEN;
        }
        else if (au32LightColor == LIGHT_COLOR_GREEN)
        {
            au32LightColor = LIGHT_COLOR_BLUE;
            gu8LightValue = LIGHT_ON_BLUE;
        }
        else
        {
            au32LightColor = LIGHT_COLOR_RED;
            gu8LightValue = LIGHT_ON_RED;
        }
    }
    else
    {
        /* Do nothing */
    }

    if (gu32IsSinglePress)
    {
        if (au8SkipToggle)
        {
            au8SkipToggle = 0;
        }
        else
        {
            gu32IsSinglePress = 0;
            au8IsLightOn = 1 - au8IsLightOn;
        }
    }
    else
    {
        /* Do nothing */
    }

    if (au8IsLightOn)
    {
        GPIOPinWrite(LIGHT_PORT, au32LightColor, gu8LightValue);
    }
    else
    {
        GPIOPinWrite(LIGHT_PORT, (LIGHT_COLOR_RED | LIGHT_COLOR_BLUE | LIGHT_COLOR_GREEN), LIGHT_ON_NONE);
    }
}
