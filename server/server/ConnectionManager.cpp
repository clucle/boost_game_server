#include "ConnectionManager.hpp"

Connection_ptr ConnectionManager::createConnection(boost::asio::io_context& io_context)
{
	auto connection = std::make_shared<Connection>(io_context);
	connections.insert(connection);
	return connection;
}
