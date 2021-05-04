#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class Player;
}

class Player : public QWidget
{
    Q_OBJECT

public:
    explicit Player(QWidget *parent = nullptr);
    ~Player();
/*
public slots:
    void onBack();
*/
private:
    Ui::Player *ui;
};

#endif // PLAYER_H


// selection menu的play button will send a signal(song_path, lyrics_path) to player
// (a new widget class for outputing sound and displaying lyrics) -- audio output is ok, how to display lyrics?
// player will have a slot to handle two input file urls
// it's basically like how Qt player doing OPEN -> so plz refer to that
// -- player will also have a lots of buttons: play, pause, stop...-> so have a class for that
// and initiate controller object in player, and connect -> 估计要再看看button和放不放的关系啥的
