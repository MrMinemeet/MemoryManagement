#include "Declarations.hpp"
#include "Heap.hpp"
#include "SlideBlock.hpp"
#include "TypeDescriptor.hpp"
#include "Lecture.hpp"
#include "LectNode.hpp"
#include "Student.hpp"
#include "StudNode.hpp"
#include "StudentList.hpp"
#include <iostream>
#include <string>

Heap heap;

int main() {
#if DEBUG
	std::cout << "DEBUG-mode enabled!" << std::endl;
#endif
	std::cout << "Hello, GC user!" << std::endl;
	//heap.dump();
	/*
	// TD based on "Garbage Collection" slide-set page 22
	// Create TypeDescriptor for a class (Block x; Block y; int getDataPart; Block z;)
	std::cout << std::endl;
	std::cout << "Creating TypeDescriptor for class 'SlideBlock'…" << std::endl;
	TypeDescriptor td = TypeDescriptor(32,
									   new int[3]{0, 8, 24}, // For offset explanation see SlideBlock.hpp
									   3);
	std::cout << td.ToString() << std::endl;
	if (heap.registerType("SlideBlock", td)) {
		std::cout << "Successfully registered rawTypeDescriptor!" << std::endl;
	} else {
		std::cout << "Failed to register rawTypeDescriptor!" << std::endl;
		return 1;
	}
	*/
	TypeDescriptor lecture_td = TypeDescriptor(48,
									   new int[3]{0,8,40},
									   3);
	heap.registerType("Lecture", lecture_td);

	TypeDescriptor lectNode_td = TypeDescriptor(16,
												new int[2]{0,8},
												2);
	heap.registerType("LectNode", lectNode_td);

	TypeDescriptor student_td = TypeDescriptor(48,
											   new int[3]{0,8, 40},
											   3);
	heap.registerType("Student", student_td);

	TypeDescriptor studNode_td = TypeDescriptor(16,
											   new int[2]{0,8},
											   2);
	heap.registerType("StudNode", studNode_td);

	TypeDescriptor studentList_td = TypeDescriptor(16,
											   new int[1]{0},
											   1);
	heap.registerType("StudentList", studentList_td);


	UsedBlock* ub = heap.alloc("Lecture");
	Lecture* l0 = new (ub->getDataPart()) Lecture();
	ub = heap.alloc("Lecture");
	Lecture* l1 = new (ub->getDataPart()) Lecture();
	ub = heap.alloc("Lecture");
	Lecture* l2 = new (ub->getDataPart()) Lecture();

	ub = heap.alloc("Student");
	Student* s0 = new (ub->getDataPart()) Student();
	ub = heap.alloc("Student");
	Student* s1 = new (ub->getDataPart()) Student();
	ub = heap.alloc("Student");
	Student* s2 = new (ub->getDataPart()) Student();

	s0->add(l2);
	s0->add(l1);
	s0->add(l0);

	s1->add(l2);
	s1->add(l0);

	s2->add(l2);
	s2->add(l1);


	ub = heap.alloc("StudentList");
	StudentList* studentList = new (ub->getDataPart()) StudentList();

	studentList->add(s0);
	studentList->add(s1);
	studentList->add(s2);

	heap.dump();

	/*
	std::cout << std::endl;
	std::cout << "Allocating 'SlideBlock'…" << std::endl;
	UsedBlock* b1 = heap.alloc("SlideBlock");
	// I just use "new" here to trigger the constructor
	SlideBlock* sb1 = new (b1->getDataPart()) SlideBlock();


	std::cout << std::endl;
	std::cout << "Allocating 'SlideBlock' again…" << std::endl;
	UsedBlock* b2 = heap.alloc("SlideBlock");
	SlideBlock* sb2 = new (b2->getDataPart()) SlideBlock();
	sb1->x = (Block*) sb2;

	// Test dump
	std::cout << std::endl;
	//heap.dump();

	// Test garbage collection without stuff to collect
	void* rootPointers[] = {nullptr, nullptr};
	rootPointers[0] = b1;
	rootPointers[1] = nullptr;
	std::cout << std::endl;
	std::cout << "Testing garbage collection when nothing is to collect…" << std::endl;
	//heap.gc(rootPointers);
	heap.dump();

	// Test garbage collection with stuff to collect
	std::cout << "Removing pointer in SB1 pointing to SB2" << std::endl;
	sb1->x = nullptr;
	heap.dump();
	std::cout << std::endl;
	std::cout << "Testing garbage collection when something is to collect…" << std::endl;
	heap.gc(rootPointers);
	heap.dump();



	/*
	Block* a = heap.alloc(512);
	Block* b = heap.alloc(400);
	Block* c = heap.alloc(8 KiB);
	//Block* d = heap.alloc(8 KiB);

	std::cout << heap.ToString() << std::endl;
	heap.dealloc(a);

	int* array = new int[2];
	array[0] = 1;
	array[1] = 2;

	std::string rawTypeDescriptor = "int";
	TypeDescriptor descriptor(8, array, 2);
	std::cout << descriptor.ToString() << std::endl;

	heap.registerType(rawTypeDescriptor, descriptor);

	std::cout << heap.ToString() << std::endl;

	*/
	return 0;
}
