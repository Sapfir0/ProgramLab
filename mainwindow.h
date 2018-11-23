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
    fotobase createRandomRecord(); //создание рандомной записи
    void createWindow(); //здесь конструктор класса(хех)
    //void createRandomWrite(fotobase write);
    void sorting();
    void initializationTable(int,int);

    void fillingTable(int rows); //


private slots:

    void setCheckRes();//ui
    void setCheckPolProf(); //ui
    void on_saveBtn_clicked(); //нажатие на кнопку Сохранить
    void on_denied_clicked(); //нажатие на кнопку Отменить
    void editMode(int,bool); //режим редактирования
    void enableDisableEdit(bool); //включение/выключение интерфейса
    void reset();//сброс интерфейса на дефолт

    void on_filling_clicked();
    void on_createBtn_clicked();
    void on_editBtn_clicked();
    void on_deleteBtn_clicked();
    void on_spisok_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

private:
    Ui::MainWindow *ui;  //уй
    QVector <fotobase> record; //записи тут
    int indexOfRecord = 0; //это счетчик [1,countRecordAndRows] мухах
    const int countRecordAndRows=998; //макс число записей
    bool improvisanalCurrentCellChanged=0; //костылек для выхода из режима редактирования
    int callEnableDisable = 0; //основная переменная для работы с режимом редактирования
    QStringList producerList = { "Nikon", "Panasonic", "Sony", "Canon", "Olympus", "Зенит" }; //самодокуентирующийся код
    QStringList categoryList = { "Профессиональный", "Любительский", "Полупрофессиональный"};
    QStringList nameOfModelList = { "GH-4", "TY-3", "Cyber-shot DSC-RX100", "Revolution", "X-A5", "EOS 77D", "TG-5", "Pen E-PL9" };
    QVector<double> resolution = { 2.45, 5.67, 16,73, 12.6, 11.23, 32.12};
};





#endif // MAINWINDOW_H
