#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <regex>
#include <map>
//#include <vector>

#include "Song.h"
#include "SLL.cpp"
#include "BST.cpp"
#include "listenHeap.cpp"

using namespace std;

vector<string> parseInput(const string& input) {
    vector<string> tokens;
    stringstream ss(input);
    string token;

    while (ss >> token) {
        if (token.front() == '"') { // Start of quoted text
            string quotedToken = token;

            if (token.back() != '"') { // Handle case where quoted text is more than one word
                while (ss >> token) {
                    quotedToken += " " + token;

                    if (token.back() == '"') {
                        break;
                    }
                }
            }
            // Remove the quotes
            quotedToken = quotedToken.substr(1, quotedToken.size() - 2);
            tokens.push_back(quotedToken);
        }
        else {
            tokens.push_back(token);
        }
    }
    return tokens;
}

enum Command {
    CMD_SONG,
    CMD_REMOVE,
    CMD_QUIT,
    CMD_LISTEN,
    CMD_FAVORITE,
    CMD_TIME,
    CMD_UNKNOWN //FAILBACK
};

map<string, Command> commandMap = {
    {"song", CMD_SONG},
    {"remove", CMD_REMOVE},
    {"quit", CMD_QUIT},
    {"listen", CMD_LISTEN},
    {"favorite", CMD_FAVORITE},
    {"show_listen_time", CMD_TIME}
};

void printInvalidSize(int size){
    cout << "Invalid input: " << size << " is incorrect amount of arguments for this command!" << endl;
};

bool argTesting(int size, vector<string> vec){
    if(vec.size()!=size) {
        printInvalidSize(vec.size());
        return false;
    }

    //return vec.size()==size;  USE THIS IF INVALID #ARGS == CANCEL CALL
    return true;
    //goto restartLoop;
};

int parseID(string strId){
    int id=-1234;
    try {
        int id = stoi(strId);
        return id;
    } 
    catch (const invalid_argument& e) {
        cout << "song id " << strId << " is not an integer" << endl;
        /*
       cout << "Invalid input: " << e.what() << endl;
       cout << "Invalid Input: Song Id cannot be " << strId<< endl;
       */
    }
    return id;
}

SLL songList;
BST nameBST;
listenHeap heap;

void Input() { 
  string text;
  getline(cin, text);
  
  int flag = 1;
  vector<string> stringList=/*store1.*/parseInput(text);
  if(stringList.size() > 5){
     cout << "Excess arguments" << endl;
  }
  Command cmd = commandMap.count(stringList[0]) ? commandMap[stringList[0]] : CMD_UNKNOWN;

    //This is where we add songs. We can have white space in song and artisit name but then they will be in """"
   switch (cmd) {
      case CMD_SONG:
          try {
            if(!argTesting(5,stringList)) {
                break;
            }

            int time = stoi(stringList[3]);
            flag = 0;
            int id = stoi(stringList[1]);
            Song mySong(id, stringList[2], time, stringList[4]);
            SLLNode* node = songList.insert(mySong);
            if (node != NULL) {
              nameBST.insertSong(node);
              heap.insert(node);
            }


          } 
          catch (const invalid_argument& e) {
            cout << "Invalid input: " << e.what() << endl;
            if (flag == 0) {
                cout << "song id " << stringList[1] << " is not an integer" << endl;
            }
            else {
                cout << "Invalid Input: time cannot be " << stringList[3] << endl;
            }
          }
        break;
    case CMD_REMOVE:
      if(!argTesting(2,stringList)) {
        break;
      }
      else {
	      Song tmp = nameBST.getSong(stringList[1])->Asong;
        if(!(tmp.getSongID() == 0)) {
          if(tmp.isFavorited()) {
            tmp.removeFavorite();
            heap.insert(songList.findNode(tmp.getSongID()));
            cout << "Removed " << tmp.getTitle() << " from your favorites" << endl;
          }
          else {
            nameBST.deleteSongByName(tmp.getTitle());

            int index = heap.getIndex(tmp.getSongID());
            heap.remove(index);

            songList.remove(tmp.getSongID());

            cout << "Removed " << tmp.getTitle() << " from your songs" << endl;
          }
        }
      }

      break;

    case CMD_LISTEN:
      if(!argTesting(3, stringList)) {
        break;
      }
      else {
        SLLNode* tmp = nameBST.getSong(stringList[1]);
        if(tmp->Asong.isFavorited()) {
        }
        else {
          tmp->Asong.setListenTime(stoi(stringList[2]));
          heap.listen(tmp);
          cout << "Listened to " << stringList[1] << " for " << stringList[2] << " seconds" << endl;
        }
      }
      break;

    case CMD_FAVORITE:
      if(!argTesting(1, stringList)) {
        break;
      }
      else {
        SLLNode* tmp = heap.extractMax();
        tmp->Asong.setFavorite();
        cout << "Song " << tmp->Asong.getTitle() << " added to list of favorites (Listened for " << tmp->Asong.getListenTime() << " seconds)" << endl;
      }

      break;

    case CMD_TIME:
      if(!argTesting(1, stringList)) {
        cout << "argfail" << endl;
        break;
      }
      else {
	      songList.traverse();
      }
       
      break;	    
    case CMD_QUIT:
      exit(0);
      break;
          
    default:
      cout << "Command not recognized. Please try again." << endl;
      break;
    }
    restartLoop:
      Input();
}
    
int main() {
    Input();
    return 0;
}
