#include "controls.h"
#include "ui_controls.h"
#include <QBoxLayout>
#include <QToolButton>
#include <QAudio>
#include <QStyle>
#include <QtGlobal>
#include <QDebug>


Controls::Controls(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Controls)
{
    ui->setupUi(this);
    playButton = new QToolButton(this);
    stopButton = new QToolButton(this);
    checkBox = new QCheckBox("Voice Monitoring", this);     /**< A checkBox with text "Voice Monitoring" */

    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    stopButton->setEnabled(true);
    checkBox->setCheckState(Qt::Unchecked);

    connect(playButton, &QAbstractButton::clicked, this, &Controls::playClicked);    /**< connecting signal(there're things to be handled) to slot(the method that handle things)*/
    connect(stopButton, &QAbstractButton::clicked, this, &Controls::stop);
    connect(checkBox, &QCheckBox::stateChanged, this, &Controls::mirrorChecked);

    controll_unit = new QGroupBox();
    QBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(stopButton);
    layout->addWidget(playButton);
    controll_unit->setLayout(layout);        /**< setting the layout of the player interface*/

}

Controls::~Controls()
{
    delete ui;
}


QMediaPlayer::State Controls::state() const
{
    return playerState;
}

void Controls::setState(QMediaPlayer::State state)
{
    if (state != playerState) {
        playerState = state;

        switch (state) {
        case QMediaPlayer::StoppedState:
            stopButton->setEnabled(true);
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        ///> while changing the state, we are also changing the icon of playButton to pauseButton
        case QMediaPlayer::PlayingState:
            stopButton->setEnabled(true);
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            break;
        case QMediaPlayer::PausedState:
            stopButton->setEnabled(true);
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        }
    }
}

void Controls::playClicked()
{
    switch (playerState) {
    case QMediaPlayer::StoppedState:
    case QMediaPlayer::PausedState:
        emit play();                    ///> QMediaPlayer will take care from here
        break;
    case QMediaPlayer::PlayingState:
        emit pause();
        break;
    }

}

void Controls::mirrorChecked(){
    if (checkBox->isChecked()){
        qDebug ("checked");
        system(qPrintable("pactl load-module module-loopback latency_msec=1"));  ///> pulseaudio package will handle voice monitoring
    }else{
        qDebug ("unchecked");
        system(qPrintable("pactl unload-module module-loopback"));
    }

}

QGroupBox* Controls:: getGroupBox(){
    return this->controll_unit;
}
