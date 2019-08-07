
#ifndef CDISPATCHER_QUEUE
#define CDISPATCHER_QUEUE

#include <vector>
#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>

#include "Task.hpp"

class DispatcherQueue : boost::noncopyable
{
public:
	DispatcherQueue(int n_thread);
	~DispatcherQueue();
	void addTask(Task* task);
	void dispatcher_queue_handler();

private:
	int n_threads_;
	std::vector<boost::thread> threads_;
	std::list<Task*> task_list_;
	boost::mutex task_lock_;
	boost::condition_variable cv_;

};

#endif
