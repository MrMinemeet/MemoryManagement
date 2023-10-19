#include <iostream>
#include <string>
#include "Heap.hpp"
#include "TypeDescriptor.hpp"

int main() {
	std::cout << "Hello, GC user!" << std::endl;

	Heap heap;
	heap.alloc(10);
	heap.dealloc();

	int* array = new int[2];
	array[0] = 1;
	array[1] = 2;

	std::string type = "int";
	TypeDescriptor descriptor(8, array, 2);
	std::cout << descriptor.ToString() << std::endl;

	heap.registerType(type, descriptor);

	std::cout << heap.ToString() << std::endl;

	return 0;
}