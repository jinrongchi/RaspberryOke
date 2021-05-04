#include "player.h"
#include "ui_player.h"

Player::Player(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player)
{
    ui->setupUi(this);
    ui->pushButton->show();
    ui->lineEdit->setPlaceholderText(("Search..."));
}

Player::~Player()
{
    delete ui;
}
