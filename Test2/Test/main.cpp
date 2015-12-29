#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/StreamCopier.h"

#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"

#include <iostream>
#include <string>
using namespace std;
using namespace Poco::Net;

int main()
{
	SocketAddress sa("127.0.0.1", 7000);
	
	while (true)
	{
		StreamSocket ss(sa);
		try
		{
			int n = ss.sendBytes("hello", 5);
			char buffer[256];
			n = ss.receiveBytes(buffer, sizeof(buffer));
			buffer[n] = '\0';
			printf("n = %d msg=%s\n", n, buffer);
			Sleep(1);
		}	
		catch (Poco::Exception* e)
		{
			std::cout << e->displayText() << endl;
		}
		
	}
	system("pause");
	return 0;
}