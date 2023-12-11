#include "Heap.hpp"// Include the corresponding header file
#include "Block.hpp"


// Define the member functions of the Heap class here
Heap::Heap() {
	this->heap_buffer = std::malloc(HEAP_SIZE);

#if DEBUG
	// Fill memory with 0xff (for debugging)
	for (int i = 0; i < HEAP_SIZE; ++i) {
		((char*) heap_buffer)[i] = (char) 0xff;
	}
#endif

	this->free = {new (heap_buffer) Block(HEAP_SIZE - sizeof(Block))};// - sizeof(Block) because of the overhead
	this->free_bytes = HEAP_SIZE;

	std::cout << "A new heap has been created!" << std::endl;
}

Heap::~Heap() {
	std::free(heap_buffer);
	std::cout << "A heap has been destroyed!" << std::endl;
}

/*
 * Takes memory of size "size" + sizeOf(Block) from the heap in a "first-fit" fashion.
 * The memory part, where the actual data is stored, is returned. I.e., the header of the first sizeof(Block) are skipped
 * Block-header | data ("size" bytes)
 *               ^___ returned Block*
 */
Block* Heap::alloc(int size) {
	std::cout << "Trying to allocate " << size << " bytes of memory..." << std::endl;
	if (size > free_bytes) {
		std::cout << "Not enough memory!" << std::endl;
		return nullptr;
	}
	// Implement the allocation logic here

	// Look for free block that fits the to be allocated dataSize + bit of overhead (sizeof(Block))
	Block* current = nullptr;
	for (Block* block: free) {
		current = block;
		if (current->dataSize >= size + sizeof(Block)) {
			break;
		}
	}

	// Check if last block in "free" list is big enough
	if (current->dataSize < size + sizeof(Block)) {
		std::cout << "Not enough memory!" << std::endl;
		return nullptr;
	}

	if (current == nullptr) {
		std::cout << "Somehow 'current' block pointer got null" << std::endl;
		return nullptr;
	}

	Block* p = current;
	int new_size = current->dataSize - size - sizeof(Block);
	if (new_size >= 2 * sizeof(Block)) {// split block
		//char* atBack = (char*) current + current->dataSize + sizeof(Block);
		//char* withSpaceForBlock = atBack - dataSize;
		//char* withOverhead = withSpaceForBlock - sizeof(Block);
		//char* position = withOverhead;
		char* position = (char*) current + current->dataSize - size;// sizeof(Block) can be dropped
		p = new (position) Block(size);
		current->dataSize = new_size;
	} else {// remove block from freelist
		free.remove(current);
	}
	p->used = true;

#if DEBUG
	// Fill memory with 0xab (for debugging)
	for (int i = 0; i < size; ++i) {
		((char*) p)[i + sizeof(Block)] = (char) 0xab;
	}
#endif

	free_bytes -= size + sizeof(Block);

	std::cout << "Allocated " << size << " bytes of memory at " << p << std::endl;
	return p;
}

Block* Heap::alloc(const std::string& type) {
	// Get typeDescriptor descriptor from type_map
	TypeDescriptor* descriptor = type_map[type];
	if (descriptor == nullptr) {
		std::cout << "Type " << type << " not found!" << std::endl;
		return nullptr;
	}

	// Get dataSize of object from typeDescriptor descriptor
	int objectSize = descriptor->objectSize;

	// Allocate memory
	Block* block = alloc(objectSize);

	// Set typeDescriptor of block
	if (block != nullptr) {
		block->typeDescriptor = descriptor;
	}
	return block;
}

void Heap::dealloc(Block* block) {
	std::cout << "Deallocating memory..." << std::endl;

	auto p = (Block*) heap_buffer;
	Block* left = nullptr;
	while (p != block) {
		left = p;
		p = (Block*) ((char*) p + p->dataSize + sizeof(Block));
	}
	if (left != nullptr && !left->used) {
		// merge left
	} else {
		// add p to freelist
	}

	Block* right = (Block*) ((char*) p + p->dataSize + sizeof(Block));
	if (!right->used) {
		// remove right from freelist
		// merge p and right
	}

	// Implement the reallocation logic here
}

/// Register a typeDescriptor with the Heap. Will return true if the typeDescriptor was successfully registered, false otherwise.
bool Heap::registerType(const std::string& type, TypeDescriptor& descriptor) {
	if (type_map.find(type) != type_map.end()) {
		std::cout << "Type " << type << " already exists!" << std::endl;
		return false;
	}
	std::cout << "Registering typeDescriptor " << type << std::endl;
	type_map[type] = &descriptor;
	return true;
}

std::string Heap::ToString() {
	std::string postfix;
	std::string str = "Heap {\n";
	str += "\tHeap dataSize: " + std::to_string(HEAP_SIZE) + "\n";
	str += "\tFree bytes: " + std::to_string(free_bytes) + "\n";
	str += "\tStored typeDescriptor descriptors: " + std::to_string(type_map.size()) + "\n";


	str += "\tFree blocks {\n";
	for (Block* block: free) {
		str += "\t\t" + block->ToString() + postfix + "\n";
		postfix = ", ";
	}
	str += "\t}\n";
	str += "}";

	return str;
}
