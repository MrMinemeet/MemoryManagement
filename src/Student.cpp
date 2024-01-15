#include "Student.hpp"
#include "UsedBlock.hpp"

Student::Student() {
	id = 0;
	name = "";
	lect = nullptr;
}

void Student::add(Lecture* lecture) {
	UsedBlock* ub = heap.alloc("LectNode");
	LectNode* ln = new (ub->getDataPart()) LectNode(lecture);

	ln->next = lect;
	lect = ln;
}
