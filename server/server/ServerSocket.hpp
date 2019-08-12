
#ifndef CSERVER_SOCKET
#define CSERVER_SOCKET

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>

using boost::asio::ip::tcp;

class ServerSocket : boost::noncopyable
{
public:
	ServerSocket(boost::asio::io_context& io_context) : io_context(io_context) {}
	void open(uint16_t port);

private:
	void do_accept();

	boost::asio::io_context& io_context;
	uint16_t serverPort = 0;
	tcp::endpoint endpoint;
	tcp::acceptor acceptor;
};

#endif
