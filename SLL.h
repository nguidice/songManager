#include <iostream>
#include "Song.h"

#ifndef SLL_H
#define SLL_H

using namespace std;


//node template
class SLLNode {
  
 public:
  Song Asong; //changed data to song
  SLLNode* next;
  SLLNode* prev;

  int id;

//**these do be added when compiled with heap and BST so they have full compatability
  //HeapNode* heapPtr
  //BSTNode* bstPtr
  
  SLLNode () {
    //can do this because data technically doesnt have a type
    Asong = Song();
    next = NULL;
    prev = NULL;
    //default ID
    id = -1;
  }

  SLLNode (const Song &song) {
    this->Asong = song;
    this->id = song.getSongID();
    this->next = NULL;
    this->prev = NULL;
  }

  SLLNode (const int &ID, const Song &song) {
    this->Asong = song;
    this->id = ID;
    this->next = NULL;
    this->prev = NULL;
  }
  
};


//whole ass list template
class SLL {
  
 public:
  Song notFound;
  SLLNode* head;
  SLLNode* tail;
  
  SLL() {
    head = NULL;
    tail = NULL;
    notFound = Song();
  }

  ~SLL() {
    flush();
  }

  bool isEmpty();
  bool flush();
  
  SLLNode* insert(const Song &song);
  bool remove(const int &ID); 

  Song& findSong(const int &ID);
  SLLNode* findNode(const int &ID);

  void traverse();
};

#endif