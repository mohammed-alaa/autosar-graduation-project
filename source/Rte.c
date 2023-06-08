/*
 * Rte.c
 *
 *  Created on: Nov 6, 2021
 *      Author: Mohamed
 */

//T6.A: Implement the RTE used PORTs for both sending and receiving signals from Application.

#include "include/Com.h"

/* Button Signals */
#define SIGNAL_BUTTON_PRESS (1)
#define SIGNAL_BUTTON_HOLD (3)

/* LED Signals */
#define SIGNAL_LED_PRESS (2)
#define SIGNAL_LED_HOLD (0)

void RTE_Send_ButtonPress(uint32_t au32ButtonPress)
{
    const uint32_t *pu32ButtonPress = &au32ButtonPress;
    Com_SendSignal(SIGNAL_BUTTON_PRESS, pu32ButtonPress);
}

void RTE_Send_ButtonHold(uint32_t au32ButtonHold)
{
    const uint32_t *pu32ButtonHold = &au32ButtonHold;
    Com_SendSignal(SIGNAL_BUTTON_HOLD, pu32ButtonHold);
}

void RTE_Receive_ButtonPress(uint32_t *pu32ButtonPress)
{
    Com_RecieveSignal(SIGNAL_LED_PRESS, pu32ButtonPress);
}

void RTE_Receive_ButtonHold(uint32_t *pu32ButtonHold)
{
    Com_RecieveSignal(SIGNAL_LED_HOLD, pu32ButtonHold);
}
