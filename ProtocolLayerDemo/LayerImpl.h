#pragma  once

#include <cstring>
#include <iterator>
#include <iostream>
#include <string>

#include "Layer.h"
#include "ProtocolStack.h"

class AbstractLayer: public ILayer
{

public:
	AbstractLayer(ILayerHandler* pLayerhanler):m_pLayerhanler(pLayerhanler)
	{

	}

	virtual void Send(CPacket& packet) 
	{
		std::vector<BYTE> data;

		GetHeader(data);
		packet.AddHeader(data);

		data.clear();
		GetBody(data);
		packet.AddBody(data);

		data.clear();
		GetTrailer(data);
		packet.AddTrailer(data);

		Process(packet);

		if(m_pLayerhanler->GetLowerLayer(GetLayer()))
		{
			m_pLayerhanler->GetLowerLayer(GetLayer())->Send(packet);
		}
			
	}
		
	virtual void Recv(CPacket& packet)
	{
		std::cout<<"\n "<< CProtocolStack::GetLayerName(GetLayer())<<" data is:";
		std::vector<BYTE> header;
		packet.ExtractHeader(header, GetLayer());
		packet.Print(header);

		std::vector<BYTE> body;
		packet.ExtractBody(body, GetLayer());
		packet.Print(body);

		std::vector<BYTE> trailer;
		packet.ExtractTrailer(trailer, GetLayer());
		packet.Print(trailer);

		if(m_pLayerhanler->GetUpperLayer(GetLayer()))
			m_pLayerhanler->GetUpperLayer(GetLayer())->Recv(packet);
	}

	virtual void Process(CPacket&)    = 0;
	virtual PROTOCOL_LAYER GetLayer() = 0;
	virtual void  GetHeader(std::vector<BYTE>& m_Data)  = 0;
	virtual void  GetBody(std::vector<BYTE>& m_Data)    = 0;
	virtual void  GetTrailer(std::vector<BYTE>& m_Data) = 0;

private:
	ILayerHandler* m_pLayerhanler;
};


class CApplicatioLayer : public AbstractLayer
{

public:
	CApplicatioLayer(ILayerHandler* pLayerhanler):AbstractLayer(pLayerhanler)
	{


	}	

	virtual void Process(CPacket& packet) override
	{
		std::cout<<"nProcessing packet";
	}


	virtual PROTOCOL_LAYER GetLayer() override
	{
		return APPLICATION_LAYER;
	}

	virtual void  GetHeader(std::vector<BYTE>& m_Data) override
	{
		std::string str = "APPLICATION-LAYER-HEADER";		
		std::copy(str.begin(), str.end(), std::back_inserter(m_Data));
	}

	virtual void  GetBody(std::vector<BYTE>& m_Data) override
	{
		std::string str = "APPLICATION-LAYER-BODY";		
		std::copy(str.begin(), str.end(), std::back_inserter(m_Data));
	}

	virtual void  GetTrailer(std::vector<BYTE>& m_Data) override
	{
		std::string str = "APPLICATION-LAYER-TRAILER";		
		std::copy(str.begin(), str.end(), std::back_inserter(m_Data));
	}
};

class CTransportLayer : public AbstractLayer
{
public:
	CTransportLayer(ILayerHandler* pLayerhanler):AbstractLayer(pLayerhanler)
	{

	}
	
	virtual void Process(CPacket& packet) override
	{
		std::cout<<"\nProcessing packet";
	}


	virtual PROTOCOL_LAYER GetLayer() override
	{
		return TRANSPORT_LAYER;
	}

	virtual void  GetHeader(std::vector<BYTE>& m_Data) override
	{
		std::string str = "TRANSPORT-LAYER-HEADER";		
		std::copy(str.begin(), str.end(), std::back_inserter(m_Data));
	}

	virtual void  GetBody(std::vector<BYTE>& m_Data) override
	{
		std::string str = "TRANSPORT-LAYER-BODY";		
		std::copy(str.begin(), str.end(), std::back_inserter(m_Data));
	}

	virtual void  GetTrailer(std::vector<BYTE>& m_Data) override
	{
		std::string str = "TRANSPORT-LAYER-TRAILER";		
		std::copy(str.begin(), str.end(), std::back_inserter(m_Data));
	}
	
};

class CNetworkLayer : public AbstractLayer
{

public:
	CNetworkLayer(ILayerHandler* pLayerhanler):AbstractLayer(pLayerhanler)
	{

	}
	
	virtual void Process(CPacket& packet) override
	{
		std::cout<<"\nProcessing packet";
	}


	virtual PROTOCOL_LAYER GetLayer() override
	{
		return NETWORK_LAYER;
	}

	virtual void  GetHeader(std::vector<BYTE>& m_Data) override
	{
		std::string str = "NETWORK-LAYER-HEADER";		
		std::copy(str.begin(), str.end(), std::back_inserter(m_Data));
	}

	virtual void  GetBody(std::vector<BYTE>& m_Data) override
	{
		std::string str = "NETWORK-LAYER-BODY";		
		std::copy(str.begin(), str.end(), std::back_inserter(m_Data));
	}

	virtual void  GetTrailer(std::vector<BYTE>& m_Data) override
	{
		std::string str = "NETWORK-LAYER-TRAILER";		
		std::copy(str.begin(), str.end(), std::back_inserter(m_Data));
	}

};

class CLinkLayer : public AbstractLayer
{

public:
	CLinkLayer(ILayerHandler* pLayerhanler):AbstractLayer(pLayerhanler)
	{

	}
	
	virtual void Process(CPacket& packet) override
	{
		std::cout<<"\nProcessing packet";
	}


	virtual PROTOCOL_LAYER GetLayer() override
	{
		return LINK_LAYER;
	}

	virtual void  GetHeader(std::vector<BYTE>& m_Data) override
	{
		std::string str = "LINK-LAYER-HEADER";		
		std::copy(str.begin(), str.end(), std::back_inserter(m_Data));
	}

	virtual void  GetBody(std::vector<BYTE>& m_Data) override
	{
		std::string str = "LINK-LAYER-BODY";		
		std::copy(str.begin(), str.end(), std::back_inserter(m_Data));
	}

	virtual void  GetTrailer(std::vector<BYTE>& m_Data) override
	{
		std::string str = "LINK-LAYER-TRAILER";		
		std::copy(str.begin(), str.end(), std::back_inserter(m_Data));
	}
};

class CPhysicalLayer : public AbstractLayer
{

public:
	CPhysicalLayer(ILayerHandler* pLayerhanler):AbstractLayer(pLayerhanler)
	{


	}
	
	virtual void Process(CPacket& packet) override
	{
		std::cout<<"nProcessing packet";
	}


	virtual PROTOCOL_LAYER GetLayer() override
	{
		return PHYSICAL_LAYER;
	}

	virtual void  GetHeader(std::vector<BYTE>& m_Data) override
	{
		std::string str = "PHYSICAL-LAYER-HEADER";		
		std::copy(str.begin(), str.end(), std::back_inserter(m_Data));
	}

	virtual void  GetBody(std::vector<BYTE>& m_Data) override
	{
		std::string str = "PHYSICAL-LAYER-BODY";		
		std::copy(str.begin(), str.end(), std::back_inserter(m_Data));
	}

	virtual void  GetTrailer(std::vector<BYTE>& m_Data) override
	{
		std::string str = "PHYSICAL-LAYER-TRAILER";		
		std::copy(str.begin(), str.end(), std::back_inserter(m_Data));
	}
};