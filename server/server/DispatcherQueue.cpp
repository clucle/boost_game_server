
#include "DispatcherQueue.hpp"
#include "DispatcherQueue.hpp"

DispatcherQueue::DispatcherQueue()
{
	n_threads_ = 4;
	for (int i = 0; i < n_threads_; i++) {
		threads_.push_back(boost::thread(&DispatcherQueue::dispatcher_queue_handler, this));
	}
}


DispatcherQueue::DispatcherQueue(int n_thread)
{
	n_threads_ = n_thread;
	for (int i = 0; i < n_threads_; i++) {
		threads_.push_back(boost::thread(&DispatcherQueue::dispatcher_queue_handler, this));
	}
}

DispatcherQueue::~DispatcherQueue()
{
	// TODO: joinable or terminate thread
	for (int i = 0; i < n_threads_; i++) {
		threads_[i].join();
	}
}

void DispatcherQueue::addTask(Task* task)
{
	task_lock_.lock();
	bool const was_empty = task_list_.empty();
	task_list_.push_back(task);
	task_lock_.unlock();
	if (was_empty) cv_.notify_all();
}

void DispatcherQueue::dispatcher_queue_handler()
{
	// TODO: add exit condition
	boost::unique_lock<boost::mutex> lock(task_lock_);
	do {
		cv_.wait(lock, [this]() { return task_list_.size(); });
		if (task_list_.size()) {
			Task* task = task_list_.front();
			task_list_.pop_front();
			task_lock_.unlock();

			if (task) {
				(*task)();
			}
			delete task;

			task_lock_.lock();
		}
	} while (1);
}
