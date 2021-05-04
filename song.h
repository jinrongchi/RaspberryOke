//
//  Song.h
//  CS 3307 - RaspberryOke
//
//  Created by Team 30
//

#ifndef Song_h
#define Song_h

#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <string>
#include <QString>
#include "lyrics.h"

class Song {

    // Attributes
private:

    int songID;
    QString songTitle;
    QString songArtist;
    QString songGenre;
    QString songFileLocation;
    int songTempo;
    QString songTimeLength; // Maybe change if not feasible
    int lyricsID;
    QString lyricsFileLocation;
    Lyrics *newlrc;

    // Functions

public:
    Song();
    ~Song();

    // Getter methods
    int getSongID();
    QString getSongTitle();
    QString getSongArtist();
    QString getSongGenre();
    QString getSongFileLocation();
    int getSongTempo();
    QString getSongTimeLength();

    QString getLyricsFileLocation();
    int getSongLyricsID();
    Lyrics getLyrics();


    // Setter methods
    // might not be needed

    void setSongID(int id);
    void setSongTitle(QString name);
    void setSongArtist(QString artist);
    void setSongGenre(QString genre);
    void setSongFileLocation(QString file);
    void setSongTempo(int tempo);
    void setSongTimeLength(QString length);
    void setLyricsFileLocation(QString file);
    void setLyricsID(int id);
    void setLyrics(Lyrics newLyrics);
};


#endif
