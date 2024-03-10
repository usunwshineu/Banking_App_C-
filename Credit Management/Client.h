#pragma once
#include "Bank.h"
#include <cstring>
#include <iostream>

using namespace std;

class Client 
{
    private:
        Bank bank;
        int numAccounts;
        string name;
    public:
        Client(const string& clientName);
        void saveClientToFile();
        bool checkClientExists();
        void deleteAccount();
        void createAccount();
        void viewAccount();
        void displayMenu();
        void runProgramm();
        friend class Bank;
};