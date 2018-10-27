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

    bool transferFromStrToBool(QString var);
    void denied(QList<QString> UnitedWrite);
    void saving(QList<QString> UnitedWrite);

private slots:
    void setCheckRes();
    void setCheckPolProf();

    void on_saveBtn_clicked();

    void on_denied_clicked();

    void on_spinWriting_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};





#endif // MAINWINDOW_H
