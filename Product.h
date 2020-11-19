// Product Class
// modified by Daniel Yun
// ide: XCode

#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

class Product {
private:
	string asin; // Amazon Standard Identification Number
	string manufact; // Manufacturer
	double cusReview; // Customer Review
	double shipWeight; // Shipping Weight
	double price; // Price
	bool isPrime; // Prime Product or Not

public:
	Product() {
		asin = " ";
		manufact = " ";
		cusReview = 0;
		shipWeight = 0;
		price = 0;
		isPrime = false;
	}
	Product(string asin, string manufact, double cusReview, double shipWeight,
		double price, bool isPrime) {
		asin = asin;
		manufact = manufact;
		cusReview = cusReview;
		shipWeight = shipWeight;
		price = price;
		isPrime = isPrime;
	}
	void setASIN(string newASIN) {
		asin = newASIN;
	}
	void setManufact(string newManufact) {
		manufact = newManufact;
	}
	void setCusReview(double newCusReview) {
		cusReview = newCusReview;
	}
	void setShipWeight(double newShipWeight) {
		shipWeight = newShipWeight;
	}
	void setPrice(double newPrice) {
		price = newPrice;
	}
	void setIsPrime(double newPrime) {
		isPrime = newPrime;
	}
	string getASIN() {
		return asin;
	}
	string getManufact() {
		return manufact;
	}
	double getCusReview() {
		return cusReview;
	}
	double getShipWeight() {
		return shipWeight;
	}
	double getPrice() {
		return price;
	}
	bool getPrime() {
		return isPrime;
	}

	void printInfo() {
		cout << "\n\tASIN: " << getASIN() << endl;
		cout << "\tManufactuerer: " << getManufact() << endl;
		cout << "\tCustomer Review: " << getCusReview() << endl;
		cout << "\tShipping Weight: " << getShipWeight() << endl;
		cout << "\tPrime: ";
		if (getPrime()) {
			cout << "Yes" << endl;
		}
		else {
			cout << "No" << endl;
		}
	}

	// Overloading Operator < to compare Products by ASIN
	friend bool operator< (const Product &pro1, const Product &pro2)
	{
		string temp1, temp2;
		temp1 = pro1.asin;
		temp2 = pro2.asin;
		if (temp1.compare(temp2) < 0) { // temp1 < temp2
			return true;
		}
		return false;
	}

	// Overloading Operator > to compare Products by ASIN
	friend bool operator> (const Product &pro1, const Product &pro2)
	{
		string temp1, temp2;
		temp1 = pro1.asin;
		temp2 = pro2.asin;
		if (temp1.compare(temp2) > 0) { // temp1 < temp2
			return true;
		}
		return false;
	}

	// Overloading Operator == to compare Products by ASIN
	friend bool operator== (const Product &pro1, const Product &pro2)
	{
		string temp1, temp2;
		temp1 = pro1.asin;
		temp2 = pro2.asin;
		if (temp1.compare(temp2) == 0) { // temp1 < temp2
			return true;
		}
		return false;
	}
};

#endif