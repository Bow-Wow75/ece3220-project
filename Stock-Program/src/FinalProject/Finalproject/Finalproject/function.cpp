/*
 * function.cpp
 *
 *  Created on: Nov 9, 2017
 *      Author: erik
 */

#include "header.h"

using namespace std;

void Stock::printStocks()
{
	cout << name << "  " << value << endl;
}



vector<Stock> loadStocks()
{


		std::ifstream inputFile;
		inputFile.open("stocks.txt");
		//int fileError = 0;

		if(!inputFile)
		{

			cerr << "Unable to open file" << endl;
	/*		try
			{
			throw 0;
			}
			catch(int error){

			}*/
		}

		vector<Stock> availableStocks;
		Stock temp;

		while(inputFile >> temp.name >> temp.value)
		{
			availableStocks.push_back(temp);
		}

		inputFile.close();
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



