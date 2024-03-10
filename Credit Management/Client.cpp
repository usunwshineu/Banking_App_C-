#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <windows.h>
#include "Client.h"
#include "Bank.h"

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

 
Client::Client(const string& clientName)
{
    name=clientName;
    numAccounts=0;
}

void Client::saveClientToFile() 
{
    ofstream file("clients.txt", ios::app);
    if(!file) 
	{
        cerr<<"Error opening file."<<endl;
        return;
    }
    file<<name<<endl;
    file.close();
}

bool Client::checkClientExists() 
{
    ifstream file("clients.txt");
    if(!file) 
	{
        cerr<<"Error opening file."<<endl;
        return false;
    }

    string line;
    while (getline(file, line)) 
	{
        if(line==name) 
		{
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void Client::deleteAccount()
{
    if(bank.authenticateAccount())
    {
        if(bank.getPaid()!=bank.getCreAmount())
            cout<<"Cannot delete an account with unpaid credit"<<endl;
        else
        {
            string filename=bank.getAccNo() + ".txt";
            if(remove(filename.c_str())!=0)
            {
                cerr<<"Error deleting account! Please try again!"<<endl;
                return;
            } 
            else 
            {
                numAccounts--;
                totalAccounts--;
                cout<<"Account deleted!"<<endl;
            }
        }
    }
    cin.ignore();
}

void Client::createAccount()
{
    cout<<"Creating a new account..."<<endl;

    cout<<"You account number is: "<<bank.getAccNo()<<endl;

    cout<<"Set a password: ";
    cin.ignore();
    string tempPass;
    getline(cin, tempPass);
    bank.setPass(tempPass);

    cout<<"Enter credit amount: ";
    bank.setCreAmount();
    sumCredit+=bank.getCreAmount();

    cout<<"Enter credit period(in years): ";
    bank.setCrePeriod();
    sumPeriod+=bank.getCrePeriod();

    string filename=bank.getAccNo() + ".txt";

    ofstream accountFile(filename, ios::app);
    if(!accountFile) 
    {
        cerr<<"Error opening file."<<endl;
        return;
    }
    accountFile<<bank.getAccNo()<<endl<<bank.getPass()<<endl<<bank.getCrePeriod()<<endl<<bank.getCreAmount()<<endl<<bank.getPaid()<<endl<<name;
    accountFile.close();

    cout<<"Account created successfully!"<<endl;
    numAccounts++;
    totalAccounts++;
    cin.ignore();
}

void Client::viewAccount()
{
    if(bank.authenticateAccount())
    {
        string accountFile=bank.getAccNo()+".txt";
        ifstream file(accountFile);
        if(!file)
            cerr<<"Error opening file."<<endl;
        else
        {
            string line;
            for(int i=0;i<5;i++)
            {
                getline(file,line);
                if(i==0)
                    bank.setAccNo(line);
                if(i==1)
                    bank.setPass(line);   
                if(i==2)
                    bank.fileCrePeriod(stoi(line));
                if(i==3)
                    bank.fileCreAmount(stoi(line));
                if(i==4)
                    bank.setPaid(stoi(line));
                if(i==5)
                    bank.setaccountHolder(line);
            }
            cout<<endl<<"\tAccount Holder \tAccount Number \tCredit Amount \tCredit Period \tCredit Paid \tBalance "<<endl;
            cout<<"\t-----------------------------------------------------------------------------------"<<endl;
            cout<<"\t"<<bank.getaccountHolder()<<"\t"<<bank.getAccNo()<<"\t\t"<<bank.getCreAmount()<<"\t"<<bank.getCrePeriod()<<" years\t\t"<<bank.getPaid()<<"\t\t"<<bank.getCreAmount()-bank.getPaid();
            cout<<"\n\n";
        }
    }
    cin.ignore();
}

void Client::displayMenu() 
{
    char choice;

    while(choice!=9) 
    {
        cout<<endl;
        SetConsoleTextAttribute(console, 0x71);
        cout<<"\t\t.----------------------------------------------------."<<endl;
        cout<<"\t\t|Welcome to Nasta Pasta's Credit Account Management\t|"<<endl;
        cout<<"\t\t.----------------------------------------------------."<<endl;
        cout<<endl;
        SetConsoleTextAttribute(console, 1);
        cout<<"\t--- Main Menu ---"<<endl;
        SetConsoleTextAttribute(console, 2);
        cout<<"\t1. Create Account"<<endl;
        SetConsoleTextAttribute(console, 3);
        cout<<"\t2. Delete Account"<<endl;
        SetConsoleTextAttribute(console, 4);
        cout<<"\t3. Credit Rates"<<endl;
        SetConsoleTextAttribute(console, 5);
        cout<<"\t4. Make a Payment"<<endl;
        SetConsoleTextAttribute(console, 6);
        cout<<"\t5. Check Payment History"<<endl;
        SetConsoleTextAttribute(console,11);
        cout<<"\t6. View Account"<<endl;
        SetConsoleTextAttribute(console, 8);
        cout<<"\t7. Refinance Loan"<<endl;
        SetConsoleTextAttribute(console, 9);
        cout<<"\t8. Statistics"<<endl;
        SetConsoleTextAttribute(console,10);
        cout<<"\t9. Exit"<<endl;
        SetConsoleTextAttribute(console, 7);
        cout<<endl;
        cout<<"Enter your choice (1-9): ";
        cin>>choice;

        switch(choice)
        {
            case '1':
                cout<<"Create Account"<<endl;
                createAccount();
                break;
            case '2':
                cout<<"Delete Account"<<endl;
                deleteAccount();
                break;
            case '3':
                cout<<"Credit Rates"<<endl;
                bank.creditRates();
                break;
            case '4':
                cout<<"Make a Payment"<<endl;
                bank.makePayment();
                break;
            case '5':
                cout<<"Check Payment History"<<endl;
                bank.checkPaymentHistory();
                break;
            case '6':
                cout<<"View Account"<<endl;
                viewAccount();
                break;
            case '7':
                cout<<"Refinance Loan"<<endl;
                bank.refinanceLoan();
                break;
            case '8':
                cout<<"Check Bank Information"<<endl;
                bank.Statistics();
                break;
            case '9':
                cout<<"Exiting the program. Goodbye!"<<endl;
                return;
                runProgramm();
            default:
                cout<<"Invalid choice. Please try again."<<endl;
                break;
            }
        }
}

void Client::runProgramm() 
{
    cout<<"Enter your name: ";
    getline(cin, name);

    if(!checkClientExists()) 
	{
        cout<<"Client does not exist. Saving Client Information"<<endl;
        saveClientToFile();
    }

    displayMenu();
}