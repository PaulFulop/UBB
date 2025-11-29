#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	Node* mergeTwoLists(Node* l1, Node* l2);
	void destroyList(Node* head);
	Node *current, *sortedList;
	int currentFreq, currentLen;

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
	void jumpForward(int k);
};

