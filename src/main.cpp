#include "Declarations.hpp"
#include "Heap.hpp"
#include "SlideBlock.hpp"
#include "TypeDescriptor.hpp"
#include <iostream>
#include <string>

int main() {
#if DEBUG
	std::cout << "DEBUG-mode enabled!" << std::endl;
#endif
	std::cout << "Hello, GC user!" << std::endl;
	Heap heap;
	//heap.dump();

	// TD based on "Garbage Collection" slide-set page 22
	// Create TypeDescriptor for a class (Block x; Block y; int getDataPart; Block z;)
	std::cout << std::endl;
	std::cout << "Creating TypeDescriptor for class 'SlideBlock'…" << std::endl;
	TypeDescriptor td = TypeDescriptor(32,
									   new int[3]{0, 8, 24}, // For offset explanation see SlideBlock.hpp
									   3);
	std::cout << td.ToString() << std::endl;
	if (heap.registerType("SlideBlock", td)) {
		std::cout << "Successfully registered rawTypeDescriptor!" << std::endl;
	} else {
		std::cout << "Failed to register rawTypeDescriptor!" << std::endl;
		return 1;
	}

	std::cout << std::endl;
	std::cout << "Allocating 'SlideBlock'…" << std::endl;
	UsedBlock* b1 = heap.alloc("SlideBlock");
	// I just use "new" here to trigger the constructor
	SlideBlock* sb1 = new (b1->getDataPart()) SlideBlock();


	std::cout << std::endl;
	std::cout << "Allocating 'SlideBlock' again…" << std::endl;
	UsedBlock* b2 = heap.alloc("SlideBlock");
	SlideBlock* sb2 = new (b2->getDataPart()) SlideBlock();
	sb1->x = (Block*) sb2;

	// Test dump
	std::cout << std::endl;
	heap.dump();

	// Test garbage collection without stuff to collect
	void* rootPointers[] = {nullptr, nullptr};
	rootPointers[0] = b1;
	rootPointers[1] = nullptr;
	std::cout << std::endl;
	std::cout << "Testing garbage collection when nothing is to collect…" << std::endl;
	heap.gc(rootPointers);
	heap.dump();

	// Test garbage collection with stuff to collect
	sb1->x = nullptr;
	heap.dump();
	std::cout << std::endl;
	std::cout << "Testing garbage collection when something is to collect…" << std::endl;
	heap.gc(rootPointers);
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

	std::string rawTypeDescriptor = "int";
	TypeDescriptor descriptor(8, array, 2);
	std::cout << descriptor.ToString() << std::endl;

	heap.registerType(rawTypeDescriptor, descriptor);

	std::cout << heap.ToString() << std::endl;

	*/
	return 0;
}