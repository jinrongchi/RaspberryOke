/**
  * Controls.h
  * CS 3307 - RaspberryOke
  *
  * Controllers/Buttons on the player interface.
  * This class implements three buttons, two control buttons to control the play of a song,
  * one checkbox button for voice monitoring, which is recording what a singer has sung and playing it out through speakers.
  * Details will be followed below.
  */

#ifndef CONTROLS_H
#define CONTROLS_H

#include <QWidget>
#include <QMediaPlayer>
#include <QGroupBox>
#include <QCheckBox>
#include <QtGlobal>
#include <lightshowcontroller.h>

QT_BEGIN_NAMESPACE
class QAbstractButton;
QT_END_NAMESPACE

namespace Ui {
class Controls;
}

class Controls : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor of this class.
     * Constructor of the class, setting up all the buttons, set them to default state/appearance.
     * And connect each button to its corresponding handler to handle events invoked upon it.
     * @param parent
     */
    explicit Controls(QWidget *parent = nullptr);

    /**
     * @brief Return the current state of the media player, and the default state is stopped state.
     * @return Current state of the media player
     */
    QMediaPlayer::State state() const;    /**< default StoppedState */

    /**
     * @brief Getter method when arranging layout of the player interface, i.e. where to put all the buttons.
     * @return A QGroupBox that will return a group of buttons (pointers)
     */
    QGroupBox* getGroupBox();

    /**
      * @brief Desctructor for the class
      */
    ~Controls();



public slots:
    /**
     * @brief Set the state of the media player, possible states consist of: stopped, playing, paused.
     * This is a public slot, "a function that is called in response to a particular signal" sent by other objects.
     * A slot can also be used as a normal class method.
     * And in this case, the slot is responsible for change the state of the media player based on what signal it receives from the caller.
     * @param state: set the current state to the state passed by parameter
     */
    void setState(QMediaPlayer::State state);

signals:
    /**
     * @brief A control button emitting play() signal.
     * A signal is sent when a particular event occurs, and in this case, if a play signal is sent by a controller button,
     * it is passing the message of the user wish to start play the song.
     *
     * pause(): the user wishes to pause the song
     * stop(): the user wishes to stop the song
     */
    void play();
    void pause();
    void stop();

private:
    /**
     * @brief the ui widget for the class, ease of use for designing purpose.
     */
    Ui::Controls *ui;

    /**
     * @brief playerState of the media player, now set to default state: stopped.
     */
    QMediaPlayer::State playerState = QMediaPlayer::StoppedState;

    /**
     * @brief playButton, stopButton, two controller buttons.
     * Noted: playButton can also be used as a pauseButton, just the case of switching icon
     */
    QAbstractButton *playButton;
    QAbstractButton *stopButton;

    /**
     * @brief a small checkBox offering the user the option of voice monitoring
     */
    QCheckBox *checkBox;

    /**
     * @brief controll_unit: bundle of all buttons
     */
    QGroupBox *controll_unit;



private slots:
    /**
     * @brief a public slot that objects other than this class can also call to handle the situation when the  playButton is Clicked.
     */
    void playClicked();

    /**
     * @brief handling the situation when the checkBox is checked/unchecked
     */
    void mirrorChecked();
};

#endif // CONTROLS_H
