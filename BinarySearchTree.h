// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Younseo Ryu

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include <iomanip>
#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
	BinaryNode<ItemType>* _insert2(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode, int compare(ItemType &, ItemType &));

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr,  ItemType target, bool & success);
	BinaryNode<ItemType>* _remove2(BinaryNode<ItemType>* nodePtr,  ItemType target, bool & success, int compare(ItemType &, ItemType &));

	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);

	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;
	BinaryNode<ItemType>* findNode2(BinaryNode<ItemType>* treePtr, ItemType & target, int compare(ItemType &, ItemType &));

	// search for the most left node
	BinaryNode<ItemType>* findMostLeft(BinaryNode<ItemType>* treePtr) const;
	// search for the most right node
	BinaryNode<ItemType>* findMostRight(BinaryNode<ItemType>* treePtr) const;
	// print a tree in an indented format
	void _print(BinaryNode<ItemType>* p, int indent = 0, int level = 1);
	void _print2(BinaryNode<ItemType>* p, int indent = 0, int level = 1);
	void _print3(BinaryNode<ItemType>* p, int indent = 0, int level = 1);

public:
	// insert a node at the correct location
	bool insert(const ItemType & newEntry);
	bool insert2(const ItemType & newEntry, int compare(ItemType &, ItemType &));
	// remove a node if found
	bool remove(const ItemType & anEntry);
	bool remove2( ItemType & anEntry, int compare(ItemType &, ItemType &));
	// find a target node
	bool getEntry(const ItemType & target, ItemType & returnedItem) const;
	bool getEntry2(ItemType & target, ItemType & returnedItem, int compare(ItemType &, ItemType &));
	// get the most left node
	bool getMostLeft(ItemType & returnedItem) const;
	// get the most right node
	bool getMostRight(ItemType & returnedItem) const;
	// call the _print() function 
	void print();
	void print2();
	void print3();
};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr);
	return true;
}
template<class ItemType>
bool BinarySearchTree<ItemType>::insert2(const ItemType & newEntry, int compare(ItemType &, ItemType &))
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert2(this->rootPtr, newNodePtr, compare);
	return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
	return isSuccessful;
}
template<class ItemType>
bool BinarySearchTree<ItemType>::remove2( ItemType & target, int compare(ItemType &, ItemType &))
{
	bool isSuccessful = false;
	this->rootPtr = _remove2(this->rootPtr, target, isSuccessful, compare);
	return isSuccessful;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
	BinaryNode<ItemType>* entry = findNode(this->rootPtr, anEntry);
	if (entry)
	{
		returnedItem = findNode(this->rootPtr, anEntry)->getItem();
		return true;
	}
	return false;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry2(ItemType& anEntry, ItemType & returnedItem, int compare(ItemType &, ItemType &))
{
	BinaryNode<ItemType>* entry = findNode2(this->rootPtr, anEntry, compare);
	if (entry)
	{
		BinaryNode<ItemType>* ptr1 = findNode2(this->rootPtr, anEntry, compare);
		BinaryNode<ItemType>* ptr2 = findNode2(this->rootPtr, anEntry, compare)->getRightPtr();
		ItemType p1 = ptr1->getItem();
		ItemType p2 = ptr2->getItem();
		returnedItem = findNode2(this->rootPtr, anEntry, compare)->getItem();
		int run = 1;
		while (compare(p1, p2) == 0) {
			findNode2(this->rootPtr, anEntry, compare)->getRightPtr()->getItem().printInfo();
			ptr1 = ptr1->getRightPtr();
			ptr2 = ptr2->getRightPtr();
			p1 = ptr1->getItem();
			p2 = ptr2->getItem();
		}

		return true;
	}
	return false;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::getMostLeft(ItemType & returnedItem) const
{
	BinaryNode<ItemType>* entry = findMostLeft(this->rootPtr);
	if (entry)
	{
		returnedItem = findMostLeft(this->rootPtr)->getItem();
		return true;
	}
	return false;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::getMostRight(ItemType & returnedItem) const
{
	BinaryNode<ItemType>* entry = findMostRight(this->rootPtr);
	if (entry)
	{
		returnedItem = findMostRight(this->rootPtr)->getItem();
		return true;
	}
	return false;
}

template<class ItemType>
void BinarySearchTree<ItemType>::print()
{
	int indent = 0;
	int level = 1;
	_print(this->rootPtr, indent, level);
}
template<class ItemType>
void BinarySearchTree<ItemType>::print2()
{
	int indent = 0;
	int level = 1;
	_print2(this->rootPtr, indent, level);
}
template<class ItemType>
void BinarySearchTree<ItemType>::print3()
{
	int indent = 0;
	int level = 1;
	_print2(this->rootPtr, indent, level);
}
//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNodePtr)
{
	BinaryNode<ItemType>* pWalk = nodePtr;
	BinaryNode<ItemType>* parent = newNodePtr;

	if (nodePtr == NULL) {
		nodePtr = newNodePtr;
	}
	else {
		while (pWalk != 0) {
			parent = pWalk;
			if (newNodePtr->getItem() < pWalk->getItem()) {
				pWalk = pWalk->getLeftPtr();
			}
			else {
				pWalk = pWalk->getRightPtr();
			}
		}
		if (newNodePtr->getItem() < parent->getItem()) {
			parent->setLeftPtr(newNodePtr);
		}
		else {
			parent->setRightPtr(newNodePtr);
		}
	}
	return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert2(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNodePtr, int compare(ItemType &, ItemType &))
{
	BinaryNode<ItemType>* pWalk = nodePtr;
	BinaryNode<ItemType>* parent = newNodePtr;

	if (nodePtr == NULL) {
		nodePtr = newNodePtr;
	}
	else {
		while (pWalk != 0) {
			parent = pWalk;
			ItemType p1 = newNodePtr->getItem();
			ItemType p2 = pWalk->getItem();
			
			if (compare(p1, p2) < 0) {// newNodePtr->getItem() < pWalk->getItem()) {
				pWalk = pWalk->getLeftPtr();
			}
			else {
				pWalk = pWalk->getRightPtr();
			}
		}
		ItemType p3 = newNodePtr->getItem();
		ItemType p4 = parent->getItem();
		if (compare(p3, p4) < 0) { // newNodePtr->getItem() < parent->getItem()) {
			parent->setLeftPtr(newNodePtr);
		}
		else {
			parent->setRightPtr(newNodePtr);
		}
	}
	return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
	const ItemType target,
	bool & success)

{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem() > target)
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem() < target)
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}
	return nodePtr;
}
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove2(BinaryNode<ItemType>* nodePtr,
	 ItemType target,
	bool & success, int compare(ItemType &, ItemType &))

{
	ItemType p1 = nodePtr->getItem();

	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (compare(p1,target)>0)
		nodePtr->setLeftPtr(_remove2(nodePtr->getLeftPtr(), target, success, compare));
	else if (compare(p1,target)<0)
		nodePtr->setRightPtr(_remove2(nodePtr->getRightPtr(), target, success, compare));
	else
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}
	return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
	ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
	const ItemType & target) const
{
	if (nodePtr == NULL)
	{
		return 0;
	}
	else if (target < nodePtr->getItem())
	{
		return findNode(nodePtr->getLeftPtr(), target);
	}
	else if (target > nodePtr->getItem())
	{
		return findNode(nodePtr->getRightPtr(), target);
	}
	else
		return nodePtr;
}template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode2(BinaryNode<ItemType>* nodePtr,
	ItemType & target, int compare(ItemType &, ItemType &)) 
{

	ItemType p1 = nodePtr->getItem();

	if (nodePtr == NULL)
	{
		return 0;
	}
	else if (compare(target, p1) <0)
	{
		return findNode2(nodePtr->getLeftPtr(), target, compare);
	}
	else if (compare(target, p1) > 0)
	{
		return findNode2(nodePtr->getRightPtr(), target, compare);
	}
	else
		return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findMostLeft(BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr == NULL)
	{
		return 0;
	}
	else if (nodePtr->getLeftPtr() != NULL)
	{
		return findMostLeft(nodePtr->getLeftPtr());
	}
	else
		return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findMostRight(BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr == NULL)
	{
		return 0;
	}
	else if (nodePtr->getRightPtr() != NULL)
	{
		return findMostRight(nodePtr->getRightPtr());
	}
	else
		return nodePtr;
}

template<class ItemType>
void BinarySearchTree<ItemType>::_print(BinaryNode<ItemType>* nodePtr, int indent, int level)
{
	if (nodePtr != NULL)
	{
		if (nodePtr->getLeftPtr())
		{
			_print(nodePtr->getLeftPtr(), indent + 0, level + 1);
		}
		if (indent) //indent != 0
		{
			cout << setw(indent) << " ";
		}
		cout << "\t" << nodePtr->getItem().getASIN();
		cout << endl;

		if (nodePtr->getRightPtr())
		{
			_print(nodePtr->getRightPtr(), indent + 0, level + 1);
		}
	}
}

template<class ItemType>
void BinarySearchTree<ItemType>::_print2(BinaryNode<ItemType>* nodePtr, int indent, int level)
{
	if (nodePtr != NULL)
	{
		if (nodePtr->getLeftPtr())
		{
			_print2(nodePtr->getLeftPtr(), indent + 0, level + 1);
		}
		if (indent) //indent != 0
		{
			cout << setw(indent) << " ";
		}
		cout << "\t" << nodePtr->getItem().getManufact();
		cout << endl;

		if (nodePtr->getRightPtr())
		{
			_print2(nodePtr->getRightPtr(), indent + 0, level + 1);
		}
	}
}

template<class ItemType>
void BinarySearchTree<ItemType>::_print3(BinaryNode<ItemType>* nodePtr, int indent, int level)
{
	if (nodePtr != NULL)
	{
		if (nodePtr->getLeftPtr())
		{
			_print(nodePtr->getLeftPtr(), indent + 13, level + 1);
		}
		if (indent) //indent != 0
		{
			cout << setw(indent) << " ";
		}
		cout << nodePtr->getItem().getASIN();
		cout << endl;

		if (nodePtr->getRightPtr())
		{
			_print(nodePtr->getRightPtr(), indent + 13, level + 1);
		}
	}
}
#endif