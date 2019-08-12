
#ifndef CCONNECTION
#define CCONNECTION

#include <iostream>
#include <boost/asio.hpp>
#include "chat_message.hpp"

using boost::asio::ip::tcp;

class Connection : public std::enable_shared_from_this<Connection>
{
public:
	Connection(boost::asio::io_context& io_context) : socket(io_context) {}
	tcp::socket& getSocket() { return socket; }
	void do_read_header();
	void do_read_body();

private:
	tcp::socket socket;
	chat_message read_msg;
};

#endif
