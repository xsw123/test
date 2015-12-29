#include <Poco/Net/TCPServer.h>
#include <Poco/Net/TCPServerConnection.h>
#include <Poco/Net/TCPServerConnectionFactory.h>
#include <Poco/Util/Application.h>
#include <Poco/Util/ServerApplication.h>
#include <string>
using namespace std;
using namespace Poco::Net;
using namespace Poco::Util;

class TestConnection : public TCPServerConnection
{
public:
	TestConnection(const StreamSocket& s) :
		TCPServerConnection(s)
	{
		socket().setBlocking(false);
	}
	void run()
	{
		StreamSocket& ss = socket();
		try
		{
			char buffer[256];
			int n = ss.receiveBytes(buffer, sizeof(buffer));
			while (n > 0)
			{
				buffer[n] = '\0';
				std::cout << buffer << endl;
				string strMsg = "I recive your msg !!!";
				ss.sendBytes(strMsg.c_str(), strMsg.length());
				n = ss.receiveBytes(buffer, sizeof(buffer));
			}
		}
		catch (Poco::Exception& exc)
		{
			std::cerr << "EchoConnection: " << exc.displayText() << std::endl;
		}
	}
};
class TestConnectionFactory : public TCPServerConnectionFactory
{
public:
	TCPServerConnection* createConnection(const StreamSocket& socket)
	{
		TestConnection* tc = new TestConnection(socket);
		return tc;
	}
};
//ServerApplication
class Server : public ServerApplication
{
protected:
	void initialize(Application& self)
	{
		loadConfiguration();
		ServerApplication::initialize(self);
	}

	void uninitialize()
	{
		ServerApplication::uninitialize();
	}

	int main(const std::vector<std::string>& args)
	{
		ServerSocket serverSock(7000);
		TCPServer tcpServer(new TestConnectionFactory(), serverSock);
		tcpServer.start();
		waitForTerminationRequest();
		tcpServer.stop();
		return Application::EXIT_OK;
	}
};
int main(int argc, char* argv[])
{
	Server app;
	return app.run(argc, argv);
}