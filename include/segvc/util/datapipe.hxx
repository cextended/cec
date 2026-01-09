#pragma once

#include <queue>
#include <condition_variable>
#include<mutex>

namespace segvc {

template<typename T>
struct DataPipe {

	std::condition_variable con_var;

	std::mutex mut;
	std::queue<T> data;

	inline DataPipe() = default;
	inline DataPipe(const DataPipe&) = delete;
	inline DataPipe& operator=(const DataPipe&) = delete;

	inline DataPipe<T>& operator<<(T &&value) {
		std::unique_lock<std::mutex> lock(mut);

		this->data.push(std::move(value));

		con_var.notify_one();
		return *this;
	}

	inline DataPipe<T>& operator>>(T &value) {
		std::unique_lock<std::mutex> lock(mut);
		while(data.empty())
			con_var.wait(lock);

		value = std::move(this->data.front());
		this->data.pop();

		return *this;
	}

};

}
