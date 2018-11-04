#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QValidator>
#include <QDate>
#include "fotobase.h"
#include <QStringList>

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

    fotobase createRandomRecord();
    void denied();
    void filling();
    void createWindow(); //здесь конструктор класса(хех)
    void createRandomWrite(fotobase write);

    void sorting();

    void initializationTable(int,int);

    void fillingTable(int rows);


private slots:

    void setCheckRes();
    void setCheckPolProf();
    void on_saveBtn_clicked(); //нажатие на кнопку Сохранить
    void on_denied_clicked(); //нажатие на кнопку Отменить
    void on_spinWriting_valueChanged(int arg1);

    void on_filling_clicked();

private:
    Ui::MainWindow *ui;
    fotobase record[10]; //10 экземпляров
    int indexOfRecord = 1; //это счетчик [1,10]

    //перекинь это в класс фотобейс
    //Инициализируйте static QList вне объявления класса.
    //static const QList<QString> MyClass::list={"1", "2"};
    QStringList producerList = { "Nikon", "Panasonic", "Sony", "Canon", "Olympus", "Зенит" };
    QStringList categoryList = { "Профессиональный", "Любительский", "Полупрофессиональный"};
    QStringList nameOfModelList = { "GH-4", "TY-3", "Porec", "Revolution", "Фото", "GEK", "KEK", "I" };

};





#endif // MAINWINDOW_H
