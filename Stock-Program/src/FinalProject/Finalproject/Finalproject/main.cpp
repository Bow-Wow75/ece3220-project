//
//  main.cpp
//  Finalproject
//
//  Created by Nicholas Bouckaert on 11/9/17.
//  Copyright © 2017 Nicholas Bouckaert. All rights reserved.
//


#define COMPILER 1      ////...........IF USING XCODE COMPILE USING 0.....GNU COMPILER USE 1...............///////////
						////...........This is needed primarily because XCode handles files very oddly....../////////

#define ACCOUNTS "accounts.txt"
#define STOCKS "stocks.txt"

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

string input_file = "accounts.txt";// stores the list of accounts for the program and their passwords

class Account{
    protected:
        string account_id;
        string account_password;
        int account_type;// 1 is admin, 5 is user
        double balance;
        vector<string> stock_name;
        vector<int> number_shares;
        vector<double> stock_price;
        vector<double> availableStocks;// erik
    public:
        Account();
        ~Account();
        void sellStocks();
        void update_user_file();
        void buyStocks();
        void login();
        void locate_account(string entered_id, string entered_password );
        void menu();
        void display_profolio();
        void read_accountinfo();
        void readstock_price();
        void loadstocks();// may use later in the code
        void setstockformarketcharge();
        void search_forstock(string stock); // will open available stocks and search for that stock in the folder
};

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

//.........END HEADER........//




//..........from Erik's functions........//

void Account::sellStocks()
{
	string name;
	int number;
	int check=0;
	cout << "Enter name of stock to sell: " << endl;
	cin >> name;
	cout << "Enter the number of Stocks you would like to sell: " << endl;
	cin >> number;

	for(int i=0;i<stock_name.size();i++)
	{
		if(stock_name[i].compare(name)==0)//iterate until we find the stock that matches
		{
			if((number_shares[i]-number) < 0)//ensure we have enough stocks to sell
			{
				throw 2;
			}
			else if((number_shares[i]-number)==0)//delete the stock element if we sell them all
			{
				stock_name.erase(stock_name.begin()+i);
				number_shares.erase(number_shares.begin()+i);
				balance += number*stock_price[i];
				check = 1;
			}
			else{//update stock numbers and balance
			number_shares[i] -= number;
			balance += number*stock_price[i];
			check = 1;
			}
			break;
		}
	}

	if(check == 0)//stock isn't found so throw error code
	{
		throw 21;
	}

	stock_price.clear();//update stock values
	this->readstock_price();

	update_user_file();//update user file
	return;
}

void Account::update_user_file()
{
		  string filename;
		    filename = "inputfiles/accounts/" +account_id + ".txt";




		std::ofstream outputFile(filename.c_str());
		int i = 0;

		if (outputFile.is_open()) //if the file is open
		    {

			outputFile << balance << endl;

		        for(i=0;i<stock_name.size();i++) //while the end of file is NOT reached
		        {
		            outputFile << stock_name[i] << " " << number_shares[i] << endl;
		        }
		        outputFile.close(); //closing the file
		    }
		    else
		    	{
		    	cout << "Unable to open file\n"; //if the file is not open output
		    	return;
	}


}

void Account::buyStocks()
{
	string name;
	int number;
	int check=0;
	cout << "Enter name of stock to buy: " << endl;
	cin >> name;
	cout << "Enter the number of Stocks you would like to buy: " << endl;
	cin >> number;

	int i;
	for(i=0;i<stock_name.size();i++)//iterate until stock is found
	{
		if(stock_name[i].compare(name)==0)
		{
			if((balance -(stock_price[i]*number)) < 0)//ensure user has enough money
			{
				throw 1;
			}
			number_shares[i] += number;//update share numbers
			balance -= number*stock_price[i];
			check = 1;
			break;
		}
	}

	if(check == 0)//this runs if this is the first time the user buys this companies stock
	{
		stock_name.push_back(name);
		number_shares.push_back(0);//We don't want to give user the stocks until we know they have enough money

		try{
		stock_price.clear();
		this->readstock_price();
		}

		catch(int error)
		{
			if(error == 11)//runs if the stock doesn't exist in our market file
			{
				stock_name.pop_back();
				number_shares.pop_back();
				throw error;
			}
		}

		if((balance - (stock_price.back()*number)) < 0)//check if user has enough money
		{
			stock_name.pop_back();//if not, get rid of these elements
			number_shares.pop_back();
			throw 1;
		}

		number_shares[i] = number;//set share number
		balance -= number*stock_price[i];//update balance
	}

	update_user_file();//update user file
	return;
}


void Stock::printStocks()
{
	cout << name << "  " << value << endl;
}
void Account::setstockformarketcharge(){
    string stock;
    string retry;
    try{
      // try block to determine is the stock is available
    cout<<"Enter the name of the stock you would like to buy or sell"<<endl;
    cin>>stock;
    this->search_forstock(stock);
        cout<<"Sorry your stock can not be found"<<endl;
        cout<<"Would you like to try again if so enter yes: "<<endl;
        cin>>retry;
    }
    
    catch( double price)
    {
    ofstream input;
    input.open("set_to_sell_or_buy.txt");
    if(!input.is_open())
    {
        cerr<<"Error accessing the stock to sell or buy for a market change"<<endl;
    }
    // a why of getting to the end of the file will need to be implemented
    {
        //input.seekg(0, ios::end);
        //int lenght = file.tellg();
        //input.seekg(lenght, )
        input<<account_id<<" "<<stock<<" "<<price<<endl;
    }
        input.close();
    }
    cout<<"would you like to add another stock if so type yes"<<endl;
            cin>>retry;
            if(retry == "yes")
            {
                this->setstockformarketcharge();
            }
    
}
void Account::search_forstock(string stock){
    double price;
    int found = 0;
    string name;

    ifstream input;
    input.open("market_price.txt");
    if( !input.is_open())
    {
        cout<<"error reading in market prices"<<endl;
    }
    //int total
        while( !input.eof() || found != 0)
        {
            input>>name;
            input>>price;
            if(stock.compare(name) == 0){
                stock_price.push_back(price);
                cout<<""<<name<<endl;
                cout<<""<<price<<endl;
                found = 0;
                input.seekg(0, ios::beg);
                throw price;
            };
            
        }
    input.close();
    
}

void Account:: loadstocks()
{


		ifstream inputFile;
		inputFile.open("stocks.txt");
		//int fileError = 0;

		if(!inputFile)
		{

			cerr << "Unable to open file" << endl;
			throw 0;
		}

		vector<Stock> availableStocks;
		Stock temp;

		while(inputFile >> temp.name >> temp.value)
		{
			availableStocks.push_back(temp);
		}

		inputFile.close();
}

void printMenu()
{
	cout << "(1) See Available stocks: " << endl
		 << "(2) Sell stocks: " << endl
		 << "(3) Set Stock Seller Requirements" << endl
		 << "(4) Account info: " << endl
		 << "(5) Update account balance: " << endl;
}
Account::Account(){
    
}

Account::~Account(){
    
}
void Account::readstock_price(){
    
    ifstream input;
    string name;
    double price;
    int found = 9;
#if COMPILER == 0
    input.open("market_price.txt");
#endif
#if COMPILER == 1
    input.open("inputfiles/market_price.txt");
#endif
   
    if( !input.is_open())
    {
        cout<<"error reading in market prices"<<endl;
    }

    // new function accounts for all cases unlike the old
    /*for( int i = 0; i < (stock_name.size()); i++){
    	j=0;
        
        while( !input.eof() || found != 0)
        {
            input>>name;
            input>>price;
            if(stock_name[i].compare(name) == 0){
                stock_price.push_back(price);
                cout<<name<<endl;
                cout<<price<<endl;

                //cout<<""<<name<<endl;
                //cout<<""<<price<<endl;
                found = 0;
                i++;
                input.seekg(0, ios::beg);
            }
            
        }*/
    for( int i = 0; i < (stock_name.size()); i++){
       
    	found = 9;
       // input>>name;
        //input>>price;
        while( found != 0)
        {
            input>>name;
            input>>price;
            
            if(stock_name[i].compare(name) == 0){
                stock_price.push_back(price);
               // cout<<""<<name<<endl;
                //cout<<""<<price<<endl;
                input.clear();
                input.seekg(0, ios::beg);
                found = 0;
                input.seekg(0, ios::beg);//I added this because it was only going back to the top of the file when

            }
            if( input.eof() && found == 9)
            {
                input.clear();
                input.seekg(0, ios::beg);
                found = 0;
                cout<<"Stock was not found: "<<stock_name[i]<<endl;
                throw 11;
                

            }
            
            
        }
       // input.seekg(0, ios::beg);//I added this because it was only going back to the top of the file when
        //we hit the end of file, but we need to look at stocks from top to bottom each time
        found = 9;
        //input.seekg(0, ios::beg);
        
    }
        
    input.close();
    
}
void Account::read_accountinfo(){
    string filename;
#if COMPILER == 0
    filename = account_id +".txt";
#endif
#if COMPILER == 1
    filename = "inputfiles/accounts/" +account_id + ".txt";
#endif
    int readFile_error = 0;
    string name;
    int number;
    ifstream input;
    input.open(filename.c_str());
    if( !input.is_open())
    {
        throw readFile_error;
    }
    input>>balance;
    while(input >> name >> number)
    {
        //input>>name;
        stock_name.push_back(name);
        
        //input>>number;
        number_shares.push_back(number);
    }


    input.close();
    this->readstock_price();
}

void Account::display_profolio(){
    
    int i;
    cout<<"Profolio for "<<account_id<<endl;
    cout<<"Account Balance: "<<balance<<endl;
    
    cout<<"Stock "<<"Shares "<<"Price"<<endl;
    
    for( i = 0; i <stock_name.size(); i++)
    {
      //  cout << "test1" << endl;
        cout<<" "<<stock_name[i]<<" "<<number_shares[i]<<" "<<stock_price[i]<<endl;
      //  cout<<" "<<stock_name[i]<<" "<<number_shares[i]<<endl;

    }
    
}
void Account::menu(){
    //User function
    int choice;
    try{
    this->read_accountinfo();
    }

    catch( int reading_error)
    {
        cout<<"Error reading the users file"<<endl;
    }
    try{

    if( account_type == 5 )
    {
        cout<<"Select what you would like to do"<<endl
        <<"\t1: Buy stocks: "<<endl
        <<"\t2: Sell stocks: "<<endl
        <<"\t3: Set stock to buy or sell: "<<endl
        <<"\t4: Display profolio: "<<endl
        <<"\t5: To Exit your profolio: "<<endl;
        cin>>choice;
        
        switch( choice ){
        
            case 1: // Buy stock
            	buyStocks();
                break;
            case 2: //Sell stock
            	sellStocks();
                break;
            case 3: // set stock to buy or sell
                setstockformarketcharge();
                break;
            case 4:// display profolio
                this->display_profolio();
                break;
            case 5:// implement a throw to exit the program
                break; 
            default:
            	break;
                
                
        }
    }
    }//for try statement

    catch(int menuError)
    {
    	switch(menuError)
    	{
    	case 1: cout << "Not enough money in account" << endl;
    	break;

    	case 2: cout << "Not enough stocks to sell" << endl;
    	break;

    	case 21: cout << "Stock not found" << endl;
    	break;

    	default: cout << "Unknown error has occurred" << endl;
    	break;
    	}
    }
    
    
    
}
void Account:: locate_account(string entered_id, string entered_password ){
    int type;
    int input_error = 1;
   string user_id, password;
    ifstream input;


#if COMPILER ==1
    //................gnu compiler needs input_file defined.....................................//

    string input_file = "inputfiles/accounts.txt";

    //..........................This may need removed in XCode^^^^  !!!CHANGE COMPILER TO 0, DON'T DELETE!!!.............................////////
#endif

    input.open(input_file.c_str());

    if(!input)
    {
        throw input_error;
    }
    while( !input.eof())
    {
        input>>user_id;
        input>>password;
        input>>type;
        
        if( entered_id.compare(user_id) == 0){
            if( entered_password.compare(password)== 0 ){
                account_id = user_id;
                account_password = password;
                account_type = type;
                //cout<<"successful login"<<endl;
                throw 0;// throws zero if correct
            }
        }
        
    }
    input.close();
}
void Account::login(){
    string user_id; string password;
    int incorrect = 1;
    string exit = "";
   try
    {


        do{
        if( incorrect == 2)
        {
            cout<<"Incorrect User ID or Password: try again"<<endl;
            cout<<"if you would like to exit type exit:  "<<endl;
            getline(cin, exit);
        }
    cout<<"Please enter in your user id: "<<endl;
    getline(cin, user_id);
    cout<<"Please enter in your password: "<<endl;
    getline(cin, password);
    
    this->locate_account( user_id ,password);
            incorrect = 2;
    }while( exit != "exit");
      
    }
    
    catch( int error )
    {
    	if(error == 0)
        cout<<"login was successful"<<endl;
    	if(error == 1)
    		cout << "Unable to open file" << endl;
    }
}


int main( int argc, char** argv){
    try{
        Account user;
        user.login();
        user.menu();
        
   
    
    }
    
    catch( int input_error)
    {
        cout<<"Error opening the accounts file"<<endl;
    }
}
