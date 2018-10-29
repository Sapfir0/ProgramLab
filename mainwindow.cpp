#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp>
#include <QDate>

#include <QRandomGenerator>

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

void MainWindow::on_saveBtn_clicked()
{
    write[indexWrite] = createRecord();
    loadRecord( write[indexWrite] );
}

void MainWindow::on_denied_clicked()
{
    loadRecord(write[indexWrite]);
}

void MainWindow::on_spinWriting_valueChanged(int arg1)
{
    indexWrite = arg1;
    qDebug() << indexWrite;
}


QString MainWindow::transferFromBoolToStr(bool var) {
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


}
