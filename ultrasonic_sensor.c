/******************************************************************************
 *
 * Module: ultrasonic sensor
 *
 * File Name: ultrasonic_sensor.c
 *
 * Description: Source file for the ultrasonic driver
 *
 *
 *******************************************************************************/

#include <avr/io.h>
#include "icu.h"
#include "std_types.h"
#include "ultrasonic_sensor.h"
#include <util/delay.h> /* To use the delay functions */

uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;
uint16 distance = 0;


void Ultrasonic_init(void) {
	GPIO_setupPinDirection(TRIGGER_PORT, TRIGGER_PIN, PIN_OUTPUT);
	//GPIO_setupPinDirection(ECHO_PORT, ECHO_PIN, PIN_INPUT);

	/* Create configuration structure for ICU driver */
	Icu_ConfigType Icu_Config = { F_CPU_8, RISING };

	/* Set the Call back function pointer in the ICU driver */
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	Icu_init(&Icu_Config);

}

void Ultrasonic_Trigger(void) {
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void) {
	Ultrasonic_Trigger();
	distance = (uint16)(((float) g_timeHigh)/(58.8));
	return distance;

}

void Ultrasonic_edgeProcessing(void) {

	g_edgeCount++;
	if (g_edgeCount == 1) {
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);


	} else if (g_edgeCount == 2) {
		/* Store the High time value */
		g_timeHigh = Icu_getInputCaptureValue();

		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(RISING); // reseting the ICU to detect the rising edge
		g_edgeCount = 0; //reinitializing g_edgeCount
	}

}

