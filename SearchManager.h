// Search Manager
// modified by Daniel Yun
// ide: XCode

#include "HashTable.h"
#include "BinarySearchTree.h"
#include <iostream>
#include <iomanip>
using namespace std;

int compareM(Product &p1, Product &p2)
{
	return p1.getManufact().compare(p2.getManufact());
}

void upperString(string &word) {
	for (size_t i = 0; i < word.length(); i++) {
		word[i] = toupper(word[i]);
	}
}

void searchManager(BinarySearchTree<Product> *tree1, BinarySearchTree<Product> *tree2) {
	int searchChoice = 0;
	bool wrongInput = true;
	string temp;
	Product tempProduct;

	cout << "________________________________________\n";
	cout << "\t1 - Search by ASIN\n";
	cout << "\t2 - Search by Manufacturer\n\n";
	cout << "\tWhat would you like to search by? ";

	while (wrongInput) {
		cin >> searchChoice;
		if (searchChoice != 1 && searchChoice != 2) {
			cout << "\n\tWrong Input…Try Again\n";
		}
		else {
			wrongInput = false;
		}
	}

	cin.ignore();

	if (searchChoice == 1) {
		cout << "\n\tInsert ASIN to search: ";
		getline(cin, temp);
		upperString(temp);
		tempProduct.setASIN(temp);
		//Search Using BinarySearch Tree
		if (tree1->getEntry(tempProduct, tempProduct)) {
			tempProduct.printInfo();
		}
		else {
			cout << "\n\tITEM NOT FOUND\n";
		}
	}
	else {
		cout << "\n\tInsert Manufacturer to search: ";
		getline(cin, temp);
		upperString(temp);
		tempProduct.setManufact(temp);
		//Search Using BinarySearch Tree
		if (tree2->getEntry2(tempProduct, tempProduct, compareM)) {
			tempProduct.printInfo();
		}
		else {
			cout << "\n\tITEM NOT FOUND\n";
		}
	}
	cout << "________________________________________\n\n";
}

void showList(HashTable &table, BinarySearchTree<Product> *tree1, BinarySearchTree<Product> *tree2) {

	char listChoice = 'A';
	bool wrongInput = true;

	cout << "\n________________________________________";
	cout << "\n\tP - Sort by Primary Key";
	cout << "\n\tS - Sort by Secondary Key";
	cout << "\n\n\tWhat list would you like? ";

	while (wrongInput) {
		cin >> listChoice;
		if (listChoice != 'U' && listChoice != 'P' && listChoice != 'S' && listChoice != 'I' && listChoice != 'H') {
			cout << "\n\tERROR: Input must be U, P, S or I"
				<< "\n\n\tWhat list would you like? ";
		}
		else {
			wrongInput = false;
		}
	}

	switch (listChoice) {
	case 'U':

	case 'P':
		//Print Sorted List - Primary Key
		cout << endl;
		tree1->print();
		break;
	case 'S':
		//Print Sorted List - Secondary Key
		cout << endl;
		tree2->print2();
		break;
	case 'I':
		//Print Indented Tree - Primary Key
		tree1->print3();
		break;
	case 'H':
		cout << "\n\t____________________\n"
			<< "\t~*^* Developers *^*~\n"
			<< "\tSeung Yoon Han\n"
			<< "\tDaniel Yun\n"
			<< "\tKelly Ho\n"
			<< "\tYounseo Ryu\n"
			<< "\tSungmin Jin\n"
			<< "\t____________________\n\n";
		break;
	default:
		cout << "Error\n";
	}
	cout << "________________________________________\n\n";
}
