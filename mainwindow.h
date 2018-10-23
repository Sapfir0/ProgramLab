#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QValidator>
#include <QDate>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createWrite();
    QString transferFromBoolToStr(bool var);
    QString checkForAble();


private slots:
    void setCheckRes();
    void setCheckPolProf();

    void on_saveBtn_clicked();

    void on_write2_clicked();

    void on_write1_clicked();

    void on_saveBtn2_clicked();

private:
    Ui::MainWindow *ui;
};



class fotoBase
{
    private:
        QString nameOfModel;
        QString category;
        bool analogOrNot;
        QString producer;
        QString/*float*/ matrixRes;
        bool changeLens;
        QString size;
        int weight;
        int cost;
        QDate date;
    public:
        void setNameOfModel(QString nameofModelclass){
            nameOfModel = nameofModelclass;
        }
        QString getNameOfModel(){
            qDebug() << "Имя модели: " << nameOfModel;
            return nameOfModel;
        }

        void setCategory(QString categoryclass){
            category = categoryclass;
        }
        QString getGategory(){
            qDebug() << "Категория: " << category;
            return category;
        }

        void setAnalogOrNot(int analogOrNotclass){
            analogOrNot = analogOrNotclass;
        }
        bool getAnalogOrNot(){
            qDebug() << "Цифровой?: " << analogOrNot;
            return analogOrNot;
        }

        void setProducer(QString producerclass){
            producer = producerclass;
        }
        QString getProducer(){
            qDebug() << "Производитель: " <<  producer;
            return producer;
        }

        void setMatrRes(/*float*/QString matrixResolutionclass){
            matrixRes = matrixResolutionclass;
        }
        QString/*float*/ getMatrRes(){
            qDebug() << "Разрешение матрицы: " <<  matrixRes;
            return matrixRes;
        }
        //        bool changeLens;
        void setChangeLense(bool changeLenseclass){
             changeLens = changeLenseclass;
        }
        bool getChangeLense(){
            qDebug() << "Смена линзы: " << changeLens;
            return changeLens;
        }
        //QString size;
        void setSize(QString sizeclass){
              size = sizeclass;
        }
        QString getSize(){
            qDebug() << "Размер: " << size;
            return size;
        }
        //  int weight;
        void setWeight(int weightclass){
              weight = weightclass;
        }
        int getWeight(){
            qDebug() << "Вес: " << weight;
            return weight;
        }
        //int cost;
        void setCost(int costclass){
              cost = costclass;
        }
        int getCost(){
            qDebug() << "Цена: " << cost;
            return cost;
        }
        //QDate date;
        void setmyDate(QDate dateclass){
              date = dateclass;
        }
        void getmyDate(){
            qDebug() << "Дата: " << date;
        }
};

#endif // MAINWINDOW_H
