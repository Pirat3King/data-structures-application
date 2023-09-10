#pragma once

// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: New for phase 2 - Generic template BTree class which includes
//              some basdic methods.
// Author: Pirat3King
// Date: 2023-04-25
// ---------------------------------------------------------------------------

#include <vector>
#include "BTreeNode.h"

template <typename N>
class BTree 
{
private:
    BTreeNode<N>* root;
public:
    // BTree constructor
    BTree()
    {
        root = new BTreeNode<N>(true);
    }

    // BTree destructor
    ~BTree()
    {
        delete root;
    }

    // insert a key into the tree
    void insert(const N& key)
    {
        if (root->getNumKeys() == root->getMaxSize()) //node is full
        {
            BTreeNode<N>* newNode = new BTreeNode<N>(false);
            newNode->getChildren().push_back(root);
            newNode->insert(key);

            root = newNode;
        }
        else
        {
            root->insert(key);
        }
    }

    // search for a key in the tree
    bool search(const N& key)
    {
        if (!root)
            return false;

        else
            return root->search(key);
    }

    template <typename Callback>
    void traverse(Callback callback) const
    {
        if (root)
        {
            root->traverse(callback);
        }
    }

    // print the tree
    void print() { root->print(); }

    //getter
    BTreeNode<N>* getRoot() { return root; }
};