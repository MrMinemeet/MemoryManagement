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
};

#endif // BLOCK_HPP