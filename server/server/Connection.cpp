#include "Connection.hpp"

void Connection::do_read_header()
{
	auto self(shared_from_this());
	boost::asio::async_read(socket,
		boost::asio::buffer(read_msg.data(), chat_message::header_length),
		[this, self](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec && read_msg.decode_header())
			{
				do_read_body();
			}
			else
			{
				// out
			}
		});
}

void Connection::do_read_body()
{
	auto self(shared_from_this());
	boost::asio::async_read(socket,
		boost::asio::buffer(read_msg.body(), read_msg.body_length()),
		[this, self](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{
				ConnectionManager::getInstance().sendAll(read_msg);
				do_read_header();
			}
			else
			{
				// out
			}
		});
}

void Connection::send(const chat_message& msg)
{
	bool write_in_progress = !write_msgs.empty();
	write_msgs.push_back(msg);
	if (!write_in_progress)
	{
		do_write();
	}
}

void Connection::do_write()
{
	auto self(shared_from_this());
	boost::asio::async_write(socket,
		boost::asio::buffer(write_msgs.front().data(),
			write_msgs.front().length()),
		[this, self](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{
				write_msgs.pop_front();
				if (!write_msgs.empty())
				{
					do_write();
				}
			}
			else
			{
				// out
			}
		});
}

Connection_ptr ConnectionManager::createConnection(boost::asio::io_context& io_context)
{
	auto connection = std::make_shared<Connection>(io_context);
	connections.insert(connection);
	return connection;
}

void ConnectionManager::sendAll(const chat_message& msg)
{
	for (auto connection : connections)
		connection->send(msg);
}
