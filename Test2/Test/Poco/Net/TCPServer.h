#include <iostream>
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"

#define BUFFER_SIZE 1024

using Poco::Net::SocketAddress;
using Poco::Net::StreamSocket;

int main(int argc, const char * argv[])
{
	SocketAddress sa("127.0.0.1", 7000);
	StreamSocket ss(sa);
	int n = ss.sendBytes("hello", 5);
	char buffer[256];
	n = ss.receiveBytes(buffer, sizeof(buffer));
	printf("n = %d\n", n);
	return 0;
}