#pragma once

#include <vector>
#include <string>
#include "Layer.h"

class CProtocolStack: public ILayerHandler
{
public:
	CProtocolStack();
	~CProtocolStack();
	void Send (CPacket& packet);
	void Recv(CPacket& packet);
	ILayer* GetLowerLayer(PROTOCOL_LAYER layer);
	ILayer* GetUpperLayer(PROTOCOL_LAYER layer);
	ILayer* GetLayer(PROTOCOL_LAYER layer);
	void Display(CPacket& packet);
	static std::string GetLayerName(PROTOCOL_LAYER layer);
private:
	void CreateStack();
	std::vector<ILayer*> m_Layers;
};