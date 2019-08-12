
#ifndef CCONNECTION
#define CCONNECTION

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Connection
{
public:
	Connection(boost::asio::io_context& io_context) : socket(io_context) {}
	tcp::socket& getSocket() { return socket; }

private:
	tcp::socket socket;
};

#endif
