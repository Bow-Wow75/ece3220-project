//============================================================================
// Name        : Stock.cpp
// Author      : Erik Bowers & Nicholas B
// Version     :
// Copyright   :
// Description : Stock trading program for ece 3220
//============================================================================

#include "header.h"
using namespace std;

int main() {
	int action = 0;

	vector<Stock> availableStocks = loadStocks();

	for(int i=0;i<availableStocks.size();i++)
	{
		availableStocks[i].printStocks();
	}

	while(action != -1)
	{//print menu
		printMenu();
		cin >> action;
	}

	return 0;
}
