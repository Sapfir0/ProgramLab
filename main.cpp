#include "mainwindow.h"
#include <QApplication>
#include <QTime>
#include <QDebug>

#include <stdio.h>
#include <stdlib.h>
#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    try {
        MainWindow w;
        w.show();
        w.connect(&w, &MainWindow::destroyed, &a, &QApplication::quit);
        return a.exec();

    } catch (std::exception error) {

        QMessageBox::critical(nullptr, "Ошибка подключения к серверу", "К сожалению приложение не может работать");
        return -1;
    }

    qsrand( QTime::currentTime().msec() );

}
