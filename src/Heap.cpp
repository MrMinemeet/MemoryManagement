#include "Heap.hpp"// Include the corresponding header file


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

	std::cout << fbHead->ToString() << std::endl;

	std::cout << "A new heap has been created!" << std::endl;

}

Heap::~Heap() {
	std::free(heap_buffer);
	std::cout << "A heap has been destroyed!" << std::endl;
}

/*
 * Takes a chunk of size "sizeof(Block) + type.totalSize" from heap and return Block pointer
 */
UsedBlock* Heap::alloc(const std::string& type) {
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
	UsedBlock* block = new (cur) UsedBlock(typeDescriptor);

	// Adjust free_bytes
	free_bytes -= requestedTotalSize;

	// Return the allocated block
	return block;
}

/*
// Commented out, as I think this is not actually needed.
// The GC should perform deallocate of unused blocks in a more general context.
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
*/

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
	while (bCur != nullptr && traversedSize < HEAP_SIZE) {
 		if (!bCur->isFreeBlock()) {
			// UsedBlock
			str += "" + bCur->ToString() + postfix;
			postfix = ", ";
		}
		traversedSize += bCur->totalSize();
		bCur = (Block*) ((char*) bCur + bCur->totalSize());
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
 * Prints a list of all live objects as well as free blocks. <br>
 * <br>
 * Print the total amount of memory used by live objects. <br>
 * For every live object the following values should be printed: <br>
 * - address (hex) <br>
 * - name of the object's type <br>
 * - the first 4 bytes of te object in hex form (to get a clue of the object's contents) <br>
 * - a list of all pointers in this object (in hex form) <br>
 * <br>
 * Print the total amount of free memory. <br>
 * For every free block the following values should be printed: <br>
 * - address (hex) <br>
 * - length (in bytes) <br>
 */
void Heap::dump() const {
	std::cout << std::endl;
	std::cout << "Dumping heap..." << std::endl;
	// Live Objects
	std::string str = "Total bytes used: " + std::to_string(HEAP_SIZE - free_bytes) + "\n";
	str += "Live objects: {\n";
	std::string postfix;
	int traversedSize = 0;
	Block* bCur = (Block*) heap_buffer;
	while (bCur != nullptr && traversedSize < HEAP_SIZE) {
		int curBlkSize;
		if (!bCur->isFreeBlock()) {
			// UsedBlock
			UsedBlock* ubCur = (UsedBlock*) bCur;
			curBlkSize = ubCur->totalSize();
			char* data = (char*) ubCur->getDataPart();
			TypeDescriptor* type = ubCur->getTypeDescriptor();

			str += "\tUsed Block {\n";
			str += "\t\tAddress: " + Heap::pointerToHexString((int*) ubCur) + "\n";
			str += "\t\tType: " + getTypeDescriptorName(type) + "\n";
			str += "\t\tIs marked: " + boolToString(ubCur->isMarked()) + "\n"; // This was not requested but I found it very helpful
			str += "\t\tFirst 4 bytes: [ ";
			for (int i = 0; i < 4; ++i) {
				str += "0x" + Heap::charToHex(data[i]);
				if (i < 3) {
					str += ", ";
				}
			}
			str += " ]\n";
			str += "\t\tPointers: [ ";
			for (int i = 0; i < type->offsetAmount; ++i) {
				int* addr = (int*) ((char*) ubCur + type->pointerOffsetArray[i]);
				str += Heap::pointerToHexString(addr);
				if (i < type->offsetAmount - 1) {
					str += ", ";
				}
			}
			str += " ]\n";
			str += "\t}\n";
		} else {
			// FreeBlock
			FreeBlock* fbCur = (FreeBlock*) bCur;
			curBlkSize = fbCur->totalSize();
		}
		traversedSize += curBlkSize;
		bCur = (Block*) ((char*) bCur + curBlkSize);
	}
	str += "}\n";

	// Free Blocks
	str += "Total free bytes: " + std::to_string(free_bytes) + "\n";
	str += "Free blocks {\n";
	FreeBlock* fbCur = fbHead;
	while (fbCur != nullptr) {
		str += "\tFreeBlock {\n";
		str += "\t\tAddress: " + Heap::pointerToHexString((int*) fbCur) + "\n";
		str += "\t\tLength: " + std::to_string(fbCur->totalSize()) + "\n";
		str += "\t}\n";
		fbCur = fbCur->getNextFree();
	}
	str += "}";

	std::cout << str << std::endl;
	std::cout << "Heap dumped!" << std::endl;
	std::cout << std::endl;
}

/**
 * Converts a pointer to a hex string.
 * @param ptr The pointer to convert.
 * @return The hex string.
 */
std::string Heap::pointerToHexString(int* ptr) {
	std::stringstream ss;
	ss << std::hex << (uintptr_t) ptr;
	return "0x" + ss.str();
}

/**
 * Converts a char to a hex string.
 * @param c The char to convert.
 * @return The hex string.
 */
std::string Heap::charToHex(char c) {
	std::stringstream ss;
	ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
	return ss.str();
}

/**
 * Converts a bool to a string.
 * @param b The bool to convert.
 * @return "true" if b is true, "false" otherwise.
 */
std::string Heap::boolToString(bool b) {
	return b ? "true" : "false";
}

/**
 * Returns the name of the typeDescriptor.
 * @param typeDescriptor The typeDescriptor to get the name of.
 * @return The name of the typeDescriptor.
 */
std::string Heap::getTypeDescriptorName(TypeDescriptor* typeDescriptor) const {
	for (auto& it: type_map) {
		if (it.second == typeDescriptor) {
			return it.first;
		}
	}
	return "NOT FOUND";
}

/**
 * Invoke the Deutsch-Schorr-Waite garbage collector algorithm.
 * The root is an array of root pointers with a null value as termination.
 * @param array of root pointers
 */
void Heap::gc(void* rootPointers[]) {
	// ---- Mark Phase

	// Loop through all root pointers
	for(int i = 0; rootPointers[i] != nullptr; ++i) {
		// Run Marking starting from that root pointer
		void* rootPointer = rootPointers[i];
		mark(static_cast<Block*>(rootPointer));
	}

	// ---- Sweep Phase
	sweep();
}

/**
 * Call GC with an array of root pointers.
 * @param rootPointers array of Block root pointers
 */
void Heap::gc(Block* rootPointers[]) {
	// Basically just a helper because of size difference between void* and Block* when using indices access
	gc((void**) rootPointers);
}


/**
 * Marks objects that can be (in-)directly reached from the roots.
 * The marking is performed on the LSB of the TypeDescriptor address.
 * @param rootPointer to start marking from
 */
void Heap::mark(Block* rootPointer) {
	// Skip if no valid pointer or was already checked
	if (rootPointer == nullptr || rootPointer->isMarked()) {
		return;
	}

	/* Instead of marking the currently visited pointer inside "Block" I decided to use a map here.
	 * Since this is only needed for the marking phase, I think it is okay to use a map here.
	 */
	std::unordered_map<Block*, int> currentVisitIndex;

	Block* prev = nullptr;
	Block* cur = rootPointer;// Don't want to use rootPointer directly, as it is a parameter
	while (true) {
		if (!currentVisitIndex.contains(cur)) {
			// Add to map if never visited before
			currentVisitIndex.insert({cur, -1});
#if DEBUG
			std::cout << "Added block curChildIdx " << cur << " to map" << std::endl;
#endif
		}
		// The current block as visited
		currentVisitIndex[cur] =  currentVisitIndex[cur] + 1;
		int curIdx = currentVisitIndex[cur];
		cur->mark(true); // Somewhat redundant to mark it each time, but checking it would also be almost the same effort

#if DEBUG
		std::cout << "Marked block " << cur << " with index " << curIdx << std::endl;
#endif
		int offset = cur->getTypeDescriptor()->pointerOffsetArray[curIdx];
		if (curIdx < cur->getTypeDescriptor()->offsetAmount) {
			// Advance
#if DEBUG
			std::cout << "Advancing to child " << curIdx << " of block " << cur << std::endl;
#endif
			Block** childPointerAddr = (Block**) ((int*) cur->getDataPart() + offset);
			Block* p = *childPointerAddr;
			if (p != nullptr && !p->isMarked()) {
				// Basically a "cur.td.pointerOffset[curIdx] = prev" operation
				*childPointerAddr = prev;
				prev = cur;
				cur = p;
			}
		} else {
			// Retreat
#if DEBUG
			std::cout << "Retreating from block " << cur << std::endl;
#endif
			if (prev == nullptr) {
				// Done
				break;
			}
			Block* p = cur;
			cur = prev;
			// Basically a "prev = cur.td.pointerOffset[curIdx]" operation
			prev = (Block*) *((Block**) ((char*) cur->getDataPart() + offset));
			// Basically a "cur.td.pointerOffset[curIdx] = p" operation
			*((Block**) ((char*) cur->getDataPart() + offset)) = p;
		}
	}
}

/**
 * Builds a new freelist and merge adjacent free blocks
 */
void Heap::sweep() {
	Block* p = (Block*) heap_buffer;
	FreeBlock* free = nullptr;

	while((void*) p < getHeapEnd()) {
		if(p->isFreeBlock()) {
			p->mark(false);
		} else {
			TypeDescriptor* pTD = p->getTypeDescriptor();
			int size = pTD->totalSize;

			Block* q = (Block*)((char*) p + size);
			// FIXME: Here a SegFault occurs
			TypeDescriptor* qTD = q->getTypeDescriptor();
			while(q < getHeapEnd() && !q->isMarked()) {
				// Merge
				size += qTD->totalSize;
				q = q + qTD->totalSize;
			}
			p->setTypeDescriptor((TypeDescriptor*) p);
			pTD->totalSize = size;
			FreeBlock* freeP = (FreeBlock*) p;
			freeP->setNextFreePointer(free);
			free = freeP;
		}
	}
}

/**
 * Calculates and returns the end of the heap
 * @return Address of the end of the heap
 */
void* Heap::getHeapEnd() const {
	return (char*)heap_buffer + HEAP_SIZE;
}
