#include "LectNode.hpp"

LectNode::LectNode() {
	next = nullptr;
	lect = nullptr;
}

LectNode::LectNode(Lecture* lect) {
	this->next = nullptr;
	this->lect = lect;
}

LectNode::LectNode(LectNode* next, Lecture* lect) {
	this->next = next;
	this->lect = lect;
}
