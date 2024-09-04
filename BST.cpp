#include <iostream>
#include <string>
#include "BST.h"

using namespace std;

BSTNode::BSTNode(string name, SLLNode* song) : name(name), song(song), left(nullptr), right(nullptr) {}

bool BSTNode::operator<(const BSTNode& n) {
    return name < n.name;
}

BST::BST() : root(nullptr) {}

bool BST::insertSong(SLLNode* song) //insert song to playlist
{
  BSTNode* newSongNode = new BSTNode(song->Asong.getTitle(), song);
  if (!root) 
  {
    root = newSongNode;
  } 
  
  else 
  {
    BSTNode* leaf = root;
    while(leaf) 
    {
      if(newSongNode->name < leaf->name) 
      {
        if(leaf->left == nullptr) 
        {
            leaf->left = newSongNode;
            return true;
        }
        leaf = leaf->left;
      }
      else if( newSongNode->name > leaf->name) 
      {
        if(leaf->right == nullptr) 
        {
          leaf->right = newSongNode;
          return true;
        }
        leaf = leaf->right;
      }
      else 
      {
        //already exists
        delete newSongNode;
        return false;
      }
    }
    return false;
  }
  return false;
}


bool BST::deleteSongByName(string name, BSTNode* parent = NULL, BSTNode* node = NULL)
{
  if(!node) {
    return false;
  }
  if(node->name < name) {
    return deleteSongByName(name, node, node->right);

  }
  else if(node->name > name) {
    return deleteSongByName(name, node, node->right);
  }
  else {
     if(node->left == nullptr && node->right == nullptr) {
       if(!parent) {
           root = nullptr;
       }
       else {
          if(parent->left == node) parent->left = nullptr;
          if(parent->right == node) parent->right = nullptr;
       }
       delete node;
     }
     else if(node->left == nullptr) {
       if(!parent) {
            root = node->right;
       }
       else {
          if(parent->left == node) parent->left = node->right;
          if(parent->right == node) parent->right = node->right;
       }
       delete node;
     }
     else if(node->right == nullptr)
     {
       if(!parent) {
            root = node->left;
       }
       else {
        if(parent->left == node) parent->left = node->left;
        if(parent->right == node) parent->right = node->left;
       }
       delete node;
     }
     else {
        BSTNode* temp = node->left;
        BSTNode* parentleft = nullptr;
        if(!parent) {
             root = node->right;
             parentleft = node->right->left;
        }
        else {
            if(parent->left == node) {
                parent->left = node->right;
            }
            if(parent->right == node) {
                parent->right = node->right;
            }
            parentleft = node->right->left;
        }
        if(!parentleft ) {
          node->right->left = temp;
        }
        else {
          while(parentleft->left != nullptr) parentleft = parentleft->left;
          parentleft->left = temp;
        }
        delete node;
    }
    return true;
  }
  return false;
}

SLLNode* BST::getSong(string name) //check the tree for song 
{
    BSTNode* current = root;
    while (current != nullptr) 
    {
        if (name == current->name) 
        {
            return (current->song); //if the root is the song we're looking for this is it
        } 
        else if (name < current->name) //if the name's alphabet is lowever than the root rank go left and push scanned node as root
        {
            current = current->left; 
        }
        else 
        {
            current = current->right; //like above, if bigger go right
        }
    }
    // Return an empty Song if the song with the given name is not found
    
    return new SLLNode();
}


