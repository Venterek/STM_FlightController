/*
 * config.h
 *
 * Created: 21/07/2019 11:32:35
 *  Author: Jan Wielgus
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

#include <FC_MPU6050Lib.h>
#include <FC_HMC5883L_Lib.h>


namespace config
{
	// pins
	struct 
	{
		/* not used in the code
		// motors
		uint8_t mTL = PA6;
		uint8_t mTR = PA7;
		uint8_t mBR = PB0;
		uint8_t mBL = PB1;
		*/
		
		
		// diodes
		uint8_t redDiode = PB15;
		uint8_t blueDiode = PB14;
		
		
		// radio module
		uint8_t m0pin = PA1;
		uint8_t m1pin = PA0;
		uint8_t aux = PB5;
		
		
	} pin;
	
	
	// mpu6050
	struct 
	{
		// mpu6050
		FC_MPU6050Lib::vector3Int accelerometer;
		
		// GYRO CALIBRATION VALUES
		
		
		// hmc5883l
		// Default calibration values
		FC_HMC5883L_Lib::vector3Int compassMin = {-503, -505, -1440};
		FC_HMC5883L_Lib::vector3Int compassMax = {504, 463, -330};
		
		
		
	} calibVal;
}




#endif /* CONFIG_H_ */