/*
 * Storage.h
 *
 * Created: 21/07/2019 17:45:28
 *  Author: Jan Wielgus
 *
 *
 * There are all global variables and objects
 */ 


#ifndef STORAGE_H_
#define STORAGE_H_


#include <FC_ObjectTasker.h>
#include <FC_Task.h>
#include <MyPID.h>
#include <FC_Communication_Base.h>
#include "FC_MainCommunication.h"
#include <FC_MPU6050Lib.h>
#include <FC_HMC5883L_Lib.h>
#include <FC_MS5611_Lib.h>
#include <FC_EVA_Filter.h>
#include "FC_Motors.h"
#include "DebugSystem.h"
#include "FlightMode.h"
#include "StabilizeFlightMode.h"
#include "AltHoldFlightMode.h"
#include "PosHoldFlightMode.h"
#include "VirtualPilot.h"



// Variables and changing state stuff

namespace Storage
{
    // Flags
    struct
    {
        bool needToExtrapolateStickVlaues = false;
    } flags;



    // Objects
    extern FC_ObjectTasker tasker;
    extern FC_MainCommunication com;
    extern FC_MPU6050Lib mpu;
    extern FC_HMC5883L_Lib compass;
    extern FC_Motors motors;
    extern DebugSystem debug;


    // PID objects
    extern MyPID levelXpid;
    extern MyPID levelYpid;
    extern MyPID yawPID;
    extern MyPID altHoldPID;


    // Used flight modes
    extern StabilizeFlightMode stabilizeFlightMode;
    extern AltHoldFlightMode altHoldFlightMode;
    extern PosHoldFlightMode posHoldFlightMode;


    // VirtualPilot object
    extern VirtualPilot virtualPilot;


    // Variables
    extern FC_MPU6050Lib::vector3Float angle;
    extern float heading;
    extern float headingToHold;
    extern float pressureToHold;


    // Extrapolation variables
    extern int16_t previousTBvalue;
    extern int16_t previousLRvalue;
    extern float extrapolatedTBstick;
    extern float extrapolatedLRstick;
    extern FC_EVA_Filter tbFilter;
    extern FC_EVA_Filter lrFilter;


    // Flight modes
    extern int16_t lastPID_LevelX_value;
    extern int16_t lastPID_LevelY_value;
    extern int16_t lastPID_Yaw_value;
    extern int16_t lastPID_AltHold_value;
}




#endif /* STORAGE_H_ */

