#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExp>
#include <QDate>


#include <QGraphicsEffect>
//НЕДОРАБОТКА
//как перевести значение из QString в QDate
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

    ui->matrixResolution->setPrefix("Мпикс ");

    //ui->size->setText("ШШ-ДД-ВВ");
    ui->size->setCursorPosition(0);
    ui->size->setInputMask("00-00-00");  //нужна маска

    ui->nameOfModel->setPlaceholderText("Название модели");

    ui->cost->setSuffix(" руб.");
    ui->weight->setSuffix(" гр.");




//теняха
//    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
//     shadowEffect -> setBlurRadius(9.0);
//     shadowEffect -> setColor(QColor(0, 0, 0, 100));
//     shadowEffect -> setOffset(4.0);
//     ui->spisok->setGraphicsEffect(shadowEffect);
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
    //checkForAble();
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

void MainWindow::on_saveBtn_clicked() //переписать эту херню,
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
}//бля надо начинать писать документацию
void MainWindow::saving(QList<QString> UnitedWrite) {


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

    if ( !write.isEmpty() )
    {
        qDebug() << "NULL";
        ui->nameOfModel->setText(UnitedWrite[0]);
        ui->category->setCurrentText(UnitedWrite[1]);
        ui->analogOrNot->setChecked( transferFromStrToBool(UnitedWrite[2]) );
        ui->producer->setCurrentText(UnitedWrite[3]);
        ui->matrixResolution->setValue( UnitedWrite[4].remove(0,6).toInt() );
        ui->changeLens->setChecked( transferFromStrToBool(UnitedWrite[5]) );
        ui->size->setText(UnitedWrite[6]);
        ui->weight->setValue(UnitedWrite[7].remove( UnitedWrite[7].size()-3, UnitedWrite[7].size()).toInt() );
        ui->cost->setValue(UnitedWrite[8].remove( UnitedWrite[8].size()-4, UnitedWrite[8].size()).toInt() );
       // ui->date->setDate(UnitedWrite[9]);

    }
}

void MainWindow::on_spinWriting_valueChanged(int arg1)
{
    if ( arg1 == 1) {
        //очистить райтN ..  записать значения в райтN
        //очистить список .. показать райтN
        ui->spisok->clear();
        ui->spisok->addItems(write1);
    }
    else if ( arg1 == 2) {
        ui->spisok->clear();
        ui->spisok->addItems(write2);
    }
    else
        qDebug() << "ucantseethis";

}




//удалить хех

void MainWindow::resizeEvent(QResizeEvent *evt)
{
//бекграунд
//    Q_UNUSED(evt);
//    QPixmap bkgnd(":/img/95579c89365128e9322bfd247b353bc6.jpg");
//    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
//    QPalette plt = palette();
//    plt.setBrush(QPalette::Background,bkgnd);
//    setPalette(plt);
}

