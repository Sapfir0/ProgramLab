#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qsrand( QTime::currentTime().msec() ); //угадай что это такое

//      QTextCodec *codec = QTextCodec::codecForName("UTF8");
//      QTextCodec::setCodecForTr(codec);
//      QTextCodec::setCodecForCStrings(codec);
//      QTextCodec::setCodecForLocale(codec);


    MainWindow w;
    w.show();

    return a.exec();
}
