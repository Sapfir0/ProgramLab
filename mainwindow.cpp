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

    if (ui->analogOrNot->isChecked() == true)
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

    QString ModelsName = randString(rand()%30+1);
    QString strCategory = category.at(rand()%3);
    bool analogOrNot = randomBool();
    QString strProducer = producer.at(rand()%6);
//    double whatismatrres;
    bool changeLens = randomBool();
    QString size = randString(rand()%6+1);
    int weight = rand() % 8000 + 100 ;
    int cost = rand() % 150000  + 1000;
//    QDate mydata;

    write.setNameOfModel(ModelsName);
    write.setCategory(strCategory);
    write.setAnalogOrNot(analogOrNot);
    write.setProducer(strProducer);
//    write.setMatrRes(whatismatrres);
    write.setChangeLense(changeLens);
    write.setSize(size); //нужна специальная функция
    write.setWeight(weight);
    write.setCost(cost);
//    write.setmyDate(mydata);
    qDebug() << write.getProducer();
    return write;
}

void MainWindow::zapolnenie() {

    for (int i=1; i<=10; i++)
    {
        record[indexOfRecord] = createRandomRecord();

    }
}
void MainWindow::loadRecord(fotobase value) //выводит на ui данные из экземпляра класса
{
    //set ui from value;
    ui->nameOfModel->setText(value.getNameOfModel());
    ui->category->setCurrentText(value.getGategory());
    ui->analogOrNot->setChecked(value.getAnalogOrNot());
    ui->producer->setCurrentText(value.getProducer());
    ui->changeLens->setChecked(value.getChangeLense());
    ui->size->setText(value.getSize());
    ui->weight->setValue(value.getWeight());
    ui->cost->setValue(value.getCost());
    ui->date->setDate(value.getmyDate());

}

void MainWindow::on_saveBtn_clicked() //нажатие на кнопку Сохранить
{
    record[indexOfRecord] = createRecord(); //запишем в текущий record значения из ui
    loadRecord( record[indexOfRecord] ); //показать их
}

void MainWindow::on_denied_clicked()//нажатие на кнопку Отменить
{
    loadRecord(record[indexOfRecord]);
}

void MainWindow::on_spinWriting_valueChanged(int arg1) //Spinbox изменил значение
{
    indexOfRecord = arg1;
    loadRecord( record[indexOfRecord] );
}


QString transferFromBoolToStr(bool var) {
    if(var == true)
        return "true";
    else
        return "false";
}

void MainWindow::createWindow() {

    QRegExp AcceptIter ("^[a-zA-zа-яА-Я]\\w{0,29}");
    QValidator *validno = new QRegExpValidator(AcceptIter, this);
    ui->nameOfModel->setValidator(validno);

    connect( ui->analogOrNot, SIGNAL(clicked(bool)), this, SLOT(setCheckRes()) );
    connect( ui->category, SIGNAL(currentIndexChanged(int)), this, SLOT(setCheckPolProf()) );

    ui->changeLens->setEnabled(false);
    ui->matrixResolution->setEnabled(false);

    //ui->size->setText("ШШ-ДД-ВВ");
    ui->size->setCursorPosition(0);
    ui->size->setInputMask("00-00-00 мм.");  //нужна маска

    ui->nameOfModel->setPlaceholderText("Название модели");

    ui->cost->setSuffix(" руб.");
    ui->weight->setSuffix(" гр.");

    setWindowTitle("Почти курсач");

    ui->producer->addItems(producer);
    ui->category->addItems(category);





}

void MainWindow::on_filling_clicked()
{
    createRandomRecord();
}
