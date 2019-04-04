#include "Packet.h"

#include <algorithm>
#include <iostream>

using namespace std;

char CPacket::LAYER_EXTRACTOR = '>';
char CPacket::LAYER_DATA_EXTRACTOR = '|';
size_t CPacket::MAX_PACKET_LENGTH = 1024;

void CPacket::Print( vector<BYTE>& data )
{
    std::cout<<"\n";
	for(int nIndex = 0; nIndex < data.size(); nIndex++)
	{
		std::cout<<data[nIndex];
	}
}

CPacket::CPacket():m_nOffset(0)
{
	m_Data.reserve(MAX_PACKET_LENGTH);
}

void CPacket::AddHeader( vector<BYTE>& Data )
{
	size_t index = m_nOffset, nDataIndex = 0;
	for (index = m_nOffset, nDataIndex = 0; nDataIndex < Data.size(); index++)
	{
		m_Data.push_back(Data[nDataIndex++]);
	}
	m_Data.push_back(LAYER_DATA_EXTRACTOR);
	m_nOffset = index+1;
}

void CPacket::AddBody( vector<BYTE>& Data )
{	
	size_t index = m_nOffset, nDataIndex = 0;
	for (index = m_nOffset, nDataIndex = 0; nDataIndex < Data.size(); index++)
	{
		m_Data.push_back(Data[nDataIndex++]);
	}
	m_Data.push_back(LAYER_DATA_EXTRACTOR);
	m_nOffset = index+1;
}

void CPacket::AddTrailer( vector<BYTE>& Data )
{
	size_t index = m_nOffset, nDataIndex = 0;
	for (index = m_nOffset, nDataIndex = 0; nDataIndex < Data.size(); index++)
	{
		m_Data.push_back(Data[nDataIndex++]);
	}
	m_Data.push_back(LAYER_DATA_EXTRACTOR);
	m_nOffset = index+1;
}

void CPacket::ExtractHeader( vector<BYTE>& m_Data, PROTOCOL_LAYER layer )
{
	Split(m_Data, layer, HEADER);
}

void CPacket::ExtractBody( vector<BYTE>& m_Data, PROTOCOL_LAYER layer )
{
    Split(m_Data, layer, BODY);
}

void CPacket::ExtractTrailer( vector<BYTE>& m_Data, PROTOCOL_LAYER layer )
{
    Split(m_Data, layer, TRAILER);
}

void CPacket::Split( vector<BYTE>& result, PROTOCOL_LAYER& layer, SECTION section )
{
	std::vector<std::vector<BYTE>> m_SplitteData;
	std::vector<BYTE>::iterator iter = m_Data.begin();
	std::vector<BYTE>::iterator statInex = iter;

	int ncount =0;
	int nDiv = (APPLICATION_LAYER - layer)*3+(section+1);
	while ((iter = std::find(iter,m_Data.end(), LAYER_DATA_EXTRACTOR)) != m_Data.end())
	{
		// Do something with iter
		ncount++;
		
		if(ncount%nDiv == 0){
			std::vector<BYTE> temp(statInex, iter);
			result =temp;
			break;
		}
		iter++;
		statInex = iter;
	}
}

void CPacket::Display()
{
	size_t nCount =0;
	std::cout<<"\n---------------------------------------------------------------\n";
	for (size_t nDataIndex = 0; nDataIndex < m_Data.size(); nDataIndex++)
	{
		if(m_Data[nDataIndex] == '|'){
			nCount++;
			if(nCount % 3 == 0)
				std::cout<<"\n";
		}
		std::cout<<m_Data[nDataIndex];
	}
	std::cout<<"\n---------------------------------------------------------------\n";
}






