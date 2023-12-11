#include "Declarations.hpp"
#include "Heap.hpp"
#include "TypeDescriptor.hpp"
#include <iostream>
#include <string>

int main() {
#if DEBUG
	std::cout << "DEBUG-mode enabled!" << std::endl;
#endif
	std::cout << "Hello, GC user!" << std::endl;
	Heap heap;
	std::cout << heap.ToString() << std::endl;


	// TD based on "Garbage Collection" slide-set page 22
	// Create TypeDescriptor for a class (Block x; Block y; int data; Block z;)
	TypeDescriptor td = TypeDescriptor(20, new int[3]{0, 4, 12}, 3);
	std::cout << td.ToString() << std::endl;
#if DEBUG
	if(heap.registerType("Block", td)) {
		std::cout << "Successfully registered typeDescriptor!" << std::endl;
	} else {
		std::cout << "Failed to register typeDescriptor!" << std::endl;
		return 1;
	}
#endif

	Block* blockFromTD = heap.alloc("Block");
	std::cout << blockFromTD->ToString() << std::endl;
	std::cout << heap.ToString() << std::endl;

	/*
	Block* a = heap.alloc(512);
	Block* b = heap.alloc(400);
	Block* c = heap.alloc(8 KiB);
	//Block* d = heap.alloc(8 KiB);

	std::cout << heap.ToString() << std::endl;
	heap.dealloc(a);

	int* array = new int[2];
	array[0] = 1;
	array[1] = 2;

	std::string typeDescriptor = "int";
	TypeDescriptor descriptor(8, array, 2);
	std::cout << descriptor.ToString() << std::endl;

	heap.registerType(typeDescriptor, descriptor);

	std::cout << heap.ToString() << std::endl;

	*/
	return 0;
}