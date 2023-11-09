#include <iostream>
#include <string>
#include "Heap.hpp"
#include "TypeDescriptor.hpp"

int main() {
	std::cout << "Hello, GC user!" << std::endl;

	Heap heap;
	std::cout << heap.ToString() << std::endl;

	auto a = heap.alloc(8*1024);
	auto b = heap.alloc(8*1024);
	auto c = heap.alloc(8*1024);
	auto d = heap.alloc(8*1024);


	std::cout << heap.ToString() << std::endl;
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