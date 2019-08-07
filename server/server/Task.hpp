
#ifndef CTASK
#define CTASK

#include <boost/function.hpp>
#include <boost/thread.hpp>

class Task
{

private:
	boost::function<void(void)> f_;
};

#endif
