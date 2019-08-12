
#ifndef CSERVER_SOCKET
#define CSERVER_SOCKET

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/bind.hpp>

#include "ConnectionManager.hpp"

using boost::asio::ip::tcp;

class ServerSocket : boost::noncopyable, std::enable_shared_from_this<ServerSocket>
{
public:
	ServerSocket(boost::asio::io_context& io_context) : io_context(io_context) {}
	void open(uint16_t port);
	void on_accept(Connection_ptr connection, const boost::system::error_code& error);

private:
	void do_accept();

	boost::asio::io_context& io_context;
	uint16_t serverPort = 0;
	tcp::endpoint endpoint;
	std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor;
};

#endif
