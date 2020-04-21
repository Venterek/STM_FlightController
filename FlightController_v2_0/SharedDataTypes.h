/*
 * CustomDataTypes.h
 *
 * Created: 10/02/2020
 *  Author: Jan Wielgus
 *
 *
 * Data types created for the drone program needs
 */


#ifndef CUSTOMDATATYPES_H_
#define CUSTOMDATATYPES_H_

#include <FC_MPU6050Lib.h>



 // list of all flight modes
enum FlightModeType
{
    STABILIZE,
    ALT_HOLD,
    POS_HOLD,
};
// Do not use separate flight modes type. ADD ALL FLIGHT MODES TO THE ENUM ABOVE !!!
// {LANDING, RETURN_TO_LAUNCH, RETURN_OVER_PILOT};

enum BaudRates { BAUD_9600 = 9600, BAUD_19200 = 19200, BAUD_38400 = 38400, BAUD_57600 = 57600, BAUD_115200 = 115200 };


struct virtualSticksType
{
    uint16_t throttle; // 0 : 1000
    int16_t rotate; // -500 : 500
    int16_t TB; // -500 : 500
    int16_t LR; // -500 : 500
};


struct readingsType
{
    FC_MPU6050Lib::vector3Float angle = { 0, 0, 0 }; // X and Y angles
    float heading = 0;
    float pressure = 0; // not extrapolated value (about 110 Hz)
    float smoothPressure = 0;
};


struct pidCommPack
{
    floatByte P;
    floatByte I;
    floatByte D;
    uint16Byte I_max;
};




// Only for STM32 (maybe not necessary)
typedef uint8 uint8_t;
typedef int8 int8_t;
typedef uint16 uint16_t;
typedef int16 int16_t;




#endif /* STORAGE_H_ */
