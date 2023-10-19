#include <iostream>
#include <string>

class Heap {
	private:
		const int HEAP_SIZE = 32 * 1024; // 32 KB
		void* heap_buffer = malloc(HEAP_SIZE);


	public:
		// Constructor
		Heap() {
			std::cout << "A new heap has been created!" << std::endl;
		}

		// Destructor
		~Heap() {
			free(heap_buffer);
			std::cout << "A heap has been destroyed!" << std::endl;
		}

		// Methods
		void* alloc(int size) {
			std::cout << "Allocating " << size << " bytes of memory..." << std::endl;
		}

		void dealloc() {
			std::cout << "Deallocating memory..." << std::endl;
			
		}
};

int main() {
	std::cout << "Hello, World!" << std::endl;

	Heap heap;
	heap.alloc(10);
	heap.dealloc();

	return 0;
}
