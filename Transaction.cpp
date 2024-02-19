#include <stdio.h>

#include "Transaction.h"

Transaction::Transaction(char identifier, int accNum, int fundID)
{
  this->identifier = identifier;
  this->accNum = accNum;
  this->fundID = fundID;
}

Transaction::Transaction(char identifier, string firstName, string lastName,
                         int accNum)
{
  this->identifier = identifier;
  this->firstName = firstName;
  this->lastName = lastName;
  this->accNum = accNum;
}

Transaction::Transaction(char identifier, int accNum, int fundID, int amount,
                         int transAccNum, int transFundID)
{
  this->identifier = identifier;
  this->accNum = accNum;
  this->fundID = fundID;
  this->amount = amount;
  this->transAccNum = transAccNum;
  this->transFundID = transFundID;
}

Transaction::Transaction(char identifier, int accNum)
{
  this->identifier = identifier;
  this->accNum = accNum;
}

Transaction::Transaction(char identifier, int accNum, int fundID, int amount)
{
  this->identifier = identifier;
  this->accNum = accNum;
  this->fundID = fundID;
  this->amount = amount;
}

Transaction::Transaction(char identifier, int accNum, int fundID, int amount,
                         int transAccNum, int transFundID,
                         bool validTransaction)
{
  this->identifier = identifier;
  this->accNum = accNum;
  this->fundID = fundID;
  this->amount = amount;
  this->transAccNum = transAccNum;
  this->transFundID = transFundID;
  this->validTransaction = validTransaction;
}

Transaction::Transaction(char identifier, int accNum, int fundID, int amount,
                         bool validTransaction)
{
  this->identifier = identifier;
  this->accNum = accNum;
  this->fundID = fundID;
  this->amount = amount;
  this->validTransaction = validTransaction;
}

bool Transaction::checkValidTransaction() const
{
  if (validTransaction == false)
  {
    return false;
  }
  else
  {
    return true;
  }
}

char Transaction::getIdentifier() const { return identifier; }

string Transaction::getFirstName() const { return firstName; }

string Transaction::getLastName() const { return lastName; }

int Transaction::getAccNum() const { return accNum; }

int Transaction::getFundID() const { return fundID; }

int Transaction::getAmount() const { return amount; }

int Transaction::getTransAccNum() const { return transAccNum; }

int Transaction::getTransFundID() const { return transFundID; }

ostream &operator<<(ostream &out, const Transaction &trans)
{

  if (trans.checkValidTransaction())
  {
    if (trans.getIdentifier() == 'T')
    {
        
      out << " " << trans.getIdentifier() << " " << trans.getAccNum()
          << trans.getFundID() << " " << trans.getAmount() << " "
          << trans.getTransAccNum() << trans.getTransFundID();
    }
    else if (trans.getIdentifier() == 'W' || trans.getIdentifier() == 'D')
    {
      out << " " << trans.getIdentifier() << " " << trans.getAccNum()
          << trans.getFundID() << " " << trans.getAmount();
    }
    else
    {
      // Do nothing
    }
  }
  else
  {
    if (trans.getIdentifier() == 'T')
    {
      out << " " << trans.getIdentifier() << " " << trans.getAccNum()
          << trans.getFundID() << " " << trans.getAmount() << " "
          << trans.getTransAccNum() << trans.getTransFundID() << " (Failed)";
    }
    else if (trans.getIdentifier() == 'W' || trans.getIdentifier() == 'D')
    {
      out << " " << trans.getIdentifier() << " " << trans.getAccNum()
          << trans.getFundID() << " " << trans.getAmount() << " (Failed)";
    }
  }
  return out;
}

