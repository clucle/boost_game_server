#include "task.hpp"

Task::Task(boost::function<void(void)>&& f) {
	f_ = std::move(f);
}

Task* create_task(boost::function<void(void)> f) {
	return new Task(std::move(f));
}
