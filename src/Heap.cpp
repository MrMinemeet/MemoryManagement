#include "Heap.hpp" // Include the corresponding header file
#include "Block.hpp"


// Define the member functions of the Heap class here
Heap::Heap() {
    this->heap_buffer = std::malloc(HEAP_SIZE);
	this->free = {new (heap_buffer) Block(HEAP_SIZE)};
	this->free_bytes = HEAP_SIZE;
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

	Block* current = nullptr;
	for (Block* block: free) {
		current = block;
		if (current->size >= size+4) {
			break;
		}
	}

	if (current->size < size+4) {
		std::cout << "Not enough memory!" << std::endl;
		return nullptr;
	}

	auto p = current;
	int new_size = current->size - (size + 4);
	if (new_size >= 8) { // split block
		char* position = (char*) current + current->size - size - 4;
		p = new (position) Block(size + 4);
		current->size = new_size;
	} else { // remove block from freelist
		free.remove(current);
	}

	free_bytes -= size;

	p->used = true;
	return p;
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
	return true;
}

std::string Heap::ToString() {
	std::string postfix;
	std::string str = "Heap size: " + std::to_string(HEAP_SIZE) + "\n";
	str += "Free bytes: " + std::to_string(free_bytes) + "\n";


	str += "Free blocks {\n";
	for (Block* block : free) {
		str += "\t" + block->ToString() + postfix + "\n";
		postfix = ", ";
	}
	str += "}\n";

	return str;
}
