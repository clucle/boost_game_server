
#ifndef CCONNECTION
#define CCONNECTION

#include <iostream>
#include <boost/asio.hpp>
#include <unordered_set>
#include <deque>
#include "chat_message.hpp"
#include "Connection.hpp"

class Connection;

using Connection_ptr = std::shared_ptr<Connection>;

class ConnectionManager
{
public:
	static ConnectionManager& getInstance() {
		static ConnectionManager instance;
		return instance;
	}

	Connection_ptr createConnection(boost::asio::io_context& io_context);

	void sendAll(const chat_message& msg);

	std::unordered_set<Connection_ptr> connections;
};

using boost::asio::ip::tcp;

class Connection : public std::enable_shared_from_this<Connection>
{
public:
	Connection(boost::asio::io_context& io_context) : socket(io_context) {}
	tcp::socket& getSocket() { return socket; }
	void do_read_header();
	void do_read_body();
	void send(const chat_message& msg);
	void do_write();

private:
	tcp::socket socket;
	chat_message read_msg;
	std::deque<chat_message> write_msgs;
};

#endif
