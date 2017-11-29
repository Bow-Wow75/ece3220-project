//
//  main.cpp
//  Finalproject
//
//  Created by Erik Bowers and Nicholas Bouckaert
//


#define COMPILER 0      ////...........IF USING XCODE COMPILE USING 0.....GNU COMPILER USE 1...............///////////
						////...........This is needed primarily because XCode handles file locations very oddly....../////////

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
class Log_in{
public:
    Log_in(){};
    ~Log_in(){};
    void login();
    void locate_account(string entered_id, string entered_password );
};
class Account:public Log_in{
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
        Account(){};
        Account(string user_id, string password, int type);
        ~Account(){};
        void sellStocks();
        void update_user_file();
        void buyStocks();
        //void locate_account(string entered_id, string entered_password );
        virtual void menu();
        void display_profolio();
        void read_accountinfo();
        void readstock_price();
        void loadstocks();// may use later in the code
        void setstockformarketcharge();
        void search_forstock(string stock); // will open available stocks and search for that stock in the folder
};
class Administrator: public Account {//extension of the case account class
    
private:
    string admin_id;
    string admin_password;
    int admin_type;
public:
    Administrator(){};
    Administrator(string user_id, string password, int type);
    ~Administrator(){};
    virtual void menu();
    void change_password();
    void create_account(int type);
    virtual void display_all();
};
void Administrator:: change_password(){
    string user_name,space;
    string id, password, new_password;
    int type;
    
    int error = 0;
    getline( cin, space);
    cout<<"Enter the name of the user whose was word needs to be change:"<<endl;
    getline(cin, user_name);
    try
    {
    fstream input;
        input.open(input_file, ios::app);
    if(!input.is_open())
    {
        throw error;
    }
        while(!input.eof())
    {
        input>>id;
             if(user_name.compare(id) == 0)
             {
                 cout<<"Enter in your new password"<<endl;
                 getline(cin, new_password);
                 input<<new_password;//need to get this to work
                 input.close();
                 throw 21;
             }
        input>>password;
        input>>type;
    }
        input.close();
    }
    catch( int error)
        {
        switch(error){
                
        case 0: cout<<"Unable to change password: try again if you would like"<<endl;
                break;
        case 21: cout<<"Password has been changed"<<endl;
                break;
        }
    }
    
    
}
void Administrator:: create_account(int type){
    string user_name, password;
    string space;
    try{
        getline(cin, space);//take in the enter from the user and dont use
        cout<<"Enter the User name you would like to use"<<endl;
        getline(cin, user_name);
        cout<<"Enter the password you would like to"<<endl;
        getline(cin, password);

    ofstream input;
    input.open(input_file, ios::app);
    if( !input.is_open() )
    {
        throw 0;
    }
    {
        input<<user_name;
        input<<" "<<password;
        input<<" "<<type;
    }
        input.close();
        
    }
    catch(...){
        cout<<"error writing to the creating account"<<endl;
    }
}

void Administrator:: display_all(){
    string user_name, password;
    int type;
    
    ifstream input;
    input.open(input_file);
    if( !input.is_open())
    {
        cout<<"error reading in market prices"<<endl;
    }
    cout<<"List of Accounts and account type"<<endl;
    input>>user_name;
    input>>password;
    input>>type;
   while( !input.eof())
   {
       if(type == 5 )
    {
        cout<<user_name<<" "<<"User"<<endl;
    }
       else{
        cout<<user_name<<" "<<"Admin"<<endl;
       }
       input>>user_name;
       input>>password;
       input>>type;
       
   }
    input.close();
    cout<<"End of list of accounts"<<endl;
    
}
void Administrator:: menu()
{
    string space;
    int choice = 0;
try{
    do{
        if( admin_type == 1 )
       {
        cout<<"Select what you would like to do"<<endl
        <<"\t1: See all accounts: "<<endl
        <<"\t2: Create account: "<<endl
        <<"\t3: Change user password: "<<endl
        <<"\t4: Login with user profolio "<<endl
        <<"\t5: To Exit your profolio: "<<endl;
        cin>>choice;
        
        switch( choice ){
                
            case 1://See all accounts
                display_all();
                break;
            case 2:// Create account
                int type;
                cout<<"what type account will this be:"<<endl
                <<"1:admin"<<endl
                <<"5:user"<<endl;
                cin>>type;
                create_account(type);
                break;
            case 3://change user password or id
                change_password();
                break;
            case 4://Display users profolio
                cout<<"Please have the client login"<<endl;;
                getline(cin, space);
                login();
                break;
            case 5://exit
                throw 0;
                break;
            default:
                break;
            }
       }
    }while( choice != 5);
}
    
    catch(...){
        cout<<"you have been logged out of your account"<<endl;
    }
    
}
Administrator::Administrator( string user_id, string password, int type)
{
    admin_id = user_id;
    admin_password = password;
    admin_type = type;
}
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

	while(!(cin >> number)){
		cin.clear();

		while(cin.get() != '\n')
			continue;

			cout << "Invalid input.  Try again: ";
	}

	while(number <= 0)
	{
		cout << "Not a valid number of stocks" << endl << "Enter number of Stocks you would like to sell: " << endl;

		while(!(cin >> number)){
			cin.clear();

			while(cin.get() != '\n')
				continue;

				cout << "Invalid input.  Try again: ";
		}
	}

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

	while(!(cin >> number)){
		cin.clear();

		while(cin.get() != '\n')
			continue;

			cout << "Invalid input.  Try again: ";
	}

	while(number <= 0)
	{
		cout << "Not a valid number of stocks" << endl << "Enter number of Stocks you would like to buy: " << endl;

		while(!(cin >> number)){
			cin.clear();

			while(cin.get() != '\n')
				continue;

				cout << "Invalid input.  Try again: ";
		}
	}

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
			//runs if the stock doesn't exist in our market file
				error = 11;
				stock_name.pop_back();
				number_shares.pop_back();
				throw error;

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

#if COMPILER == 1
    input.open("inputfiles/set_to_sell_or_buy.txt");
#endif

#if COMPILER == 0
    input.open("set_to_sell_or_buy.txt");
#endif

        input.open("set_to_sell_or_buy.txt", ios::app);
    if(!input.is_open())
    {
        cerr<<"Error accessing the stock to sell or buy for a market change"<<endl;
    }
    // a way of getting to the end of the file will need to be implemented
        input<<account_id<<" "<<stock<<" "<<price<<endl;
    
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
    int found = 9;
    string name;
    int i = 0;

    ifstream input;

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
    //int total
        while( found != 0 )
        {
            input>>name;
            input>>price;
            i++;
            if(stock.compare(name) == 0){
                stock_price.push_back(price);
                cout<<""<<name<<endl;
                cout<<""<<price<<endl;
                found = 0;
                input.seekg(0, ios::beg);
                input.close();
                throw price;
            };
            if( input.eof() )
            {
                input.clear();
                input.seekg(0, ios::beg);
                found = 0;
                cout<<"Stock was not found: "<<stock <<endl;
            }
            
}
    input.close();
    
}

void printMenu()
{
	cout << "(1) See Available stocks: " << endl
		 << "(2) Sell stocks: " << endl
		 << "(3) Set Stock Seller Requirements" << endl
		 << "(4) Account info: " << endl
		 << "(5) Update account balance: " << endl;
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
        throw 91;
    }
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
                stock_price.push_back(00);
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
    while( !input.eof())
    {
        input>>name;
        input>>number;
        stock_name.push_back(name);
        number_shares.push_back(number);
    }


    input.close();
    try{
    this->readstock_price();
    }

    catch(int marketValueError)
    {
    throw 2;
    }
}

void  Account::display_profolio(){
    
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
    int choice = 0;
    try{
    read_accountinfo();
    }

    catch( int reading_error)
    {
    	if(reading_error == 0)
    	{
        cout<<"Error reading the users file"<<endl;
        return;
    	}
    	else
    	{
    		cout << "unable to update stock values" << endl;
    		return;
    	}
    }
    catch( char prompt )
    {
        
    }
    do{
    try{
    if( account_type == 5 )
        {
        cout<<"Select what you would like to do"<<endl
        <<"\t1: Buy stocks: "<<endl
        <<"\t2: Sell stocks: "<<endl
        <<"\t3: Set stock to buy or sell: "<<endl
        <<"\t4: Display profolio: "<<endl
        <<"\t5: To Exit your profolio: "<<endl;
        
        while(!(cin >> choice)){
        			cin.clear();

        			while(cin.get() != '\n')
        				continue;

        				cout << "Invalid input.  Try again: ";
        		}

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
                display_profolio();
                break;
            case 5:// implement a throw to exit the program
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

    	case 11: cout << "Stock not found" << endl;
    	break;

    	case 2: cout << "Not enough stocks to sell" << endl;
    	break;

    	case 21: cout << "Stock not found" << endl;
    	break;

    	case 91: cout << "Unable to load stock values" << endl;
    	break;

    	default: cout << "Unknown error has occurred" << endl;
    	break;
    	}
    }
    }while( choice !=5 );
}
void Log_in::locate_account(string entered_id, string entered_password ){
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
               
                if( type ==  5){//will create a user class
                    Account user(user_id, password, type);
                    input.close();
                    user.menu();

                    throw password;
                }
                
                if( type == 1){
                    Administrator user(user_id, password, type);
                    input.close();
                    user.menu();
                    throw password;
                }
                
            }
        
        }
    }
    input.close();
        throw 1;
}
Account:: Account(string user_id, string password, int type){
    account_id = user_id;
    account_password = password;
    account_type = type;
    
}
void Log_in:: login(){
    string user_id; string password, space;
    int incorrect = 1;
    string exit = "";
    do{
       
        try
        {
            if( incorrect == 2)
        {
            cout<<"Incorrect User ID or Password: try again"<<endl;
            cout<<"if you would like to exit type exit:  "<<endl;
            getline(cin, exit);
        }
    cout<<"Welcome"<<endl;
    cout<<"Please enter in your user id: "<<endl;
    getline(cin, user_id);
    cout<<"Please enter in your password: "<<endl;
    getline(cin, password);
    locate_account( user_id, password);//seeing if there information is there
            incorrect = 2;
        }
        
       
        catch(char password)
        {
            cout<<"You have been logged out or your account"<<endl;
            getline(cin, space);//used to take in the enter from the user otherwise skips the user i when exiting
        }
        
        catch( int no_loggin)
        {
            if(no_loggin == 1)
                cout<<"Unsuccesful login"<<endl;
            incorrect = 2;
        }
       

    }while( exit != "exit");


  /*  catch( int error )
    {
    	if(error == 0)
        cout<<"login was successful"<<endl;
    	if(error == 1)
    	{
    		cout << "Unable to open file" << endl;
    		throw error;
    	}
    }*/
    return;
}
int main( int argc, char** argv){
    try{
        Log_in user;
        user.login();
    }
    
    catch( int input_error)
    {
        cout<<"Error opening the accounts file"<<endl;
    }
    return 0;
}
