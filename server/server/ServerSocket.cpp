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
		[this, connection](boost::system::error_code error) {
			if (!error) {
				this->on_accept(connection, error);
			}
			do_accept();
		});
}

void ServerSocket::on_accept(Connection_ptr connection, const boost::system::error_code& error)
{
	if (!error) {
		connection->do_read_header();
	}
}
