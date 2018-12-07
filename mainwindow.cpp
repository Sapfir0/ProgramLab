#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp>
#include <QDate>

#include <QMessageBox>
#include <algorithm>

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

    if ( countRecordAndRows-ui->spisok->rowCount() <= 11 ) {
         QMessageBox::warning(nullptr,"Alert", "Превышено максимальное число записей");
         return;
    }

    for (int i = 0; i < 10; i++) {
        record[numberOfRecords+i] =  fotobase::randomix();
    }

    for (int i=0; i < 10; i++)
        initializationTable(numberOfRecords+i+1);

    numberOfRecords += 10;

    sorting();
    fillingTable(numberOfRecords);
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
    record[indexOfRecord] = createRecord(); //запишем в текущий record значения из ui
    sorting();
    fillingTable(numberOfRecords);

    callEnableDisable=0;
    loadRecord(fotobase());
    ui->changeLens->setEnabled(false);
    ui->matrixResolution->setEnabled(false);
    editMode(false);

    kostil=0;
}

void MainWindow::sorting() {
    std::sort(record, record+numberOfRecords);
   //  Записи упорядочиваются по следующим полям: категория, разрешение матрицы, цена, производитель, модель
}

void MainWindow::on_denied_clicked()//нажатие на кнопку Отменить
{
    callEnableDisable=0;
    loadRecord(fotobase());
    ui->changeLens->setEnabled(false);
    ui->matrixResolution->setEnabled(false);
    editMode(false);
    loadRecord(record[indexOfRecord]);

    ///////////
    /// \brief deleting

    kostil=0;

    qDebug() << edit;
    if (edit == 0) {
        deleting();
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
    ui->editBtn->setEnabled(!arg);

}

void MainWindow::on_editBtn_clicked()
{
    if ( callEnableDisable == 0)    {
        editMode(true);
        callEnableDisable=1;
        loadRecord(record[indexOfRecord]);
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
         QMessageBox::warning(nullptr,"Achive completed", "Превышено максимальное число записей");
         return;
    }
    initializationTable(numberOfRecords+1);
    record[numberOfRecords] = fotobase();

    QTableWidgetItem *item = new QTableWidgetItem(record[numberOfRecords].getNameOfModel());
    QTableWidgetItem *item2 = new QTableWidgetItem(record[numberOfRecords].getCost());
    ui->spisok->setItem(numberOfRecords, 0, item);
    ui->spisok->setItem(numberOfRecords, 1, item2);
    ui->spisok->setCurrentItem(item);
    callEnableDisable=1;
    numberOfRecords++;
    editMode(true);

    improvisanalCurrentCellChanged =1;

    loadRecord(fotobase());

    edit=0; //нажатие на кнопку отмену было после крейт -> удалить запись
    kostil=1; //строка создана, а запись еще нет
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

//    if (ui->spisok->rowCount() != 1)
//        ui->spisok->removeRow(indexOfRecord);
//    else {
//        initializationTable(0);
//    }
//    for (int i = indexOfRecord; i < numberOfRecords-1; i++)
//        record[i] = record[i+1];
//    numberOfRecords--;
//    if (numberOfRecords < 0)
//        numberOfRecords = 0;


    deleting();

}



int MainWindow::deleting() {

    if (ui->spisok->rowCount() == 1 ) {
        qDebug("ыыы");
        return -1;
    }

    if (improvisanalCurrentCellChanged == 1) {

        QTableWidgetItem *ditem  = ui->spisok->takeItem(indexOfRecord, 0);
        QTableWidgetItem *ditem2 = ui->spisok->takeItem(indexOfRecord, 1);
        delete ditem;
        delete ditem2;
        ui->spisok->removeRow(indexOfRecord);
        numberOfRecords--;
    }
    return 0;
}


void MainWindow::on_spisok_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{

    indexOfRecord = currentRow;
    loadRecord( record[indexOfRecord]);
    editMode(false);

    if (kostil==1) {
        qDebug() << "Тут должен быть костыль: "<< kostil;
//        int resOfDeleting = deleting();

//        if (resOfDeleting == -1)
//            qDebug() << "Исключение";
        ui->spisok->removeRow(previousRow);
        numberOfRecords--;
        kostil=0;
    }


}

void MainWindow::createWindow() {

    QRegExp AcceptIter ("^[a-zA-zа-яА-Я]\\w{0,29}");
    QValidator *validno = new QRegExpValidator(AcceptIter, this);
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

   loadRecord( record[indexOfRecord] ); //первая инициализация

   ui->saveBtn->hide();
   ui->denied->hide();
   ui->spinWriting->setDisabled(true);

   ui->changeLens->setEnabled(false);
   ui->matrixResolution->setEnabled(false);
}
