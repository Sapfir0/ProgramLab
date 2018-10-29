#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QValidator>
#include <QDate>
#include "fotobase.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createWrite(fotobase writing);
    QString transferFromBoolToStr(bool var);

    bool transferFromStrToBool(QString var);
    void denied(QList<QString> UnitedWrite);
    void zapolnenie();

    void createWindow();


    void createRandomWrite(fotobase write);
//    fotobase whereiswrite;
////    fotobase write1;
////    fotobase write2;
//    fotobase write[10];

private slots:
    void setCheckRes();
    void setCheckPolProf();

    void on_saveBtn_clicked();

    void on_denied_clicked();

    void on_spinWriting_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    fotobase write[10];
};





#endif // MAINWINDOW_H
