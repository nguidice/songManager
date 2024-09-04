#ifndef SONG_H
#define SONG_H

#include <string>

using namespace std;


class Song {
private:

public:

    //Song notFound;
    int id;
    string artist;
    string duration; // Duration in minutes
    string title;
    int listenTime;
    bool favorited; 

    Song(); 
    Song(int id, string artistName, int songDurationSeconds, string songTitle); 
    Song(const Song& other); // Copy constructor
    Song& operator=(const Song& other); // Copy assignment operator
    ~Song(); 

    //setters here
    void setSongID(int id);
    void setArtist(std::string artistName);
    void setDuration(int seconds);
    void setTitle(std::string songTitle);
    void setListenTime(int addedListenTime);
    void setFavorite();
    void removeFavorite();

    //getters here
    int getSongID() const;
    string getArtist() const;
    string getDuration() const;
    string getTitle() const;
    int getListenTime() const;
    bool isFavorited() const; //to check if favorited

    //others here
    void displaySongInfo() const;
};

#endif // SONG_H
