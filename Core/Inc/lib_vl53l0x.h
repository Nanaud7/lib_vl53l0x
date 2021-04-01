/*
 * lib_vl53l0x.h
 *
 *  Created on: 1 avr. 2021
 *      Author: Arnaud CHOBERT
 */

#ifndef INC_LIB_VL53L0X_H_
#define INC_LIB_VL53L0X_H_

/* #include */
#include <stdio.h>
#include "retarget.h"

#include "vl53l0x_api.h"
#include "vl53l0x_platform.h"
#include "vl53l0x_device.h"

/* #define */
//#define GET_DEVICE_INFO
#define HIGH_ACCURACY 0
#define LONG_RANGE 1
#define HIGH_SPEED 2

/* Prototypes */
uint8_t vl53l0x_Initialization(VL53L0X_Dev_t* dev);
uint8_t vl53l0x_PerformMeasurement(VL53L0X_Dev_t* dev, VL53L0X_RangingMeasurementData_t* VL53L0X_RangingMeasurementData);
uint16_t vl53l0x_PerformRangingMeasurement(VL53L0X_Dev_t* dev);

#endif /* INC_LIB_VL53L0X_H_ */
