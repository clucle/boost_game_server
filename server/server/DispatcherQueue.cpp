#include "DispatcherQueue.h"
#include "DispatcherQueue.h"

DispatcherQueue::DispatcherQueue(int thread_cnt)
{
	for (int i = 0; i < thread_cnt; i++) {
		threads_.push_back(boost::thread(boost::bind(&DispatcherQueue::dispatcher_queue_handler, (void*)this)));
	}
}

DispatcherQueue::~DispatcherQueue()
{
	// TODO: join thread
}

void DispatcherQueue::addTask(Task* task)
{
	// TODO: Lock
	task_list_.push_back(task);
}

void DispatcherQueue::dispatcher_queue_handler()
{
	// TODO: thread work
}
