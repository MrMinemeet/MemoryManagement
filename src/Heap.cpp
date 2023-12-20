#include "Heap.hpp"// Include the corresponding header file
#include "Block.hpp"


// Define the member functions of the Heap class here
Heap::Heap() {
	this->heap_buffer = std::malloc(HEAP_SIZE);

#if DEBUG
	// Fill memory with 0xaa (for debugging)
	for (int i = 0; i < HEAP_SIZE; ++i) {
		((char*) heap_buffer)[i] = (char) 0xaa;
	}
#endif

	this->fbHead = new (heap_buffer) FreeBlock(HEAP_SIZE - (int) sizeof(FreeBlock));// - sizeof(FreeBlock) because of the overhead
	this->free_bytes = HEAP_SIZE;

	std::cout << "A new heap has been created!" << std::endl;
}

Heap::~Heap() {
	std::free(heap_buffer);
	std::cout << "A heap has been destroyed!" << std::endl;
}

/*
 * Takes a chunk of size "sizeof(Block) + type.totalSize" from heap and return Block pointer
 */
Block* Heap::alloc(const std::string& type) {
	TypeDescriptor* typeDescriptor = type_map[type];
	if (typeDescriptor == nullptr) {
		std::cerr << "Type " << type << " not found!" << std::endl;
		return nullptr;
	}
	int requestedDataSize = typeDescriptor->totalSize;
	int requestedTotalSize = requestedDataSize + (int) sizeof(Block);
#if DEBUG
	std::cout << "Allocating a total of " << requestedTotalSize << " bytes from heap for " << requestedDataSize << " bytes of data…" << std::endl;
#endif

	// Go through free list and find a free block with enough space
	FreeBlock* cur = fbHead;
	FreeBlock* prev = nullptr;
	while (cur != nullptr) {
		if (cur->totalSize() >= requestedTotalSize) {
			// Found a free block with enough space
			break;
		}
		prev = cur;
		cur = cur->getNextFree();
	}
	if (cur == nullptr) {
		std::cerr << "No free block with enough space found!" << std::endl;
		return nullptr;
	}
	// check if it is necessary/worth it to split the block
	int leftOver = cur->totalSize() - requestedTotalSize;
	if (leftOver < FreeBlock::getMinFreeBlockSize()) {
#if DEBUG
		std::cout << "Can't split free block any further!" << std::endl;
#endif
		// Don't split, not enough space for a new FreeBlock
		// Remove cur from free list
		if (prev == nullptr) {
			// cur is the head of the free list, set the next free block as the new head
			fbHead = cur->getNextFree();
		} else {
			// cur is not the head of the free list, set the next free block as the next free block of the previous block
			*(FreeBlock**) prev->getNextFreePointer() = cur->getNextFree();
		}
	} else {
#if DEBUG
		std::cout << "Splitting free block!" << std::endl;
#endif
		// Split
		// Create a new FreeBlock after the allocated block
		FreeBlock* newFreeBlock = new ((char*) cur + requestedTotalSize) FreeBlock(leftOver - (int) sizeof(FreeBlock));
		// Set the next freeBlock of the new FreeBlock to the next free block of cur
		newFreeBlock->setNextFreePointer(cur->getNextFree());
		// Set the nextFreeBlock of prev to the new FreeBlock
		if (prev == nullptr) {
			// cur is the head of the free list, set the new FreeBlock as the new head
			fbHead = newFreeBlock;
		} else {
			// cur is not the head of the free list, set the new FreeBlock as the next free block of the previous block
			*(FreeBlock**) prev->getNextFreePointer() = newFreeBlock;
		}
	}

	// Set the typeDescriptor of the allocated block
	Block* block = new (cur) Block(typeDescriptor);

	// Adjust free_bytes
	free_bytes -= requestedTotalSize;

	// Return the allocated block
	return block;
}

void Heap::dealloc(Block* block) {
	std::cout << "Deallocating memory..." << std::endl;

	auto p = (Block*) heap_buffer;
	Block* left = nullptr;
	while (p != block) {
		left = p;
		p = (Block*) ((char*) p + p->dataSize() + sizeof(Block));
	}
	if (left != nullptr && !left->used) {
		// merge left
	} else {
		// add p to freelist
	}

	Block* right = (Block*) ((char*) p + p->dataSize() + (int) sizeof(Block));
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
	str += "Heap dataSize: " + std::to_string(HEAP_SIZE) + "\n";
	str += "Free bytes: " + std::to_string(free_bytes) + " | Used bytes: " + std::to_string((HEAP_SIZE - free_bytes)) + "\n";
	str += "Stored typeDescriptor descriptors: " + std::to_string(type_map.size()) + "\n";

	str += "Live blocks { ";
	int traversedSize = 0;
	Block* bCur = (Block*) heap_buffer;
	// FIXME: Results in  a SegFault when a block is allocated (e.g., executing line 34 in main.cpp)
	while (bCur != nullptr && traversedSize < HEAP_SIZE) {
		int curBlkSize;
		if (bCur->used) {
			// Normal Block
			str += "" + bCur->ToString() + postfix;
			postfix = ", ";
			curBlkSize = bCur->totalSize();
		} else {
			// FreeBlock
			FreeBlock* fbCur = (FreeBlock*) bCur;
			curBlkSize = fbCur->totalSize();
		}
		traversedSize += curBlkSize;
		bCur = (Block*) ((char*) bCur + curBlkSize);
	}
	str += " }\n";

	str += "Free blocks { ";
	FreeBlock* fbCur = fbHead;
	while (fbCur != nullptr) {
		str += "" + fbCur->ToString() + postfix;
		postfix = ", ";
		fbCur = fbCur->getNextFree();
	}
	str += " }\n";
	str += "}";

	return str;
}

/**
 * Prints a list of all live objects as well as free blocks.
 * Print the total amount of memory used by live objects.
 * For every live object the following values should be printed:
 * - address (hex)
 * - name of the object's type
 * - the first 4 bytes of te object in hex form (to get a clue of the object's contents)
 * - a list of all pointers in this object (in hex form)
 *
 */
void Heap::dump() const {
	std::cout << std::endl;
	std::cout << "Dumping heap..." << std::endl;
	std::string str = "Total bytes used: " + std::to_string(HEAP_SIZE - free_bytes) + "\n";
	str += "Live objects: { ";

	str += " }";
	std::cout << str << std::endl;
	std::cout << "Heap dumped!" << std::endl;
	std::cout << std::endl;
}
