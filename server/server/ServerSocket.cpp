#include "ServerSocket.hpp"

void ServerSocket::open(uint16_t port)
{
	serverPort = port;
	endpoint = tcp::endpoint(tcp::v4(), port);
	acceptor.reset(new tcp::acceptor(io_context, endpoint));
	do_accept();
}

void ServerSocket::do_accept()
{
	if (!acceptor) {
		return;
	}

	auto connection = ConnectionManager::getInstance().createConnection(io_context);
	acceptor->async_accept(connection->getSocket(),
		[this](boost::system::error_code error) {
			if (!error) {
				std::cout << "accept client" << std::endl;
			}
			do_accept();
		});
}
