#include "UsedBlock.hpp"

/*
 * The head takes 8 bytes in memory for the typeDescriptor pointer.
 * The rest until the next block is the data part. which depends on the typeDescriptor
 */
UsedBlock::UsedBlock(TypeDescriptor* typeDescriptor): Block(typeDescriptor) {
#if DEBUG
	// Fill memory with 0x02 (for debugging)
	if (typeDescriptor != nullptr) {
		int totalSize = typeDescriptor->totalSize;
		for (int i = 0; i < totalSize + sizeof(Block); ++i) {
			((char*) this)[i] = (char) 0x02;
		}
	}
#endif
}

std::string UsedBlock::ToString() const {
	std::string str = "UsedBlock { ";
	str += "totalSize: " + std::to_string(totalSize()) + ", ";
	str += "headerSize: " + std::to_string(headerSize()) + ", ";
	str += "dataSize: " + std::to_string(dataSize());
	str += "}";
	return str;
}

int UsedBlock::headerSize() const {
	return sizeof(UsedBlock);
}
