#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

// BC: theta(1)
// WC: theta(1)
// TC: theta(1)
SortedMap::SortedMap(Relation r) : rel (r), n (0), list (nullptr) {}

// BC: theta(1) -> we want to add a new value that has the key equivalent to the key of the root
// WC: theta(n) -> in the general case when the BST is unbalanced, meaning every node could have only 1 child;
                    // we add an elemen with the largest key
// TC: O(n)
TValue SortedMap::add(TKey k, TValue v) {
	TElem newElem = TElem(k, v);
	if (!list) { // if the list is empty we add the root
		list = new Node{ newElem, nullptr, nullptr };
		++n;
		return NULL_TVALUE;
	}

	Node* currentNode = list;
	while (currentNode && currentNode->data.first != k) {
		if (rel(k, currentNode->data.first)) {
			if (!currentNode->leftChild) {
				currentNode->leftChild = new Node{ newElem, nullptr, nullptr };
				++n;
				return NULL_TVALUE;
			}

			currentNode = currentNode->leftChild;
		}
		else {
			if (!currentNode->rightChild) {
				currentNode->rightChild = new Node{ newElem, nullptr, nullptr };
				++n;
				return NULL_TVALUE;
			}

			currentNode = currentNode->rightChild;
		}
	}

	if (currentNode) {
		TValue oldValue = currentNode->data.second;
		currentNode->data.second = v;
		return oldValue;
	}

	return NULL_TVALUE;
}

// BC: theta(1) -> we are looking for the root
// WC: theta(n) -> in the general case when the BST is unbalanced, meaning every node could have only 1 child
// TC: O(n)
TValue SortedMap::search(TKey k) const {
	if (!list) return NULL_TVALUE; // BST is empty

	Node* currentNode = list;
	while (currentNode && currentNode->data.first != k) {
		if (rel(k, currentNode->data.first))
			currentNode = currentNode->leftChild;
		else
			currentNode = currentNode->rightChild;
	}

	if (currentNode) return currentNode->data.second;
	return NULL_TVALUE;
}

// BC: theta(1) -> we want to remove the root and it only has one branch
// WC: theta(n) -> in the general case when the BST is unbalanced, meaning every node could have only 1 child
// TC: O(n)
TValue SortedMap::remove(TKey k) {
    Node* currentNode = list;
    Node* parentNode = nullptr;

    // Search for node with key k
    while (currentNode && currentNode->data.first != k) {
        parentNode = currentNode;
        if (rel(k, currentNode->data.first))
            currentNode = currentNode->leftChild;
        else
            currentNode = currentNode->rightChild;
    }

    if (!currentNode)
        return NULL_TVALUE;  // Key not found

    TValue removedValue = currentNode->data.second;

    // Case 1: Leaf node
    if (!currentNode->leftChild && !currentNode->rightChild) {
        if (!parentNode)
            list = nullptr; // removing the root
        else if (parentNode->leftChild == currentNode)
            parentNode->leftChild = nullptr;
        else
            parentNode->rightChild = nullptr;

        delete currentNode;
    }

    // Case 2: One child (right)
    else if (!currentNode->leftChild) {
        Node* child = currentNode->rightChild;
        if (!parentNode)
            list = child;
        else if (parentNode->leftChild == currentNode)
            parentNode->leftChild = child;
        else
            parentNode->rightChild = child;

        delete currentNode;
    }

    // Case 3: One child (left)
    else if (!currentNode->rightChild) {
        Node* child = currentNode->leftChild;
        if (!parentNode)
            list = child;
        else if (parentNode->leftChild == currentNode)
            parentNode->leftChild = child;
        else
            parentNode->rightChild = child;

        delete currentNode;
    }

    // Case 4: Two children
    else {
        Node* predParent = currentNode;
        Node* pred = currentNode->leftChild;
        while (pred->rightChild) {
            predParent = pred;
            pred = pred->rightChild;
        }

        // Copy predecessor's data into currentNode
        currentNode->data = pred->data;

        // Remove predecessor node
        if (predParent == currentNode)
            predParent->leftChild = pred->leftChild;
        else
            predParent->rightChild = pred->leftChild;

        delete pred;
    }

    --n;
    return removedValue;
}

// BC: theta(1)
// WC: theta(1)
// TC: theta(1)
int SortedMap::size() const {
	return n;
}

// BC: theta(1)
// WC: theta(1)
// TC: theta(1)
bool SortedMap::isEmpty() const {
	return n == 0;
}

// BC: theta(1)
// WC: theta(1)
// TC: theta(1)
SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

// BC: theta(n) -> considering we always remove the root
// WC: theta(n^2) -> WC for the remove function is theta(n)
// TC: O(n^2)
SortedMap::~SortedMap() {
	while (n) {
		remove(list->data.first);
	}
}

// BC: theta(n) -> must visit all the nodes 
// WC: theta(n)
// TC: theta(n)
int SortedMap::getValueRange() const {
    if (list == nullptr) return -1;

    int k = 0;
    Node** stack = new Node*[n];
    stack[k++] = list;
    int minValue = stack[0]->data.second, maxValue = stack[0]->data.second;

    while (k) {
        Node* node = stack[--k];
        minValue = min(node->data.second, minValue);
        maxValue = max(node->data.second, maxValue);

        if (node->leftChild)
            stack[k++] = node->leftChild;

        if (node->rightChild)
            stack[k++] = node->rightChild;
    }

    delete[] stack;
    return maxValue - minValue;
}
