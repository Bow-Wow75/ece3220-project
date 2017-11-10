#include <iostream>
#include <vector>
#include <string>


class Stock{
private:
	double value;
	std::string name;

protected:

public:
	std::vector<Stock> loadStocks();
	//constructor
	Stock(std::string name, double value);

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
