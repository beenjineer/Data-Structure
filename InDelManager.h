//Unit 1: Insert and Delete Manager
//Writer: Seung Yoon Han
//IDE: Visual Studio


#include "HashTable.h"
#include "BinarySearchTree.h"
#include <iostream>
#include <iomanip>
using namespace std;


void addNewProduct(HashTable &table, BinarySearchTree<Product> *tree1, BinarySearchTree<Product> *tree2)
{
	cin.ignore();
	const string PROMPT = "\nEnter ASIN to start inserting a new product (or Q for stop inserting) : ";
	Product newProduct;
	string asin, manufact;
	double cusReview, shipWeight, price;
	string isPrime;
	bool duplicated;

	cout << "\n________________________________________";

	// Use the comma operator to avoid duplicating code
	while (cout << PROMPT, getline(cin, asin), asin[0] = toupper(asin[0]), asin != "Q")
	{
		if (duplicated = table.hashSearch(asin))
		{
			cout << "\n\tASIN must not be duplicated. Try other ASIN.\n";
		}
		else
		{
			cout << "\n\tManufacturer: ";
			getline(cin, manufact);
			cout << "\tCustomer Review (between 0 and 5): ";
			cin >> cusReview;
			cout << "\tShip Weight: ";
			cin >> shipWeight;
			cout << "\tPrice (>$0): ";
			cin >> price;
			cout << "\tPrime (Yes or No): ";
			cin >> isPrime;

			cin.ignore();
			newProduct.setASIN(asin);
			newProduct.setManufact(manufact);
			newProduct.setCusReview(cusReview);
			newProduct.setShipWeight(shipWeight);
			if (isPrime == "Yes")
				newProduct.setIsPrime(1);
			else if (isPrime == "No")
				newProduct.setIsPrime(0);

			if (table.isValid(newProduct))
			{
				cout << "\n\tNEW PRODUCT ADDED\n";
				table.insertTable(newProduct);
				tree1->insert(newProduct);
				tree2->insert2(newProduct, compareM);
			}
			else
			{
				cout << "\n\tInserted product is NOT VALID. Try again.\n";
			}
		}
	}
	cout << "________________________________________\n\n";
}

void deleteProduct(Stack &s, HashTable &table, BinarySearchTree<Product> *tree1, BinarySearchTree<Product> *tree2)
{
	const string PROMPT = "Enter ASIN to delete (or Q for stop deleting) : ";
	Product obj;
	string asin;

	cout << "\n________________________________________";

	cout << endl << PROMPT;
	cin >> asin;
	asin[0] = toupper(asin[0]);
	while (asin != "Q")
	{
		if (table.hashSearch(asin)) {
			obj.setASIN(asin);
			table.deleteHash(obj);
			s.push(obj);
			tree1->remove(obj);
			tree2->remove2(obj, compareM);
			cout << "\n\tITEM DELETED\n";
		}
		else {
			cout << "\n\tITEM NOT FOUND\n";
		}
		cout << endl << PROMPT;
		cin.ignore();
		cin >> asin;
		asin[0] = toupper(asin[0]);
	}
	cout << "________________________________________\n\n";
}
