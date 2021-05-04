#include "lyrics.h"

using namespace std;

Lyrics::Lyrics(string& lyrics_file, QStringList &lyrics_list, QMap<qint64, qint64> &time_index)
{
    file_analysis(lyrics_file);		///> call file_analysis function to analyze .lrc file
    lyrics_analysis(lyrics_list, time_index);			///> call lyrics_analysis to analyze the vector from file_analysis

    stable_sort(line_lyrics.begin(), line_lyrics.end());		///> sort the lyrics by time
}

Lyrics::Lyrics()    ///> default constructor
{

}

Lyrics::~Lyrics()   ///> the destructor
{

}

void Lyrics::file_analysis(string& lyrics_file)
{
    string lrc_line;
    ifstream filename(lyrics_file);

    if (filename.fail())    ///> file does not exist
    {
        cout << "Error: file doesn't exist." << endl;
        exit(1);
    }
    while (!filename.eof())				///> while loop for going through each line of the file
    {
        getline(filename, lrc_line);		///> get the content of each line which stores information of lyrics
        origin_lyrics.push_back(lrc_line);	///> add the content to vector "orgin_lyrics"
    }
}

void Lyrics::lyrics_analysis(QStringList &lyrics_list, QMap<qint64, qint64> &time_index) {
    int index;
    string temp_min;
    string temp_sec;
    Lyric lyric;
    MyTime lrc_time;
    qint64 map_index = 0;

    for (size_t i = 0; i < origin_lyrics.size(); i++) {
        // get the content of the lyrics from lyrics string
        index = origin_lyrics[i].find_last_of(']');		///> find the last ']' in the string
        ///> the text from the indexth charater to the last character of string is lyrics content
        lyric.lrc_content = origin_lyrics[i].substr(index + 1, origin_lyrics[i].size() - index - 1);
        lyrics_list.append(QString::fromStdString(origin_lyrics[i].substr(index + 1, origin_lyrics[i].size() - index - 1)));

        // get the time tag of lyrics from lyrics string
        index = -1;
        while (true)
        {
            index = origin_lyrics[i].find_first_of('[', index + 1);		///> find the first '[' in the string

            if (index == string::npos) break;

            int min_index = origin_lyrics[i].find_first_of(":", index);		///> min_index stores the place of first ":"
            int sec_index = origin_lyrics[i].find_first_of(".", min_index);		///> sec_index stores the place of first "."

            // the value after first "[" and before ":" represents minute
            temp_min = origin_lyrics[i].substr(index + 1, min_index - index - 1);
            lrc_time.min = atoi(temp_min.c_str());

            // the value after first ":" and before "." represents second
            temp_sec = origin_lyrics[i].substr(min_index + 1, sec_index - min_index - 1);
            lrc_time.sec = atoi(temp_sec.c_str());

            // call the function from Time.h to convert the value to integer
            lyric.time = lrc_time.from_Time_to_int(lrc_time);
            time_index.insert(lyric.time, map_index++);

        }

        line_lyrics.push_back(lyric);
    }
}


string Lyrics::get_lyric(int long time)
{
    for (size_t i = 0; i < line_lyrics.size(); i++)
    {
        if (line_lyrics[i].time > time)
        {
            return line_lyrics[i - 1].lrc_content;
        }
    }
    return line_lyrics[line_lyrics.size() - 1].lrc_content;
}
