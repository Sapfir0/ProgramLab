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

    ui->write1->setEnabled(false);
    ui->write2->setEnabled(false);
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
   // QString analog = transferFromBoolToStr( ui->changeLens->isChecked());

    fotoBase AnalogOrNot;
    AnalogOrNot.setAnalogOrNot(analogOrNot);
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


///
///
//    QString arr = static_cast<QString>(changeLensOrNot.getChangeLense());
//    qDebug() << &arr;

    write1 <<  Model.getNameOfModel() //string just here, but int, bool arenot
    << category.getGategory()
    << producer.getProducer()
    << matrixResolution.getMatrRes()

    << sizeOfModel.getSize()
    << ui->weight->text()
    << ui->cost->text()
    << ui->date->text();
    //<< ;
    write2 <<  Model.getNameOfModel() //string just here, but int, bool arenot
    << category.getGategory()
    << producer.getProducer()
    << matrixResolution.getMatrRes()
    << sizeOfModel.getSize()
    << ui->date->text();
//баг в 1 список добавляется еще и второй

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
//    if(write2.takeFirst() != nullptr)

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
        if(1) {
            ui->write1->setEnabled(true);
            write1.clear();///////////////////////TOO ALERT
            ui->spisok->clear();
            createWrite();
            ui->spisok->addItems(write1);
            access++;
        }
    }
}//бля надо начинать писать документацию
void MainWindow::on_saveBtn2_clicked()
{
    if ( ui->nameOfModel->text() != nullptr ) {
        static int access=0;
        if(1) {
            ui->write2->setEnabled(true);
            write2.clear(); //////////////////////////ALERT
            ui->spisok->clear();
            createWrite();
            ui->spisok->addItems(write2);

            access++;
        }
    }
}
