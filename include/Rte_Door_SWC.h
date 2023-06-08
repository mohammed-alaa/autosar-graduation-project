/*
 * Rte_Door_SWC.h
 *
 *  Created on: Nov 6, 2021
 *      Author: Mohamed
 */

#ifndef INCLUDE_RTE_DOOR_SWC_H_
#define INCLUDE_RTE_DOOR_SWC_H_

/* Button States */
#define BUTTON_STATE_RELEASED (0)
#define BUTTON_STATE_PRESSED (1)
#define BUTTON_STATE_LONG   (2)

/* Button states times */
#define BUTTON_PRESS_SHORT_TIME (10)
#define BUTTON_PRESS_LONG_TIME (300)

/* Button Settings */
#define BUTTON_PORT (GPIO_PORTF_BASE)
#define BUTTON_PIN (GPIO_PIN_4)

void Door_UpdateState10ms(void);
void Door_CheckState10ms(void);
void Door_CheckColor3s(void);

#endif /* INCLUDE_RTE_DOOR_SWC_H_ */
