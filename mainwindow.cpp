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

  //  ui->cost->setPrefix("руб. ");
  //  ui->weight->setPrefix("гр. ");
    ui->matrixResolution->setPrefix("Мпикс ");

    //ui->size->setText("ШШ-ДД-ВВ");
    ui->size->setCursorPosition(0);
    ui->size->setInputMask("00-00-00");  //нужна маска


    ui->nameOfModel->setPlaceholderText("Название модели");


ui->cost->setSuffix(" руб.");
ui->weight->setSuffix("гр.");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::spinChanged() {


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

QList<QString> write; //сначала запишем сюда
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


 //   bool changeLENS = ui->changeLens->isChecked();
//    QString lensChangeOrNot = transferFromBoolToStr(changeLENS);

    write <<  Model.getNameOfModel() //string just here, but int, bool arenot
    << category.getGategory()
    << transferFromBoolToStr(ui->analogOrNot->isChecked())
    << producer.getProducer()
    << matrixResolution.getMatrRes()
    << transferFromBoolToStr(ui->changeLens->isChecked())
    << sizeOfModel.getSize()
    << ui->weight->text()
    << ui->cost->text()
    << ui->date->text();

 //   write2 = write1;
//баг в 1 список добавляется еще и второй

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

void MainWindow::on_saveBtn_clicked()
{
    if ( ui->nameOfModel->text() != nullptr ) {
        write1.clear();
        ui->spisok->clear();
        if (ui->spinWriting->value() == 1) {
            createWrite();
            ui->spisok->addItems(write1);
            qDebug() << "1i";
        }
        else  {
            createWrite();
            ui->spisok->addItems(write2);
            qDebug() << "1e";
        }

    }
}//бля надо начинать писать документацию
void MainWindow::on_denied_clicked()
{

}


void MainWindow::on_spinWriting_valueChanged(int arg1)
{
    if ( arg1 == 1) {
        //очистить райтN ..  записать значения в райтN
        //очистить список .. показать райтN
        write1.clear();
        write = write1;
        ui->spisok->clear();
        ui->spisok->addItems(write1);        qDebug() << "I";
    }
    else if ( arg1 == 2) {
        write2.clear();
        write = write2;
        ui->spisok->clear();
        ui->spisok->addItems(write2);        qDebug() << "E";
    }
    else
        qDebug() << "ucantseethis";

}
