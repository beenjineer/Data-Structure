//Unit 3: Hash Table
//Writer: Kelly Khanh Ho
//IDE: Visual Studio
#pragma once
#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <iostream>
#include <string>
#include "Product.h"


using namespace std;

class LinkedList
{
private:
	struct ListNode
	{
		Product item;
		//string key = item.getASIN();
		ListNode *next;
	};
	ListNode *head;
	int count;
public:
	LinkedList();  // Constructor
	~LinkedList();   // Destructor

					  // Linked list operations
	int getCount() const { return count; }
	void insertNode(const Product &);
	bool deleteNode(const Product &);
	//void displayList(); 
	Product* searchList(string target);
	bool isEmpty();
	Product getItem() const { return head->item; }
	void deleteList();

};
//Constructor
LinkedList::LinkedList()
{
	head = nullptr;
	count = 0;
}
//Destructor
LinkedList::~LinkedList()
{
	ListNode *pWalk = head;
	while (pWalk != nullptr)
	{
		pWalk = pWalk->next;
		delete head;
		head = pWalk;
	}
	count = 0;
}
//insert in sorted order
void LinkedList::insertNode(const Product &newobj)
{
	ListNode *newNode = new ListNode;
	ListNode *pWalk;
	newNode->item = newobj;
	newNode->next = nullptr;
	if (!head)
	{
		head = newNode;
	}
	else
	{
		pWalk = head;
		while (pWalk->next)
			pWalk = pWalk->next;
		pWalk->next = newNode;
	}
	count++;
}
//delete node
bool LinkedList::deleteNode(const Product &obj)
{
	ListNode *pWalk;
	ListNode *prev = nullptr;
	if (!head)
		return false;
	if (head->item == obj)
	{
		pWalk = head->next;
		delete head;
		head = pWalk;
	}
	else
	{
		pWalk = head;
		while (pWalk != nullptr && !(pWalk->item == obj))
		{
			prev = pWalk;
			pWalk = pWalk->next;
		}
		if (pWalk)
		{
			prev->next = pWalk->next;
			delete pWalk;
		}
	}
	count--;
	return true;
}
//search changing return type from bool to ListNode*
//string LinkedList::searchList(string value)
Product* LinkedList::searchList(string target)
{
	if (head == nullptr)
		return nullptr;
	else
	{
		ListNode *pWalk = head;
		while (pWalk != nullptr)
		{
			if (pWalk->item.getASIN() == target)
				return &pWalk->item;
			pWalk = pWalk->next;
		}
	}
	return nullptr;
}
//check if empty
bool LinkedList::isEmpty()
{
	return(!head);
}
//Delete the entire a list.
//Call this when we do rehash.
void LinkedList::deleteList()
{
	ListNode *pWalk = head;
	while (pWalk != nullptr)
	{
		pWalk = pWalk->next;
		delete head;
		head = pWalk;
	}
	count = 0;
}
#endif