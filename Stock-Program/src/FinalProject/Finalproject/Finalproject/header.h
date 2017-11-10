#include <iostream>
#include <vector>
#include <string>
#include <fstream>


class Stock{
private:

protected:

public:
	double value;
	std::string name;

	void printStocks();
	//constructor

};


class User{
private:
	double balance;
	int id;
	std::vector<Stock> stocks;
	std::vector<int> stockNums;
protected:

public:

};


void printMenu();
std::vector<Stock> loadStocks();
