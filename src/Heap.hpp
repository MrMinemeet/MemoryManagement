#ifndef HEAP_HPP
#define HEAP_HPP

#include <unordered_map>
#include <string>
#include "Declarations.hpp"
#include "Block.hpp"

#include <iostream>
#include <list>
#include "TypeDescriptor.hpp"

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
	Block* alloc(int size);
	Block* alloc(const std::string& type);
    void dealloc(Block* block);
    bool registerType(const std::string& type, TypeDescriptor& descriptor);
	std::string ToString();
};

#endif // HEAP_HPP
