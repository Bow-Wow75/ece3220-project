//
//  main.cpp
//  Finalproject
//
//  Created by Erik Bowers and Nicholas Bouckaert
//

//......................COMPILE USING C++11 STANDARDS.........................//////


#define COMPILER 1      ////...........IF USING XCODE COMPILE USING 0.....GNU COMPILER USE 1...............///////////
						////...........This is needed primarily because XCode handles file locations very oddly....../////////
#define SLEEPTIME 5  //in seconds

#define ACCOUNTS "accounts.txt"
//#define STOCKS "stocks.txt"

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include <string.h>
#include <unistd.h>
#include <iomanip>

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
        vector<double> availableStocks;
    
    public:
        Account(){};
        Account(string user_id, string password, int type);
        ~Account(){};
        void operator+(int add);
        void operator-(int subtract);
        void sellStocks(string name, int number);
        void update_user_file();
        void buyStocks(string name, int number);
        //void locate_account(string entered_id, string entered_password );
        virtual void menu();
        void display_profolio();
        void read_accountinfo();
        void readstock_price();
        void loadstocks();// may use later in the code
        void setstockformarketcharge();
        void search_forstock(string stock); // will open available stocks and search for that stock in the folder
        int checkBackgroundUpdate(string stock_name, int numStocks, double price, int action);

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
    void backgroundUpdate();
};
void Account:: operator-(int subtract){//simple and not completely need but demomstates operators which is a requirement to meet
    balance = balance - subtract;
}
void Account:: operator+(int add){//simple and not completely need but demomstates operators which is a requirement to meet
    balance = balance + add;
}
int Account::checkBackgroundUpdate(string NewStock, int numStocks, double price, int action)
{
	this->read_accountinfo();
	this->readstock_price();


	int i = 0;


	for(i=0;i<stock_name.size();i++)//iterate until stock is found
	{
		if(action == 1)
		{
		if(stock_name[i].compare(NewStock)==0)
		{
			//cout << "Cost:" << stock_price[i] << endl;
			if(stock_price[i] <= price)
		{
				cout << account_id << " buying " << numStocks  << " "<< NewStock << " stocks for " << stock_price[i]<< endl;
			buyStocks(NewStock, numStocks);
			return 1;
		}
			break;
		}
		}

		if(action == 2)
		{
			if(stock_name[i].compare(NewStock)==0)
			{
				if(stock_price[i] >= price)
				{
					cout << account_id << " selling " << numStocks  << " "<< NewStock << " stocks for " << stock_price[i]<< endl;
				sellStocks(NewStock, numStocks);
				return 1;
				}
				break;
			}

		}
	}
	return 0;

}

void Administrator::backgroundUpdate()
{
													/*This function will loop and buy/sell user stocks based on their preferences.
													 * Right now the only way to exit out of this loop is to use ctrl c to exit
													 * the entire program.  Mulithreading would be one solution to this and we could
													 * even run this function in the background, but that is currently
													 * a little out of scope for this project.
													 *
													 * In the future, multithreading will hopefully be implemented
													 */
//	ifstream input;
//	input.open("inputfiles/set_to_sell_or_buy.txt");

	int exit = 0;
	cout << "Auto update is now running. Message will be displayed when stocks are bought or sold" << endl;
	cout << "ctrl c to exit" << endl;
	//cin >> exit;

	int numStocks = 0;
	double price = 0;
	int action = 0;
	string account_id;
	string stock_name;

	while(exit != -1)
	{
//	cin >> exit;
	sleep(SLEEPTIME);//sleep takes in seconds

	ifstream input;
	input.open("inputfiles/set_to_sell_or_buy.txt");

	ofstream outputTemp;
	outputTemp.open("inputfiles/temp.txt", ios::app);    				/*This temp file is used so that we can essentially
																		 *delete the line from the set to buy/sell file once
																		 *that stock has been bought. We rewrite the file and then delete
																		 *the original and rename the temp file*/

//		this->readstock_price();//I don't know why "this->" is needed
		while(input >> account_id >> stock_name >> numStocks >> price >> action)
		{
			Account temp(account_id, "password", 5);
			//The buy/sell functions will need modified to take the name and number as arguments instead of asking for them


				if(temp.checkBackgroundUpdate(stock_name, numStocks, price, action) == 0)
				{
					outputTemp << account_id << " " << stock_name << " " << numStocks << " " << price << " " << action << endl;
				}
				else
				{
					//This is run instead so the line that was run is not written back to the file
				}



		}

		outputTemp.close();
		input.close();
	    remove("inputfiles/set_to_sell_or_buy.txt");
	    rename("inputfiles/temp.txt","inputfiles/set_to_sell_or_buy.txt");

	//	input.clear();          ///These ensure we go back to the top of the file
	//	input.seekg(0, ios::beg);

	}


	return;

}

void Administrator:: change_password(){ // allows admin to reset a password. However they can not see the original password

	/*This function is not working on linux. I can't follow it well enough to to try and get it working.  I
	 * edited the file names and it straight up froze my machine.
	 */
    
    // backwords way of changing the file and i dont like it all since im rewriteing the whole file. Luis when grading this if you wont mind emailing my school email pawprint is nabyq6 i would like to know if that was an easier way of doing this. I tried setting the trunc flag however whenever i did the file would never open.
    string user_name,space;
    string file_password, file_id;
    int type;
    vector<string> id, password;
    vector<int> level;
    
    int error = 0;
    getline( cin, space);
    cout<<"Enter the name of the user whose password needs to be change:"<<endl;
    getline(cin, user_name);
    try
    {
    fstream input;
       /* input.open(input_file, ios::app);           What does this do? Eric this opebs a file for appending mean that it will write to the end of the text file by setting the app flag.
                                                            Update: this needs c++11 standard to compile*/
#if COMPILER == 0
        input.open(input_file);//reads the entire  file and stores everything in vectors
#endif

#if COMPILER == 1
	    string filename = "inputfiles/accounts.txt";
	    input.open(filename.c_str());
#endif

        //input.seekp(0, ios::beg);
    if(!input.is_open())
    {
        error = 1;
        throw error;
    }
        while(!input.eof())
    {
        input>>file_id;
        id.push_back(file_id);
        
        if(user_name.compare(file_id) == 0)
             {
                 input>>file_password;
                 string new_password;
                 cout<<"Enter in your new password"<<endl;
                 cin>>new_password;
                 password.push_back(new_password);
                 cout<<"Password as been successfully changed"<<endl;
                 error = 2;
             }
        else{
            input>>file_password;
            password.push_back(file_password);
            }
        input>>type;
        level.push_back(type);
    }
        input.close();
        if( error != 2)
        {
            throw error;
        }
        
            
    }
    catch( int error)// what to print depending on error thrown
        {
        switch(error){
                
        case 1: cout<<"Unable to change password: try again if you would like but accounts file could not be opened"<<endl;
                break;
        case 0: cout<<"Unable to locate account in system directory"<<endl<<endl;
            
        }
    }
    ofstream input;//ios::out flag clears the entire file
#if COMPILER == 0
    input.open(input_file);//rewrite the vectors to the entire file with the password update. would be a horrible idea if the file was large. only way i could get function to work file is clear a whole file and rewrite everything trunc flag would compile
#endif

#if COMPILER == 1
    string filename = "inputfiles/accounts.txt";
    input.open(filename.c_str());
#endif
    if( !input.is_open())
    {
        cerr<<"apon rewrite the file could not be opened";
    }
    for( int i = 0; i < id.size()-1; i++)
    {
        input<<id[i]<<" "<<password[i]<<" "<<level[i]<<endl;
    }
    input.close();
    
}
void Administrator:: create_account(int type){//allows the admin to create an account once admin is logged in.
    string user_name, password;
    string space;
    try{
        getline(cin, space);//take in the enter from the user and dont use
        cout<<"Enter the User name you would like to use"<<endl;
        getline(cin, user_name);
        cout<<"Enter the password you would like to"<<endl;
        getline(cin, password);


#if COMPILER == 1                                            //This was added because Xcode handles files in a manner that
        													//No other compiler can. We also added a newline for the new user
        ofstream input;
           input.open("inputfiles/accounts.txt", ios::app);
           if( !input.is_open() )
           {
               throw 0;
           }
           {
        	   input << endl << user_name << " " << password << " " << type;
           }
               input.close();

        

#endif

#if COMPILER == 0                      //This code doesn't add a new line for the users so they will be in one line
    ofstream input;
    input.open(input_file, ios::app);//append flag is set and will allow the file to be write to from the end of the file
    if( !input.is_open() )
    {
        throw 0;
    }
    {
        input<<user_name;
        input<<" "<<password;
        input<<" "<<type<<endl;
    }
        input.close();
        
    
#endif

    int balance;
        string filename;
    cout<<"what is the balance they user wants to despoit"<<endl;
    cin>>balance;
    ofstream output;
#if COMPILER == 1
filename = "inputfiles/accounts/" + user_name + ".txt";
#endif
#if COMPILER == 0
        filename =  user_name + ".txt";
#endif
//    cout<<filename<<endl;
    output.open(filename);
    if(!output.is_open())
    {
        throw  balance;//throw as error
    }
    output<<balance;
    output.close();
    
    }

    catch(int balance)
    {
        cout<<"Error creating new protfolio file"<<endl;
    }
    catch(...){
        cout<<"error writing to the creating account"<<endl;// throws are if the file doesnt open
    }
}

void Administrator:: display_all(){// displays all the accounts with the company
    string user_name, password;
    int type;
    
    ifstream input;

#if COMPILER == 1
    input.open("inputfiles/accounts.txt");
#endif

#if COMPILER == 0
    input.open(input_file);
#endif


    if( !input.is_open())//This doesn't seem to work
    {
        cout<<"Unable to open accounts file"<<endl;
    }
    cout<<"List of Accounts and account type"<<endl << endl;

#if COMPILER == 1         /*I wrote this because the code below started an output loop. On linux at least. There are no comments
							so I don't really know how you tried to implement it or if you error checked it

 	 	 	 	 	 	 */

    while(input >> user_name >> password >> type)
    {												//We don't print the password because no one should have access to them
    	 if(type == 5 )								//In production the passwords would be hashed or encrypted
    	    {
    	        cout<<user_name<<" "<<"User"<<endl;
    	    }
    	 else{
    		 cout<<user_name<<" "<<"Admin"<<endl;
    	 }
    }

#endif

#if COMPILER == 0                 //Was this error checked?  I rewrote the function above in a more concise manner
    								//but left this because it might work on XCode? On linux this results in an output loop.
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
#endif
    input.close();
    cout << endl <<"End of list of accounts"<<endl;
    
}

/*
 * When logging in as another user there is no way to log out as them.  It throws an error.
 * I don't know how you implemented this. -Erik
 */


void Administrator:: menu()// menu for the admin user with the type = 5 in file
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
        <<"\t5: To Exit your profolio: "<<endl
        <<"\t6: Run program in background for auto buy/sell" << endl;
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
            case 6://Run sleep/background updating
            	backgroundUpdate();
            	break;
            default:
                break;
            }
       }
    }while( choice != 5);
}
    
    catch(...){
        cout<<"you have been logged out of your account"<<endl;// thrown whenever the account is signed out of
    }
}
Administrator::Administrator( string user_id, string password, int type)//admin constructor
{
    admin_id = user_id;
    admin_password = password;
    admin_type = type;
}
//.........END HEADER........//
//..........from Erik's functions........//

void Account::sellStocks(string name, int number)//allows the user to sell a stock if it available on the list of stocks that company trades
{
int check = 0;

	while(number <= 0)
	{
		cout << "Not a valid number of stocks" << endl << "Enter number of Stocks you would like to sell: " << endl;//error check for if the number of stocks to by is below 0

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
                //operator add to demonstate ablility to use correctly
                operator+(number*stock_price[i]);
				//balance += number*stock_price[i];
				check = 1;
			}
			else{//update stock numbers and balance
			number_shares[i] -= number;
            operator+(number*stock_price[i]);
            //balance += number*stock_price[i];
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

void Account::update_user_file()//updates the users file if stocks are brought or solid.
{
		  string filename;
		    filename = "inputfiles/accounts/" +account_id + ".txt";     /*This directory works for linux and the filesystem I'm using.
		    															  add a flag for changing it
		    															*/




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

void Account::buyStocks(string name, int number)// allows the user to buy stocks if the company is selling them at the current time
{
int check = 0;

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
            operator-(number*stock_price[i]);
            //balance -= number*stock_price[i];
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
        operator-(number*stock_price[i]);
        //balance -= number*stock_price[i];//update balance
	}

	update_user_file();//update user file
	return;
}
void Account::setstockformarketcharge(){// enables the user to set the stock for buy or sale. FOr a preset amount whenever there is an update in that file
    string stock;
    string retry;

#if COMPILER == 0
    try{
      // try block to determine is the stock is available
    cout<<"Enter the name of the stock you would like to buy or sell"<<endl;
    cin>>stock;
    this->search_forstock(stock);
        cout<<"Sorry your stock can not be found"<<endl;
        cout<<"Would you like to try again if so enter yes: "<<endl;
        cin>>retry;
    }
#endif




#if COMPILER == 1

      // try block to determine is the stock is available

    	double priceSet = 0;
    	int action = 0;
    	int number = 0;
    	cout << "Enter (1) to buy or (2) to sell: " << endl;// checks the users input if they want to buy or sell the stock when an update occurs
    	cin >> action;

    	if(action == 1)
    	{
    	    cout<<"Enter the name of the stock you would like to buy: "<<endl;
    	    cin>>stock;

    	    cout << endl << "Enter the max price that you would like to buy that stock for: " << endl;
    	    cin >> priceSet;
    	    while(priceSet <= 0)
    	    {
    	    cout << endl << "Price must be greater than 0: " << endl;

    	    cin >> priceSet;
    	    }

    	    cout << endl << "How many stocks would you like to buy at/below this price?" << endl;
    	    cin >> number;
    	    while(number <= 0){
    	    cout << endl << "Number must be greater than 0:" << endl;
    	    cin >> number;
    	    }

    	}

    	else if(action == 2)
    	{
    	    cout<<"Enter the name of the stock you would like to sell: "<<endl;
    	    cin>>stock;

    	    cout << endl << "Enter the minimum price that you would like to sell that stock for: " << endl;
    	    cin >> priceSet;
    	    while(priceSet <= 0)
    	    {
    	    cout << endl << "Price must be greater than 0: " << endl;
    	    cin >> priceSet;
    	    }

    	    cout << endl << "How many stocks would you like to sell at/above this price?" << endl;
    	    cin >> number;
    	    while(number <=0)
    	    {
    	    cout << endl << "Number must be greater than 0:" << endl;
    	    cin >> number;
    	    }

    	}
    	else
    	{
    		cout << "Invalid number entered" << endl;
    		return;
    	}

try{
    this->search_forstock(stock);// sreach to insure the stock is availabel
        cout<<"Sorry your stock can not be found"<<endl;
        return;
     //   cout<<"Would you like to try again if so enter yes: "<<endl;
      //
        cin>>retry;
    }
    
#endif




#if COMPILER == 1
catch(double price){//if the stock is available set prices parameters
//There isn't anything needed to do with this
}
	ofstream output;
	output.open("inputfiles/set_to_sell_or_buy.txt", ios::app);

    if(!output.is_open())
    {
        cerr<<"Error accessing the stock to sell or buy for a market change"<<endl;
        //This doesn't exit when there's an error. Will it need to?
    }
    // a way of getting to the end of the file will need to be implemented
        output<<account_id<<" "<<stock<<" "<<number<<" "<<priceSet<<" "<<action<<endl;

        output.close();
//bracket was here


#endif



#if COMPILER == 0
    catch( double price)         //Is using a catch when there isn't an error appropriate? Wouldn't return work better?
    {
    ofstream input;

#if COMPILER == 1
    input.open("inputfiles/set_to_sell_or_buy.txt", ios::app);
#endif




#if COMPILER == 0
    //input.open("set_to_sell_or_buy.txt");              //I'm assuming this isn't needed twice


        input.open("set_to_sell_or_buy.txt", ios::app);
#endif






        if(!input.is_open())
        {
            cerr<<"Error accessing the stock to sell or buy for a market change"<<endl;
            //This doesn't exit when there's an error. Will it need to?
        }
        // a way of getting to the end of the file will need to be implemented
            input<<account_id<<" "<<stock<<" "<<price<<endl;

            input.close();
        }
#endif
/*
#if COMPILER == 1
        cout<<"would you like to add another stock if so type yes"<<endl;
                cin>>retry;
                if(retry == "yes")
                {
                    this->setstockformarketcharge();
                }
#endif
*/




/*

#if COMPILER == 0                             //This won't work with the sleep() function
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
#endif
    */
}
void Account::search_forstock(string stock){//functions searches to insure the stock is available for the client
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
            if(stock.compare(name) == 0){//if the names equal will take in the stock
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
                input.seekg(0, ios::beg);//resets the flag for the beginning of the file. so if they go to search for another stock in runs through the entire file
                found = 0;
                cout<<"Stock was not found: "<<stock <<endl;
            }
            
}
    input.close();
    
}
void Account::readstock_price(){// reads the current price of the stock from the updated file. and shows the user there stocks current value
    
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
        cout<<"error reading in market prices"<<endl;// throws back to the menu function
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
                throw 11;
                /*Im not sure why this throw was deleted.  Other functions need to know when a stock isn't found
                 *
                 */
            }
            
            
        }
       // input.seekg(0, ios::beg);//I added this because it was only going back to the top of the file when
        //we hit the end of file, but we need to look at stocks from top to bottom each time
        found = 9;
        //input.seekg(0, ios::beg);
        
    }
        
    input.close();
    
}
void Account::read_accountinfo(){// reads in the users profilo include balance. companies they own stock in and how many shares they own
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

#if COMPILER == 1
    while( input >> name >> number)
    {
        stock_name.push_back(name);//pushes the information onto the object that was created upon login
        number_shares.push_back(number);
    }
#endif

    /*Comment in future.  This doesn't work on linux and I wouldn't
     * think it would work on Xcode either, but that needs error checked on it's own.  I added these flags so
     * they can be error checked separately, but This will be graded using linux, not Xcode.
     *
     * Note: Using eof often fails especially if there is an empty line at the end of the file
     */
#if COMPILER == 0
    while( !input.eof())
    {
        input>>name;
        input>>number;
        stock_name.push_back(name);
        number_shares.push_back(number);
    }
#endif


    input.close();
    try{
    this->readstock_price();
    }

    catch(int marketValueError)
    {
    throw 2;
    }
}

void  Account::display_profolio(){//displays the users complete profilo for there eyes when they are logged into the account
    
    int i;
    cout<<"Profolio for "<<account_id<<endl;
    cout<<"Account Balance: "<<balance<<endl;
    
    cout<<left<<setw(15)<<"Stock"<<setw(15)<<"Shares"<<setw(15)<<"Price"<<endl;
    
    for( i = 0; i <stock_name.size(); i++)
    {
      //  cout << "test1" << endl;
        cout<<left<<setw(15)<<stock_name[i]<<setw(15)<<number_shares[i]<<setw(15)<<stock_price[i]<<endl;
      //  cout<<" "<<stock_name[i]<<" "<<number_shares[i]<<endl;
    }
}
void Account::menu(){// displays the menu for the user to decide what they want to do whenever they are logged into there account
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
    catch( char prompt )//What is this doing?  Please comment.
    {
        
    }
    do{
    try{
    if( account_type == 5 )// all opitions available to the user
        {
        cout<<"Select what you would like to do"<<endl
        <<"\t1: Buy stocks: "<<endl
        <<"\t2: Sell stocks: "<<endl
        <<"\t3: Set stock to buy or sell: "<<endl
        <<"\t4: Display portfolio: "<<endl
        <<"\t5: To Exit your portfolio: "<<endl;
        
        while(!(cin >> choice)){
        			cin.clear();

        			while(cin.get() != '\n')
        				continue;

        				cout << "Invalid input.  Try again: ";
        		}

        switch( choice ){
        
            case 1: // Buy stock
            {
            	string name;
            	int number;
            	cout << "Enter name of stock to buy: " << endl;
            	cin >> name;
            	cout << "Enter the number of Stocks you would like to buy: " << endl;

            	while(!(cin >> number)){
            		cin.clear();

            		while(cin.get() != '\n')
            			continue;

            			cout << "Invalid input.  Try again: ";
            	}
            	buyStocks(name, number);
                break;
            }
            case 2: //Sell stock
            {
            	string name;
            	int number;
            	cout << "Enter name of stock to sell: " << endl;
            	cin >> name;
            	cout << "Enter the number of Stocks you would like to sell: " << endl;

            	while(!(cin >> number)){
            		cin.clear();

            		while(cin.get() != '\n')
            			continue;

            			cout << "Invalid input.  Try again: ";
            	}
            	sellStocks(name, number);
                break;
            }
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

    catch(int menuError)//throw statement from the entire try block above3
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
    
    cout<<"You are logged out"<<endl<<endl;
    
}
void Log_in::locate_account(string entered_id, string entered_password ){// when user logs in it verifies that there information matches an account located in account.txt
    int type;
    int input_error = 1;
   string user_id, password;
    ifstream input;
    char out;

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
                    input.close();
                    out = 1;
                    throw out;
                }
                if( type == 1){
                    Administrator user(user_id, password, type);//will create an admin class when type is 1
                    input.close();
                    user.menu();
                    input.close();
                    out = '1';
                    throw out;
                }
                
            }
        
        }
    }
    input.close();
        throw 1;
}
Account:: Account(string user_id, string password, int type){//account class constructor with parameters
    account_id = user_id;
    account_password = password;
    account_type = type;
    
}
void Log_in:: login(){ //login is a seperate function not tieing to any object we change to this design to allow for the program to be an endless loop. before it would treminate because the deconstuctor would be called
    string user_id; string password, space;
    int incorrect = 1;
    string exit;
    do{
       
        try
        {
            if( incorrect == 2)
        {
            cout<<"************Incorrect User ID or Password:***********"<<endl<<"try again"<<endl;
            cout<<"if you would like to exit type exit, if not hit enter  "<<endl;
            getline(cin, exit);
        }
    cout<<"****************Welcome **************"<<endl;
    cout<<"Please enter in your user id: "<<endl;
    getline(cin, user_id);
    cout<<"Please enter in your password: "<<endl;
    getline(cin, password);
    locate_account( user_id, password);//seeing if their information is there
            incorrect = 2;
        }
        
       
        
        
        catch( int no_loggin)
        {
            if(no_loggin == 1)
                cout<<"Unsuccesful login"<<endl;
            incorrect = 2;
        }
        catch(...)
        {
            getline(cin, space);
            //empty catch to bypass the other catch and so we can throw out of the locate_account
            for( int i = 0; i < 1000; i++)
            {
                cout<<endl;
            }
        }
       

    }while( exit != "exit");   //This doesn't work.  Needs error checked..
   
    return;
}
int main( int argc, char** argv){//its one short main but shows the power of C++ with objects and it is beautiful beautiful
    try{
        Log_in user;
        user.login();
    }
    
    catch( int input_error)
    {
        cout<<"Error opening the accounts file"<<endl;// should ever reach this point thus this is a safe does we would know something is wayyyy wrong with login
        
    }
    return 0;
}
