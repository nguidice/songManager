#include <iostream>
#include "listenHeap.h"

using namespace std;


//Percolate Functions

//Check current node against it's parent, if greater, swap with parent. Repeat until either node is not greater than parent or root is reached
void listenHeap::percolateUp(int index){
  if (index == 0){ //If Index = 0, then at root
    return;
  }

  int parentIndex = (index - 1) / 2; //Calculate Index of Parent

  if (maxHeap[index]->Asong.getListenTime() > maxHeap[parentIndex]->Asong.getListenTime()) { //Check if the current node is greater than it's parent
    swap(maxHeap[index], maxHeap[parentIndex]); //Swap node and it's parent
    percolateUp(parentIndex); //Recursively call percolateUp on the parent node to traverse all heap levels
  }
}

  //Check current node against it's child, if less, swap with child. Repeat until either node is not less than child or leaf is reached
void listenHeap::percolateDown(int index, int size){
  //Calculate indices of left and right children
  int leftChildIndex = 2 * index + 1;
  int rightChildIndex = 2 * index + 2;

  //Set largest node to current node
  int largestIndex = index;

  //Compare largest index with its left child
  if(leftChildIndex < size && maxHeap[leftChildIndex] > maxHeap[largestIndex]){
    largestIndex = leftChildIndex; //Set left child to largest if greater than current index
  }

  //Compare largest index with its right child
  if(rightChildIndex < size && maxHeap[rightChildIndex] > maxHeap[largestIndex]){
    largestIndex = rightChildIndex; //Set right child to largest if greater than current index
  }

  //If largest is not current index
  if (largestIndex != index){
    swap(maxHeap[index], maxHeap[largestIndex]); //Swap current index with its largest child
    percolateDown(largestIndex, size); //Recursively call percolateDown on the largest child
  }
}

  //Insert new element into the heap
void listenHeap::insert(SLLNode* val){
  maxHeap.push_back(val); //Add new element to the end of the heap

  percolateUp(maxHeap.size() - 1); //Call percolateUp on the new element to maintain max heap
}

void listenHeap::remove(int index) {
 //swap gotten element with the front
  maxHeap[index]->Asong.setListenTime(999999);
  percolateUp(index);
  extractMax();
}

int listenHeap::getIndex(int ID) {
  for (int i = 0; i < maxHeap.size(); i++) {
    if(maxHeap[i]->id == ID) {
      return i;
    }
  }
  cout << "not found. error" << endl;
  return -1;
}

void listenHeap::listen(SLLNode* node) {
  int index = getIndex(node->id);
  if (index > 0) {
    percolateUp(index);
  }
  
}

  //Removes and returns the maximum element from the heap
SLLNode* listenHeap::extractMax(){
  //If heap is empty return nullptr
  if (maxHeap.empty()){
    return nullptr;
  }

  swap(maxHeap[0], maxHeap.back()); //Swap root with last element

  SLLNode* maxIndex = maxHeap.back(); //Get max index

  maxHeap.pop_back(); //remove max from end of heap

  percolateDown(0,maxHeap.size()); //Call percolateDown to remake heap

  return maxIndex; //Return largest value
}

  //Returns the maximum element in the heap but does not remove
SLLNode* listenHeap::getMax(){
  //Check if heap is empty
  if (maxHeap.empty()){
      throw runtime_error("Heap is empty");
    }
    
    return maxHeap[0]; //Return first index as that is the root/max index in a max heap
}

  //Return true if heap is empty, false otherwise 
  bool listenHeap::isEmpty(){
    return maxHeap.empty();
  }

  //Return the size of the heap
  int listenHeap::size(){
    return maxHeap.size();
  }

