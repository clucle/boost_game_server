
#ifndef CDISPATCHER_QUEUE
#define CDISPATCHER_QUEUE

#include <vector>
#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>

#include "Task.hpp"

class DispatcherQueue : boost::noncopyable
{
public:
	DispatcherQueue(int thread_cnt);
	~DispatcherQueue();
	void addTask(Task* task);
	void dispatcher_queue_handler();

private:
	std::vector<boost::thread> threads_;
	std::list<Task*> task_list_;
};

#endif
