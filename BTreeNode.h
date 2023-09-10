#pragma once

// ---------------------------------------------------------------------------
// Project: Web Design Business App
// Description: New for phase 2 - Node class for generic templated BTree.
//              Includes some basic methods to manage nodes.
// Author: Pirat3King
// Date: 2023-04-25
// ---------------------------------------------------------------------------

#include <vector>
#include <iostream>

template<typename T>
class BTreeNode
{
private:
    const int MAX_KEYS = 5; // maximum number of keys in a node

    bool isLeaf;
    int numKeys;
    std::vector<T> keys;
    std::vector<BTreeNode<T>*> children;

    // helper function to split the node into two child nodes
    BTreeNode<T>* split()
    {
        if (numKeys <= 1)
            return nullptr;

        int midIndex = numKeys / 2;
        BTreeNode<T>* newNode = new BTreeNode<T>(isLeaf);
        newNode->numKeys = midIndex;

        for (int i = 0; i < midIndex; i++)
        {
            newNode->keys.push_back(keys[midIndex + 1 + i]);

            if (!isLeaf)
                newNode->children.push_back(children[midIndex + 1 + i]);
        }

        if (!isLeaf)
            newNode->children.push_back(children.back());

        numKeys = midIndex;
        keys.resize(numKeys);
        children.resize(numKeys + 1);

        return newNode;
    }

 public:
    // BTreeNode constructor
    BTreeNode(bool is_leaf)
    {
        isLeaf = is_leaf;
        numKeys = 0;
    }

    // BTreeNode destructor
    ~BTreeNode()
    {
        for (int i = 0; i < children.size(); i++)
        {
            delete children[i];
        }
    }

    // insert a key into the node
    void insert(const T& key)
    {
        int i = numKeys - 1;

        if (isLeaf)
        {
            //node is not full
            if (numKeys < MAX_KEYS)
            {
                //tree is empty
                if (numKeys == 0)
                {
                    keys.push_back(key);
                    numKeys++;
                    return;
                }

                while (i >= 0 && keys[i] > key)
                {
                    //avoid out-of-bounds access
                    if (i + 1 == numKeys)
                        keys.push_back(keys[i]);
                    else
                        keys[i + 1] = keys[i];
                    i--;
                }

                if (i + 1 == numKeys)
                    keys.push_back(key);
                else
                    keys[i + 1] = key;

                numKeys++;
            }
            else //node is full
            {
                BTreeNode<T>* new_node = split();

                if (key > keys[numKeys / 2])
                    new_node->insert(key);

                else
                    insert(key);
            }
        }
        else //node is not leaf
        {
            while (i >= 0 && keys[i] > key)
            {
                i--;
            }

            BTreeNode<T>* child = children[i + 1];

            if (child->numKeys == MAX_KEYS)
            {
                BTreeNode<T>* new_node = child->split();
                children[i + 1] = new_node;

                if (key > keys[i + 1])
                {
                    i++;
                    child = new_node;
                }
            }
            child->insert(key);
        }
    }

    // search for a key in the node
    bool search(const T& key)
    {
        int i = 0;
        while (i < numKeys && keys[i] < key)
        {
            i++;
        }

        if (i < numKeys && keys[i] == key)
            return true;

        if (isLeaf)
            return false;

        return children[i]->search(key);
    }

    // print the node
    void print()
    {
        for (int i = 0; i < numKeys; i++)
        {
            if (!isLeaf)
                children[i]->print();

            std::cout << keys[i] << " ";
        }

        if (!isLeaf)
            children.back()->print();
    }

    //traverse node
    template <typename Callback>
    void traverse(Callback callback) const
    {
        for (size_t i = 0; i < numKeys; ++i)
        {
            if (!isLeaf)
            {
                children[i]->traverse(callback);
            }
            callback(keys[i]);
        }

        if (!isLeaf)
        {
            children[numKeys]->traverse(callback);
        }
    }

    //getters
    bool getIsLeaf() const { return isLeaf; }
    int getNumKeys() const { return numKeys; }
    const T& getKey(int index) const { return keys[index]; }
    BTreeNode<T>* getChild(int index) const { return children[index]; }
    std::vector<BTreeNode<T>*> getChildren() const { return children; }
    int getMaxSize() const { return MAX_KEYS; }


};