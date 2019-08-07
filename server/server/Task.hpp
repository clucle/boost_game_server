
#ifndef CTASK
#define CTASK

#include <boost/function.hpp>
#include <boost/thread.hpp>

class Task
{
public:
	Task(boost::function<void(void)>&& f);
	void operator()() { f_(); }

private:
	boost::function<void(void)> f_;
};

Task* create_task(boost::function<void(void)> f);

#endif
