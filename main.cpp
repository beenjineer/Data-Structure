//Unit 1: Main test driver with menu and other related functions
//Writer: Seung Yoon Han
//IDE: Visual Studio

#include "Product.h"			// Product object
#include "LinkedList.h"			// LinkedList ADT
#include "HashTable.h"			// HashTable ADT
#include "Stack.h"				// Stack ADT
#include "BinarySearchTree.h"	// BinarySearchTree
#include "SearchManager.h"		// Search Manager
#include "InDelManager.h"		// Insert and Delete Manager
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Constants for the menu choices
const char ADD_CHOICE = 'A',
DELETE_CHOICE = 'D',
UNDO_CHOICE = 'U',
SEARCH_CHOICE = 'S',
PRINT_CHOICE = 'P',
STATISTICS_CHOICE = 'T',
MENU_CHOICE = 'M',
SAVE_CHOICE = 'V',
QUIT_CHOICE = 'Q';

void menu();
void readProducts(string filename, HashTable &table, BinarySearchTree<Product> *tree1, BinarySearchTree<Product> *tree2);
void display(Product &p);
void addNewProduct(HashTable &table, BinarySearchTree<Product> *tree1, BinarySearchTree<Product> *tree2);
void deleteProduct(Stack &s, HashTable &table, BinarySearchTree<Product> *tree1, BinarySearchTree<Product> *tree2);
void undoDelete(HashTable &table, Stack &s);
void showStatistics(HashTable &table);

int main()
{
	char inputFileName[] = "products.txt";
	char choice;
	bool run = true;
	const int SIZE = 53;

	HashTable table(SIZE);
	BinarySearchTree<Product>* tree1 = new BinarySearchTree<Product>();
	BinarySearchTree<Product>* tree2 = new BinarySearchTree<Product>();
	Stack s;

	readProducts(inputFileName, table, tree1, tree2);

	menu();
	while (run)
	{
		cout << "Choose from the menu: ";
		cin >> choice;
		choice = toupper(choice);

		switch (choice)
		{
		case ADD_CHOICE:
			addNewProduct(table, tree1, tree2);
			break;

		case DELETE_CHOICE:
			deleteProduct(s, table, tree1, tree2);
			break;

		case UNDO_CHOICE:
			undoDelete(table, s);
			break;

		case SEARCH_CHOICE:
			searchManager(tree1, tree2);
			break;

		case PRINT_CHOICE:
			showList(table, tree1, tree2);
			break;

		case STATISTICS_CHOICE:
			showStatistics(table);
			break;

		case MENU_CHOICE:
			cout << endl;
			menu();
			break;

		case QUIT_CHOICE:
			cout << "\n________________________________________"
				<< "\n\t   PROGRAM SHUT DOWN"
				<< "\n________________________________________\n\n";
			run = false;
			break;

		default:
			cout << "\n\tWRONG INPUT. Please try again.\n\n";
			cin.ignore();
			break;
		}
	}

	// rewrite the list into text file (output)

	// table->clear(); // delete everything

	system("pause");
	return 0;
}

void menu()
{
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		<< "\t\tA - Add new item\n"
		<< "\t\tD - Delete existing item\n"
		<< "\t\tU - Undo delete\n"
		<< "\t\tS - Search list\n"
		<< "\t\tP - Print list\n"
		<< "\t\tT - Show statistics\n"
		<< "\t\tM - Show menu\n"
		<< "\t\tV - Save to file\n"
		<< "\t\tQ - Quit\n"
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void readProducts(string filename, HashTable &table, BinarySearchTree<Product> *tree1, BinarySearchTree<Product> *tree2)
{
	ifstream inputFile;

	inputFile.open(filename);

	if (inputFile.fail())
	{
		cout << "\nThe file failed to open! Please try again...\n";
		exit(EXIT_FAILURE);
	}

	// use local variables to store data from file and use them
	// to build a Product object
	Product obj;		// Local Product object
	string asin;		// Amazon Standard Identification Number
	string manufact;	// Manufacturer
	double cusReview;	// Customer Review
	double shipWeight;	// Shipping Weight
	double price;		// Price
	bool isPrime;		// Prime Product or Not

	// assume the input file has valid format and data
	while (inputFile >> asin >> manufact >> price >> cusReview >> shipWeight >> isPrime)
	{
		obj.setASIN(asin);
		obj.setManufact(manufact);
		obj.setPrice(price);
		obj.setCusReview(cusReview);
		obj.setShipWeight(shipWeight);
		obj.setIsPrime(isPrime);

		table.insertTable(obj);
		tree1->insert(obj);
		tree2->insert2(obj, compareM);
	}
	inputFile.close();
}

void undoDelete(HashTable &table, Stack &s)
{
	cout << "\n________________________________________\n";
	Product obj;
	if (s.isEmpty())
	{
		cout << "\n\tThere is no item to undo deletion.\n";
	}
	else
	{
		s.getTop(obj);
		s.pop(obj);
		table.insertTable(obj);
		cout << "\n\tDeleted tem '" << obj.getASIN() << "' is listed again.\n";
	}

	cout << "________________________________________\n\n";
}

void showStatistics(HashTable &table)
{
	cout << "\n________________________________________\n"
		<< "\n\tLoad Factor: " << table.getLoadFactor()
		<< "\n\tNumber of Collision: " << table.getNumOfCollisions()
		<< "\n________________________________________\n\n";
}
