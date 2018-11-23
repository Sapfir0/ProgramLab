#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QValidator>
#include <QDate>
#include "fotobase.h"
#include <QStringList>
#include <vector>

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
    void editMode(int,bool);
    void enableDisableEdit(bool);
    void reset();

    void on_filling_clicked();

    void on_createBtn_clicked();

    void on_editBtn_clicked();

    void on_deleteBtn_clicked();

    void on_spisok_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    Ui::MainWindow *ui;
    QVector <fotobase> record; //10 экземпляров
    int indexOfRecord = 0; //это счетчик [1,10] мухах
    const int countRecordAndRows=35;
    bool improvisanalCurrentCellChanged=0;
    int callEnableDisable = 0;
    QStringList producerList = { "Nikon", "Panasonic", "Sony", "Canon", "Olympus", "Зенит" };
    QStringList categoryList = { "Профессиональный", "Любительский", "Полупрофессиональный"};
    QStringList nameOfModelList = { "GH-4", "TY-3", "Cyber-shot DSC-RX100", "Revolution", "X-A5", "EOS 77D", "TG-5", "Pen E-PL9" };
    std::vector<double> resolution = { 2.45, 5.67, 16,73, 12.6, 11.23, 32.12};
};





#endif // MAINWINDOW_H
