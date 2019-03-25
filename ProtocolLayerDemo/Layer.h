#pragma  once

#include "Packet.h"
#include <vector>

class CPacket;

class ILayer
{
public:
	virtual void Send(CPacket&)       = 0;
	virtual void Recv(CPacket&)       = 0;
	virtual void Process(CPacket&)    = 0;
	virtual PROTOCOL_LAYER GetLayer() = 0;
	virtual void  GetHeader(std::vector<BYTE>& m_Data)  = 0;
	virtual void  GetBody(std::vector<BYTE>& m_Data)    = 0;
	virtual void  GetTrailer(std::vector<BYTE>& m_Data) = 0;
};

class ILayerHandler
{
public:
	virtual ILayer* GetLowerLayer(PROTOCOL_LAYER layer) = 0;
	virtual ILayer* GetUpperLayer(PROTOCOL_LAYER layer) = 0;
};


