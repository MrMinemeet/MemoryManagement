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

void Student::remove(Lecture* lecture) {
	LectNode* prev = nullptr;
	LectNode* cur = lect;

	while (cur != nullptr && cur->lect != lecture) {
		prev = cur;
		cur = cur->next;
	}

	if (cur == nullptr) {
		// Lecture not in list
		return;
	}

	// Lecture in list, remove
	if (prev == nullptr) {
		// Lecture was 1st element
		lect = cur->next;
	} else {
		// Lecture was somewhere else
		prev->next = cur->next;
	}
}
