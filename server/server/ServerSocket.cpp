#include "ServerSocket.hpp"

void ServerSocket::open(uint16_t port)
{
	serverPort = port;
	if (acceptor.is_open()) acceptor.close();
	endpoint = tcp::endpoint(tcp::v4(), port);
	acceptor = tcp::acceptor(io_context, endpoint);
	do_accept();
}

void ServerSocket::do_accept()
{
	
}
