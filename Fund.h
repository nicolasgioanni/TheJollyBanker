#ifndef Fund_h
#define Fund_h
#include "Transaction.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Fund
{

public:
    // Constructors
    Fund();
    Fund(int fundID);
    ~Fund(); ///////// not sure if we need, assignment doesnt specifiy to deallocate memory

    // Actions
    bool deposit(int amount);
    bool withdraw(int amount);
    bool recordTransaction(Transaction trans);
    void printFundTransactions();
    // Function to check balance possibly

    // Getters and setters
    string getName() const; //////////////
    int getId() const;
    int getBalance() const;
    void setName(string name);

private:
    string name;
    int balance = 0;
    int fundID; //////// not sure if we need
    vector<Transaction> transactionRecord;
};

#endif /* Fund_h */
