#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QString OS="default";
#if (defined (_WIN32) || defined (_WIN64))
     OS = "Windows";
#elif (defined (LINUX) || defined (__linux__))
     OS = "Linux";
#endif

//     if ( OS == "Windows")     {
//        qApp->setWindowIcon(QIcon(":/img/icons8-windows-xp-26.png"));
//     }
//     else if ( OS == "Linux")     {
//         qApp->setWindowIcon(QIcon(":/img/icons8-linux-26.png"));
//     }


    MainWindow w;
    w.show();

    return a.exec();
}
