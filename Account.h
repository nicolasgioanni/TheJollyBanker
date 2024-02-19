#ifndef Account_h
#define Account_h

#include "Fund.h"
#include "Transaction.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Account
{

  static const int MAX_FUNDS = 10;

public:
  Account();
  ~Account();
  Account(string firstName, string lastName, int accNum);

  // access fund with fundID and add amount
  bool addFunds(int fundID, int amount);

  // access fund with fundID and remove amount
  bool removeFunds(int fundID, int amount);

//    bool add(int fundID, int amount);
//    bool remove(int fundID, int amount);
//    bool recordTransaction(char identifier, int accNum, int fundID, int amount, int transAccNum, int transFundID, bool validTransaction);
  // if transfer is not possible between funds
  //  return false
  // transfer amount from fundID to transFundID
  bool transferFunds(int fundID, int transFundID, int amount);
   
    
    bool transferRemove(int fundID, int amount);
    bool transferAdd(int fundID, int amount);
    
    void recordTrans(Transaction t, int fundID);
bool transfer(Account acc1, Account acc2, int fundID, int transFundID, int amount);


  // transfer amount for joint funds
  bool withdrawFromJointFunds(int fundIDX, int fundIDY, int amount);

  // prints fund history
  void printFundHistory(int fundID);

  // print entire account transaction history
  void printAllHistory();

  // if an error occurs don't allow the transaction and record it
  void error(string firstName, string lastName, int fundID, int amount);

  // Setter
  void setFundBalance(int fundID);

  // Getters
  int getAccNum() const;
  int getBalance(int fundID) const;
  string getFirstName() const;
  string getLastName() const;
  string getFundName(int fundID) const;
  vector<Transaction> getTransactionRecords() const;

  friend ostream &operator<<(ostream &out, Account &account);

  bool operator==(Account &list);
  bool operator<(Account &list);
  bool operator>(Account &list);


private:
  string firstName;
  string lastName;
  int accNum;
  Fund fundList[MAX_FUNDS];
  vector<Transaction> transactionRecords;
};

#endif /* Account_h */
