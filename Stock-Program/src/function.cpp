/*
 * function.cpp
 *
 *  Created on: Nov 9, 2017
 *      Author: erik
 */

#include "header.h"

using namespace std;

//Stock constructor
Stock::Stock(string named, double valued)
{
	name = named;
	value = valued;
}

vector<Stock> Stock::loadStocks()
{

	Stock boeing("Boeing", 262.70);
	Stock AMD("AMD", 11.12);
	Stock intel("Intel", 46.40);

	vector<Stock> availableStocks{boeing, AMD, intel};

return availableStocks;

}

void printMenu()
{
	cout << "(1) See Available stocks: " << endl
		 << "(2) Sell stocks: " << endl
		 << "(3) Set Stock Seller Requirements" << endl
		 << "(4) Account info: " << endl
		 << "(5) Update account balance: " << endl;
}



