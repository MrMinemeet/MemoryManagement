#include "UsedBlock.hpp"

/*
 * The head takes 8 bytes in memory for the rawTypeDescriptor pointer.
 * The rest until the next block is the data part. which depends on the rawTypeDescriptor
 */
UsedBlock::UsedBlock(TypeDescriptor* typeDescriptor): Block(typeDescriptor) {}

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
