

/**
 * main.c
 */
#include <stdbool.h>
#include <stdint.h>
#include "include/Can_User.h"
#include "include/Com.h"
#include "FreeRtos/FreeRTOS.h"
#include "FreeRtos/task.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

extern const ComConfig_type ComConfiguration;

extern void Task_DoorCheck_10ms(void *pvParameters);
extern void Task_ButtonPressed_10ms(void *pvParameters);
extern void Task_ButtonHeld_10ms(void *pvParameters);
extern void Task_SendIPUs_10ms(void *pvParameters);
extern void Task_ReceiveIPUs_10ms(void *pvParameters);
extern void Task_LedCheck_10ms(void *pvParameters);

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    //T8.A: Initialize TivaC DIO.
    //T8.A: Use SW1 as inupt, and the three leds (RGB LEDs) as output.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3));
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    //T8.B: Initialize the AUTOSAR Com Stack
    //T8.B: call can init function, call com init function and pass to it the configuration structure ComConfiguration by reference

    Can_User_Init();
    Com_Init(&ComConfiguration);

    //T8.C: Initialize the OS and create the needed tasks with the right input parameters
    //T8.C: Call vTaskStartScheduler() to start OS.

    xTaskCreate(Task_DoorCheck_10ms, NULL, 100, NULL, 1, NULL);
    xTaskCreate(Task_ButtonPressed_10ms, NULL, 100, NULL, 1, NULL);
    xTaskCreate(Task_ButtonHeld_10ms, NULL, 100, NULL, 1, NULL);

    xTaskCreate(Task_SendIPUs_10ms, NULL, 100, NULL, 1, NULL);
    xTaskCreate(Task_ReceiveIPUs_10ms, NULL, 100, NULL, 1, NULL);

    xTaskCreate(Task_LedCheck_10ms, NULL, 100, NULL, 1, NULL);

    vTaskStartScheduler();

    while (1)
    {
    }

    return 0;
}
