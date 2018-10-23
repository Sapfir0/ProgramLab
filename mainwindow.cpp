#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp>
#include <QDate>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QRegExp AcceptIter ("^[a-zA-z]\\w{0,29}");
    QValidator *validno = new QRegExpValidator(AcceptIter, this);
    ui->nameOfModel->setValidator(validno);



    connect( ui->analogOrNot, SIGNAL(clicked(bool)), this, SLOT(setCheckRes()) );
    connect( ui->category, SIGNAL(currentIndexChanged(int)), this, SLOT(setCheckPolProf()) );

    ui->changeLens->setEnabled(false);
    ui->matrixResolution->setEnabled(false);

    ui->cost->setPrefix("руб. ");
    ui->weight->setPrefix("гр. ");
    ui->matrixResolution->setPrefix("Мпикс ");

    //ui->size->setText("ШШ-ДД-ВВ");
    ui->size->setCursorPosition(0);
    ui->size->setInputMask("00-00-00");  //нужна маска
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


QList<QString> write1;
QList<QString> write2;

void MainWindow::createWrite() {
    QString ModelsName = ui->nameOfModel->text();
    fotoBase Model;
    Model.setNameOfModel(ModelsName);
    Model.getNameOfModel();

    QString strCategory = ui->category->currentText();
    fotoBase category;
    category.setCategory(strCategory);
    category.getGategory();

    bool analogOrNot = ui->analogOrNot->isChecked();
    QString analog = transferFromBoolToStr( ui->changeLens->isChecked());

    fotoBase AnalogOrNot;
    AnalogOrNot.setAnalogOrNot(analog);
    AnalogOrNot.getAnalogOrNot();

    QString strProducer = ui->producer->currentText();
    fotoBase producer;
    producer.setProducer(strProducer);
    producer.getProducer();

   /* float*/ QString whatismatrres = ui->matrixResolution->text().remove(0,6);
    fotoBase matrixResolution;
    matrixResolution.setMatrRes(whatismatrres);
    matrixResolution.getMatrRes();

    bool changeLens = ui->changeLens->isChecked();
    checkForAble();
    fotoBase changeLensOrNot;
    changeLensOrNot.setChangeLense(changeLens);
    changeLensOrNot.getChangeLense();


    QString size = ui->size->text();
    fotoBase sizeOfModel;
    sizeOfModel.setSize(size);
    sizeOfModel.getSize();

    int weight = ui->weight->text().remove(0,3).toInt();
    fotoBase whatisweight;
    whatisweight.setWeight(weight);
    whatisweight.getWeight();

    int cost = ui->cost->text().remove(0,4).toInt();
    fotoBase whatiscost;
    whatiscost.setCost(cost);
    whatiscost.getCost();

//    QString date = ui->date->text();
//    fotoBase whatisdate;
//    whatisdate.setmyDate(date);
//    whatisdate.getmyDate();

    write1 <<  Model.getNameOfModel() //string just here, but int, bool arenot
    << category.getGategory()
    << producer.getProducer()
    << matrixResolution.getMatrRes()
    << sizeOfModel.getSize()
    << ;

//    bool analogOrNot = ui->analogOrNot->isChecked();
//    bool changeLens = ui->changeLens->isChecked();
//    int weight = ui->weight->text().remove(0,3).toInt();
//    int cost = ui->cost->text().remove(0,4).toInt();
}
QString MainWindow::transferFromBoolToStr(bool var) {
    if(var == true)
        return "true";
    else
        return "false";

}
QString MainWindow::checkForAble() {
    if(!ui->changeLens->isEnabled())
        return "unable";

}


void MainWindow::on_write2_clicked()
{
    ui->spisok->clear();
    ui->spisok->addItems(write2);
}

void MainWindow::on_write1_clicked()
{
    ui->spisok->clear();
    ui->spisok->addItems(write1);
}

void MainWindow::on_saveBtn_clicked()
{
    if ( ui->nameOfModel->text() != nullptr ) {
        static int access=0;
        if(access<2) {
            ui->spisok->clear();
            createWrite();
            ui->spisok->addItems(write1);
            access++;
        }
    }
}
void MainWindow::on_saveBtn2_clicked()
{
    if ( ui->nameOfModel->text() != nullptr ) {
        static int access=0;
        if(access<2) {
            ui->spisok->clear();
            createWrite();
            ui->spisok->addItems(write2);

            access++;
        }
    }

}
