#include "Lecture.hpp"
#include "iostream"

Lecture::Lecture() {
	std::cout << &id << std::endl;
	id = 0;
	std::cout << &name << std::endl;
	name = "Hello there!";
	std::cout << &semester << std::endl;
	semester = 0;
}