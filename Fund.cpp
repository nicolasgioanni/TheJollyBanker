#include <stdio.h>

#include <iostream>
#include <ostream>

#include "Fund.h"

Fund::Fund()
{
    balance = 0;
}

Fund::Fund(int fundID)
{
    balance = 0;
    this->fundID = fundID;
}
Fund::~Fund()
{
}

bool Fund::deposit(int amount)
{
    balance += amount;
    return true;
}

bool Fund::withdraw(int amount)
{
    balance -= amount;
    return true;
}

bool Fund::recordTransaction(Transaction trans)
{
    transactionRecord.push_back(trans);
    return true;
}

void Fund::printFundTransactions()
{
    cout<<getName()<<": $"<<getBalance()<<endl;
    for (int i = 0; i < transactionRecord.size(); i++)
    {
        
        cout << transactionRecord[i]<<endl;
    }
}

string Fund::getName() const
{
    return name;
}

int Fund::getId() const
{
    return fundID;
}

int Fund::getBalance() const
{
    return balance;
}

void Fund::setName(string name)
{
    this->name = name;
}
