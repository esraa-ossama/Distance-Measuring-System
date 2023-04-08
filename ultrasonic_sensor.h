/******************************************************************************
 *
 * Module: ultrasonic sensor
 *
 * File Name: ultrasonic_sensor.h
 *
 * Description: Header file for the ultrasonic driver
 *
 *
 *******************************************************************************/


#include"std_types.h"
#include"gpio.h"

#ifndef ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_H_


#define TRIGGER_PORT   PORTB_ID
#define TRIGGER_PIN    PIN5_ID


void Ultrasonic_init(void);

void Ultrasonic_Trigger(void);

uint16 Ultrasonic_readDistance(void);

void Ultrasonic_edgeProcessing(void);



#endif /* ULTRASONIC_SENSOR_H_ */
