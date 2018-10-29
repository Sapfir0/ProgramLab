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

    fotobase createRecord();//из ui в экземпляр класса
    void loadRecord(fotobase value); //выводит на ui данные из экземпляра класса

    QString transferFromBoolToStr(bool var);

    void denied();
    void zapolnenie();

    void createWindow();

    void createRandomWrite(fotobase write);


private slots:

    void setCheckRes();
    void setCheckPolProf();
    void on_saveBtn_clicked();
    void on_denied_clicked();
    void on_spinWriting_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    fotobase record[10]; //10 экземпляров
    int indexOfRecord = 0; //это счетчик [1,10]
};





#endif // MAINWINDOW_H
