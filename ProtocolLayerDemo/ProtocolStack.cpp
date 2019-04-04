#include "ProtocolStack.h"
#include "LayerImpl.h"
#include "profiler.h"

CProtocolStack::CProtocolStack()
{
	CreateStack();
}

CProtocolStack::~CProtocolStack()
{
	for(auto it =m_Layers.begin(); it != m_Layers.end(); ++it)
	{
		ILayer* pLayer = *it;
		delete pLayer;
	}
	m_Layers.clear();
}

void CProtocolStack::CreateStack()
{
	ILayer* pLayer = new CPhysicalLayer(this);
	m_Layers.push_back(pLayer);

	pLayer = new CLinkLayer(this);
	m_Layers.push_back(pLayer);

	pLayer = new CNetworkLayer(this);
	m_Layers.push_back(pLayer);

	pLayer = new CTransportLayer(this);
	m_Layers.push_back(pLayer);

	pLayer = new CApplicatioLayer(this);
	m_Layers.push_back(pLayer);
}

void CProtocolStack::Send( CPacket& packet )
{
	PROFILE_FUNCTION;
	GetLayer(APPLICATION_LAYER)->Send(packet);
}

void CProtocolStack::Recv( CPacket& packet )
{
	PROFILE_FUNCTION;
	GetLayer(PHYSICAL_LAYER)->Recv(packet);
	std::cout << std::endl;
}

ILayer* CProtocolStack::GetLowerLayer( PROTOCOL_LAYER layer )
{
  ILayer* pLayer = NULL;
  switch(layer)
  {
  case PHYSICAL_LAYER:
	  break;
  default:
	  pLayer = m_Layers[layer-1];
	  break;
  }
  return pLayer;
}

ILayer* CProtocolStack::GetUpperLayer( PROTOCOL_LAYER layer )
{
	ILayer* pLayer = NULL;
	switch(layer)
	{
	case APPLICATION_LAYER:
		break;
	default:
		pLayer = m_Layers[layer+1];
		break;
	}
	return pLayer;
}

ILayer* CProtocolStack::GetLayer( PROTOCOL_LAYER layer )
{
	return m_Layers[layer];
}

std::string CProtocolStack::GetLayerName( PROTOCOL_LAYER layer )
{
	std::string sLayer;
	switch(layer)
	{		
		case PHYSICAL_LAYER:
			sLayer ="Physical Layer";
			break;
		case LINK_LAYER:
			sLayer ="Link Layer";
			break;
		case NETWORK_LAYER:
			sLayer ="Network Layer";
			break;
		case TRANSPORT_LAYER:
			sLayer ="Transport Layer";
			break;
		case APPLICATION_LAYER:
			sLayer ="Application Layer";
			break;
	}
	return sLayer;
}

void CProtocolStack::Display( CPacket& packet )
{
	packet.Display();
}
