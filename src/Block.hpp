#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <string>

class Block {
	public:
		// Heap
		bool used;
		int size;

		// GC
		/*
		bool marked;
		Block* left;
		Block* right;
		*/
		Block(int size);  // Constructor declaration
		~Block(); // Destructor declaration

		// Additional member function declarations, if needed
		std::string ToString();

		/**
		 * Returns the data pointer of this block.
		 * @return the data pointer of this block.
		 * @return nullptr if this block is free.
		 */
		void* data();
};

#endif // BLOCK_HPP