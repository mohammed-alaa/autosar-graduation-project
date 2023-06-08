/*
 * DOOR_SWC.c
 *
 *  Created on: Nov 6, 2021
 *      Author: Mohamed
 */

//T4.A: Design the DOOR_SWC with the following specifications:
//T4.A: The SWC should have a runnable to check the door current state, the runnable should check every 10ms.
//T4.A: The SWC should have a runnable to send Door State changes to the corresponding Com signal.
//T4.A: The SWC should have a runnable to send the change in light color if door is opened for more that 3 seconds.
//T4.A: The SWC shuoldn't access Com_SendSignal directly, it should be accessed through RTE module(e.g. RTE_Write_Signalname).

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "include/Rte_Door_SWC.h"

extern void RTE_Send_ButtonPress(uint32_t au32ButtonState);
extern void RTE_Send_ButtonHold(uint32_t au32ButtonState);

static uint8_t gu8ButtonCurrState = BUTTON_STATE_RELEASED;
static uint8_t gu8ButtonPrevState = BUTTON_STATE_RELEASED;
static uint8_t gu8ButtonSinglePressCounter = 0;
static uint16_t gu16ButtonLongPressCounter = 0;
static uint8_t gu8ButtonStateSingle = 0;

static uint8_t Door_ReadState(void)
{
    if (GPIOPinRead(BUTTON_PORT, BUTTON_PIN) == 0)
    {
        return BUTTON_STATE_PRESSED;
    }
    else
    {
        return BUTTON_STATE_RELEASED;
    }
}

static void Door_ResetValues(void)
{
    gu8ButtonCurrState = BUTTON_STATE_RELEASED;
    gu8ButtonPrevState = BUTTON_STATE_RELEASED;
    gu8ButtonSinglePressCounter = 0;
    gu16ButtonLongPressCounter = 0;
    gu8ButtonStateSingle = 0;
}

void Door_UpdateState10ms(void)
{
    /* Read button state */
    uint8_t au8IsButtonPressed = Door_ReadState();

    /* Check whether button is pressed */
    if (au8IsButtonPressed == BUTTON_STATE_PRESSED)
    {
        /* Check whether the button state isnt single pressed */
        if (!gu8ButtonStateSingle)
        {
            /* Increase single press counter and check whether its over the debounce */
            if (++gu8ButtonSinglePressCounter >= BUTTON_PRESS_SHORT_TIME)
            {
                /* Set the single press variable to 1 to indicate that the variable is pressed */
                gu8ButtonStateSingle = 1;
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

        /* Check if button is pressed and previous state was pressed */
        if (gu8ButtonStateSingle && (gu8ButtonPrevState == BUTTON_STATE_PRESSED))
        {
            /* Increase long press counter and check if its over long press time minimum value */
            if (++gu16ButtonLongPressCounter >= BUTTON_PRESS_LONG_TIME)
            {
                /* Set the current state to be long press */
                gu8ButtonCurrState = BUTTON_STATE_LONG;
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

        /* Set the previous button state to be as the current state */
        gu8ButtonPrevState = au8IsButtonPressed;
    }
    /* Check whether button isnt pressed */
    else if (au8IsButtonPressed == BUTTON_STATE_RELEASED)
    {
        /* Check if button is single pressed */
        if (gu8ButtonStateSingle)
        {
            /* Check if the single press counter is > 0 */
            if (gu8ButtonSinglePressCounter)
            {
                /* Decrease the sinle press counter by 1 */
                gu8ButtonSinglePressCounter--;
            }
            else
            {
                /* Set the single press variable to 0 which means the button is no longer pressed */
                gu8ButtonStateSingle = 0;

                /* Check if the long press counter is less than the minimum value of long press time */
                if (gu16ButtonLongPressCounter < BUTTON_PRESS_LONG_TIME)
                {
                    /* Set the current state to be pressed */
                    gu8ButtonCurrState = BUTTON_STATE_PRESSED;
                }
                else
                {
                    /* Do nothing */
                }
            }
        }
        else
        {
            /* Set the long press counter to 0 */
            gu16ButtonLongPressCounter = 0;
        }
    }
    else
    {
        /* Do nothing */
    }
}

void Door_CheckState10ms(void)
{
    if (gu8ButtonCurrState == BUTTON_STATE_PRESSED)
    {
        RTE_Send_ButtonPress(1);
        Door_ResetValues();
    }
    else
    {
        RTE_Send_ButtonPress(0);
    }
}

void Door_CheckColor3s(void)
{
    if (gu8ButtonCurrState == BUTTON_STATE_LONG)
    {
        RTE_Send_ButtonHold(1);
        Door_ResetValues();
    }
    else
    {
        RTE_Send_ButtonHold(0);
    }
}
