#include <stdio.h>

#include "BSTree.h"
#include <iostream>
using namespace std;

BSTree::BSTree()
{
    root = nullptr;
}

BSTree::~BSTree()
{
    Empty();
}

bool BSTree::Insert(Account* insert)
{
    
    if (insert->getAccNum() < 1000 || insert->getAccNum() > 9999)
    {
        cerr << "ERROR: Account number not valid" << endl;
        return false;
    }

    if (root == NULL)
    {
        root = new Node;
        root->pAcct = insert;
        root->left = NULL;
        root->right = NULL;
        return true;
    }
    else
    {
        Node* temp = root;
        RecursiveInsert(temp, insert);
    }
    return false;
}

bool BSTree::Retrieve(const int& accID, Account*& account) const
{
    Node* temp = root;
    bool search = false;

    while (!search)
    {
        if (temp != NULL && accID == temp->pAcct->getAccNum())
        {
            search = true;
            account = temp->pAcct;
            return search;
        }
        else if (temp != NULL && accID < temp->pAcct->getAccNum())
        {
            temp = temp->left;
        }
        else if (temp != NULL && accID > temp->pAcct->getAccNum())
        {
            temp = temp->right;
        }
        
        else
        {
            search = true;
        }
    }
    cerr << "ERROR: Account " << accID << " not found. Transferal refused." << endl;
    return false;
}

bool BSTree::Display() const
{
    if (root != NULL)
    {
        RecursivePrint(root);
    }
    return false;
}

void BSTree::Empty()
{
    delete root;
    root = NULL;
}

bool BSTree::isEmpty() const
{
    if (root->left == NULL && root->right == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool BSTree::RecursiveInsert(Node* temp, Account* insert)
{
    if (insert->getAccNum() > temp->pAcct->getAccNum())
    {
        if (temp->right == NULL)
        {
            Node* toInsert = new Node();
            toInsert->pAcct = insert;
            toInsert->left = NULL;
            toInsert->right = NULL;
            temp->right = toInsert;
            return true;
        }
        else
        {
            return RecursiveInsert(temp->right, insert);
        }

    }
    else if (insert->getAccNum() < temp->pAcct->getAccNum())
    {
        if (temp->left == NULL)
        {
            Node* toInsert = new Node();
            toInsert->pAcct = insert;
            toInsert->left = NULL;
            toInsert->right = NULL;
            temp->left = toInsert;
            return true;
        }
        else
        {
            return RecursiveInsert(temp->left, insert);
        }

    }
    else
    {
        cerr << "ERROR: Account " << insert->getAccNum() << " is already opened. Transaction refused." << endl;
        return false;
    }
}

void BSTree::RecursivePrint(Node* node)const
{
    if (node != NULL)
    {
        RecursivePrint(node->left);
        cout << node->pAcct->getFirstName() << " " << node->pAcct->getLastName()
            << " Account ID: " << node->pAcct->getAccNum() << endl;
        for (int i = 0; i < 10; i++)
        {
            cout << "   " << node->pAcct->getFundName(i) << ": $" << node->pAcct->getBalance(i) << endl;
        }
        cout << endl;
        RecursivePrint(node->right);
    }
}
