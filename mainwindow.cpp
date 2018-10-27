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
    ui->size->setInputMask("00-00-00 мм.");  //нужна маска

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

//static QList<QString> write; //сначала запишем сюда
//static QList<QString> write1; //если будут ошибки, убрать статик
//static QList<QString> write2;
static QDate DATA;

void MainWindow::createWrite() {
    fotobase write;
    fotobase write1;
    fotobase write2;

    QString ModelsName = ui->nameOfModel->text();
    QString strCategory = ui->category->currentText();
    bool analogOrNot = ui->analogOrNot->isChecked();
    QString strProducer = ui->producer->currentText();
    /* float*/ QString whatismatrres = ui->matrixResolution->text().remove(0,6);
    bool changeLens = ui->changeLens->isChecked();
    QString size = ui->size->text();
    int weight = ui->weight->text().remove(0,3).toInt();
    int cost = ui->cost->text().remove(0,4).toInt();
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



   // DATA = data.getmyDate();



    // qDebug() << write.getNameOfModel();
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
            createWrite();
            fotobase::ourBaseGetter(fotobase::ourBaseSetter());
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


