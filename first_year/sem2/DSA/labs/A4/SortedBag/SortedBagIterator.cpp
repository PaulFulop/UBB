#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

// merging each of the m buckets (merging 2 buckets has total complexity theta(n)) 
//BC: theta(n) -> only one bucket is non-empty
//WC: theta(n * m) -> each bucket has n/m elements
//TC: theta(n * m)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b), current(nullptr), currentFreq(1), currentLen(0)
{
	sortedList = nullptr;
	for (int i = 0; i < bag.m; ++i) {
		if (bag.bag[i]) {
			Node* auxSortedList = sortedList;
			sortedList = mergeTwoLists(sortedList, bag.bag[i]);		
			if (auxSortedList)
				destroyList(auxSortedList);
		}
	}

	first();
}

//BC: theta(1) -> both buckets are empty 
//WC: theta(n1 + n2) – both lists have elements
//TC: O(n1 + n2)
Node* SortedBagIterator::mergeTwoLists(Node* l1, Node* l2)
{
	Node *list = nullptr, *tail = nullptr;

	while (l1 && l2) {
		Node* newNode = new Node;

		newNode->next = nullptr;
		if (bag.r(l1->data.first, l2->data.first)) {
			newNode->data = l1->data;

			if (!list) {
				newNode->prev = nullptr;
				list = newNode;
				tail = newNode;
			}
			else {
				newNode->prev = tail;
				tail->next = newNode;
				tail = newNode;
			}

			l1 = l1->next;
		}
		else {
			newNode->data = l2->data;

			if (!list) {
				newNode->prev = nullptr;
				list = newNode;
				tail = newNode;
			}
			else {
				newNode->prev = tail;
				tail->next = newNode;
				tail = newNode;
			}

			l2 = l2->next;
		}
	}

	while (l1) {
		Node* newNode = new Node;
		newNode->data = l1->data;
		newNode->next = nullptr;

		if (!list) {
			newNode->prev = nullptr;
			list = newNode;
			tail = newNode;
		}
		else {
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
		}

		l1 = l1->next;
	}

	while (l2) {
		Node* newNode = new Node;
		newNode->data = l2->data;
		newNode->next = nullptr;

		if (!list) {
			newNode->prev = nullptr;
			list = newNode;
			tail = newNode;
		}
		else {
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
		}

		l2 = l2->next;
	}

	return list;
}

//BC: Θ(1) - list is empty
//WC: Θ(k) - list has k elements
//TC: O(k)
void SortedBagIterator::destroyList(Node* head) {
	while (head) {
		Node* current = head;
		head = head->next;
		delete current;
	}
}

//BC: theta(1)
//WC: theta(1)
//TC: theta(1)
TComp SortedBagIterator::getCurrent() {
	if (!valid())
		throw std::exception("Invalid!\n");

	if (current)
		return current->data.first;
	return NULL_TCOMP;
}

//BC: theta(1)
//WC: theta(1)
//TC: theta(1)
bool SortedBagIterator::valid() {
	return current != nullptr;
}

//BC: theta(1)
//WC: theta(1)
//TC: theta(1)
void SortedBagIterator::next() {
	if (!valid())
		throw std::exception("Invalid!\n");

	if (currentFreq == current->data.second) {
		current = current->next;
		currentFreq = 1;
	}
	else
		++currentFreq;

	++currentLen;
}

//BC: theta(1)
//WC: theta(1)
//TC: theta(1)
void SortedBagIterator::first() {
	current = sortedList;
	currentFreq = 1;
	currentLen = 0;
}

//BC: theta(1)
//WC: theta(k)
//TC: O(k)
void SortedBagIterator::jumpForward(int k)
{
	if (k <= 0)
		throw std::exception("Invalid number of steps!\n");

	if (currentLen + k > bag.n) { // iterator becomes invalid if I try jumping out of range
		current = nullptr;
		return;
	}

	while (k--) {
		next();
	}
}
