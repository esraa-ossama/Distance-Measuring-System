/******************************************************************************
 *
 * Module: Distance measurement application
 *
 * File Name: distance_measurement.c
 *
 * Description: Source file for measuring distance
 *
 *
 *******************************************************************************/


#include "lcd.h"
#include "icu.h"
#include <avr/io.h> /* To use the SREG register */
#include "ultrasonic_sensor.h"
#include<util/delay.h>


int main() {
	uint16 distance = 0;
	uint16 prev_distance = 0;
	/* Enable Global Interrupt I-Bit */
	SREG |= (1 << 7);
	Ultrasonic_init();
	LCD_init();
	LCD_displayString("distance = ");

	while (1) {

		LCD_moveCursor(0, 11);
		distance = Ultrasonic_readDistance() + 1;
		if (distance != prev_distance) {
			LCD_intgerToString(distance);
			LCD_displayString("cm   ");
		}

		prev_distance = distance;
		_delay_ms(100);
	}
	return 0;
}

