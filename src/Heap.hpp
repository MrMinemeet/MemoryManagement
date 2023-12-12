#ifndef HEAP_HPP
#define HEAP_HPP

#include "Block.hpp"
#include "Declarations.hpp"
#include <string>
#include <unordered_map>

#include "TypeDescriptor.hpp"
#include <iostream>
#include <list>

class Heap {
private:
	// TODO: Adjust heap to 32 KiB for the final submission
	const uint HEAP_SIZE = 8 KiB;
	void* heap_buffer;
	uint free_bytes;
	std::list<Block*> free;
	std::unordered_map<std::string, TypeDescriptor*> type_map;

public:
	// Constructor
	Heap();

	// Destructor
	~Heap();

	// Methods
	Block* alloc(const std::string& type);
	void dealloc(Block* block);
	bool registerType(const std::string& type, TypeDescriptor& descriptor);
	std::string ToString();
};

#endif// HEAP_HPP
