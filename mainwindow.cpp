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


void MainWindow::createWrite(fotobase write) {

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

  // qDebug() << write.getNameOfModel();
}

void MainWindow::on_saveBtn_clicked()
{
    if ( ui->nameOfModel->text() != nullptr ) {

        if (ui->spinWriting->value() == 1 ) {
            createWrite(write[1]);
            qDebug() << write[1].getNameOfModel();

            createRandomWrite(write[1]);

        }
        else if (ui->spinWriting->value() == 2) {
            createWrite(write[2]);
            qDebug() << write[2].getGategory();
        }
    }
}

void MainWindow::zapolnenie() {

    //записать во все 10 записей
    for (int i=1; i<=9; i++)
    {
        createWrite(write[i]);
    }

}
int randomRange(int low, int high)
{
    return rand() % (high - low + 1) + low;
}

void MainWindow::createRandomWrite(fotobase write) {

    srand(time(NULL));

    int stop = rand() % 30 + 1;
    for (int n = 0; n < stop; ++n)
    {
        const char ch = randomRange('A', 'Z');
        qDebug() << ch;
    }
    QRandomGenerator randoming;
//задать рандмное выражение соотвествувющее регулярке


    int randCategory = rand() % 3 + 1;
    int randProducer = rand() % 6 + 1;
    QString ModelsName;
    QString strCategory = ui->category->currentText();
    bool analogOrNot = ui->analogOrNot->isChecked();
    QString strProducer = ui->producer->currentText();
    /* float*/ QString whatismatrres = ui->matrixResolution->text().remove(0,6);
    bool changeLens = ui->changeLens->isChecked();
    QString size = ui->size->text();
    int randWeight = rand() % 8000 + 100;
    int weight = ui->weight->text().remove(0,3).toInt();
    int randCost = rand() % 150000 + 1000;
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


}

void MainWindow::on_denied_clicked()
{
    //при нажатии на отмену мы должны запизхнуть в форму вводимых данных
    //то что у нас в текущем райте
    //мы не можем использовать райт, потому что при переключении между записями райт не меняется
    if ( ui->spinWriting->value() == 1)
    {

    }
    else if (ui->spinWriting->value() == 2)
    {

    }
}
void MainWindow::denied(QList<QString> UnitedWrite) {

}

void MainWindow::on_spinWriting_valueChanged(int arg1)
{
    int arg[9];
    if ( arg1 == 1) {
    }
    else if ( arg1 == 2) {
    }
    else
        qDebug() << "ucantseethis";

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

void MainWindow::createWindow() {

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
