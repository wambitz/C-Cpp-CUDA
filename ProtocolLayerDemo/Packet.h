#pragma  once
#include <vector>
//#include "Layer.h"
// using namespace std;

typedef unsigned char BYTE;

enum PROTOCOL_LAYER
{		
	PHYSICAL_LAYER = 0,
	LINK_LAYER,
	NETWORK_LAYER,
	TRANSPORT_LAYER,
	APPLICATION_LAYER
};

//[ <Header_Information> ! <Body_Information> ! <Trailer_information> ]
class CPacket
{
public:
	CPacket();
	static char  LAYER_EXTRACTOR;
	static char  LAYER_DATA_EXTRACTOR;
	static size_t MAX_PACKET_LENGTH;	
	enum SECTION
	{
		HEADER =0,
		BODY,
		TRAILER
	};

	void AddHeader(std::vector<BYTE>& m_Data);
	void AddBody(std::vector<BYTE>& m_Data);
	void AddTrailer(std::vector<BYTE>& m_Data);

	void ExtractHeader(std::vector<BYTE>& m_Data, PROTOCOL_LAYER layer);
	void ExtractBody(std::vector<BYTE>& m_Data, PROTOCOL_LAYER layer);
	void ExtractTrailer(std::vector<BYTE>& m_Data, PROTOCOL_LAYER layer);
	size_t GetLength() { return m_nOffset; }
	void Split( std::vector<BYTE>& result, PROTOCOL_LAYER& layer, SECTION section );
	static void Print(std::vector<BYTE>& data);
	void Display();

private:
	std::vector<BYTE> m_Data;
	size_t m_nOffset;
};