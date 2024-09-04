
#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include "SLL.cpp"

using namespace std;

class BSTNode {
private:
    string name;
    SLLNode* song;
    BSTNode* left;
    BSTNode* right;

public:
    BSTNode() {
        name = "";
        song = NULL;
        left = NULL;
        right = NULL;
    }
    BSTNode(string name, SLLNode* song);
    bool operator<(const BSTNode& n);
    friend class BST; //grant BST Node Class's both privates and publics
};

class BST {
private:
    BSTNode* root;

public:
    BST();//BST Constructor
    bool insertSong(SLLNode* song);
    bool deleteSongByName(string name, BSTNode* parent, BSTNode* node);
    SLLNode* getSong(string name);
};

#endif