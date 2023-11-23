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
    void dealloc(Block* block);
    bool registerType(std::string& type, TypeDescriptor& descriptor);
	std::string ToString();
};

#endif // HEAP_HPP
