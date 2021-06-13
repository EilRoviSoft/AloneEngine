#include <string>
#include <iostream>
#include <chrono>

#include <atl/manager/ThreadPool.hpp>
using namespace atl::manager;

size_t inc(size_t _out) {
	return _out + 1;
}

int main() {
	ThreadPool tp(1);

	auto result = tp.push(std::function(inc), 10ull);

	result.wait();

	std::string what = std::to_string(result.get()) + '\n';
	std::cout << what;

	std::this_thread::sleep_for(std::chrono::seconds(5));

	return 0;
}