#include "Heap.hpp" // Include the corresponding header file
#include "Block.hpp"

// Define the member functions of the Heap class here
Heap::Heap() {
    this->heap_buffer = std::malloc(HEAP_SIZE);
	this->free = {new Block(HEAP_SIZE)};
    std::cout << "A new heap has been created!" << std::endl;
}

Heap::~Heap() {
    std::free(heap_buffer);
    std::cout << "A heap has been destroyed!" << std::endl;
}

Block* Heap::alloc(int size) {
	if (size > free_bytes) {
		std::cout << "Not enough memory!" << std::endl;
		return nullptr;
	}
    std::cout << "Trying to allocate " << size << " bytes of memory..." << std::endl;
    // Implement the allocation logic here

	auto itr = this->free.begin();

	Block* freeBlock = this->free.front();
	while ( freeBlock->size < size) {

	}


	free_bytes -= size;
}

void Heap::dealloc() {
    std::cout << "Deallocating memory..." << std::endl;
    // Implement the deallocation logic here
}

/// Register a type with the Heap. Will return true if the type was successfully registered, false otherwise.
bool Heap::registerType(std::string& type, TypeDescriptor& descriptor) {
	if (type_map.find(type) != type_map.end()) {
		std::cout << "Type " << type << " already exists!" << std::endl;
		return false;
	}
	std::cout << "Registering type " << type << std::endl;
	type_map[type] = &descriptor;
}

std::string Heap::ToString() {
	std::string str = "Heap size: " + std::to_string(HEAP_SIZE) + "\n";
	str += "Free bytes: " + std::to_string(free_bytes) + "\n";

	return str;
}
