/*
 * Rte_Light_SWC.h
 *
 *  Created on: Nov 8, 2021
 *      Author: Mohamed
 */

#ifndef INCLUDE_RTE_LIGHT_SWC_H_
#define INCLUDE_RTE_LIGHT_SWC_H_

/* Light Colors */
#define LIGHT_COLOR_RED (GPIO_PIN_1)
#define LIGHT_COLOR_BLUE (GPIO_PIN_2)
#define LIGHT_COLOR_GREEN (GPIO_PIN_3)

/* Light Port */
#define LIGHT_PORT (GPIO_PORTF_BASE)

/* Light Turn-on Values */
#define LIGHT_ON_NONE (0)
#define LIGHT_ON_RED (2)
#define LIGHT_ON_BLUE (4)
#define LIGHT_ON_GREEN (8)

void Led_CheckState10ms(void);

#endif /* INCLUDE_RTE_LIGHT_SWC_H_ */
