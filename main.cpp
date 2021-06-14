#include <atl/manager/ThreadPool.hpp>

size_t inc(size_t _what) {
	return _what + 1;
}

int main() {
	atl::manager::ThreadPool tp(1);
	tp.start();

	auto result = tp.request(std::function(inc), 10ull);

	result.wait();

	std::string what = std::to_string(result.get()) + '\n';
	std::cout << what;

	tp.stop(500, true);

	return 0;
}