#include "TypeDescriptor.hpp"

// Define member functions for the TypeDescriptor class here, if needed
TypeDescriptor::TypeDescriptor(int obj_size, int* pointer_offset_array, int offset_amount) {
    // Constructor implementation
    this->objectSize = obj_size;
	this->offsetAmount = offset_amount;
	this->pointerOffsetArray = pointer_offset_array;
}

TypeDescriptor::~TypeDescriptor() {
    // Destructor implementation
    delete(this->pointerOffsetArray);
}

std::string TypeDescriptor::ToString() {
	// ToString implementation
	std::string str = "Object size: " + std::to_string(this->objectSize) + "\n";
	str += "Offset amount: " + std::to_string(this->offsetAmount) + "\n";
	str += "Pointer offset array: [";
	for (int i = 0; i < this->offsetAmount; i++) {
		str += std::to_string(this->pointerOffsetArray[i]);
		if (i != this->offsetAmount - 1) {
			str += ", ";
		}
	}
	str += "]\n";
	return str;
}