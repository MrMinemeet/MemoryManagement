#include <iostream>
#include <string>
#include "Heap.hpp"

int main() {
	std::cout << "Hello, World!" << std::endl;

	Heap heap;
	heap.alloc(10);
	heap.dealloc();

	return 0;
}