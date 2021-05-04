//
//  Song.cpp
//  CS 3307 - RaspberryOke
//
//  Created by Team 30


#include "song.h"


using namespace std;

// The constructor
Song::Song() {

    // do something...

}

// The destructor
Song::~Song() {

    // destroy something...

}

// Getter methods

// Return th song ID

// Return the song title
QString Song::getSongTitle() {

    return this->songTitle;
}

// Return the song's artist name
QString Song::getSongArtist() {

    return this->songArtist;
}

QString Song::getSongGenre() {

    return this->songGenre;
}

int Song::getSongTempo() {

    return this->songTempo;
}

int Song::getSongID(){
    return this->songID;
}
QString Song::getSongTimeLength() {

    return this->songTimeLength;
}

QString Song::getSongFileLocation(){
    return this->songFileLocation;
}

Lyrics Song:: getLyrics(){
    return *(this->newlrc);
}

QString Song:: getLyricsFileLocation(){
    return this->lyricsFileLocation;
}

int Song:: getSongLyricsID(){
    return this->lyricsID;
}

// Setter methods

void Song::setSongID(int id) {
    this->songID = id;
}
void Song::setSongTitle(QString title) {
    this->songTitle = title;
}
void Song::setSongArtist(QString artist) {
    this->songArtist = artist;
}
void Song::setSongGenre(QString genre) {
    this->songGenre = genre;
}
void Song::setSongFileLocation(QString file) {
   this->songFileLocation = file;
}
void Song::setSongTempo(int tempo) {
    this->songTempo = tempo;
}
void Song::setSongTimeLength(QString length) {
    this->songTimeLength = length;
}

void Song:: setLyricsFileLocation(QString file){
    this->lyricsFileLocation = file;
    std::string filename = file.toUtf8().constData();
    //newlrc = new Lyrics(filename);
    // initializing a lyrics object, then we can get a vector containing all time+lyrics_content out of it
}

void Song:: setLyricsID(int id){
    this->lyricsID = id;
}

void Song:: setLyrics(Lyrics newLyrics){
    this->newlrc = &newLyrics;
}
