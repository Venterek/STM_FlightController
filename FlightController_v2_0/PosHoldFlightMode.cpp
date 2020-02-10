// 
// 
// 

#include "PosHoldFlightMode.h"
#include "AltHoldFlightMode.h"
#include "CustomDataTypes.h"


PosHoldFlightMode::PosHoldFlightMode(AltHoldFlightMode* altHoldFM)
	: FlightMode(FlightModeType::POS_HOLD)
{
	this->baseFlightMode = altHoldFM;

	//...
}


void PosHoldFlightMode::execute()
{

}


void PosHoldFlightMode::reset()
{

}
