#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp>
#include <QDate>

#include <QRandomGenerator>
#include "randomfunctions.h"
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

    qDebug() << write.getMatrRes();

    return write;
}
fotobase MainWindow::createRandomRecord() //тут ошибка
{
    fotobase write;

    QTime now = QTime::currentTime();
    qsrand( now.msec() ); //угадай что это такое

    //QString ModelsName = randString(rand()%30+1);
    QString ModelsName = modelsName.at(rand()%modelsName.size());
    QString strCategory = fotobase categoryList.at(rand()%category.size());
    bool changeLens;
    if (strCategory == category.at(2))
        changeLens = randomBool();
    else
        changeLens = "2."; //ставит 20.00

    double whatismatrres;
    bool analogOrNot = randomBool();
    if ( analogOrNot == true)
        whatismatrres = my_rand(0.01, 20.00);


    QString strProducer = producer.at(rand()%producer.size());
    QString size = randSize();
    int weight = rand() % 8000 + 100 ;
    int cost = rand() % 150000  + 1000;
    QDate mydata = randomDate(mydata);

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

    for (int i=0; i<=9; i++)
    {
        record[i] = createRandomRecord();
        qDebug() << record[i].getProducer();
    }
    qDebug() << "Рандомная запись" << indexOfRecord << "создана";
    loadRecord( record[indexOfRecord] ); //показать их
    qDebug() << "Рандомная запись" << indexOfRecord << "загружена";

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
    ///////////////////вывод на table
//    Колонка	Формат
//    Название модели	Полностью
//    Цена (руб)	В формате целых чисел

    ui->spisok->setShowGrid(true);
    ui->spisok->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->spisok->horizontalHeader()->setStretchLastSection(true);
    ui->spisok->verticalHeader()->setStretchLastSection(true);

    ui->spisok->setRowCount(10);

    for ( int rows=0; rows<ui->spisok->rowCount();  rows++)
    {
            ui->spisok->setItem(rows,0,new QTableWidgetItem(record[rows].getNameOfModel()));
            ui->spisok->setItem(rows,1,new QTableWidgetItem(QString::number(record[rows].getCost()))); //не в строках, а в интах
     }


}

void MainWindow::on_saveBtn_clicked() //нажатие на кнопку Сохранить
{
    record[indexOfRecord] = createRecord(); //запишем в текущий record значения из ui
    qDebug() << "Запись" << indexOfRecord << "создана";
    loadRecord( record[indexOfRecord] ); //показать их
    qDebug() << "Запись" << indexOfRecord << "загружена";
}

void MainWindow::sorting() {
   //  Записи упорядочиваются по следующим полям: категория, разрешение матрицы, цена, производитель, модель

}
void MainWindow::on_denied_clicked()//нажатие на кнопку Отменить
{
    loadRecord(record[indexOfRecord]);
    qDebug() << "Запись" << indexOfRecord << "загружена";

}

void MainWindow::on_spinWriting_valueChanged(int arg1) //Spinbox изменил значение
{
    indexOfRecord = arg1;
    loadRecord( record[indexOfRecord] );
    qDebug() << "Запись" << indexOfRecord << "загружена";
}


void MainWindow::createWindow() {

    QRegExp AcceptIter ("^[a-zA-zа-яА-Я]\\w{0,29}");
    QValidator *validno = new QRegExpValidator(AcceptIter, this);
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

    ui->producer->addItems(producer);
    ui->category->addItems(category);


   loadRecord( record[indexOfRecord] ); //первая инициализация
   //по-другому не получилось

}
