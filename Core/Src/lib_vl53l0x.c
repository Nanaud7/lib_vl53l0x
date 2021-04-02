/*
 * lib_vl53l0x.c
 *
 *  Created on: 1 avr. 2021
 *      Author: Arnaud CHOBERT
 */

#include "lib_vl53l0x.h"

uint8_t vl53l0x_Initialization_Flow(VL53L0X_Dev_t* dev){
	// Device initialization
	vl53l0x_Device_Initialization(dev);

	// Calibration data loading
	vl53l0x_Calibration_Data_Load(dev);

	// System settings
	vl53l0x_System_Settings(dev);

	// Start Measurement
	VL53L0X_StartMeasurement(dev);

	return 0;
}

uint8_t vl53l0x_Device_Initialization(VL53L0X_Dev_t* dev){
	uint8_t status = VL53L0X_ERROR_NONE;

	// DataInit
	if(VL53L0X_ERROR_NONE != (status = VL53L0X_DataInit(dev))){
		printf("Error DataInit() : %d\r\n",status);
		return 1;
	}

	// StaticInit
	if(VL53L0X_ERROR_NONE != (status = VL53L0X_StaticInit(dev))){
		printf("Error StaticInit() : %d\r\n",status);
		return 1;
	}

	return 0;
}

uint8_t vl53l0x_Calibration_Data_Load(VL53L0X_Dev_t* dev){
	// Reference SPADs
	uint32_t count; uint8_t isApertureSpads;
	VL53L0X_PerformRefSpadManagement(dev, &count, &isApertureSpads);
	//VL53L0X_SetReferenceSpads(dev, count, isApertureSpads);
	//VL53L0X_GetReferenceSpads(dev, &count, &isApertureSpads);


	// Ref calibration
    uint8_t VhvSettings, PhaseCal;
	VL53L0X_PerformRefCalibration(dev, &VhvSettings, &PhaseCal);
	//VL53L0X_SetRefCalibration(dev, VhvSettings, PhaseCal);

	// Offset calibration

	// Cross-talk correction

	return 0;
}

uint8_t vl53l0x_System_Settings(VL53L0X_Dev_t* dev){
	// Device Mode
	VL53L0X_SetDeviceMode(dev, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);

	// Polling and interrupt mode
	//VL53L0X_SetGpioConfig(dev, Pin, DeviceMode, Functionality, Polarity)

	// API range profiles
	vl53l0x_Range_Profiles(dev);

	return 0;
}

uint8_t vl53l0x_Range_Profiles(VL53L0X_Dev_t* dev){
	FixPoint1616_t signalLimit = (FixPoint1616_t)(0.25*65536);
	FixPoint1616_t sigmaLimit = (FixPoint1616_t)(18*65536);
	uint32_t timingBudget = 33000;
	uint8_t preRangeVcselPeriod = 14;
	uint8_t finalRangeVcselPeriod = 10;

	switch(RANGE_PROFILE_SELECTED) {
	case LONG_RANGE:
		signalLimit = (FixPoint1616_t)(0.1*65536);
		sigmaLimit = (FixPoint1616_t)(60*65536);
		timingBudget = 33000;
		preRangeVcselPeriod = 18;
		finalRangeVcselPeriod = 14;
		break;
	case HIGH_ACCURACY:
		signalLimit = (FixPoint1616_t)(0.25*65536);
		sigmaLimit = (FixPoint1616_t)(18*65536);
		timingBudget = 200000;
		preRangeVcselPeriod = 14;
		finalRangeVcselPeriod = 10;
		break;
	case HIGH_SPEED:
		signalLimit = (FixPoint1616_t)(0.25*65536);
		sigmaLimit = (FixPoint1616_t)(32*65536);
		timingBudget = 20000;
		preRangeVcselPeriod = 14;
		finalRangeVcselPeriod = 10;
		break;
	default:
		printf("Not Supported");
	}

	VL53L0X_SetLimitCheckValue(dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, signalLimit);
	VL53L0X_SetLimitCheckValue(dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, sigmaLimit);
	VL53L0X_SetMeasurementTimingBudgetMicroSeconds(dev, timingBudget);
	VL53L0X_SetVcselPulsePeriod(dev, VL53L0X_VCSEL_PERIOD_PRE_RANGE, preRangeVcselPeriod);
	VL53L0X_SetVcselPulsePeriod(dev, VL53L0X_VCSEL_PERIOD_FINAL_RANGE, finalRangeVcselPeriod);
}

uint8_t vl53l0x_Manufacturing_Calibration(VL53L0X_Dev_t* dev){
	/* Manufacturing calibration flow*/

	// Device initialization and settings
	vl53l0x_Device_Initialization(dev);

	// SPADs calibration
	uint32_t refSpadCount; uint8_t isApertureSpads;
	VL53L0X_PerformRefSpadManagement(dev, &refSpadCount, &isApertureSpads);

	// Temperature calibration
    uint8_t VhvSettings, PhaseCal;
	VL53L0X_PerformRefCalibration(dev, &VhvSettings, &PhaseCal);

	// Offset calibration (il faut utiliser un obstacle blanc)
	FixPoint1616_t CalDistanceMilliMeter; int32_t OffsetMicroMeter;
	VL53L0X_PerformOffsetCalibration(dev, CalDistanceMilliMeter, &OffsetMicroMeter);

	// CrossTalk calibration
	FixPoint1616_t XTalkCalDistance, XTalkCompensationRateMegaCps;
	VL53L0X_PerformXTalkCalibration(dev, XTalkCalDistance, &XTalkCompensationRateMegaCps);

	return 0;
}

uint8_t vl53l0x_PerformMeasurement(VL53L0X_Dev_t* dev, VL53L0X_RangingMeasurementData_t* VL53L0X_RangingMeasurementData){
	uint8_t status = VL53L0X_ERROR_NONE;

	VL53L0X_WaitDeviceReadyForNewMeasurement(dev, 100);

	if(VL53L0X_ERROR_NONE != (status = VL53L0X_GetRangingMeasurementData(dev, VL53L0X_RangingMeasurementData))){
		printf("Error GetRangingMeasurementData() : %d\r\n",status);
		return 1;
	}

	return 0;
}

uint16_t vl53l0x_PerformRangingMeasurement(VL53L0X_Dev_t* dev){
	VL53L0X_RangingMeasurementData_t VL53L0X_RangingMeasurementData;

	vl53l0x_PerformMeasurement(dev, &VL53L0X_RangingMeasurementData);

	return VL53L0X_RangingMeasurementData.RangeMilliMeter;
}
