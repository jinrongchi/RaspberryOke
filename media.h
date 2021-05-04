/**
  * Media.h
  * CS 3307 - RaspberryOke
  *
  * This is the interface for the player.
  * It will have all the buttons/checkbox we defined in our controls.h class, and a view for displaying lyrics.
  * This player interface will only pop out after user has selected a song from the selection menu.
  * And the user will have to close this interface if he/she wants to change a song.
  *
  */

#ifndef MEDIA_H
#define MEDIA_H

#include <QDialog>
#include "controls.h"
#include <QListWidget>
#include <QAudioProbe>
#include <QBoxLayout>
#include <QMediaPlaylist>
#include <lyrics.h>
#include <QTime>
#include <QStringList>
#include <QMap>

QT_BEGIN_NAMESPACE
class QAudioProbe;
class QPushButton;
class QAbstractItemView;
QT_END_NAMESPACE

namespace Ui {
class Media;
}

class Media : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor of the class: set up the ui, initiating objects, connecting this signal to that slot...
     * @param parent
     */
    explicit Media(QWidget *parent = nullptr);
    ~Media();

    /**
     * @brief Getter method for the current position in format of int (seconds)
     * @return the current position time (in seconds)
     */
    qint64 getPositionTime();

public slots:
    /**
     * @brief file_open: this is the slot/method that will open two files passed by the selecton menu.
     * This method will
     *      1) pass the song path to a QMediaPlayer object, and QMediaPlayer object will find the song following this path and play the song
     *      2) get the lyrics path from parameter and pass it to a private method lyricsReady to process the file: initiate a lyrics object
     *      3) set up the view for displaying the lyrics
     *      4) set volume
     * @param song_path: song file path
     * @param lyrics_path: lyrics file path
     */
    void file_open(QString song_path, QString lyrics_path);

private slots:
    /**
     * @brief slotPositionChanged: this slot is responsible for changing the line of lyrics to display according to different position of time in a song
     * @param positionTime
     */
    void slotPositionChanged(qint64 positionTime);

private:
    Ui::Media *ui;
    QMediaPlayer *media = nullptr;
    QListWidget *lyrics_box = nullptr;
    QAudioProbe *aup = nullptr;
    qint64 position_t;
    qint64 current_row;
    qint64 max_rows;

    /**
     * @brief the following three instance variables are needed for processing the lyrics file
     */
    Lyrics *lyrics;
    QStringList *lyrics_list;
    QMap<qint64, qint64> *time_index;

    /**
     * @brief changeLyricsFormat: this method is a decorating lines of lyrics: changing fonts, colors...
     */
    void changeLyricsFormat();

    /**
     * @brief changeLyricsCurrentRow: this method will change the format of the current row of the line of lyrics to notify users which line they should be sing along.
     * And set other rows back to normal
     */
    void changeLyricsCurrentRow();

    /**
     * @brief lyricsReady: a method to initiate a lyrics object
     * @param lyrics_path
     * @param lyrics_list
     * @param time_index
     */
    void lyricsReady(QString lyrics_path, QStringList &lyrics_list, QMap<qint64, qint64> &time_index);

    /**
     * @brief getLyricsList
     * @return the string list that containing all literal contents of lyrics
     */
    QStringList& getLyricsList();

    /**
     * @brief getTimeIndexMap
     * @return a map containing pairs of indices and time tags
     */
    QMap<qint64, qint64>& getTimeIndexMap();

    QFont lyric_font;
    void lightscontrol();


};

#endif // MEDIA_H
