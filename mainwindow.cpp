#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "fotobasetablewidgetitem.h"

#include <QCloseEvent>

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
    if ( callEnableDisable == 1) {
        if (ui->analogOrNot->isChecked())
            ui->matrixResolution->setEnabled(true);
        else
            ui->matrixResolution->setEnabled(false);
    }
}

void MainWindow::setCheckPolProf() {
    if ( callEnableDisable == 1) {
        if (ui->category->currentIndex() == 2)
            ui->changeLens->setEnabled(true);
        else
            ui->changeLens->setEnabled(false);
    }
}

fotobase MainWindow::createRecord() //из ui в экземпляр класса
{
    fotobase write;

    write.setNameOfModel(ui->nameOfModel->text());
    write.setCategory(ui->category->currentText());
    write.setAnalogOrNot(ui->analogOrNot->isChecked());
    write.setProducer(ui->producer->currentText());
    write.setMatrRes(ui->matrixResolution->value());
    write.setChangeLense(ui->changeLens->isChecked());
    write.setSize(ui->size->text());
    write.setWeight(ui->weight->value());
    write.setCost(ui->cost->value());
    write.setmyDate(ui->date->date());

    return write;
}

void MainWindow::on_filling_clicked()
{
    initializationTable(db.count()+10);
    for (int i=0; i<10; i++) {
        fotobase random = fotobase::randomix();
		setToUi(db.append(random), db.count());
    }
    //sorting();
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
}


void MainWindow::initializationTable (int rows) {

    ui->spisok->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->spisok->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->spisok->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->spisok->setRowCount(rows);
}


void MainWindow::setToUi(uint id, int indORnumb) {

    QTableWidgetItem *item = new fotobaseTableWidgetItem(id, &db, 0);
    QTableWidgetItem *item2 = new fotobaseTableWidgetItem(id, &db, 1);

    ui->spisok->setItem(indORnumb,0,item);
    ui->spisok->setItem(indORnumb,1,item2);

}


void MainWindow::on_saveBtn_clicked() //нажатие на кнопку Сохранить
{
    if (ui->nameOfModel->text() == nullptr ) {//пустая строка
        QMessageBox::warning(nullptr,"Alert", "Название не задано");
        return;
    }


    if (edit==0) { //различаем нажатие: либо после кнопки создать(иф), либо после редактировать(елс)
        qDebug() << "Кнопка save нажата после кнопочки create";

        initializationTable(db.count()+1); //почти дефолтный метод
        fotobase temp = createRecord();
		setToUi(db.append(temp), db.count());


	} else {
        qDebug() << "Кнопка save нажата после кнопочки edit";

        auto nameOfModel = static_cast<fotobaseTableWidgetItem*>(ui->spisok->item(indexOfRecord, 0)); //кастуем заклинание
        auto cost = static_cast<fotobaseTableWidgetItem*>(ui->spisok->item(indexOfRecord, 1));
        db.update(nameOfModel->get_id(), createRecord());
        nameOfModel->update_text();
        cost->update_text();

        edit=0; //Редактирование завершено
	}


    editMode(false);

    //sorting();
}


/***
 * void QTableWidget::sortItems(int column, Qt::SortOrder order = Qt::AscendingOrder)
 * Sorts all the rows in the table widget based on column and order.
 */
void MainWindow::sorting() {
   //  Записи упорядочиваются по следующим полям: категория, разрешение матрицы, цена, производитель, модель
	ui->spisok->sortItems(0);
}

void MainWindow::on_denied_clicked()//нажатие на кнопку Отменить
{

    editMode(false);
    if (createClicked==true) {
        initializationTable(db.count()); //почти дефолтный метод
        createClicked=false;
    }
    //то что ниже внимание
    if (!createClicked && db.count() != 0)
        on_spisok_currentCellChanged(indexOfRecord);


}

void MainWindow::enableDisableEdit(bool arg) {

    ui->analogOrNot->setEnabled(arg);
    ui->category->setEnabled(arg);
    ui->cost->setEnabled(arg);
    ui->date->setEnabled(arg);
    ui->nameOfModel->setEnabled(arg);
    ui->producer->setEnabled(arg);
    ui->size->setEnabled(arg);
    ui->weight->setEnabled(arg);

    ui->saveBtn->setVisible(arg);
    ui->denied->setVisible(arg);

    ui->filling->setEnabled(!arg);
    ui->deleteBtn->setEnabled(!arg);
    ui->createBtn->setEnabled(!arg);
    ui->editBtn->setEnabled(!arg);

}

void MainWindow::on_editBtn_clicked()
{//нужно еще заливать изменения в список

    if ( callEnableDisable == 0)    {
        editMode(true);
        qDebug() << "callEnableDisable == 0";
        callEnableDisable=1;
    }
    else if(callEnableDisable ==1) {
        editMode(false);
        qDebug() << "callEnableDisable == 1";
        callEnableDisable=0;
    }
    ui->matrixResolution->setEnabled(false);
    ui->changeLens->setEnabled(false);
    edit=1;

    callEnableDisable=0; //подумать над строчкой
}


void MainWindow::on_createBtn_clicked()
{
    editMode(true);
    initializationTable(db.count()+1); //почти дефолтный метод

    createClicked = true;
    loadRecord( fotobase() );
    nonCreating=1; //не переключай столбцы или накажу
}


void MainWindow::editMode(bool arg) {

    if (arg)
        ui->statusBar->showMessage("Режим редактирования");
    else
        ui->statusBar->showMessage(" ");

    enableDisableEdit(arg);
}

void MainWindow::on_deleteBtn_clicked()
{
	db.remove(currentId);

//    if (indexOfRecord == ui->spisok->rowCount()-2) {
//        qDebug() << "м";
//    }

    if (ui->spisok->rowCount() == 1 || ui->spisok->rowCount()-2 == indexOfRecord) {
        ui->spisok->reset();
    }

    ui->spisok->removeRow(indexOfRecord);
    indexOfRecord--;

//    if (indexOfRecord < 0 && ui->spisok->rowCount() > 0)
//        indexOfRecord++;//хз почему но куте тейбл так работает

	ui->spisok->setCurrentCell(indexOfRecord, 0);
    //sorting();

    //qDebug() << "now index of record" << indexOfRecord;
}


void MainWindow::on_spisok_currentCellChanged(int currentRow)
{
    indexOfRecord = currentRow;

    if (nonCreating==1) {
        qDebug() << "Переключена строчка. Создание записи отменено";
        qDebug() << currentRow << ui->spisok->rowCount();
        if (currentRow+1==ui->spisok->rowCount())
            return;
        initializationTable(db.count()); //почти дефолтный метод
        //надо вызвать denied
        editMode(false);
        nonCreating=0;
    }


    bool dataBaseIsEmpty = db.count() == 0; // if(db.count==0) var=db.count

	ui->editBtn->setEnabled(!dataBaseIsEmpty);
	ui->deleteBtn->setEnabled(!dataBaseIsEmpty);

    qDebug() << "current record: " << indexOfRecord;

    if (indexOfRecord != -1) {
		currentId = static_cast<fotobaseTableWidgetItem*>(ui->spisok->item(indexOfRecord, 0))->get_id();
		loadRecord(db.record(currentId));
	}

	if (dataBaseIsEmpty) {
        loadRecord(fotobase()); //кидаем пустые поля
	}

}


void MainWindow::createWindow() {

    QRegExp AcceptIter ("^[a-zA-zа-яА-Я]\\w{0,29}");
    QValidator *validno = new QRegExpValidator(AcceptIter, this);
    ui->nameOfModel->setValidator(validno);

    connect( ui->analogOrNot, SIGNAL(clicked(bool)), this, SLOT(setCheckRes()) );
    connect( ui->category, SIGNAL(currentIndexChanged(int)), this, SLOT(setCheckPolProf()) );

    enableDisableEdit(false);

    ui->size->setCursorPosition(0);
    ui->size->setInputMask("00-00-00 мм.");  //нужна маска

    ui->nameOfModel->setPlaceholderText("Название модели");

    ui->cost->setSuffix(" руб.");
    ui->weight->setSuffix(" гр.");
    setWindowTitle("Почти курсач");

   ui->saveBtn->hide();
   ui->denied->hide();

   ui->changeLens->setEnabled(false);
   ui->matrixResolution->setEnabled(false);

}

void MainWindow::on_saveUsBtn_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this , "Сохранить файл Foto Base", QString() , "fotobase data (*.fm)"); // получение названия файла
	if (!filename.isEmpty())
		db.save(filename);
}

void MainWindow::on_loadBtn_clicked()
{

    QString filename = QFileDialog::getOpenFileName(this , "Открыть файл Foto Base", QString() , "fotobase data (*.*)"); // получение названия файла
	db.clear();
	initializationTable(0);


	if (!filename.isEmpty()) {
		if (db.load(filename)) {
			auto buff = db.records();
			initializationTable(buff.size());
            //qDebug() << buff.size() << db.count();
			for (int i=0; i<buff.size(); i++) {
				setToUi(buff[i].id, i);
			}
            //sorting();
		} else {
			QMessageBox::warning(this, "Alert", "Ошибка, файл не загружен");
		}
	}
}


void MainWindow::closeEvent(QCloseEvent *cEvent){
    QMessageBox::StandardButton wquit = QMessageBox::question(this, "Внимание", "Вы действительно хотите выйти?");
    if (wquit == QMessageBox::Yes) {
        cEvent->accept();
        /*if (db.isModidfied()) {
            QMessageBox::StandardButton wsave = QMessageBox::question(this, "Внимание", "Сохранить изменения?");
            if (wsave == QMessageBox::Yes) {
                if (filename.isEmpty())
                    filename = QFileDialog::getSaveFileName(this , "Сохранить файл fotodatabase Data Base", QDir::homePath() , "Tyrist Manual Data Base (*.tm)"); // получение названия файла
                if (!filename.isEmpty())
                    db.save(filename);
            }
        }*/
    }
    else cEvent->ignore();
}

void MainWindow::on_sortBtn_clicked()
{
    sorting();
}
