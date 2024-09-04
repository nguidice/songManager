#include <iostream>
#include <string>
#include <sstream> 
#include "Song.h"

#ifndef SONG_CPP
#define SONG_CPP

using namespace std;

//Default constructor
Song::Song() : id(0), artist("Unknown"), duration("0:00"), title("Untitled"), listenTime(0), favorited(false) {
}

//actual constructor
Song::Song(int id, string artistName, int songDurationSeconds, string songTitle) {

    if(id > 0) {
        // Convert seconds to minutes:seconds format and assign to duration
        int minutes = songDurationSeconds / 60;
        int seconds = songDurationSeconds % 60;
        
        stringstream ss;
        ss << minutes << ":"; 
        if(seconds < 10) ss << "0"; // Leading zero for seconds less than 10
        ss << seconds; 
        
        duration = ss.str(); //this should set durration itself

        //actually setting everything
        setSongID(id);
        setArtist(artistName);
        setTitle(songTitle);
        listenTime = 0;
        favorited = false;

        cout << "new song " << id << " " << title << " by " << artist << " " << duration << endl;
    }
    else {
        cout << "ID is less than 1, please use valid ID (SONG NOT MADE)" << endl;
    }
    
}

Song::Song(const Song& source)
  : id(source.id), artist(source.artist), duration(source.duration), title(source.title), listenTime(source.listenTime), favorited(source.favorited) {
    
    //basically a copy constructor but with another song
}

Song& Song::operator=(const Song& source) {
    if (this != &source) { 
        id = source.id;
        artist = source.artist;
        duration = source.duration;
        title = source.title;
    }

    return *this;
}

Song::~Song() {
}

// Setters
void Song::setSongID(int ID) {
    id = ID;
}

void Song::setArtist(string artistName) {
    artist = artistName;
}

void Song::setDuration(int seconds) {
    int minutes = seconds / 60;
    int remainingSeconds = seconds % 60;
    
    stringstream ss;
    ss << minutes << ":";
    if(remainingSeconds < 10) ss << "0"; // Leading zero for seconds less than 10
    ss << remainingSeconds; 
    
    duration = ss.str(); // Assign the formatted string to duration
}

void Song::setTitle(string songTitle) {
    title = songTitle;
}

void Song::setListenTime(int addedListenTime) {
    listenTime = listenTime + addedListenTime;
}

void Song::setFavorite() {
    favorited = true;
}

void Song::removeFavorite() {
    favorited = false;
}


// Getters
int Song::getSongID() const {
    return id;
}

string Song::getArtist() const {
    return artist;
}

string Song::getDuration() const {
    return duration;
}

string Song::getTitle() const {
    return title;
}

int Song::getListenTime() const {
    return listenTime;
}

bool Song:: isFavorited() const {
  return favorited;
}

// Method to display song details
void Song::displaySongInfo() const {

    cout << id << " " << title << " has been listen to for " << listenTime << " seconds" << endl;

}

#endif