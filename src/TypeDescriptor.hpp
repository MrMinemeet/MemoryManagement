#ifndef TYPEDESCRIPTOR_HPP
#define TYPEDESCRIPTOR_HPP

#include <string>

class TypeDescriptor {
	private:
		int offsetAmount;

	public:
		int objectOffset;
		int* pointerOffsetArray;

		TypeDescriptor(int obj_size, int* pointer_offset_array, int offset_amount);  // Constructor declaration
		~TypeDescriptor(); // Destructor declaration

		// ToString method declaration
		std::string ToString();
};

#endif // TYPEDESCRIPTOR_HPP