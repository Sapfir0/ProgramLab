#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp>
#include <QDate>

#include <QRandomGenerator>
#include "randomfunctions.h"

#include <algorithm>
#include <functional>

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

    if (ui->analogOrNot->isChecked())
        ui->matrixResolution->setEnabled(true);
    else
        ui->matrixResolution->setEnabled(false);
}

void MainWindow::setCheckPolProf() {
    if (ui->category->currentIndex() == 2)
        ui->changeLens->setEnabled(true);
    else
        ui->changeLens->setEnabled(false);
}

fotobase MainWindow::createRecord() //из ui в экземпляр класса
{
    fotobase write;

    QString ModelsName = ui->nameOfModel->text();
    QString strCategory = ui->category->currentText();
    bool analogOrNot = ui->analogOrNot->isChecked();
    QString strProducer = ui->producer->currentText();
    double whatismatrres = ui->matrixResolution->value();
    bool changeLens = ui->changeLens->isChecked();
    QString size = ui->size->text();
    int weight = ui->weight->value();
    int cost = ui->cost->value();
    QDate mydata = ui->date->date();

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
fotobase MainWindow::createRandomRecord() //тут ошибка
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
        whatismatrres = workingRandom(0.05, 20.00);
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
    write.setSize(size); //нужна специальная функция
    write.setWeight(weight);
    write.setCost(cost);
    write.setmyDate(mydata);

    return write;
}


void MainWindow::filling() {


}

void MainWindow::on_filling_clicked()
{
    for (int i = 0; i < 10; i++)
    {
        record[i] = createRandomRecord();
    }
    sorting();
    fillingTable(record.size());

    qDebug() << "Рандомная запись" << indexOfRecord << "создана";
    loadRecord( record[indexOfRecord] ); //показать их
    qDebug() << "Рандомная запись" << indexOfRecord << "загружена";

//    std::function<int(fotobase, fotobase)> foo;
//    foo = fotobase::compare;
//    foo();
}

void MainWindow::fillingTable(int rows) {

    for ( int rowsCount=0; rowsCount<rows; rowsCount++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(record[rowsCount].getNameOfModel());
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        ui->spisok->setItem(rowsCount, 0, item);

        item = new QTableWidgetItem(QString::number(record[rowsCount].getCost()));
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
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
    ui->spisok->verticalHeader()->setStretchLastSection(true);
    /*for (int i=0; i<rows; i++)
        for (int j=0; j<columns; j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        }*/

    ui->spisok->setRowCount(rows);
    ui->spisok->setColumnCount(columns);
}


void MainWindow::on_saveBtn_clicked() //нажатие на кнопку Сохранить
{
    if (ui->nameOfModel->text() == nullptr ) //пустая строка
        return;

    record[indexOfRecord] = createRecord(); //запишем в текущий record значения из ui
    qDebug() << "Запись" << indexOfRecord << "создана";
    loadRecord( record[indexOfRecord] ); //показать их
    qDebug() << "Запись" << indexOfRecord << "загружена";

    ui->spisok->setItem( indexOfRecord, 0, new QTableWidgetItem(record[indexOfRecord].getNameOfModel())  );
    ui->spisok->setItem( indexOfRecord, 1, new QTableWidgetItem(QString::number(record[indexOfRecord].getCost()))  );
}

void MainWindow::sorting() {
   //  Записи упорядочиваются по следующим полям: категория, разрешение матрицы, цена, производитель, модель
    std::sort(record.begin(), record.end());
    qDebug() << "Записи отсортированы";

}

void MainWindow::on_denied_clicked()//нажатие на кнопку Отменить
{
    loadRecord(record[indexOfRecord]);
    qDebug() << "Запись" << indexOfRecord << "загружена";

}

void MainWindow::on_spinWriting_valueChanged(int arg1) //Spinbox изменил значение
{
    indexOfRecord = arg1-1; //вычтем 1 чтобы в спине было значение [1,10], а в таблице  [0,9]
    loadRecord( record[indexOfRecord] );

    ui->spisok->selectRow(indexOfRecord);
    qDebug() << "Запись" << indexOfRecord << "загружена";
}


void MainWindow::createWindow() {

    QRegExp AcceptIter ("^[a-zA-zа-яА-Я]\\w{0,29}");
    QValidator *validno = new QRegExpValidator(AcceptIter, this);
    record.resize(10);
    ui->nameOfModel->setValidator(validno);

    connect( ui->analogOrNot, SIGNAL(clicked(bool)), this, SLOT(setCheckRes()) );
    connect( ui->category, SIGNAL(currentIndexChanged(int)), this, SLOT(setCheckPolProf()) );

    ui->changeLens->setEnabled(false);
    ui->matrixResolution->setEnabled(false);

    ui->size->setCursorPosition(0);
    ui->size->setInputMask("00-00-00 мм.");  //нужна маска

    ui->nameOfModel->setPlaceholderText("Название модели");

    ui->cost->setSuffix(" руб.");
    ui->weight->setSuffix(" гр.");

    setWindowTitle("Почти курсач");

    ui->producer->addItems(producerList);
    ui->category->addItems(categoryList);

   loadRecord( record[indexOfRecord] ); //первая инициализация

   initializationTable(10, 2);

}
