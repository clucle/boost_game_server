
#ifndef CCONNECTION
#define CCONNECTION

#include <iostream>
#include <boost/asio.hpp>
#include <unordered_set>
#include <deque>
#include "chatmessage.hpp"
#include "dispatcherqueue.hpp"
#include "connection.hpp"


extern DispatcherQueue g_dispatcherQueue;
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

	void sendAll(const ChatMessage& msg);

	std::unordered_set<Connection_ptr> connections;
};

using boost::asio::ip::tcp;

class Connection : public std::enable_shared_from_this<Connection>, boost::noncopyable
{
public:
	enum ConnectionState_t {
		OPEN,
		CLOSED,
	};

	Connection(boost::asio::io_context& io_context) : socket(io_context) {
		connection_state = CLOSED;
	}

	tcp::socket& getSocket() { return socket; }
	void do_read_header();
	void do_read_body();
	void send(const ChatMessage& msg);
	void do_write();
	void set_state(ConnectionState_t state);

private:
	tcp::socket socket;
	ChatMessage read_msg;
	std::deque<ChatMessage> write_msgs;
	ConnectionState_t connection_state;
};

#endif
