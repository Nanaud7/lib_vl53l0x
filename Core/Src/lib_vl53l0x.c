/*
 * lib_vl53l0x.c
 *
 *  Created on: 1 avr. 2021
 *      Author: Arnaud CHOBERT
 */

#include "lib_vl53l0x.h"

uint8_t vl53l0x_Initialization(VL53L0X_Dev_t* dev){
	uint8_t rangingConfig = HIGH_ACCURACY;
	uint8_t status = VL53L0X_ERROR_NONE;
    uint8_t VhvSettings;
    uint8_t PhaseCal;
    uint32_t refSpadCount;
	uint8_t isApertureSpads;
	FixPoint1616_t signalLimit = (FixPoint1616_t)(0.25*65536);
	FixPoint1616_t sigmaLimit = (FixPoint1616_t)(18*65536);
	uint32_t timingBudget = 33000;
	uint8_t preRangeVcselPeriod = 14;
	uint8_t finalRangeVcselPeriod = 10;

	// DataInit()
	if(VL53L0X_ERROR_NONE != (status = VL53L0X_DataInit(dev))){
		printf("Error DataInit() : %d\r\n",status);
		return 1;
	}

	// StaticInit
	if(VL53L0X_ERROR_NONE != (status = VL53L0X_StaticInit(dev))){
		printf("Error StaticInit() : %d\r\n",status);
		return 1;
	}

	// Ref (temperature) calibration
	if(VL53L0X_ERROR_NONE != (status = VL53L0X_PerformRefCalibration(dev, &VhvSettings, &PhaseCal))){
		printf("Error PerformRefCalibration() : %d\r\n",status);
		return 1;
	}

	// Reference SPADs
	if(VL53L0X_ERROR_NONE != (status = VL53L0X_PerformRefSpadManagement(dev, &refSpadCount, &isApertureSpads))){
		printf("Error PerformRefSpadManagement() : %d\r\n",status);
		return 1;
	}

	// Device Mode
	if(VL53L0X_ERROR_NONE != (status = VL53L0X_SetDeviceMode(dev, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING))){
		printf("Error SetDeviceMode() : %d\r\n",status);
		return 1;
	}

	// LimitCheckEnable
	if(VL53L0X_ERROR_NONE != (status = VL53L0X_SetLimitCheckEnable(dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1))){
		printf("Error SetLimitCheckEnable() : %d\r\n",status);
		return 1;
	}


	if(VL53L0X_ERROR_NONE != (status = VL53L0X_SetLimitCheckEnable(dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1))){
		printf("Error SetLimitCheckEnable() : %d\r\n",status);
		return 1;
	}


	/* Ranging configuration */
	switch(rangingConfig) {
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

	// SetLimitCheckValue
	if(VL53L0X_ERROR_NONE != (status = VL53L0X_SetLimitCheckValue(dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, signalLimit))){
		printf("Error SetLimitCheckEnable() : %d\r\n",status);
		return 1;
	}

	if(VL53L0X_ERROR_NONE != (status = VL53L0X_SetLimitCheckValue(dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, sigmaLimit))){
		printf("Error SetLimitCheckEnable() : %d\r\n",status);
		return 1;
	}

	// SetMeasurementTimingBudgetMicroSeconds
	if(VL53L0X_ERROR_NONE != (status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(dev, timingBudget))){
		printf("Error SetMeasurementTimingBudgetMicroSeconds() : %d\r\n",status);
		return 1;
	}

	// SetVcselPulsePeriod
	if(VL53L0X_ERROR_NONE != (status = VL53L0X_SetVcselPulsePeriod(dev, VL53L0X_VCSEL_PERIOD_PRE_RANGE, preRangeVcselPeriod))){
		printf("Error SetVcselPulsePeriod() : %d\r\n",status);
		return 1;
	}

	if(VL53L0X_ERROR_NONE != (status = VL53L0X_SetVcselPulsePeriod(dev, VL53L0X_VCSEL_PERIOD_FINAL_RANGE, finalRangeVcselPeriod))){
		printf("Error SetVcselPulsePeriod() : %d\r\n",status);
		return 1;
	}

	// PerformRefCalibration
	if(VL53L0X_ERROR_NONE != (status = VL53L0X_PerformRefCalibration(dev, &VhvSettings, &PhaseCal))){
		printf("Error SetVcselPulsePeriod() : %d\r\n",status);
		return 1;
	}

	// Start measurement
	if(VL53L0X_ERROR_NONE != (status = VL53L0X_StartMeasurement(dev))){
		printf("Error StartMeasurement() : %d\r\n",status);
		return 1;
	}

	return 0;
}

uint8_t vl53l0x_PerformMeasurement(VL53L0X_Dev_t* dev, VL53L0X_RangingMeasurementData_t* VL53L0X_RangingMeasurementData){
	uint8_t status = VL53L0X_ERROR_NONE;
	uint8_t data_ready = 0;

	/*
	do{
		VL53L0X_GetMeasurementDataReady(dev, &data_ready);
	} while(data_ready != 1);
	*/

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
