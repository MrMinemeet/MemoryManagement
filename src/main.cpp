#include <iostream>
#include <string>
#include "Declarations.hpp"
#include "Heap.hpp"
#include "TypeDescriptor.hpp"

int main() {
#if DEBUG
	std::cout << "DEBUG-mode enabled!" << std::endl;
#endif

	std::cout << "Hello, GC user!" << std::endl;

	Heap heap;

	std::cout << heap.ToString() << std::endl;

	auto a = heap.alloc(512);
	auto b = heap.alloc(400);
	auto c = heap.alloc(8 KiB);
	//auto d = heap.alloc(8 KiB);


	std::cout << heap.ToString() << std::endl;
	heap.dealloc(a);

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