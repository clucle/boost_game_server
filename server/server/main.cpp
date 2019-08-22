#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>
#include "chat_message.hpp"
#include "DispatcherQueue.h"
#include "ServerSocket.hpp"

using boost::asio::ip::tcp;

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
