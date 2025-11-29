#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

// BC : theta(1)
// WC : theta(1)
// TC : theta(1)
MultiMap::MultiMap() {
	this->capacity = INITIAL_CAPACITY;
	this->node = new Node[this->capacity];
	this->head = -1;
	this->freeHead = 0;
	this->mpSize = 0;

	for (int i = 0; i < this->capacity - 1; ++i) {
		this->node[i].next = i + 1;
		this->node[i].data = NULL_TELEM;
	}

	this->node[this->capacity - 1].next = -1;
}

// BC : theta(1) -> we dont need to resize the array
// WC : theta(n) -> we need to resize the array (n = capacity * 2)
// TC : O(n)
void MultiMap::add(TKey c, TValue v) {
	if (this->freeHead == -1) {
		int newCapacity = this->capacity * 2;
		Node* newNodeArray = new Node[newCapacity];

		for (int i = 0; i < this->capacity; ++i)
			newNodeArray[i] = this->node[i];

		for (int i = this->capacity; i < newCapacity - 1; ++i) {
			newNodeArray[i].next = i + 1;
			newNodeArray[i].data = NULL_TELEM;
		}

		newNodeArray[newCapacity - 1].next = -1;
		this->freeHead = this->capacity;

		delete[] this->node;
		this->node = newNodeArray;
		this->capacity = newCapacity;
	}

	TElem newElem = pair<TKey, TValue>(c, v);

	int auxHead = freeHead;
	freeHead = node[freeHead].next;

	node[auxHead].data = newElem;
	node[auxHead].next = head;
	head = auxHead;

	++this->mpSize;
}


// BC : theta(1) -> if the element that we're searching for is the first in the list
// WC : theta(n) -> if the element that we're searching for is the last in the list or we didn't find that element (n is the length of the list)
// TC : O(n)
bool MultiMap::remove(TKey c, TValue v) {
	TElem elem = pair<TKey, TValue>(c, v);
	if (this->isEmpty())
		return false;

	if (this->node[head].data == elem)
	{
		int auxHead = this->head;
		this->head = this->node[head].next;
		this->node[auxHead].next = freeHead;
		this->node[auxHead].data = NULL_TELEM;
		this->freeHead = auxHead;
		--this->mpSize;

		return true;
	}

	int auxHead = this->head;
	while (this->node[auxHead].next != -1 && this->node[this->node[auxHead].next].data != elem)
		auxHead = this->node[auxHead].next;

	if (this->node[auxHead].next == -1)
		return false;

	if (this->node[this->node[auxHead].next].next == -1) {
		this->node[this->node[auxHead].next].data = NULL_TELEM;
		this->node[this->node[auxHead].next].next = freeHead;
		this->freeHead = this->node[auxHead].next;
		this->node[auxHead].next = -1;
		--this->mpSize;

		return true;
	}

	int currNodePos = this->node[auxHead].next;
	this->node[this->node[auxHead].next].data = NULL_TELEM;
	this->node[auxHead].next = this->node[this->node[auxHead].next].next;
	this->node[currNodePos].next = freeHead;
	freeHead = currNodePos;
	--this->mpSize;
	
	return true;
}

// BC : theta(n)
// WC : theta(n)
// TC : theta(n)
vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> assocKeyValues = vector<TValue>();

	int auxHead = this->head;
	while (auxHead != -1) {

		if (this->node[auxHead].data.first == c)
			assocKeyValues.push_back(this->node[auxHead].data.second);

		auxHead = this->node[auxHead].next;
	}

	return assocKeyValues;
}

// BC : theta(n^2)
// WC : theta(n^2)
// TC : theta(n^2)
//going through the whole map, and for each element check how many times it's value appears by iterating through it again
TValue MultiMap::mostFrequent()
{
	if (this->isEmpty())
		return NULL_TVALUE;

	int auxHead = this->head, maxFreq = 0, bestTvalue = 0;
	while (auxHead != -1) {

		int auxHead1 = this->head;
		int currFreq = 0, currTvalue = this->node[auxHead].data.second;

		while (auxHead1 != -1) {
			if (this->node[auxHead1].data.second == currTvalue)
				++currFreq;
			auxHead1 = this->node[auxHead1].next;
		}

		if (currFreq > maxFreq) {
			maxFreq = currFreq;
			bestTvalue = currTvalue;
		}

		auxHead = this->node[auxHead].next;
	}

	return bestTvalue;
}

// BC : theta(1)
// WC : theta(1)
// TC : theta(1)
int MultiMap::size() const {
	return this->mpSize;
}

// BC : theta(1)
// WC : theta(1)
// TC : theta(1)
bool MultiMap::isEmpty() const {
	return !this->mpSize;
}

// BC : theta(1)
// WC : theta(1)
// TC : theta(1)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

// BC : theta(1)
// WC : theta(1)
// TC : theta(1)
MultiMap::~MultiMap() {
	delete[] this->node;
}

