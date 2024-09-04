//Guard Headers
#ifndef LISTENHEAP_H
#define LISTENHEAP_H

#include <iostream> 
#include <vector>
#include "Song.h"
#include "SLL.h"

using namespace std;

class listenHeap {
 private:
  vector<SLLNode*> maxHeap; //Heap Array

  //Percolate Functions
  void percolateUp(int index);//Check current node against it's parent, if greater, swap with parent. Repeat until either node is not greater than parent or root is reached
  void percolateDown(int index, int size);//Check current node against it's child, if less, swap with child. Repeat until either node is not less than child or leaf is reached

 public:
  listenHeap(){//Default Constructor
  }

  ~listenHeap(){//Deconstructor
  }

  //bool operator<(const SLLNode* &node);

  void insert(SLLNode* val);//Insert new element into the heap

  void remove(int index);

  int getIndex(int ID);

  void listen(SLLNode* node);

  SLLNode* extractMax();//Removes and returns the maximum element from the heap

  SLLNode* getMax();//Returns the maximum element in the heap but does not remove

  bool isEmpty();//Return true if heap is empty, false otherwise 

  int size(); //Return the size of the heap
  
};

#endif//LISTENHEAP_H