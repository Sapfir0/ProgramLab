#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QFileDialog>
#include <QMessageBox>


#include "fotobase.h"
#include "fotodatabase.h"


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

		void setToUi(uint id, int index);

        void saveChanges();


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

    void on_spisok_currentCellChanged(int currentRow);

    void on_saveUsBtn_clicked();

    void on_loadBtn_clicked();

private:
    Ui::MainWindow *ui;
	fotoDatabase db;
	uint currentId = 0;
    int indexOfRecord = 0; //это счетчик [1,countRecordAndRows] мухах
    int callEnableDisable = 0; //основная переменная для работы с режимом редактирования
	bool createClicked;

    bool edit=0; //нажатие на кнопку отмену было после create -> удалить запись
    bool nonCreating=0;//строка создана, а запись еще нет

    bool stopIt;

    QString filename = "./os.txt";

};




#endif // MAINWINDOW_H
