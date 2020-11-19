//Unit 3: Hash Table
//Writer: Kelly Khanh Ho
//IDE: Visual Studio
#pragma once
#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "LinkedList.h"
#include "Product.h"
#include <iostream>
#include <string>
using namespace std;

class HashTable
{
private:

	LinkedList **table;
	double loadFactor;
	int numOfCollisions;
	int capacity;
	int size;
public:
	//Constructor
	HashTable(int size1)
	{
		table = new LinkedList*[size1];
		for (int i = 0; i < size1; i++)
		{
			table[i] = nullptr;
		}
		loadFactor = 0;
		numOfCollisions = 0;
		size = size1;
		capacity = 0;
	}
	//Destructor
	~HashTable()
	{
		for (int i = 0; i < size; i++)
		{
			//LinkedList* list = table[i];
			//list->deleteList();
			//while (list != nullptr)
			//{
			//    LinkedList * prev = list;
			//    list = list->next;
			//    delete prev;
			//}
			delete table[i]; // TODO: delete linkedlist, set other values to 0
		}
		delete[] table;
	}

	//Good hash function.
	//Size = 53 => gives 4 collisions
	int hashingGood(string key, int size)
	{
		int sum = 0;
		//J6B1 = J + 3*6 + B*B + 7*1
		sum = key[3] + 3 * key[4] + key[5] * key[5] + 7 * key[6];
		return sum % size;
	}

	//Bad hash function
	//Size = 53 = > gives 7 collisions
	int hashingBad(string key, int size)
	{
		int sum = 0;
		//j6b1 = j *6 * b *1
		sum = key[3] * key[4] * key[5] * key[6];
		return sum % size;
	}

	//Insert an object Product into the hash table
	void insertTable(Product& obj)
	{
		//HashNode *newNode = new HashNode;
		//newNode->key = key;
		//newNode->next = nullptr;
		int index = hashingGood(obj.getASIN(), size);
		if (table[index] == nullptr)
		{
			// cout << "inside insert" << endl;
			table[index] = new LinkedList();
			table[index]->insertNode(obj);
			capacity++;
		}
		else
		{
			// cout << "inside collision" << endl;
			numOfCollisions++;
			//cout << "after " << endl;
			table[index]->insertNode(obj);
			//cout << "insert collision succeed" << endl;
		}
	}

	//Search a object Product in hash table.
	//Function recieves a string as a ASIN of 1 object.
	//Return pointer to an object so we can output it.
	Product* hashSearch(string key)
	{
		//cout << "inher";

		int index = hashingGood(key, size);
		if (table[index] == nullptr)
		{
			return nullptr;
		}
		else
		{
			//cout << "inher";
			//Product temp;
			//temp.setASIN(key);
			return table[index]->searchList(key);
		}
	}

	//Delete object Product in hash table.
	//It goes into the linked list and delete the object there.
	bool deleteHash(Product &obj)
	{
		int index = hashingGood(obj.getASIN(), size);
		if (table[index] == nullptr)
		{
			return false;
		}
		else
		{
			//Product temp;
			//temp.setASIN(key);
			capacity--;
			return table[index]->deleteNode(obj);
		}
	}

	//Statistics
	double getLoadFactor()
	{
		loadFactor = capacity*1.0 / size;
		return loadFactor;
	}
	int getNumOfCollisions()
	{
		return numOfCollisions;
	}

	//Check if product is valid
	bool isValid(Product &validProduct)
	{
		bool valid = true;

		if (validProduct.getASIN().length() != 10)
		{
			cout << "\n\tERROR: ASIN must be exactly 10 digits\n";
			valid = false;
		}
		if (validProduct.getPrice() < 0)
		{
			cout << "\n\tERROR: Product Price must be more than $0\n";
			valid = false;
		}
		if (validProduct.getCusReview() < 0 || validProduct.getCusReview() > 5)
		{
			cout << "\n\tERROR: Customer Review must be between 0 and 5\n";
			valid = false;
		}
		if (validProduct.getPrime() == 0 || validProduct.getPrime() != 1)
		{
			valid;
		}
		else if (validProduct.getPrime() == 1)
			valid;
		else
		{
			cout << "\n\tERROR: Prime must be Yes or No\n";
			valid = false;
		}
		return valid;
	}
};

#endif