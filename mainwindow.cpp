#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp>
#include <QDate>

#include <QMessageBox>
#include <algorithm>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createWindow();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCheckRes() {
    if ( callEnableDisable == 1) {
        if (ui->analogOrNot->isChecked())
            ui->matrixResolution->setEnabled(true);
        else
            ui->matrixResolution->setEnabled(false);
    }
}

void MainWindow::setCheckPolProf() {
    if ( callEnableDisable == 1) {
        if (ui->category->currentIndex() == 2)
            ui->changeLens->setEnabled(true);
        else
            ui->changeLens->setEnabled(false);
    }
}

void MainWindow::addRecordToDatabase(const fotobase &data) {
    unsigned int t = record.appender(data);

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

void MainWindow::on_filling_clicked()
{
    for (int i=0; i<10; i++) {
        record.append(fotobase::randomix());
    }
    for (int i=0; i < 10; i++)
        initializationTable(numberOfRecords+i+1);

    numberOfRecords+=10;

    fillingTable(ui->spisok->rowCount());

}

void MainWindow::fillingTable(int rows) {

    for ( int rowsCount=0; rowsCount<rows; rowsCount++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(record.at(rowsCount).getNameOfModel());
        ui->spisok->setItem(rowsCount, 0, item);

        item = new QTableWidgetItem(QString::number(record.at(rowsCount).getCost()));
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


void MainWindow::initializationTable (int rows) {

    ui->spisok->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->spisok->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->spisok->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->spisok->setRowCount(rows);

}


void MainWindow::on_saveBtn_clicked() //нажатие на кнопку Сохранить
{

    if (ui->nameOfModel->text() == nullptr ) {//пустая строка
        QMessageBox::warning(nullptr,"Alert", "Название не задано");
        return;
    }

    callEnableDisable=0;

    indexOfRecord++;
    numberOfRecords++;


    editMode(false);


}

void MainWindow::sorting() {
   //  Записи упорядочиваются по следующим полям: категория, разрешение матрицы, цена, производитель, модель
}

void MainWindow::on_denied_clicked()//нажатие на кнопку Отменить
{
    record.removeLast();
    initializationTable(numberOfRecords);

    editMode(false);
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
    ui->editBtn->setEnabled(!arg);



}

void MainWindow::on_editBtn_clicked()
{
    if ( record.count() == 0)
        return;

    else if ( callEnableDisable == 0)    {
        editMode(true);
        callEnableDisable=1;
        loadRecord(record[indexOfRecord]);
        //не уверен что нужно то что ниже
        ui->changeLens->setEnabled(false);
        ui->matrixResolution->setEnabled(false);
    }
    else if(callEnableDisable ==1) {
        editMode(false);
        ui->changeLens->setEnabled(false);
        ui->matrixResolution->setEnabled(false);
        loadRecord(fotobase());
        callEnableDisable=0;
    }
    edit=1;

}


void MainWindow::on_createBtn_clicked()
{
    if ( countRecordAndRows-ui->spisok->rowCount() <= 1 ) {
         QMessageBox::warning(nullptr,"Achive 1 completed", "Превышено максимальное число записей");
         return;
    }

    editMode(true);

    initializationTable(numberOfRecords+1);
    fillingTable(ui->spisok->rowCount());

}


void MainWindow::editMode(bool arg) {

    if ( arg)
        ui->statusBar->showMessage("Режим редактирования");
    else
        ui->statusBar->showMessage(" ");

    enableDisableEdit(arg);
}

void MainWindow::on_deleteBtn_clicked()
{
    record.removeAt(indexOfRecord);
    if (ui->spisok->rowCount() == 1)
        ui->spisok->reset();

    ui->spisok->removeRow(indexOfRecord);
    indexOfRecord--;
    numberOfRecords--;
}



int MainWindow::deleting() {

    return 0;
}


void MainWindow::on_spisok_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    indexOfRecord=currentRow;
    loadRecord(record.at(indexOfRecord));

}

void MainWindow::exit() {
//    QMessageBox msgBox;
//    msgBox.setText("The document has been modified.");
//    msgBox.setInformativeText("Do you want to save your changes?");
//    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
//    msgBox.setDefaultButton(QMessageBox::Save);
//    int ret = msgBox.exec();

}

void MainWindow::createWindow() {

    QRegExp AcceptIter ("^[a-zA-zа-яА-Я]\\w{0,29}");
    QValidator *validno = new QRegExpValidator(AcceptIter, this);
    ui->nameOfModel->setValidator(validno);

    connect( ui->analogOrNot, SIGNAL(clicked(bool)), this, SLOT(setCheckRes()) );
    connect( ui->category, SIGNAL(currentIndexChanged(int)), this, SLOT(setCheckPolProf()) );
 //   connect( this, SIGNAL(destroyed(QObject*)), this, SLOT(exit) );

    enableDisableEdit(false);

    ui->size->setCursorPosition(0);
    ui->size->setInputMask("00-00-00 мм.");  //нужна маска

    ui->nameOfModel->setPlaceholderText("Название модели");

    ui->cost->setSuffix(" руб.");
    ui->weight->setSuffix(" гр.");
    setWindowTitle("Почти курсач");

   ui->saveBtn->hide();
   ui->denied->hide();
   ui->spinWriting->setDisabled(true);

   ui->changeLens->setEnabled(false);
   ui->matrixResolution->setEnabled(false);

}
