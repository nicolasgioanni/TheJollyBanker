#include "Account.h"
#include <stdio.h>

#include "Fund.h"

using namespace std;

Account::Account() {}

Account::~Account() {}
Account::Account(string firstName, string lastName, int accNum)
{

  this->firstName = firstName;
  this->lastName = lastName;
  this->accNum = accNum;

  string fundType[] = {"Money Market", "Prime Money Market",
                       "Long-Term Bond", "Short-Term Bond",
                       "500 Index Fund", "Capital Value Fund",
                       "Growth Equity Fund", "Growth Index Fund",
                       "Value Fund", "Value Stock Index"};

  for (int i = 0; i < MAX_FUNDS; i++)
  {

    fundList[i].setName(fundType[i]);
  }
}

bool Account::addFunds(int fundID, int amount)
{

  if (fundID >= MAX_FUNDS || fundID < 0)
  {

    cerr << "FundID " << fundID << " doesn't exist." << endl;
    return false;
  }
  fundList[fundID].deposit(amount);
  Transaction trans('D', accNum, fundID, amount);
  fundList[fundID].recordTransaction(trans);
  transactionRecords.push_back(trans);
  return true;
};

bool Account::transferAdd(int fundID, int amount)
{

  if (fundID >= MAX_FUNDS || fundID < 0)
  {

    cerr << "FundID " << fundID << " doesn't exist." << endl;
    return false;
  }
  fundList[fundID].deposit(amount);
 
  return true;
};

bool Account::transferRemove(int fundID, int amount)
{
    
    if (fundID >= MAX_FUNDS || fundID < 0)
    {
        
        cerr << "FundID " << fundID << " doesn't exist." << endl;
        return false;
    }
    
    if (amount <= fundList[fundID].getBalance())
    {
        
        
        fundList[fundID].withdraw(amount);
       
    }
    return true;
}


void Account:: recordTrans(Transaction t, int fundID){
    
    fundList[fundID].recordTransaction(t);
    
}




//bool Account:: transfer(Account acc1, Account acc2, int fundID, int transFundID, int amount){
//    if(acc1.fundList[fundID].getBalance() >= amount)
//     {
//        
//        acc1.fundList[fundID].withdraw(amount);
//        acc2.fundList[transFundID].deposit(amount);
//        
//         Transaction t ('T', acc1.getAccNum(), fundID, amount, acc2.getAccNum(), transFundID, true);
//         fundList[fundID].recordTransaction(t);
//         transactionRecords.push_back(t);
//         return true;
//     }
//    Transaction t ('T', acc1.getAccNum(), fundID, amount, acc2.getAccNum(), transFundID, false);
//    fundList[fundID].recordTransaction(t);
//    transactionRecords.push_back(t);
//    return false;
//}

bool Account::removeFunds(int fundID, int amount)
{

  if (fundID >= MAX_FUNDS || fundID < 0)
  {

    cerr << "FundID " << fundID << " doesn't exist." << endl;
    return false;
  }

  if (amount <= fundList[fundID].getBalance())
  {

    Transaction trans('W', accNum, fundID, amount);
    fundList[fundID].withdraw(amount);
    fundList[fundID].recordTransaction(trans);
    transactionRecords.push_back(trans);
    return true;
  }
    


  // For money market, withdraw from money market + prime money market
  else if (fundID == 0 &&
           (amount <= fundList[0].getBalance() + fundList[1].getBalance()))
  {
    return withdrawFromJointFunds(fundID, fundList[1].getId(), amount);
  }

  // For prime money market, withdraw from prime money market + money market
  else if (fundID == 1 &&
           (amount <= fundList[1].getBalance() + fundList[0].getBalance()))
  {
    return withdrawFromJointFunds(fundID, fundList[0].getId(), amount);
  }

  // For Long-Term Bond, withdraw from Long-Term Bond + Short-Term Bond
  else if (fundID == 2 &&
           (amount <= fundList[2].getBalance() + fundList[3].getBalance()))
  {
    return withdrawFromJointFunds(fundID, fundList[3].getId(), amount);
  }

  // For Short-Term Bond, withdraw from Short-Term Bond + Long-Term Bond
  else if (fundID == 3 &&
           (amount <= fundList[3].getBalance() + fundList[2].getBalance()))
  {
    return withdrawFromJointFunds(fundID, fundList[2].getId(), amount);
  }

  else
  {
    error(firstName, lastName, fundID, amount);

    return false;
  }
};

bool Account::withdrawFromJointFunds(int fundIDX, int fundIDY, int amount)
{

  int withdrawAmount = amount;                             // the amount user wants to withdraw from fund
  int initialFundBalance = fundList[fundIDX].getBalance(); // the amount balance the user has in the fund
  withdrawAmount = withdrawAmount - initialFundBalance;    // insufficent amount that needs to borrowed from joint fund

  fundList[fundIDX].withdraw(initialFundBalance);                     // user balance is withdrawn
  Transaction transaction1('W', accNum, fundIDX, initialFundBalance); // transaction recorder
  transactionRecords.push_back(transaction1);                         // recorded transaction pushed to list of transaction records
  fundList[fundIDX].recordTransaction(transaction1);                  // transaction recorded for specific fund type

  fundList[fundIDY].withdraw(withdrawAmount);                     // the remaining insufficent anount is withdraen
  Transaction transaction2('W', accNum, fundIDY, withdrawAmount); // transaction recorder
  transactionRecords.push_back(transaction2);                     // recorded transaction pushed to list of transaction records
  fundList[fundIDY].recordTransaction(transaction2);              // transaction recorded for specific fund type

  return true;
};

void Account::error(string firstName, string lastName, int fundID, int amount)
{

  cerr << "ERROR: "<<lastName << ", " << firstName << " has insufficient balance of "
       << "$" << amount << " to withdraw from " << fundList[fundID].getName()  << endl;
  Transaction transaction('W', accNum, fundID, amount, false);
  fundList[fundID].recordTransaction(transaction);
  transactionRecords.push_back(transaction);
}

// gets the account number of of the customer
int Account::getAccNum() const
{

  return accNum;
}

// gets the balance of specific fund type
int Account::getBalance(int fundID) const
{
  return fundList[fundID].getBalance();
}

string Account::getFirstName() const
{

  return firstName;
}

string Account::getLastName() const
{

  return lastName;
}

vector<Transaction> Account::getTransactionRecords() const
{
  return transactionRecords;
}

string Account::getFundName(int fundID) const
{

  return fundList[fundID].getName();
}

void Account::printFundHistory(int fundID)
{

  cout << "Transaction history for " << lastName << ", " << firstName << " "<<getFundName(fundID) <<": "<<getBalance(fundID)<< endl;
  fundList[fundID].printFundTransactions();
}

ostream &operator<<(ostream &out, Account &account)
{

  out << account.getLastName() << "" << account.getFirstName() << " Account: " << account.getAccNum() << endl;

  for (int i = 0; i < Account::MAX_FUNDS; i++)
  {
    out << account.fundList[i].getName() << ": $" << account.fundList[i].getBalance() << endl;
  }
  return out;
}

void Account::printAllHistory()
{

    cout<<" Transaction history for "<< lastName<<", "<<firstName<<" "<<"By Fund."<<endl;
  for (int i = 0; i < MAX_FUNDS; i++)
  {
     
      fundList[i].printFundTransactions();
  }
}

bool Account::operator==(Account &account)
{
  return(accNum == account.getAccNum());
}

bool Account::operator<(Account &account)
{
  return(accNum < account.getAccNum());
}

bool Account::operator>(Account &account)
{
  return(accNum > account.getAccNum());
}


