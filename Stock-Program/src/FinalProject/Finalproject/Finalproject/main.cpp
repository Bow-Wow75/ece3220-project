//
//  main.cpp
//  Finalproject
//
//  Created by Nicholas Bouckaert on 11/9/17.
//  Copyright © 2017 Nicholas Bouckaert. All rights reserved.
//

#define ACCOUNTS "accounts.txt"

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
string input_file = "accounts.txt";// stores the list of accounts for the program and there passwords

class Account{
    protected:
        string account_id;
        string account_password;
        int account_type;// 1 is admin, 5 is user
    
    public:
        Account();
        ~Account();
        void login();
        void locate_account(string entered_id, string entered_password );
        void menu();
    
    
    
    
};
Account::Account(){
    
}

Account::~Account(){
    
}
void Account::menu(){
    //User function
    int choice;
    if( account_type == 5 )
    {
        cout<<"Select what you would like to do"<<endl
        <<"\t1: Buy stocks: "<<endl
        <<"\t2: Sell stocks: "<<endl
        <<"\t3: Set stock to buy or sell"<<endl
        <<"\t4: Display profolio"<<endl
        <<"\t5: to exit your profolio"<<endl;
        cin>>choice;
        
        switch( choice ){
        
            case 1: // Buy stock
                break;
            case 2: //Sell stock
                break;
            case 3: // set stock to buy or sell
                break;
            case 4:// display profolio
                break;
            case 5:// implement a throw to exit the program
                break; 
                
                
        }
    }
     //Adminstor functions
    if( account_type == 1)
    {
        
        
        
    }
    
}

void Account:: locate_account(string entered_id, string entered_password ){
    int type;
    int input_error = 0;
   string user_id, password;
    ifstream input;
    input.open(input_file);
    if( !input.is_open())
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
                cout<<"successful login"<<endl;
                return;
            }
        }
    }
    
    
}
void Account::login(){
    string user_id; string password;
    cout<<"Please enter in your user id: "<<endl;
    getline(cin, user_id);
    cout<<"Please enter in your password: "<<endl;
    getline(cin, password);
    
    this->locate_account( user_id ,password);
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
