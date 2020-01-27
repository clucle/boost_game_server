#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>
#include "chatmessage.hpp"
#include "dispatcherqueue.hpp"
#include "serversocket.hpp"

using boost::asio::ip::tcp;

DispatcherQueue g_dispatcherQueue;

int main(int argc, char* argv[])
{
	try
	{
		boost::asio::io_context io_context;
		ServerSocket serverSocket(io_context);
		serverSocket.open(9404);
		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
