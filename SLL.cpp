#ifndef SLL_CPP
#define SLL_CPP

#include <iostream>
#include "SLL.h"

using namespace std;

//BST nameTree;
//listenHeap listenHeap;

//pretty basic is empty -- from my CP3
bool SLL::isEmpty() {
  if (head == NULL) { //&& tail == NULL
    return true;
  }
  return false;
}

bool SLL::flush() {
  //destructor
  //keep deleting nodes until Head = Tail then know at last one
  if (head == NULL) {
    return true;
  }
  while (head != tail) {
    SLLNode* tmp = head;
    head = head->next;
    delete tmp;
  }
  //the last one they equal bc theres one left. Still need to delete that one
  SLLNode* tmp = head;
  head = NULL;
  tail = NULL;
  delete tmp;
  return true;
}

SLLNode* SLL::insert(const Song &song) {
    //make a node for song
    //insert it in proper place based on ID
    //check for edge cases
    SLLNode* node = new SLLNode(song);
    if (head == NULL) { 
    
        head = node; 
        if (tail == NULL) { 
            tail = node; 
        }
        return node;
    }
    

    SLLNode* ptr = head;

    while (ptr != NULL) {
        
        if (ptr->Asong.getSongID() == node->Asong.getSongID()) {
            cout << "id in use, please try again" << endl;
            return NULL;
        }
        else if (ptr->Asong.getSongID() < node->Asong.getSongID()) {
            if (ptr->next == NULL) {
                //adding to end
                ptr->next = node;
                node->prev = ptr;
                tail = node;
                return node;
            }
            ptr = ptr->next;
        }
        else if (ptr->Asong.getSongID() > node->Asong.getSongID()) {
            if (ptr == head) {
                //adding id before head
                node->next = ptr;
                ptr->prev = node;
                head = node;
            }
            else {
                SLLNode* ptrPrev = ptr->prev;

                ptrPrev->next = node;
                node->prev = ptrPrev;

                ptr->prev = node;
                node->next = ptr;
                delete ptrPrev;
            }
            delete ptr;
            return node;
        }
    }
    return NULL;
}

bool SLL::remove(const int &ID) {
    SLLNode* ptr = head;
    while (ptr != NULL) {
        if (ptr->id == ID) {
            SLLNode* tmp = ptr;
            if (tmp == tail) {
                if(head == tail) {
                ptr = ptr->next;
                head = NULL;
                tail = NULL;
                delete tmp;
                delete ptr;
                }

                else {
                ptr = ptr->next;
                tail->prev->next = NULL;
                tail = tail->prev;
                delete tmp;
                delete ptr;
                }
            }
            else if (tmp == head) {
                ptr = ptr->next;
                head = head->next;
                delete tmp;
                delete ptr;
            } 

            else {
                ptr = ptr->next;
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
                delete tmp;
                delete ptr;
            }
            
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

Song& SLL::findSong(const int &ID) {
    SLLNode* ptr = head;
    while(ptr != NULL) {
        if (ptr->id == ID) {
            return ptr->Asong;
        }    
        else {
            ptr = ptr->next;
        }
    }
    cout << "song not found" << endl;
    return notFound;
}

SLLNode* SLL::findNode(const int &ID) {

    SLLNode* tmp = head;
    while (tmp != NULL) {
        if (tmp->Asong.getSongID() == ID) {
            return tmp;
        }
        else {
            tmp = tmp->next;
        }
    }
    cout << "ERROR: Node not found" << endl;
    delete tmp;
    return NULL;

}

void SLL::traverse() {
    SLLNode* ptr = head;

    while (ptr != NULL) {
        cout << ptr->id << " ";
        cout << ptr->Asong.title << " has been listened to for ";
        cout << ptr->Asong.listenTime << " seconds" << endl;

        ptr = ptr->next;
    }
    delete ptr;
}

#endif