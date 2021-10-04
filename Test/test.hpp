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

		auto startTime = std::chrono::high_resolution_clock::now();
		function();
		auto endTime = std::chrono::high_resolution_clock::now();

		auto executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
		std::cout << "Execution time: " << executionTime.count() << "ms" << std::endl << std::endl;
	}
};