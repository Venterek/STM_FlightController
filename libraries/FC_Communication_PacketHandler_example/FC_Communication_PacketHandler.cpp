// 
// 
// 

#include "FC_Communication_PacketHandler.h"


FC_Communication_PacketHandler::FC_Communication_PacketHandler(Stream* serial, uint8_t bufSize)
	:FC_Communication_Base(serial, bufSize)
{
	
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


bool FC_Communication_PacketHandler::receiveAndUnpackData()
{
	// Stop if any data packet was received
	if (!receiveData())
		return false;
	
	// Check if this packet is the specific one (TYPE1)
	if (checkReceivedDataPacket(receivedPacketTypes.TYPE1_ID, receivedPacketTypes.TYPE1_SIZE, true))
	{
		// Unpack data by updating proper variables
		// [0] - checksum
		// [1] - ID
		data.received.var1 = dpReceived.buffer[2];
	}
	
	// Check if this packet is TYPE2
	//else if (checkReceivedDataPacket(.......))
	// ...
	
	
	
	return true;
}


void FC_Communication_PacketHandler::packAndSendData(uint8_t packetID)
{
	
}


bool FC_Communication_PacketHandler::connectionState()
{
	
}


bool FC_Communication_PacketHandler::checkReceivedDataPacket(uint8_t packetID, uint8_t packetSize, bool checkChecksumFlag)
{
	static uint8_t IDpos;
	IDpos = checkChecksumFlag==true ? 1 : 0;
	
	if (dpReceived.buffer[IDpos] == packetID && dpReceived.size == packetSize)
	{
		if (!checkChecksumFlag)
		return true;
		
		//else
		if (checkChecksum())
		return true;
	}
	
	return false;
}


