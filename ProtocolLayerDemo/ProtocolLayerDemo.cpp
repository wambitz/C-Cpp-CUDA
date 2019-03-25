// ProtocolLayerDemo.cpp : Defines the entry point for the console application.

#include "ProtocolStack.h"
#include "Packet.h"

int main(int argc, char* argv[])
{
	CProtocolStack stack;
	CPacket packet;
	stack.Send(packet);
	stack.Display(packet);
	stack.Recv(packet);
	return 0;
}

