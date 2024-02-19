#ifndef Transaction_h
#define Transaction_h

#pragma once
#include <iostream>

using namespace std;

class Transaction
{

public:
    // Constructors
    Transaction();
    Transaction(char identifier, int accNum, int fundID);
    Transaction(char identifier, string firstName, string lastName, int accNum);
    Transaction(char identifier, int accNum, int fundID, int amount, int transAccNum, int transFundID);
    Transaction(char identifier, int accNum);
    Transaction(char identifier, int accNum, int fundID, int amount);
    Transaction(char identifier, int accNum, int fundID, int amount, int transAccNum, int transFundID, bool validTransaction);
    Transaction(char identifier, int accNum, int fundID, int amount, bool validTransaction);

    // Actions
    bool checkValidTransaction() const;

    // Getters
    char getIdentifier() const;
    string getFirstName() const;
    string getLastName() const;
    int getAccNum() const;
    int getFundID() const;
    int getAmount() const; ////////////////////
    int getTransAccNum() const;
    int getTransFundID() const;

    // Overloading operator
    friend ostream &operator<<(ostream &out, const Transaction &trans); ///// const

private:
    char identifier;
    string firstName;
    string lastName;
    int accNum;
    int fundID;
    int amount;
    int transAccNum;
    int transFundID;
    bool validTransaction = true;
};
#endif /* Transaction_h */
