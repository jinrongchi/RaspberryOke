#include "media.h"
#include "ui_media.h"
#include <QMediaPlaylist>
#include <QtWidgets>
#include "lightshowcontroller.h"
#include <stdio.h>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <future>

using namespace std;

bool blinking;
LightShowController *lights;

Media::Media(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Media)
{
    ui->setupUi(this);

    media = new QMediaPlayer(this);
    media->setAudioRole(QAudio::MusicRole);
    Controls *controller = new Controls(this);
    controller->setState(media->state());       ///> set buttons to be at default/stopped state

    // connecting signals that will possibly sent by controller to QMediaPlayer,
    // and let QMediaPlayer handle things for us
    connect(controller, &Controls::play, media, &QMediaPlayer::play);
    connect(controller, &Controls::pause, media, &QMediaPlayer::pause);
    connect(controller, &Controls::stop, media, &QMediaPlayer::stop);

    connect(media, &QMediaPlayer::stateChanged, controller, &Controls::setState);
    ///> if the state of playing a song is changed (like from play to pause),
    /// we will ask controller to handle this situation by like changing the icon of a button...

    connect(media, &QMediaPlayer::positionChanged, this, &Media::slotPositionChanged);
    ///> as the song plays, the position (in time/seconds) will also change,
    /// so connecting positionChanged to the slot:slotPositionChanged,
    /// the player is capable of changing the line of lyric to be displayed

    QBoxLayout *mediaLayout = new QVBoxLayout;          ///< setting up layout of this player interface
    lyrics_box = new QListWidget(this);
    lyrics_box->viewport()->setCursor(Qt::ArrowCursor);
    mediaLayout->addWidget(lyrics_box);
    mediaLayout->addWidget(controller->getGroupBox());
    setLayout(mediaLayout);

    lyrics_list = new QStringList();                   ///> initiating objects
    time_index = new QMap<qint64, qint64>();
    lyric_font = QFont("current_font", 13, QFont::DemiBold);
    
    lights = new LightShowController(60);

}

Media::~Media()
{   
    lyrics_box->clear();
    delete lyrics;
    lyrics_list->clear();
    time_index->clear();
    delete media;
    delete ui;
    lights->stop();
    delete lights;
    delete this;
}

void Media:: file_open(QString song_path, QString lyrics_path){
    media->setMedia(QUrl::fromLocalFile(song_path));
    
    lyrics_box->clear();
    lyrics_list->clear();
    time_index->clear();
    lyricsReady(lyrics_path, *lyrics_list, *time_index);
    lyrics_box->addItems(this->getLyricsList());
    changeLyricsFormat();

    media->setVolume(50);
    setWindowTitle("RaspberryOke Player");
    exec();
}

void Media::slotPositionChanged(qint64 positionTime){       ///> this positionTime will be given by QMediaPlayer
    position_t = positionTime/1000;
    QTime currentTime((position_t / 3600) % 24, (position_t / 60) % 60,
                           position_t % 60, (position_t * 1000) % 1000);
    QString currentTimeChanged = currentTime.toString("mm:ss");
    changeLyricsCurrentRow();
    lightscontrol();
}

qint64 Media::getPositionTime(){
    return position_t;
}

void Media::changeLyricsFormat(){
    for (int i = 0; i < this->getLyricsList().size(); i++){
        lyrics_box->item(i)->setTextAlignment(Qt::AlignCenter);
        lyrics_box->item(i)->setForeground(Qt::blue);
    }
}

void Media::changeLyricsCurrentRow(){
    if (this->getTimeIndexMap().contains(this->getPositionTime())){
        current_row = this->getTimeIndexMap().value(this->getPositionTime());
        max_rows = this->getTimeIndexMap().value(this->getTimeIndexMap().keys().last());

        lyrics_box->setCurrentRow(current_row);
        lyrics_box->item(current_row)->setForeground(Qt::green);
        lyrics_box->item(current_row)->setFont(lyric_font);

        if (current_row>0){
            for (int i = 0; i < current_row; i++){
                lyrics_box->item(i)->setForeground(Qt::blue);
                lyrics_box->item(i)->setFont(QFont());
            }
            for (int i = current_row+1; i<max_rows; i++){
                lyrics_box->item(i)->setForeground(Qt::blue);
                lyrics_box->item(i)->setFont(QFont());
            }
        }

    }
}

void Media::lyricsReady(QString lyrics_path, QStringList &lyrics_list, QMap<qint64, qint64> &time_index){
    std::string filename = lyrics_path.toUtf8().constData();
    lyrics = new Lyrics(filename, lyrics_list, time_index);
}

QStringList& Media:: getLyricsList(){
    return *(this->lyrics_list);
}

QMap<qint64, qint64>& Media:: getTimeIndexMap(){
    return *(this->time_index);
}

void Media::lightscontrol(){
    //blinking = true;
    //lights= new LightShowController(60);
    //auto func = async(launch::async, [] {
            //while(blinking) {

            lights->start();

            //this_thread::sleep_for(chrono::milliseconds(200));
          }

        //});

