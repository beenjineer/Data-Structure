/**~*~*
   Stack template
*~**/
#ifndef STACK_ADT_H
#define STACK_ADT_H
#include <iostream>
#include "Product.h"	// Product object
using namespace std;

class Stack
{
private:
	// Structure for the stach nodes
	struct StackNode
	{
		Product value;          // Value in the node
		StackNode *next;  // Pointer to next node
	};

	StackNode *top;     // Pointer to the stack top
	int count;

public:
	//Constructor
	Stack() { top = NULL; count = 0; }

	// Destructor
	~Stack();

	// Stack operations
	bool push(Product);
	bool pop(Product &);
	bool isEmpty();
	int getCount();
	bool getTop(Product &);
};

/**~*~*
   Destructor
*~**/
Stack::~Stack()
{
	StackNode *currNode, *nextNode;

	// Position nodePtr at the top of the stack.
	currNode = top;

	// Traverse the list deleting each node.
	while (currNode) //while (currNode != NULL)
	{
		nextNode = currNode->next;
		delete currNode;
		currNode = nextNode;
	}
}

/**~*~*
  Member function push pushes the argument onto
  the stack.
*~**/
bool Stack::push(Product item)
{
	StackNode *newNode; // Pointer to a new node

	// Allocate a new node and store num there.
	newNode = new StackNode;
	if (!newNode)
		return false;
	newNode->value = item;

	// Update links and counter
	newNode->next = top;
	top = newNode;
	count++;

	return true;
}

/**~*~*
  Member function pop pops the value at the top
  of the stack off, and copies it into the variable
  passed as an argument.
*~**/
bool Stack::pop(Product &item)
{
	StackNode *temp; // Temporary pointer

	// empty stack
	if (count == 0)
		return false;

	// pop value off top of stack
	item = top->value;
	temp = top->next;
	delete top;
	top = temp;
	count--;

	return true;
}

/**~*~*
  Member function isEmpty returns true if the stack
  is empty, or false otherwise.
*~**/
bool Stack::isEmpty()
{
	return count == 0;
}

/**~*~*
  Member function getCount returns
  the number of elements in the stack
*~**/
int Stack::getCount()
{
	return count;
}

/**~*~*
  Member function getTop copies the value at the top
  of the stack into the variable passed as an argument.
*~**/
bool Stack::getTop(Product &item)
{
	if (top == NULL)
		return false;

	item = top->value;

	return true;
}

#endif