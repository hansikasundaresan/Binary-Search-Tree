//
//  binarySearchTree.h
//  assignment4
//
//  Created by Hansika Sundaresan on 11/13/19.
//  Copyright © 2019 Hansika Sundaresan. All rights reserved.
//

#ifndef binarySearchTree_h
#define binarySearchTree_h
#include <cassert>
#include <iostream>
#include <iomanip>
#include <cstddef>
#include <iterator>
#include <algorithm>
#include <string>

// forward declaration of the template class binarySearchTree
template<class DataType>
class binarySearchTree;

//tree node class, used to create node object to store word data and pointers for tree
template <class DataType>
class treeNode
{
    //friend allows access to private data members of treeNode
    friend class binarySearchTree<DataType>;
    
private:
    // contains the actual data
    DataType dataType;
    // pointer to the right item in the list or nullptr
    // if at the right
    treeNode<DataType>* pRight;
    // pointer to the left item in the list or nullptr
    // if at the end
    treeNode<DataType>* pLeft;
    // pointer to the parent item in the list or nullptr
    // if at the rootNode
    treeNode<DataType>* pParent;
    
public:
    // default constructor
    treeNode();
    
    // constructor with data
    treeNode(const DataType &newItem);
    
protected:
    // get the right node
    treeNode* right() const
    {
        return pRight;
    }
    
    // get the left node
    treeNode* left() const
    {
        return pLeft;
    }
    
    // get the parent node
    treeNode* parent() const
    {
        return pParent;
    }
    
    // return the data stored in the node as a const
    const DataType& data() const
    {
        return dataType;
    }
    
    // return the data stored in the node
    DataType& data()
    {
        return dataType;
    }
    
    // update the right node
    void right(treeNode *rightNode)
    {
        pRight = rightNode;
    }
    // update the left node
    void left(treeNode *leftNode)
    {
        pLeft = leftNode;
    }
    // update the parent node
    void parent(treeNode *parentNode)
    {
        pParent = parentNode;
    }
    
};

//definition of binarySearchTree class
template<class DataType>
class binarySearchTree
{
public:
    typedef std::size_t                                size_type;
    
    
private:
    //poibnts to the root of the tree
    treeNode<DataType>* rootNode;
    
    //for the number of nodes in the binary search tree
    size_t count=0;
    
public:
    //default constructor
    binarySearchTree()
    {
        rootNode = nullptr;
    }
    // copy constructor
    binarySearchTree(const binarySearchTree<DataType> &other)
    {
        copy(other.rootNode);
    }
    
    //copies all the nodes from the parameter to the binaryTree
    void copy(treeNode<DataType> * node)
    {
        if(node)
        {
            insert(node->data());
            copy(node->left());
            copy(node->right());
        }
    }
    
    //calls deleteAll with node parameter
    void deleteAll()
    {
        
        deleteAll(rootNode);
        rootNode = nullptr;
    }
    
    //deletes all nodes of the tree
    void deleteAll(treeNode<DataType>  *node)
    {
        if (node != nullptr)
        {
            // delete all nodes to the left
            deleteAll(node->left());
            node->left(nullptr);
            
            // delete all nodes to the right
            deleteAll(node->right());
            node->right(nullptr);
            
            // delete the node now
            delete node;
            count--;
        }
    }

    //equals overloading operator
    const binarySearchTree<DataType>& operator=(const binarySearchTree<DataType>& node)
    {
        if(!node.rootNode)
        {
            return *this;
        }
        
            deleteAll();
            copy(node.rootNode);
        
        return *this;
    }
    
    
    //destructor
    virtual ~binarySearchTree()
    {
        deleteAll(rootNode);
    }
    
    //returns number of nodes in tree
    std::size_t size() const
    {
        return count;
    }
    
    //returns true if tree is empty
    bool empty() const
    {
        return size() == 0;
    }
    
    //to print out whole tree
    void print() const
    {
        print(rootNode);
    }
    
    //prints tree through recurssive calling
    void print(treeNode<DataType>* nodePtr) const
    {
        if(nodePtr)
        {
            print(nodePtr->left());
            std::cout<<nodePtr->data()<<std::endl;
            print(nodePtr->right());
        }
    }
    
    //printing with ostream variable
    void print(std::ostream &out) const
    {
        print(rootNode, out);
    }
    
    //printing with ostream variable through recursive calling
    void print(treeNode<DataType>* nodePtr, std::ostream& out) const
    {
        if(nodePtr)
        {
            print(nodePtr->left(), out);
            out<<nodePtr->data()<<std::endl;
            print(nodePtr->right(), out);
        }
        
    }
    
    //traversing preOrder
    void traversePreOrder(void (*itemFound)(const DataType& foundItem)) const
    {
        traversePreOrder2(rootNode, &itemFound);
    }
    
    //traversing preOrder through recursive calling
    void traversePreOrder2( treeNode<DataType>* node, void (**itemFound)(const DataType& foundItem)) const
    {
        if (node == nullptr)
            return;
        (*itemFound)(node->data());
        traversePreOrder2(node->left(), itemFound);
        traversePreOrder2(node->right(), itemFound);
    }
    
    //travering outOrder
    void traverseOutOrder(void (*itemFound)(const DataType& foundItem)) const
    {
        traverseOutOrder2(rootNode, &itemFound);
    }
    
    //travering outOrder through recursive calling
    void traverseOutOrder2( treeNode<DataType>* node, void (**itemFound)(const DataType& foundItem)) const
    {
        if (node == nullptr)
            return;
        traverseOutOrder2(node->right(), itemFound);
        (*itemFound)(node->data());
        traverseOutOrder2(node->left(), itemFound);
    }

    //returns true if searchItem is found
    //runs foundNode method if searchItem is found
    bool find(const DataType &searchItem, void (*foundNode)(const DataType&));
    
    //debug method
    void debug(std::ostream &out)
    {
        print(rootNode);
    }
    
    //erases node with deleteItem
    bool erase(const DataType &deleteItem);
    
    //erases node and reorganizes tree
    void eraseNode(treeNode<DataType>* currNode);
    
    //inserts newItem into tree
    void insert(const DataType &newItem);
    
    //inserts item into tree and calls dupuplicateItemFound if newItem already exists in tree
    void insert(const DataType &newItem, void (*duplicateItemFound)(DataType &existingItem, const DataType &newItem));
    
    //traverses through tree
    void traverse(void (*itemFound)(const DataType& foundItem)) const
    {
        traverse2(rootNode, &itemFound);
    }
    
    //traverses through recurrsive calling through tree
    void traverse2( treeNode<DataType>* node, void (**itemFound)(const DataType& foundItem)) const
    {
        if (node == nullptr)
            return;
        traverse2(node->left(), itemFound);
        (*itemFound)(node->data());
        traverse2(node->right(), itemFound);
    }

};

//default constructor
template<class DataType>
treeNode<DataType>:: treeNode()
: dataType(), pLeft(nullptr), pRight(nullptr), pParent(nullptr)
{
}

//constructor with newItem parameter
template<class DataType>
treeNode<DataType> :: treeNode(const DataType &newItem)
: dataType(newItem), pLeft(nullptr), pRight(nullptr), pParent(nullptr)
{
}

//deletes all nodes of the tree


//returns if searchItem was found
//runs foundNode method if searchItem was found
template<class DataType>
bool binarySearchTree<DataType> :: find(const DataType &searchItem, void (*foundNode)(const DataType&))
{
    treeNode<DataType>* tempNode = nullptr;
    tempNode = rootNode;
    while(tempNode != nullptr)
    {
        if(tempNode->data() == searchItem)
        {
            foundNode(tempNode->data());
            return true;
        }
        else if(searchItem < tempNode->data())
        {
            tempNode= tempNode->left();
        }
        else
        {
            tempNode = tempNode->right();
        }
    }
    return false;
}

//erases node containing deleteItem
template<class DataType>
bool binarySearchTree<DataType> :: erase(const DataType &deleteItem)
{
    treeNode<DataType> * node = nullptr;
    node = rootNode;
    while(node != nullptr)
    {
        if(node->data() == deleteItem)
        {
            eraseNode(node);
            count--;
            return true;
        }
        else if(deleteItem < node->data())
        {
            node= node->left();
        }
        else
        {
            node = node->right();
        }
    }
    return false;
}

//erases specific node through recursive calling
template<class DataType>
void binarySearchTree<DataType> :: eraseNode(treeNode<DataType>* currNode)
{
    if(!currNode->left() && !currNode->right())
    {
        if(currNode == rootNode)
        {
            delete rootNode;
            rootNode = nullptr;
            return;
        }
        else if(currNode->parent()->right() == currNode)
        {
            currNode->parent()->right(nullptr);
            
        }
        else
        {
            currNode->parent()->left(nullptr);
            
        }
        delete currNode;
        return;
    }
    else if (!currNode->right() && currNode->left())
    {
        if(currNode == rootNode)
        {
            delete rootNode;
            rootNode = currNode->left();
            return;
        }
        else if(currNode->parent()->left() == currNode)
        {
            currNode->parent()->left(currNode->left());
            currNode->left()->parent(currNode->parent());
        }
        else
        {
            currNode->parent()->right( currNode->left());
            currNode->left()->parent(currNode->parent());
        }
        delete currNode;
        return;
        
    }
    else if( !currNode->left() && currNode->right())
    {
        if(currNode == rootNode)
        {
            delete rootNode;
            rootNode = currNode->right();
            return;
        }
        else if(currNode->parent()->left() == currNode)
        {
            currNode->parent()->left(currNode->right());
            currNode->right()->parent(currNode->parent());
        }
        else
        {
            currNode->parent()->right(currNode->right());
            currNode->right()->parent(currNode->parent());
        }
        delete currNode;
        return;
    }
    else
    {
        treeNode<DataType>* tempNode = nullptr;
        tempNode = currNode->right();
        while(tempNode->left())
        {
            tempNode= tempNode->left();
        }
        
        currNode->data() = tempNode->data();
        eraseNode(tempNode);
        
    }
    
}

//inserts new node to binary search tree
template<class DataType>
void binarySearchTree<DataType> :: insert(const DataType &newItem)
{
    treeNode<DataType>* tempNode = new treeNode<DataType>(newItem);
    treeNode<DataType>* currNode = nullptr;
    if(rootNode == nullptr)
    {
        rootNode = tempNode;
        rootNode->left(nullptr);
        rootNode->right(nullptr);
        rootNode->parent(nullptr);
        count++;
    }
    else
    {
        currNode = rootNode;
        while(currNode != nullptr)
        {
            if(tempNode->data() < currNode->data())
            {
                if(currNode->left() == nullptr)
                {
                    currNode->left(tempNode);
                    tempNode->parent(currNode);
                    count++;
                    currNode = nullptr;
                }
                else
                {
                    currNode = currNode->left();
                }
            }
            else
            {
                if(currNode->right() == nullptr)
                {
                    currNode->right(tempNode);
                    tempNode->parent(currNode);
                    count++;
                    currNode = nullptr;
                }
                else
                {
                    currNode = currNode->right();
                }
            }
        }
        
        tempNode->left(nullptr);
        tempNode->right(nullptr);
    }
    
}

//inserts newItem or runs duplicateItemFound if newItem already exists
template<class DataType>
void binarySearchTree<DataType> :: insert(const DataType &newItem, void (*duplicateItemFound)(DataType &existingItem, const DataType &newItem))
{
    treeNode<DataType>* tempNode = nullptr;
    tempNode = rootNode;
    while(tempNode != nullptr)
    {
        if(tempNode->data() == newItem)
        {
            duplicateItemFound(tempNode->data(), newItem);
            return;
        }
        else if(newItem < tempNode->data())
        {
            tempNode= tempNode->left();
        }
        else
        {
            tempNode = tempNode->right();
        }
    }
    insert(newItem);
}

#endif /* binarySearchTree_h */
