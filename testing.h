/**
  * Testing.h
  * CS 3307 - RaspberryOke
  *
  * Selection menu.
  * A selection menu interface will be implemented.
  * An user can choose a song to sing by clicking the play button at the end of each line.
  * After clicking, a player interface (media.h/.cpp) will pop up to display the lyrics
  */

#ifndef TESTING_H
#define TESTING_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QDialog>
#include <QDesktopWidget>
#include <QBoxLayout>
#include <QVector>
#include "song.h"
#include <QDebug>
#include "media.h"
#include <iostream>
#include <fstream>
#include <stdio.h> 
#include <curl/curl.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>

QT_BEGIN_NAMESPACE
namespace Ui { class Testing; }
class QAbstractItemView;
QT_END_NAMESPACE

class Testing : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor of the class: setting up ui, initiating objects
     * @param parent
     */
    Testing(QWidget *parent = nullptr);
    ~Testing();

public slots:
    /**
     * @brief onPlayBtnClicked: after the user hit the play button,
     * this slot will handle this request by passing lyrics file and song file to the player interface
     * with the help of the hitPlayBtn signal to notify the media/player class.
     */
    void onPlayBtnClicked();

signals:
    /**
     * @brief hitPlayBtn: a signal to notify things are coming for media/player class
     * @param song_path
     * @param lyrics_path
     */
    void hitPlayBtn(QString song_path, QString lyrics_path);

private:
    Ui::Testing *ui;

    /**
     * @brief model, tableView: using MVC, first set up the model which has the access to all the data,
     * then connect the view with the model to display the data.
     */
    QStandardItemModel *model;
    QTableView *tableView;

    QPushButton *playBtn;

    /**
     * @brief song_vec: this is the vector containing all the song objects.
     */
    QVector<Song*> song_vec;
    /**
     * @brief getSong_Vec: we obtain a list of the songs by using this method.
     * @return a vector containing all song objects.
     */
    QVector<Song*> getSong_Vec();
    QString xml;

    /**
* @brief The struct to store the file name and file stream to transfer the files from server to local.
*/
struct FtpFile {
    const char *filename;
    FILE *stream;
};


    /**
    * @brief The helper to write the file from file stream to a specific local address.
    * @param size size of the file
    * @param stream file stream for output
    */
    static size_t fDownload(void *buffer,size_t size, size_t nmemb, void *stream){
    struct FtpFile *out = (struct FtpFile*)stream;
    if(out && !out->stream) {
        out->stream=fopen(out->filename, "wb");
        if(!out->stream)
            return -1;
    }
    return fwrite(buffer, size, nmemb, out->stream);

}


    /**
    * @brief Download the file by using a ftp address with username and password.
    * Then download the file to the cache folder with outputname.
    * @param fileAddress a ftp address of the file with username and password
    * @param outputAddress output name for the file
    */
    int downloadFile(std::string fileAddress, std::string outputAddress);

};
#endif // TESTING_H
