#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QValidator>
#include <QDate>
#include "fotobase.h"
#include <QStringList>
#include <vector>
#include "fotodatabase.h"

#include <QList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
		explicit MainWindow(QWidget *parent = nullptr);
		~MainWindow();

		void closeEvent(QCloseEvent *cEvent);


		void addRecordToDatabase(const fotobase &data);
		fotobase createRecord();//из ui в экземпляр класса
		void loadRecord(fotobase value); //выводит на ui данные из экземпляра класса
		void createWindow(); //здесь конструктор класса(хех)
		//void createRandomWrite(fotobase write);
		void sorting();
		void initializationTable(int rows);

		void fillingTable(int rows); //
		// int deleting();

		void setToUi();




private slots:

    void setCheckRes();//ui
    void setCheckPolProf(); //ui
    void on_saveBtn_clicked(); //нажатие на кнопку Сохранить
    void on_denied_clicked(); //нажатие на кнопку Отменить
    void editMode(bool); //режим редактирования
    void enableDisableEdit(bool); //включение/выключение интерфейса


    void on_filling_clicked();
    void on_createBtn_clicked();
    void on_editBtn_clicked();
    void on_deleteBtn_clicked();

    void on_spisok_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_saveUsBtn_clicked();

    void on_loadBtn_clicked();

private:
    Ui::MainWindow *ui;
	fotoDatabase db;
    QList<fotobase> record; //записи тут
    int numberOfRecords = 0;
    int indexOfRecord = 1; //это счетчик [1,countRecordAndRows] мухах
    const int countRecordAndRows=998; //макс число записей
    //bool improvisanalCurrentCellChanged=0; //выход из режима редактирования
    int callEnableDisable = 0; //основная переменная для работы с режимом редактирования

    bool edit=0; //нажатие на кнопку отмену было после create -> удалить запись
    bool nonCreating=0;//строка создана, а запись еще нет

    int iteration=0; //для корректного удаления


};





#endif // MAINWINDOW_H
