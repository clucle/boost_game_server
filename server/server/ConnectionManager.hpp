
#ifndef CCONNECTION_MANAGER
#define CCONNECTION_MANAGER

#include <iostream>
#include <unordered_set>
#include <boost/asio.hpp>

#include "Connection.hpp"

using Connection_ptr = std::shared_ptr<Connection>;

class ConnectionManager
{
public:
	static ConnectionManager& getInstance() {
		static ConnectionManager instance;
		return instance;
	}

	Connection_ptr createConnection(boost::asio::io_context& io_context);

	std::unordered_set<Connection_ptr> connections;
};

#endif
