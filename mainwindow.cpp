#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp>
#include <QDate>

#include <QRandomGenerator>
#include "randomfunctions.h"
#include <QMessageBox>
#include <algorithm>
#include <functional>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createWindow();
}
//delete is dont working correctly
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCheckRes() {
    if ( callEnableDisable == 1)    {
        if (ui->analogOrNot->isChecked())
            ui->matrixResolution->setEnabled(true);
        else
            ui->matrixResolution->setEnabled(false);
    }
}

void MainWindow::setCheckPolProf() {
    if ( callEnableDisable == 1)    {
        if (ui->category->currentIndex() == 2)
            ui->changeLens->setEnabled(true);
        else
            ui->changeLens->setEnabled(false);
    }
}

fotobase MainWindow::createRecord() //из ui в экземпляр класса
{
    fotobase write;

    write.setNameOfModel(ui->nameOfModel->text());
    write.setCategory(ui->category->currentText());
    write.setAnalogOrNot(ui->analogOrNot->isChecked());
    write.setProducer(ui->producer->currentText());
    write.setMatrRes(ui->matrixResolution->value());
    write.setChangeLense(ui->changeLens->isChecked());
    write.setSize(ui->size->text());
    write.setWeight(ui->weight->value());
    write.setCost(ui->cost->value());
    write.setmyDate(ui->date->date());

    return write;
}
fotobase MainWindow::createRandomRecord()
{
    fotobase write;

    QTime now = QTime::currentTime();
    qsrand( now.msec() ); //угадай что это такое

    QString ModelsName = nameOfModelList.at(rand()%nameOfModelList.size());
    QString strCategory = categoryList.at(rand()%categoryList.size());
    bool changeLens;

    if (strCategory == categoryList.at(2))
        changeLens = randomBool();
    else
        changeLens = false;

    double whatismatrres;
    bool analogOrNot = randomBool();
    if ( analogOrNot == true)
        whatismatrres = resolution.at(qrand()%resolution.size());
    else
        whatismatrres = 2.0;

    QString strProducer = producerList.at(rand()%producerList.size());
    QString size = randSize();
    int weight = rand() % 8000 + 100 ;
    int cost = rand() % 150000  + 1000;

    QDate mydata;
    mydata = randomDate(mydata);

    write.setNameOfModel(ModelsName);
    write.setCategory(strCategory);
    write.setAnalogOrNot(analogOrNot);
    write.setProducer(strProducer);
    write.setMatrRes(whatismatrres);
    write.setChangeLense(changeLens);
    write.setSize(size);
    write.setWeight(weight);
    write.setCost(cost);
    write.setmyDate(mydata);

    return write;
}


void MainWindow::on_filling_clicked()
{
    //const int countOfFilling = 10;
    static int currentRow = 10;

    if ( countRecordAndRows-ui->spisok->rowCount() <= 11 ) {
         QMessageBox::warning(nullptr,"Alert", "Превышено максимальное число записей");
         return;
    }

    for (int i = 0; i < currentRow; i++)
    {
        record[i] = createRandomRecord();
    }
    for (int i=0;i<currentRow;i++)
    initializationTable(currentRow,2);

    sorting();

    fillingTable(ui->spisok->rowCount());

    currentRow+=10;

}

void MainWindow::fillingTable(int rows) {

    for ( int rowsCount=0; rowsCount<rows; rowsCount++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(record[rowsCount].getNameOfModel());
        ui->spisok->setItem(rowsCount, 0, item);

        item = new QTableWidgetItem(QString::number(record[rowsCount].getCost()));
        ui->spisok->setItem(rowsCount, 1, item);
     }

}
void MainWindow::loadRecord(fotobase value) //выводит на ui данные из экземпляра класса
{
    //set ui from value;
    ui->nameOfModel->setText(value.getNameOfModel());
    ui->category->setCurrentText(value.getGategory());
    ui->analogOrNot->setChecked(value.getAnalogOrNot());
    setCheckRes();
    ui->producer->setCurrentText(value.getProducer());
    ui->matrixResolution->setValue(value.getMatrRes());
    setCheckPolProf();
    ui->changeLens->setChecked(value.getChangeLense());
    ui->size->setText(value.getSize());
    ui->weight->setValue(value.getWeight());
    ui->cost->setValue(value.getCost());
    ui->date->setDate(value.getmyDate());   
}


void MainWindow::initializationTable (int rows, int columns) {
    ///////////////////вывод на table
//    Колонка	Формат
//    Название модели	Полностью
//    Цена (руб)	В формате целых чисел
    ui->spisok->setShowGrid(true);
    ui->spisok->horizontalHeader()->setStretchLastSection(true);
   // ui->spisok->verticalHeader()->setStretchLastSection(true);
    ui->spisok->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->spisok->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->spisok->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->spisok->setRowCount(rows);
    ui->spisok->setColumnCount(columns);

}


void MainWindow::on_saveBtn_clicked() //нажатие на кнопку Сохранить
{
    if (ui->nameOfModel->text() == nullptr ) {//пустая строка
        QMessageBox::warning(nullptr,"Alert", "Название не задано");
        return;
    }

    record[indexOfRecord] = createRecord(); //запишем в текущий record значения из ui
    qDebug() << "Запись" << indexOfRecord << "создана";
    //loadRecord( record[indexOfRecord] ); //показать их
    qDebug() << "Запись" << indexOfRecord << "загружена";

    ui->spisok->setItem( indexOfRecord, 0, new QTableWidgetItem(record[indexOfRecord].getNameOfModel())  );
    ui->spisok->setItem( indexOfRecord, 1, new QTableWidgetItem(QString::number(record[indexOfRecord].getCost()))  );

    callEnableDisable=0;
    reset();
    ui->changeLens->setEnabled(false);
    ui->matrixResolution->setEnabled(false);
    editMode(indexOfRecord, false);
    ///////////////////
//    fillingTable(ui->spisok->rowCount());
//    for (int i=0; i<ui->spisok->rowCount(); i++)
//        qDebug() << record[i];
    ////////////////////
    sorting();
}

void MainWindow::sorting() {
   //  Записи упорядочиваются по следующим полям: категория, разрешение матрицы, цена, производитель, модель
    std::sort(record.begin(), record.end());
    //fillingTable(ui->spisok->rowCount());
    qDebug() << "Записи отсортированы";
}

void MainWindow::on_denied_clicked()//нажатие на кнопку Отменить
{
    //loadRecord(record[indexOfRecord]);
    qDebug() << "Запись" << indexOfRecord << "загружена";

    callEnableDisable=0;
    reset();
    ui->changeLens->setEnabled(false);
    ui->matrixResolution->setEnabled(false);
    editMode(indexOfRecord, false);
    sorting();
    if (improvisanalCurrentCellChanged == 1)
    {
        QTableWidgetItem *ditem  = ui->spisok->takeItem(indexOfRecord, 0);
        QTableWidgetItem *ditem2 = ui->spisok->takeItem(indexOfRecord, 1);
        delete ditem;
        delete ditem2;

        ui->spisok->removeRow(indexOfRecord);
    }

}

void MainWindow::enableDisableEdit(bool arg) {

    ui->analogOrNot->setEnabled(arg);
    ui->category->setEnabled(arg);
    ui->cost->setEnabled(arg);
    ui->date->setEnabled(arg);
    ui->nameOfModel->setEnabled(arg);
    ui->producer->setEnabled(arg);
    ui->size->setEnabled(arg);
    ui->weight->setEnabled(arg);

    ui->saveBtn->setVisible(arg);
    ui->denied->setVisible(arg);

    ui->filling->setEnabled(!arg);
    ui->deleteBtn->setEnabled(!arg);
    ui->createBtn->setEnabled(!arg);

}

void MainWindow::on_editBtn_clicked()
{
    if ( callEnableDisable == 0)    {
        editMode(indexOfRecord, true);
        qDebug() << "edit";
        callEnableDisable=1;
    }
    else if(callEnableDisable ==1) {
        editMode(indexOfRecord, false);
        sorting();
        qDebug() << "!edit";
        ui->changeLens->setEnabled(false);
        ui->matrixResolution->setEnabled(false);
        reset();
        callEnableDisable=0;
    }

}
void MainWindow::reset() {

    ui->nameOfModel->setText("");
    ui->category->setCurrentText("Профессиональный");
    ui->analogOrNot->setChecked(false);
    setCheckRes();
    ui->producer->setCurrentText("Nikon");
    ui->matrixResolution->setValue(2.00);
    setCheckPolProf();
    ui->changeLens->setChecked(false);
    ui->size->setText("00-00-00");
    ui->weight->setValue(100);
    ui->cost->setValue(0);
    QDate data;
    data.setDate(2000, 1,1);
    ui->date->setDate(data);
}

void MainWindow::on_createBtn_clicked()
{
    if ( countRecordAndRows-ui->spisok->rowCount() <= 1 ) {
         QMessageBox::warning(nullptr,"Alert", "Превышено максимальное число записей");
         return;
    }
    int var = ui->spisok->rowCount();
    initializationTable(var+1,2);
    record[var] = createRecord();
    //loadRecord(record[var]);
    QTableWidgetItem *item = new QTableWidgetItem(record[var].getNameOfModel());
    QTableWidgetItem *item2 = new QTableWidgetItem(record[var].getCost());
    ui->spisok->setItem(var, 0, item);
    ui->spisok->setItem(var, 1, item2);


    ui->spisok->selectRow(var);

    callEnableDisable=1;
    editMode(var, true);

    improvisanalCurrentCellChanged =1;

    sorting();
}
void MainWindow::editMode(int row, bool arg) {

    if ( arg)
        ui->statusBar->showMessage("Режим редактирования");
    else
        ui->statusBar->showMessage(" ");

    enableDisableEdit(arg);
    ui->spisok->selectRow(row);
}

void MainWindow::on_deleteBtn_clicked()
{
    if ( ui->spisok->rowCount() <= 1 ) {
         QMessageBox::critical(nullptr,"Alert", "Не делай так");
         return;
    }

    QTableWidgetItem *ditem  = ui->spisok->takeItem(indexOfRecord, 0);
    QTableWidgetItem *ditem2 = ui->spisok->takeItem(indexOfRecord, 1);
    delete ditem;
    delete ditem2;

    ui->spisok->removeRow(indexOfRecord);

    int temp = ui->spisok->currentRow();
    if ( ui->spisok->currentRow() == 0)
        ui->spisok->selectRow(temp++);
    else
        ui->spisok->selectRow(temp--);
}


void MainWindow::on_spisok_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
   // qDebug() << currentRow;
    indexOfRecord = currentRow;
    loadRecord( record[indexOfRecord] );

    if (improvisanalCurrentCellChanged == 1 ) {
        callEnableDisable=0;
        reset();
        ui->changeLens->setEnabled(false);
        ui->matrixResolution->setEnabled(false);
        editMode(indexOfRecord, false);
        sorting();
        improvisanalCurrentCellChanged=0;
    }
}

void MainWindow::createWindow() {

    QRegExp AcceptIter ("^[a-zA-zа-яА-Я]\\w{0,29}");
    QValidator *validno = new QRegExpValidator(AcceptIter, this);
    record.resize(countRecordAndRows);
    ui->nameOfModel->setValidator(validno);

    connect( ui->analogOrNot, SIGNAL(clicked(bool)), this, SLOT(setCheckRes()) );
    connect( ui->category, SIGNAL(currentIndexChanged(int)), this, SLOT(setCheckPolProf()) );

    enableDisableEdit(false);

    ui->size->setCursorPosition(0);
    ui->size->setInputMask("00-00-00 мм.");  //нужна маска

    ui->nameOfModel->setPlaceholderText("Название модели");

    ui->cost->setSuffix(" руб.");
    ui->weight->setSuffix(" гр.");

    setWindowTitle("Почти курсач");

    ui->producer->addItems(producerList);
    ui->category->addItems(categoryList);

   loadRecord( record[indexOfRecord] ); //первая инициализация

   initializationTable(1, 2);

   ui->saveBtn->hide();
   ui->denied->hide();
   ui->spinWriting->setDisabled(true);

   ui->changeLens->setEnabled(false);
   ui->matrixResolution->setEnabled(false);
}
