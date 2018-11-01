#ifndef FOTOBASE_H
#define FOTOBASE_H

#include <QString>
#include <QDate>
#include <QDebug>

class fotobase
{
private:
    QString nameOfModel; //Название модели
    QString category; //Категория
    bool analogOrNot; //Цифровой
    QString producer; //Изготовитель
    double matrixRes; //Разрешение матрицы
    bool changeLens; //Сменная линза
    QString size; //Размер
    int weight; //Вес
    int cost; //Цена
    QDate date; //Дата

    //перекинь это в класс фотобейс
    //Инициализируйте static QList вне объявления класса.
    //static const QList<QString> MyClass::list={"1", "2"};
    QStringList producerList = { "Nikon", "Panasonic", "Sony", "Canon", "Olympus", "Зенит" };
    QStringList categoryList = { "Профессиональный", "Любительский", "Полупрофессиональный"};
    QStringList nameOfModelList = { "GH-4", "TY-3", "Porec", "Revolution", "Фото", "GEK", "KEK", "I" };

public:
    fotobase();
    int compare(const fotobase&, const fotobase&);

    void setNameOfModel(QString nameofModelclass);
    QString getNameOfModel();

    void setCategory(QString categoryclass);
    QString getGategory();

    void setAnalogOrNot(int analogOrNotclass);
    bool getAnalogOrNot();

    void setProducer(QString producerclass);
    QString getProducer();

    void setMatrRes(double matrixResolutionclass);
    double getMatrRes();

    void setChangeLense(bool changeLenseclass);
    bool getChangeLense();

    void setSize(QString sizeclass);
    QString getSize();

    void setWeight(int weightclass);
    int getWeight();

    void setCost(int costclass);
    int getCost();

    void setmyDate(QDate dateclass);
    QDate getmyDate();
};


#endif // FOTOBASE_H
