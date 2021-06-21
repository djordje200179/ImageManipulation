#pragma once

#include <functional>
#include <string>
#include <chrono>
#include <iostream>

class Test {
private:
	std::string name;
	std::function<void()> function;
public:
	Test(std::string name, std::function<void()> function) : name(name), function(function) {}

	void test() {
		std::cout << "TEST: " << name << std::endl;

		auto start_time = std::chrono::high_resolution_clock::now();
		function();
		auto end_time = std::chrono::high_resolution_clock::now();

		auto execution_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
		std::cout << "Execution time: " << execution_time.count() << "ms" << std::endl << std::endl;
	}
};