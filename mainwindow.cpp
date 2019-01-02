#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    for (int i=0; i<10; i++) {
        fotobase random = fotobase::randomix();
        record.append(random);
		db.append(random);
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


void MainWindow::setToUi() {
    QTableWidgetItem *item = new QTableWidgetItem(createRecord().getNameOfModel());
    QTableWidgetItem *item2 = new QTableWidgetItem(QString::number( createRecord().getCost()));

    if ( edit == 0) {
    ui->spisok->setItem(numberOfRecords,0,item);
    ui->spisok->setItem(numberOfRecords,1,item2);
    }
    if (edit == 1)
    {
        ui->spisok->setItem(indexOfRecord,0,item);
        ui->spisok->setItem(indexOfRecord,1,item2);
        edit = 0;
    }
}


void MainWindow::on_saveBtn_clicked() //нажатие на кнопку Сохранить
{
    if (ui->nameOfModel->text() == nullptr ) {//пустая строка
        QMessageBox::warning(nullptr,"Alert", "Название не задано");
        return;
    }

    callEnableDisable=0;
    record.insert(numberOfRecords, createRecord());
    setToUi();

    if (edit != 1) {
        indexOfRecord++;
    }
    numberOfRecords = ui->spisok->rowCount();
    editMode(false);

    //запишем в файлик

}

void MainWindow::sorting() {
   //  Записи упорядочиваются по следующим полям: категория, разрешение матрицы, цена, производитель, модель
}

void MainWindow::on_denied_clicked()//нажатие на кнопку Отменить
{
    initializationTable(numberOfRecords);
    edit =0;
    callEnableDisable=0;
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
{//нужно еще заливать изменения в список
    if ( record.count() == 0)
        return;

    else if ( callEnableDisable == 0)    {
        editMode(true);//записать запись исходя из тго что в форме
        record.replace(indexOfRecord, createRecord() ); //спорная строчка
        setToUi();
        loadRecord(record[indexOfRecord]);
        qDebug() << "callEnableDisable == 0";
        //не уверен что нужно то что ниже
        callEnableDisable=1;
    }
    else if(callEnableDisable ==1) {
        editMode(false);
        qDebug() << "callEnableDisable == 1";
        //loadRecord(fotobase());
        callEnableDisable=0;
    }
    ui->matrixResolution->setEnabled(false);
    ui->changeLens->setEnabled(false);
    edit=1;

}


void MainWindow::on_createBtn_clicked()
{
    editMode(true);
    initializationTable(numberOfRecords+1);

    loadRecord( fotobase() );


    //ui->spisok->item(indexOfRecord, 0)->setData(Qt::UserRole, fotobase::id);
    //надо бы написать еще чтения айди

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
    record.removeAt(indexOfRecord);//можно смухлевать и не удалять из списка //вылета не будет

    if (indexOfRecord == ui->spisok->rowCount()-2) {
        qDebug() << "мусор в плюсах - это ты";
    }

    if (ui->spisok->rowCount() == 1)
        ui->spisok->reset();

    ui->spisok->removeRow(indexOfRecord);
    indexOfRecord--;

    numberOfRecords = ui->spisok->rowCount();

}


void MainWindow::on_spisok_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    indexOfRecord=currentRow;
    loadRecord(record.at(indexOfRecord));

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

   ui->saveBtn->hide();
   ui->denied->hide();
   ui->spinWriting->setDisabled(true);

   ui->changeLens->setEnabled(false);
   ui->matrixResolution->setEnabled(false);

}

void MainWindow::on_saveUsBtn_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this , "Сохранить файл Foto Base", QDir::homePath() , "fotobase (*.txt)"); // получение названия файла
	if (!filename.isEmpty())
		db.save(filename);
}

void MainWindow::on_loadBtn_clicked()
{

    QString filename = QFileDialog::getOpenFileName(this , "Открыть файл Foto Base", QDir::homePath() , "fotobase (*.fm)"); // получение названия файла
	db.clear();
	ui->spisok->clear();


	if (!filename.isEmpty())
		db.load(filename);
}


void MainWindow::closeEvent(QCloseEvent *cEvent){
//    QMessageBox::StandardButton wquit = QMessageBox::question(this, "Внимание", "Вы действительно хотите выйти?");
//    if (wquit == QMessageBox::Yes) {
//        cEvent->accept();
//        if (records.isModidfied()) {
//            QMessageBox::StandardButton wsave = QMessageBox::question(this, "Внимание", "Сохранить изменения?");
//            if (wsave == QMessageBox::Yes) {
//                if (filename.isEmpty())
//                    filename = QFileDialog::getSaveFileName(this , "Сохранить файл Tyrist Manual Data Base", QDir::homePath() , "Tyrist Manual Data Base (*.tm)"); // получение названия файла
//                if (!filename.isEmpty()) records.save(filename);
//            }
//        }
//    }
//    else cEvent->ignore();
}
