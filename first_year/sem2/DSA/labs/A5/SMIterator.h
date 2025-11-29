#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar);
	void InOrderTraversal(Node* list, int& k);

	int currentPosition;
	TElem* elems;

public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
	~SMIterator();
};

