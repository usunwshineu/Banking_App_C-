#pragma once
#include <string>
#include <iostream>
using namespace std;

double sumCredit;
int sumPeriod;
int totalAccounts=0;

struct Payment
{
    double amount;
    int k=0;
    double *history= new double;
};

class Bank
{
    private:
        string accountNumber;
        double creditAmount;
        int creditPeriod;
        string password;
        double paid;
        Payment p;
        string accountHolder;
    public:
        Bank();
        void creditRates();
        void makePayment();
        void checkPaymentHistory();
        void refinanceLoan();
        string generateAccountNumber();
        bool authenticateAccount();
        void Statistics();
        string getAccNo();
        double getCreAmount();
        int getCrePeriod();
        string getPass();
        void setPass(const string& newPass);
        double getPaid();
        double setCreAmount();
        int setCrePeriod();
        string setAccNo(string line);
        double setPaid(double n);
        double fileCreAmount(double n);
        int fileCrePeriod(int n);
        string setaccountHolder(string name);
        string getaccountHolder();
};