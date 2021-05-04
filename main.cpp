#include "testing.h"
#include "media.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDesktopWidget dw;
    Testing w;
    w.setWindowTitle("RaspberryOke🎤");
    int x = dw.width()*0.6;
    int y = dw.height()*0.6;
    w.setFixedSize(x, y);

    Media m;
    QObject::connect(&w, SIGNAL(hitPlayBtn(QString, QString)), &m, SLOT(file_open(QString, QString)));
    w.show();
    return a.exec();
}
