#ifndef HEAP_HPP
#define HEAP_HPP

#include <unordered_map>
#include <string>
#include "Block.hpp"

#include <iostream>
#include <list>
#include "TypeDescriptor.hpp"

class Heap {
private:
    const int HEAP_SIZE = 32 * 1024; // 32 KB
    void* heap_buffer;
	int free_bytes;
    std::list<Block*> free;
	std::unordered_map<std::string, TypeDescriptor*> type_map;

public:
    // Constructor
    Heap();

    // Destructor
    ~Heap();

    // Methods
    Block* alloc(int size);
    void dealloc();
    bool registerType(std::string& type, TypeDescriptor& descriptor);
	std::string ToString();
};

#endif // HEAP_HPP
