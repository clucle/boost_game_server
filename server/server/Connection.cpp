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
				do_read_header();
			}
			else
			{
				// out
			}
		});
}
