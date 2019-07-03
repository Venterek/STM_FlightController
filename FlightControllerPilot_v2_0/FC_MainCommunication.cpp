// 
// 
// 

#include "FC_MainCommunication.h"



FC_MainCommunication::FC_MainCommunication(Stream* serial, uint8_t bufSize)
	:FC_Communication_Base(serial, bufSize)
{
	conStab = 0;
}


/*
	SOME IMPORTANT INFO:
	
		- How to use checksums:
		- buffer[0] in dataPacket is reserved for the checksum value
		- if you are calculating the checksum, store it in the buffer[0]
		  (calculate it after packing data to dataPacket!)
		
		- buffer[1] is reserved for data type (ID) !
		- buffer[0] is not required for checksum if you do not use it
		- buffer[1] is not required for data type (ID) if you use only one data packet type
*/




bool FC_MainCommunication::receiveAndUnpackData()
{
	atLeastOneFlag = false; // at least one packet was received. Needed to return true/false at the end
		
	while (receiveData())
	{
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		// EDIT FOR OTHER PURPOSES FROM HERE
		
		
		
		
		// Check if this packet is the specific one (TYPE1)
		if (checkReceivedDataPacket(receivedPacketTypes.TYPE1_ID, receivedPacketTypes.TYPE1_SIZE, true))
		{
			// vlotage 6 cells
			data.received.tilt_TB = dpReceived.buffer[8];
			data.received.tilt_LR = dpReceived.buffer[9];
			data.received.heading.byteArr()[0] = dpReceived.buffer[10];
			data.received.heading.byteArr()[1] = dpReceived.buffer[11];
			data.received.altitude.byteArr()[0] = dpReceived.buffer[12];
			data.received.altitude.byteArr()[1] = dpReceived.buffer[13];
			for (int i=0; i<4; i++)
				data.received.longitude.byteArr()[i] = dpReceived.buffer[14+i];
			for (int i=0; i<4; i++)
				data.received.latitude.byteArr()[i] = dpReceived.buffer[18+i];
			// random value
			data.received.errors1.byte = dpReceived.buffer[23];
			data.received.errors2.byte = dpReceived.buffer[24];
			data.received.bitSwitches1.byte = dpReceived.buffer[25];
			// margin 6x
		}
	
	
		// Check if this packet is TYPE2
		else if (checkReceivedDataPacket(receivedPacketTypes.TYPE2_ID, receivedPacketTypes.TYPE2_SIZE, true))
		{
			// voltage on the lowest cell
			data.received.errors1.byte = dpReceived.buffer[3];
			data.received.errors2.byte = dpReceived.buffer[4];
			data.received.bitSwitches1.byte = dpReceived.buffer[5];
		}
		

		
		
		// TO HERE
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
	}
	
	
	// Calculate the connection stability (edit only parameters)
	uint8_t sum = (uint8_t)pastComStatesArr[1] + pastComStatesArr[0] + atLeastOneFlag;
	// TUNE multipliers if needed (depending on the update frequency)
	conStab = sum<conStab ? 0.8*sum + 0.2*conStab  :  0.6*sum + 0.4*conStab; // slower increase than decrease
	// update historic values
	pastComStatesArr[1] = pastComStatesArr[0];
	pastComStatesArr[0] = atLeastOneFlag;
	
	
	if (atLeastOneFlag)
		return true;
	
	return false;
}


void FC_MainCommunication::packAndSendData(uint8_t packetID, uint8_t packetSize)
{
	dpToSend.size = (size_t)packetSize;
	dpToSend.buffer[1] = packetID;
	
	
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// CHANGE FOR OTHER PURPOSES FROM HERE
	
	
	
	// TYPE1 - full
	if (packetID == sendPacketTypes.TYPE1_ID)
	{
		dpToSend.buffer[2] = data.toSend.steer.throttle.byteArr()[0];
		dpToSend.buffer[3] = data.toSend.steer.throttle.byteArr()[1];
		dpToSend.buffer[4] = data.toSend.steer.rotate.byteArr()[0];
		dpToSend.buffer[5] = data.toSend.steer.rotate.byteArr()[1];
		dpToSend.buffer[6] = data.toSend.steer.TB.byteArr()[0];
		dpToSend.buffer[7] = data.toSend.steer.TB.byteArr()[1];
		dpToSend.buffer[8] = data.toSend.steer.LR.byteArr()[0];
		dpToSend.buffer[9] = data.toSend.steer.LR.byteArr()[1];
		dpToSend.buffer[10] = data.toSend.pilotDistance.byteArr()[0];
		dpToSend.buffer[11] = data.toSend.pilotDistance.byteArr()[1];
		dpToSend.buffer[12] = data.toSend.pilotDirection.byteArr()[0];
		dpToSend.buffer[13] = data.toSend.pilotDirection.byteArr()[1];
		dpToSend.buffer[14] = data.toSend.flightMode;
		dpToSend.buffer[15] = data.toSend.arming;
		// random value
		dpToSend.buffer[17] = data.toSend.bitSwitches1.byte;
		dpToSend.buffer[18] = data.toSend.bitSwitches2.byte;
		dpToSend.buffer[19] = data.toSend.signalLostScenario;
		
		
		dpToSend.buffer[0] = calcChecksum();
		
		sendData();
	}
	
	// TYPE2 - basic
	else if (packetID == sendPacketTypes.TYPE2_ID)
	{
		dpToSend.buffer[2] = data.toSend.steer.throttle.byteArr()[0];
		dpToSend.buffer[3] = data.toSend.steer.throttle.byteArr()[1];
		dpToSend.buffer[4] = data.toSend.steer.rotate.byteArr()[0];
		dpToSend.buffer[5] = data.toSend.steer.rotate.byteArr()[1];
		dpToSend.buffer[6] = data.toSend.steer.TB.byteArr()[0];
		dpToSend.buffer[7] = data.toSend.steer.TB.byteArr()[1];
		dpToSend.buffer[8] = data.toSend.steer.LR.byteArr()[0];
		dpToSend.buffer[9] = data.toSend.steer.LR.byteArr()[1];
		dpToSend.buffer[10] = data.toSend.flightMode;
		dpToSend.buffer[11] = data.toSend.arming;
		dpToSend.buffer[12] = data.toSend.bitSwitches1.byte;
		dpToSend.buffer[13] = data.toSend.bitSwitches2.byte;
		dpToSend.buffer[14] = data.toSend.signalLostScenario;
		
		
		dpToSend.buffer[0] = calcChecksum();
		
		sendData();
	}
	
	// TYPE3 - PID parameters
	else if (packetID == sendPacketTypes.TYPE3_ID)
	{
		// leveling
		for (int i=0; i<4; i++)
			dpToSend.buffer[2+i] = data.toSend.levelingPID.P.byteArr()[i];
		for (int i=0; i<4; i++)
			dpToSend.buffer[6+i] = data.toSend.levelingPID.I.byteArr()[i];
		for (int i=0; i<4; i++)
			dpToSend.buffer[10+i] = data.toSend.levelingPID.D.byteArr()[i];
		dpToSend.buffer[14] = data.toSend.levelingPID.I_max;
		
		// yaw
		for (int i=0; i<4; i++)
			dpToSend.buffer[15+i] = data.toSend.yawPID.P.byteArr()[i];
		for (int i=0; i<4; i++)
			dpToSend.buffer[19+i] = data.toSend.yawPID.I.byteArr()[i];
		for (int i=0; i<4; i++)
			dpToSend.buffer[23+i] = data.toSend.yawPID.D.byteArr()[i];
		dpToSend.buffer[27] = data.toSend.yawPID.I_max;
		
		// altHold
		for (int i=0; i<4; i++)
			dpToSend.buffer[28+i] = data.toSend.altHoldPID.P.byteArr()[i];
		for (int i=0; i<4; i++)
			dpToSend.buffer[32+i] = data.toSend.altHoldPID.I.byteArr()[i];
		for (int i=0; i<4; i++)
			dpToSend.buffer[36+i] = data.toSend.altHoldPID.D.byteArr()[i];
		dpToSend.buffer[40] = data.toSend.altHoldPID.I_max;
		
		
		dpToSend.buffer[0] = calcChecksum();
		
		sendData();
	}
	
	
	
	// TO HERE
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
}




uint8_t FC_MainCommunication::connectionStability()
{
	// calculated while receiving
	return uint8_t(conStab + 0.5); // average
}


bool FC_MainCommunication::checkReceivedDataPacket(uint8_t packetID, uint8_t packetSize, bool checkChecksumFlag)
{
	uint8_t IDpos;
	IDpos = checkChecksumFlag==true ? 1 : 0;
	
	if (dpReceived.buffer[IDpos] == packetID && dpReceived.size == packetSize)
	{
		if (!checkChecksumFlag)
		{
			atLeastOneFlag = true;
			return true;
		}
		
		//else
		if (checkChecksum())
		{
			atLeastOneFlag = true;
			return true;
		}
	}
	
	return false;
}

