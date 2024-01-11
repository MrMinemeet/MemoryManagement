#ifndef TYPEDESCRIPTOR_HPP
#define TYPEDESCRIPTOR_HPP

#include <string>

class TypeDescriptor {
	public:
		int totalSize;
		int* pointerOffsetArray;
		int offsetAmount;

		TypeDescriptor(int obj_size, int* pointer_offset_array, int offset_amount);  // Constructor declaration

		// ToString method declaration
		std::string ToString() const;
};

#endif // TYPEDESCRIPTOR_HPP