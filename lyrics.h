/**
 * Lyrics.h
 * CS 3307 - RaspberryOke
 *
 * The header file.
 * Give instructions on things should be done with the Lyrics.cpp file
 *
 */

#ifndef Lyrics_h
#define Lyrics_h

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <QStringList>
#include <QMap>
#include "mytime.h"

class Lyrics
{
private:

    /**
     * @brief structure of a line of lyric: time (from mm:ss to seconds), lrc_content (the actual literal string of lyric)
     */
    struct Lyric
    {
        long int time;
        std::string lrc_content;	///> content of a line of lyrics
        bool operator<(const Lyric&val) const{      ///> overload the operator "<", needed when comparing two lines of lyrics by their times
            return time<val.time;
        }
    };

    std::vector<std::string> origin_lyrics;	///> store each line of lyrics with time tag and content in one string

    /**
     * @brief file_analysis: splite lrc file to get each line of lyrics (with time tag) and save the string to "origin_lryics" vector.
     * @param lyrics_file: file path for lyrcis file
     */
    void file_analysis(std::string& lyrics_file);

    /**
     * @brief lyrics_analysis: analyze the lyrics string, separate the context and time.
     * @param lyrics_list: a list containing all literal lines of lyrics, not including time tags
     * @param time_index: a map containing pairs of index (position of a line of lyrics in the whole lyrics file) and corresponding time tag of that line of lyrics
     */
    void lyrics_analysis(QStringList &lyrics_list, QMap<qint64, qint64> &time_index);

public:
    /**
     * @brief line_lyrics: store each line of lyrics with time tag and content in different place.
     */
    std::vector<Lyric> line_lyrics;

    /**
     * @brief Constructor of the lyrics class
     * @param lyrics_file: the file path for lyrics file
     * @param lyrics_list: a stringlist that is going to store all literal contents
     * @param time_index: a map containing pairs of index (position of a line of lyrics in the whole lyrics file) and corresponding time tag of that line of lyrics
     */
    Lyrics(std::string& lyrics_file, QStringList &lyrics_list, QMap<qint64, qint64> &time_index);
    Lyrics();
    ~Lyrics();

    /**
     * @brief get_lyric: get a line of lyrics by a given time
     * @param time
     * @return the line of lyrics by that given time
     */
    std::string get_lyric(long int time);



};

#endif
