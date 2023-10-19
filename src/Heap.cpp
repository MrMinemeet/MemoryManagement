#include "Heap.hpp" // Include the corresponding header file

// Define the member functions of the Heap class here
Heap::Heap() {
    heap_buffer = std::malloc(HEAP_SIZE);
    std::cout << "A new heap has been created!" << std::endl;
}

Heap::~Heap() {
    std::free(heap_buffer);
    std::cout << "A heap has been destroyed!" << std::endl;
}

void* Heap::alloc(int size) {
    std::cout << "Allocating " << size << " bytes of memory..." << std::endl;
    // Implement the allocation logic here
	
}

void Heap::dealloc() {
    std::cout << "Deallocating memory..." << std::endl;
    // Implement the deallocation logic here
}

void Heap::registerType(std::string type, TypeDescriptor descriptor) {
    std::cout << "Registering type " << type << std::endl;
    // Implement the type registration logic here
}
