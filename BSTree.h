#ifndef BSTree_h
#define BSTree_h


#pragma once
#include <iostream>
#include "Account.h"

using namespace std;

class BSTree
{
public:
    
    BSTree();
    ~BSTree();

    
    bool Insert(Account*);

   
    bool Retrieve(const int& , Account*& )const;

    
    bool Display()const;

    
    void Empty();

   
    bool isEmpty()const;

private:
    struct Node
    {
        Account* pAcct ;
        Node* right ;
        Node* left ;
    };
    Node* root;
    bool RecursiveInsert(Node* pNode, Account* insert);
    void RecursivePrint(Node*)const;
};


#endif /* BSTree_h */
