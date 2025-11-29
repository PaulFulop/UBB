#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <stdexcept>

FixedCapBiMap::FixedCapBiMap(int capacity) {
	if (capacity <= 0)
		throw std::exception("Capacity can't be negative!");
	this->capacity = capacity;
	this->map_size = 0;
	this->elems = new TElem[capacity];
}

FixedCapBiMap::~FixedCapBiMap() {
	delete[] elems;
}

bool FixedCapBiMap::add(TKey c, TValue v){
	if (this->capacity == this->map_size)
		throw std::exception("Full capacity.");

	int cnt = 0;
 
	for (int i = 0; i < this->map_size; ++i)
		if (this->elems[i].first == c)
		{
			++cnt;
			if (cnt == 2)
				return false;
		}

	this->elems[this->map_size].first = c;
	this->elems[this->map_size].second = v;
	++this->map_size;
	return true;
}

ValuePair FixedCapBiMap::search(TKey c) const{
	ValuePair key = { NULL_TVALUE, NULL_TVALUE };

	for (int i = 0; i < this->map_size; ++i)
		if (this->elems[i].first == c)
		{
			if (key.first == NULL_TVALUE)
				key.first = this->elems[i].second;
			else
				if (key.second == NULL_TVALUE)
					key.second = this->elems[i].second;
		}

	return key;
}

bool FixedCapBiMap::remove(TKey c, TValue v){
	if (FixedCapBiMap::search(c).first == NULL_TVALUE)
		return false;

	int pos = -1;
	for (int i = 0; i < this->map_size; ++i)
		if (this->elems[i].first == c && this->elems[i].second == v)
		{
			pos = i;
			break;
		}

	if (pos == -1)
		return false;
	
	for (int i = pos; i < this->map_size - 1; ++i)
	{
		this->elems[i].first = this->elems[i + 1].first;
		this->elems[i].second = this->elems[i + 1].second;
	}
	
	--this->map_size;
	return true;
}


int FixedCapBiMap::size() const {
	return this->map_size;
}

bool FixedCapBiMap::isEmpty() const{
	return this->map_size == 0;
}

bool FixedCapBiMap::isFull() const {
	return this->map_size == this->capacity;
}

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}



