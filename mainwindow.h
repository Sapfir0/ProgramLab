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
    void createWindow(); //здесь конструктор класса(хех)
    //void createRandomWrite(fotobase write);
    void sorting();
    void initializationTable(int rows);

    void fillingTable(int rows); //


private slots:

    void setCheckRes();//ui
    void setCheckPolProf(); //ui
    void on_saveBtn_clicked(); //нажатие на кнопку Сохранить
    void on_denied_clicked(); //нажатие на кнопку Отменить
    void editMode(bool); //режим редактирования
    void enableDisableEdit(bool); //включение/выключение интерфейса
    void reset();//сброс интерфейса на дефолт

    void on_filling_clicked();
    void on_createBtn_clicked();
    void on_editBtn_clicked();
    void on_deleteBtn_clicked();
    void on_spisok_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    Ui::MainWindow *ui;  //уй
    fotobase record[1000]; //записи тут
    int kolvo_zapisey = 0;
    int indexOfRecord = 0; //это счетчик [1,countRecordAndRows] мухах
    const int countRecordAndRows=998; //макс число записей
    bool improvisanalCurrentCellChanged=0; //костылек для выхода из режима редактирования
    int callEnableDisable = 0; //основная переменная для работы с режимом редактирования
};





#endif // MAINWINDOW_H
