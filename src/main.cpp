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
	// Create TypeDescriptor for a class (Block x; Block y; int getDataPart; Block z;)
	std::cout << std::endl;
	std::cout << "Creating TypeDescriptor for class 'SlideBlock'…" << std::endl;
	TypeDescriptor td = TypeDescriptor(16, new int[3]{0, 4, 12}, 3);
	std::cout << td.ToString() << std::endl;
#if DEBUG
	if (heap.registerType("SlideBlock", td)) {
		std::cout << "Successfully registered typeDescriptor!" << std::endl;
	} else {
		std::cout << "Failed to register typeDescriptor!" << std::endl;
		return 1;
	}
#endif

	std::cout << std::endl;
	std::cout << "Allocating 'SlideBlock'…" << std::endl;
	Block* blockFromTD = heap.alloc("SlideBlock");
	std::cout << blockFromTD->ToString() << std::endl;
	std::cout << heap.ToString() << std::endl;


	// Test allocating multiple blocks
	std::cout << std::endl;
	std::cout << "Allocating more 'SlideBlock'…" << std::endl;
	for (int i = 0; i < 2; ++i) {
		std::cout << std::endl;
		std::cout << "Block number " << i << ":" << std::endl;
		heap.alloc("SlideBlock");
		std::cout << blockFromTD->ToString() << std::endl;
	}
	std::cout << heap.ToString() << std::endl;

	// Test dump
	std::cout << std::endl;
	heap.dump();

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