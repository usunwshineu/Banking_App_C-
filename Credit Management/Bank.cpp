#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Bank.h"

using namespace std;

Bank::Bank() 
{
    accountNumber=generateAccountNumber();
    creditAmount=0.0;
    creditPeriod=0;
    password="";
    paid=0;
    p={};
    accountHolder="";
}

void Bank::creditRates() 
{
    cout<<endl;
    cout<<"\tCredit Rates:"<<endl;
    cout<<"\t-----------------------"<<endl;
    cout<<"\t1. 14% for 12 months"<<endl;
    cout<<"\t2. 12% for 24 months"<<endl;
    cout<<"\t3. 10% for 36 months"<<endl;
    cout<<"\t4. 8% for 48 months"<<endl;
    cout<<"\t5. 6% for longer periods"<<endl;
    cout<<"\t-----------------------"<<endl;
    if(authenticateAccount())
    {
        string accountFile=accountNumber + ".txt";
        ifstream file(accountFile);
        if(!file)
        {
            cerr<<"Error opening file "<<accountFile<<endl;
            return;
        }
        else
        {
            string line;
            for(int i=0;i<5;i++)
            {
                getline(file,line);
                if(i==2)
                    creditPeriod=stoi(line);
                if(i==3)
                    creditAmount=stoi(line);
            }
            double rate=creditAmount/(creditPeriod*12);
            double a;
            char *procent=new char;

            cout<<"\tCredit Rates for your account: "<<endl;
            cout<<endl<<"\t--------------------------------------------------"<<endl;
            cout<<"\tMonth \tRate \tRate without interest \tInterest "<<endl;
            for(int i=1;i<=creditPeriod*12;i++)
            {
                cout<<"\t--------------------------------------------------"<<endl;
                if(i<=12)
                    {a=rate+rate*14/100;
                    procent="14%";}
                if(i>12 && i<=24)
                    {a=rate+rate*12/100;
                    procent="12%";}
                if(i>24 && i<=36)
                    {a=rate+rate*10/100;
                    procent="10%";}
                if(i>36 && i<=48)
                    {a=rate+rate*8/100;
                    procent="8%";}
                if(i>48)
                    {a=rate+rate*6/100;
                    procent="6%";}
                cout<<"\t"<<i<<"\t"<<a<<"\t\t"<<rate<<"\t\t\t"<<procent<<endl;
            }
            cout<<"\t--------------------------------------------------"<<endl;
            delete [] procent;
        }
    }
    cin.ignore();
}

void Bank::makePayment() 
{
    if(authenticateAccount())
    {
        string accountFile=accountNumber+".txt";
        ifstream file(accountFile);
        if (!file)
        {
            cerr<<"Error opening file."<<endl;
            return;
        }
        else
        {
            string line;
            for(int i=0;i<5;i++)
            {
                getline(file,line);
                if(i==3)
                    creditAmount=stoi(line);
            }
            cout<<"Select amount: "<<endl;
            cin>>p.amount;
            if(p.amount<=creditAmount)
            {
                p.k++;
                paid+=p.amount;
                p.history[p.k]=p.amount;
                cout<<"Payment registered!"<<endl;
            }
            else
                cout<<"Cannot choose an amount bigger than your credit";
        }
    }
    cin.ignore();
}

void Bank::checkPaymentHistory() 
{
    if(authenticateAccount())
    {
        string accountFile=accountNumber + ".txt";
        ifstream file(accountFile);
        if(!file)
        {
            cerr<<"Error opening file."<<endl;
            return;
        }
        else
        {
            string line;
            for(int i=0;i<5;i++)
            {
                getline(file,line);
                if(i==3)
                    creditAmount=stoi(line);
            }
            double balance=creditAmount;
            cout<<"\tmonth\tamount\tbalance\n";
            cout<<"\t------------------------\n";
            for(int i=1;i<=p.k;i++)
            {
                balance-=p.history[i];
                cout<<"\t"<<i<<"\t"<<p.history[i]<<"\t"<<balance<<endl;
                cout<<"\t------------------------\n";
            }
        }
    }
    cin.ignore();
}

void Bank::refinanceLoan() 
{
    if(authenticateAccount())
    {
        string accountFile=accountNumber+".txt";
        ifstream file(accountFile);
        if(!file)
        {
            cerr<<"Error opening file."<<endl;
            return;
        }
        else
        {
            string line;
            for(int i=0;i<5;i++)
            {
                getline(file,line);
                if(i==2)
                    creditPeriod=stoi(line);
                if(i==3)
                    creditAmount=stoi(line);
            }
            int ch;
            cout<<"\tChange: 1.ammount\t 2.period \t3.exit "<<endl;
            cin>>ch;
            if(ch!=3)
            {
                switch(ch)
                {
                    case 1:
                        sumCredit-=creditAmount;
                        cout<<"Introduce the new ammount: "<<endl;
                        cin>>creditAmount;
                        sumCredit+=creditAmount;
                        break;
                    case 2:
                        sumPeriod-=creditPeriod;
                        cout<<"Introduce the new period: "<<endl;
                        cin>>creditPeriod;
                        sumPeriod+=creditPeriod;
                        break;
                    default:
                        cout<<"Invalid Option! Exiting!"<<endl;
                        break;
                }
            }
            cout<<"Successful refinancing"<<endl;
        }
    }
    cin.ignore();
}

void Bank::Statistics() 
{
    int count=0;
    string line;
    ifstream file("clients.txt");
    if(!file)
    {
        cerr<<"Error opening file."<<endl;
        return;
    }
    while(getline(file, line))
    {
        ++count;
    }
    file.close();
    cout<<"\tNumber of clients: "<<count<<endl;
    cout<<"\tCredit Amount given so far: "<<sumCredit<<endl;
    cout<<"\tAverage Credit Amount per client: "<<static_cast<double>(sumCredit)/count<<endl;
    cout<<"\tAverage Credit Period per client: "<<static_cast<double>(sumPeriod)/count<<endl;
    cout<<"\tAverage Credit Amount per account: "<<static_cast<double>(sumCredit)/totalAccounts<<endl;
    cout<<"\tAverage Credit Period per account: "<<static_cast<double>(sumPeriod)/totalAccounts<<endl;
    cin.ignore();
}

string Bank::generateAccountNumber() 
{
        srand(time(nullptr));
        int randomNumber=rand() % 1000 + 1000;
        return "NPB" + to_string(randomNumber);
}

string Bank::getAccNo()
{
    return accountNumber;
}

double Bank::getCreAmount()
{
    return creditAmount;
}

int Bank::getCrePeriod()
{
    return creditPeriod;
}

string Bank::getPass()
{
    return password;
}

bool Bank::authenticateAccount() 
{
    cout<<"Enter account number: ";
    cin.ignore();
    getline(cin, accountNumber);

    cout<<"Enter password: ";
    getline(cin, password);

    string filename=accountNumber + ".txt";
    ifstream file(filename);
    if(file.is_open())
    {
        string line;
        while(getline(file, line))
            if(line==password) 
            {
                file.close();
                return 1;
            }
        file.close();
    }
    cout<<"Account doesn't exist or password is incorrect!";
    return 0;
}

void Bank::setPass(const string& newPass)
{
    password=newPass;
}

double Bank::getPaid()
{
    return paid;
}

double Bank::setCreAmount()
{
    double newAmount;
    cin>>newAmount;
    creditAmount=newAmount;
    return creditAmount;
}

int Bank::setCrePeriod()
{
    int newPeriod;
    cin>>newPeriod;
    creditPeriod=newPeriod;
    return creditPeriod;
}

string Bank::setAccNo(string line)
{
    accountNumber=line;
    return accountNumber;
}

double Bank::setPaid(double n)
{
    paid=n;
    return paid;
}

double Bank::fileCreAmount(double n)
{
    creditAmount=n;
    return creditAmount;
}

int Bank::fileCrePeriod(int n)
{
    creditPeriod=n;
    return creditPeriod;
}
string Bank::setaccountHolder(string name)
{
    accountHolder=name;
    return accountHolder;
}
string Bank::getaccountHolder()
{
    return accountHolder;
}