#ifndef HEAP_HPP
#define HEAP_HPP

#include "Block.hpp"
#include "Declarations.hpp"
#include <string>
#include <unordered_map>

#include "FreeBlock.hpp"
#include "TypeDescriptor.hpp"
#include <iostream>
#include <list>

class Heap {
private:
	// TODO: Adjust heap to 32 KiB for the final submission
	const int HEAP_SIZE = 64; // as bytes
	void* heap_buffer;
	uint free_bytes;
	FreeBlock* fbHead;
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
	void dump() const;
	std::string ToString();
};

#endif// HEAP_HPP
