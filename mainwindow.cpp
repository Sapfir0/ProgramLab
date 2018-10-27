#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp>
#include <QDate>
#include "fotobase.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRegExp AcceptIter ("^[a-zA-zа-яА-Я]\\w{0,29}");
    QValidator *validno = new QRegExpValidator(AcceptIter, this);
    ui->nameOfModel->setValidator(validno);

    connect( ui->analogOrNot, SIGNAL(clicked(bool)), this, SLOT(setCheckRes()) );
    connect( ui->category, SIGNAL(currentIndexChanged(int)), this, SLOT(setCheckPolProf()) );

    ui->changeLens->setEnabled(false);
    ui->matrixResolution->setEnabled(false);

    ui->matrixResolution->setPrefix("Мпикс ");

    //ui->size->setText("ШШ-ДД-ВВ");
    ui->size->setCursorPosition(0);
    ui->size->setInputMask("00-00-00");  //нужна маска

    ui->nameOfModel->setPlaceholderText("Название модели");

    ui->cost->setSuffix(" руб.");
    ui->weight->setSuffix(" гр.");

    setWindowTitle("Почти курсач");


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

static QList<QString> write; //сначала запишем сюда
static QList<QString> write1; //если будут ошибки, убрать статик
static QList<QString> write2;
static QDate DATA;

void MainWindow::createWrite() {
    QString ModelsName = ui->nameOfModel->text();
    fotobase Model;
    Model.setNameOfModel(ModelsName);
    Model.getNameOfModel();

    QString strCategory = ui->category->currentText();
    fotobase category;
    category.setCategory(strCategory);
    category.getGategory();

    bool analogOrNot = ui->analogOrNot->isChecked();
   // QString analog = transferFromBoolToStr( ui->changeLens->isChecked());

    fotobase AnalogOrNot;
    AnalogOrNot.setAnalogOrNot(analogOrNot);
    AnalogOrNot.getAnalogOrNot();

    QString strProducer = ui->producer->currentText();
    fotobase producer;
    producer.setProducer(strProducer);
    producer.getProducer();

   /* float*/ QString whatismatrres = ui->matrixResolution->text().remove(0,6);
    fotobase matrixResolution;
    matrixResolution.setMatrRes(whatismatrres);
    matrixResolution.getMatrRes();

    bool changeLens = ui->changeLens->isChecked();
    //checkForAble();
    fotobase changeLensOrNot;
    changeLensOrNot.setChangeLense(changeLens);
    changeLensOrNot.getChangeLense();

    QString size = ui->size->text();
    fotobase sizeOfModel;
    sizeOfModel.setSize(size);
    sizeOfModel.getSize();

    int weight = ui->weight->text().remove(0,3).toInt();
    fotobase whatisweight;

    whatisweight.setWeight(weight);
    whatisweight.getWeight();

    int cost = ui->cost->text().remove(0,4).toInt();
    fotobase whatiscost;
    whatiscost.setCost(cost);
    whatiscost.getCost();

    fotobase data;
    data.setmyDate(ui->date->date());
    DATA = data.getmyDate();


    write <<  Model.getNameOfModel() //string just here, but int, bool arenot
    << category.getGategory()
    << transferFromBoolToStr( AnalogOrNot.getAnalogOrNot() )
    << producer.getProducer()
    << matrixResolution.getMatrRes()
    << transferFromBoolToStr( changeLensOrNot.getChangeLense() )
    << sizeOfModel.getSize()
    << ui->weight->text()
    << ui->cost->text()
    << ui->date->text();
}
QString MainWindow::transferFromBoolToStr(bool var) {
    if(var == true)
        return "true";
    else
        return "false";
}
bool MainWindow::transferFromStrToBool(QString var) {
    if ( var=="true")
        return true;
    else
        return false;
}

void MainWindow::on_saveBtn_clicked()
{
    if ( ui->nameOfModel->text() != nullptr ) {

        //если на спинбоксе 1, то из write записать значения в write1 (очистить юй-список, загрузить райт1)
        //если 2, в write2
        if (ui->spinWriting->value() == 1 ) {
            write.clear();
            createWrite();
            write1.clear();
            write1 = write;
            ui->spisok->clear();
            ui->spisok->addItems(write1);
        }
        else if (ui->spinWriting->value() == 2) {
            write.clear();
            createWrite();
            write2.clear();
            write2 = write;
            ui->spisok->clear();
            ui->spisok->addItems(write2);
        }
    }
}

void MainWindow::saving(QList<QString> UnitedWrite) {
    write.clear();
    createWrite();
    UnitedWrite.clear();
    UnitedWrite = write;
    ui->spisok->clear();
    ui->spisok->addItems(UnitedWrite);

}
void MainWindow::on_denied_clicked()
{
    //при нажатии на отмену мы должны запизхнуть в форму вводимых данных
    //то что у нас в текущем райте
    //мы не можем использовать райт, потому что при переключении между записями райт не меняется
    if ( ui->spinWriting->value() == 1)
    {
        qDebug() << write1;
        denied(write1);
    }
    else if (ui->spinWriting->value() == 2)
    {
        qDebug() << write2;
        denied(write2);
    }
}
void MainWindow::denied(QList<QString> UnitedWrite) {
//происходи вылет при нажатии на отмену есл в списке ничего нет
    if ( !write.isEmpty())
    {//возвращение данных из списка в форму
        if ( (ui->spinWriting->value() == 1 and !write1.isEmpty()) or (ui->spinWriting->value() == 2 and !write2.isEmpty()))
        {
                ui->nameOfModel->setText(UnitedWrite[0]);
                ui->category->setCurrentText(UnitedWrite[1]);
                ui->analogOrNot->setChecked( transferFromStrToBool(UnitedWrite[2]) );
                ui->producer->setCurrentText(UnitedWrite[3]);
                ui->matrixResolution->setValue( UnitedWrite[4].remove(0,6).toInt() );
                ui->changeLens->setChecked( transferFromStrToBool(UnitedWrite[5]) );
                ui->size->setText(UnitedWrite[6]);
                ui->weight->setValue(UnitedWrite[7].remove( UnitedWrite[7].size()-3, UnitedWrite[7].size()).toInt() );
                ui->cost->setValue(UnitedWrite[8].remove( UnitedWrite[8].size()-4, UnitedWrite[8].size()).toInt() );
                ui->date->setDate(DATA);
        }
    }
}

void MainWindow::on_spinWriting_valueChanged(int arg1)
{
    if ( arg1 == 1) {
        //очистить райтN ..  записать значения в райтN
        //очистить список .. показать райтN
        ui->spisok->clear();
        ui->spisok->addItems(write1);

        denied(write1);

    }
    else if ( arg1 == 2) {
        ui->spisok->clear();
        ui->spisok->addItems(write2);

        denied(write2);

    }
    else
        qDebug() << "ucantseethis";

}


