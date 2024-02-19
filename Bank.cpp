#include <stdio.h>

#include "Bank.h"
#include "Transaction.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>

Bank::Bank()
{
}

Bank::~Bank()
{
}
bool Bank::ReadTransactions(string FileName)
{

  ifstream inFile;
  inFile.open(FileName);
  string transactionString;
  if (inFile.is_open())
  {
    while (!inFile.eof())
    {
      getline(inFile, transactionString);
      // this would be end of the file
      if (transactionString.empty())
      {
        return false;
      }
      istringstream readline(transactionString);
      char identifier;
      readline >> identifier;

      if (identifier == 'D')
      {
        int accNum;
        int fundID;
        int amount;
        readline >> accNum >> amount;
        fundID = accNum % 10;
        accNum = accNum / 10;
        Transaction transaction(identifier, accNum, fundID, amount);
        transList.push(transaction);
      }
      else if (identifier == 'W')
      {
        int accNum;
        int fundID;
        int amount;
        readline >> accNum >> amount;
        fundID = accNum % 10;
        accNum = accNum / 10;
        Transaction transaction(identifier, accNum, fundID, amount);
        transList.push(transaction);
      }
      else if (identifier == 'T')
      {
        int accNum;
        int fundID;
        int amount;
        int transAccNum;
        int transFundID;

        readline >> accNum >> amount >> transAccNum;

        fundID = accNum % 10;
        accNum = accNum / 10;
        transFundID = transAccNum % 10;
        transAccNum = transAccNum / 10;
        Transaction transaction(identifier, accNum, fundID, amount, transAccNum, transFundID);
        transList.push(transaction);
      }
      else if (identifier == 'H')
      {
        int accNum;
        readline >> accNum;
        Transaction transaction(identifier, accNum);
        transList.push(transaction);
      }
      else if (identifier == 'O')
      {
        string firstName;
        string lastName;
        int accNum;
        readline >> firstName >> lastName >> accNum;
        Transaction transaction(identifier, firstName, lastName, accNum);
        transList.push(transaction);
      }
      else
      {
        cout << "ERROR" << endl;
      }
    }
    inFile.close();
    return true;
  }
  else
  {
    cout << "ERROR: The file could not be opened" << endl;
    return false;
  }
}

void Bank::ExecuteTransactions()
{

  while (!transList.empty())
  {

    Transaction firstTrans = transList.front();
    if (firstTrans.getIdentifier() == 'O')
    {
      Account *account = new Account(firstTrans.getFirstName(), firstTrans.getLastName(), firstTrans.getAccNum());
      cout << firstTrans.getFirstName() << " " << firstTrans.getLastName() << " " << firstTrans.getAccNum() << endl;
      accountList.Insert(account);
    }
    else if (firstTrans.getIdentifier() == 'W')
    {

      Account *account;
      if (accountList.Retrieve(firstTrans.getAccNum(), account))
      {
        account->removeFunds(firstTrans.getFundID(), firstTrans.getAmount());
      }
    }
    else if (firstTrans.getIdentifier() == 'D')
    {
      Account *account;
      if (accountList.Retrieve(firstTrans.getAccNum(), account))
      {
        account->addFunds(firstTrans.getFundID(), firstTrans.getAmount());
      }
    }
    else if (firstTrans.getIdentifier() == 'H')
    {
      if (firstTrans.getAccNum() >= 10000 && firstTrans.getAccNum() <= 99999)
      {

        Account *account;
        int numID = firstTrans.getAccNum() % 10;
        int numAcc = firstTrans.getAccNum() / 10;
        if (accountList.Retrieve(numAcc, account))
        {
          account->printFundHistory(numID);
        }
      }
      else
      {

        Account *account;
        if (accountList.Retrieve(firstTrans.getAccNum(), account))
        {

          account->printAllHistory();
        }
      }
    }
    else if (firstTrans.getIdentifier() == 'T')
    {
      Account *acc1;
      Account *acc2 ;

      if (accountList.Retrieve(firstTrans.getAccNum(), acc2) && accountList.Retrieve(firstTrans.getTransAccNum(), acc1))
      {
         

        if (acc2->transferRemove(firstTrans.getFundID(), firstTrans.getAmount()))
        {
          acc1->transferAdd(firstTrans.getTransFundID(), firstTrans.getAmount());
            
            acc2->recordTrans(firstTrans, firstTrans.getFundID());
            acc1->recordTrans(firstTrans, firstTrans.getTransFundID());
        }
      }
    }
    transList.pop();
  }
  return;
}

void Bank::DisplayTransactions()
{
  cout << endl;
  
  cout << "Here are all the open accounts with their balances:" << endl;
  accountList.Display();
}
