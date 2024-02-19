#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "BSTree.h"
#include "Transaction.h"
using namespace std;

class Bank
{
public:
    // constructor
    Bank();
    ~Bank();

    // this method reads from the file and adds transaction to the queue.
    bool ReadTransactions(string FileName);
    void ExecuteTransactions();
    void DisplayTransactions();

private:
    // BinarySearchTree List of Accounts
    BSTree accountList;

    // Transactions List to act as queue
    queue<Transaction> transList;
};
