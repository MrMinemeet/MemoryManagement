#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>
#include "TypeDescriptor.hpp"

class Heap {
private:
    const int HEAP_SIZE = 32 * 1024; // 32 KB
    void* heap_buffer;

public:
    // Constructor
    Heap();

    // Destructor
    ~Heap();

    // Methods
    void* alloc(int size);
    void dealloc();
    void registerType(std::string type, TypeDescriptor descriptor); // You need to declare TypeDescriptor here
};

#endif // HEAP_HPP
