#include "TypeDescriptor.hpp"

// Define member functions for the TypeDescriptor class here, if needed
TypeDescriptor::TypeDescriptor(int obj_size, int pointer_offset_array[], int offset_amount) {
    // Constructor implementation
    this->objectSize = obj_size;
	this->pointerOffsetArray = pointer_offset_array;
	this->offsetAmount = offset_amount;
}

TypeDescriptor::~TypeDescriptor() {
    // Destructor implementation
    delete(this->pointerOffsetArray);
}

std::string TypeDescriptor::ToString() {
	// ToString implementation
	std::string str = "TypeDescriptor {\n";
	str += "\tObject size: " + std::to_string(this->objectSize) + "\n";
	str += "\tPointer offset array: [";
	for (int i = 0; i < this->offsetAmount; i++) {
		str += std::to_string(this->pointerOffsetArray[i]);
		if (i != this->offsetAmount - 1) {
			str += ", ";
		}
	}
	str += "]\n";
	str += "\tOffset amount: " + std::to_string(this->offsetAmount) + "\n";
	str += "}";
	return str;
}