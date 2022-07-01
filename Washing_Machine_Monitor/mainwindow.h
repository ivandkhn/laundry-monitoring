#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtGui>
#include <QtCore>
#include "qextserialport.h"
#include "qextserialenumerator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int testFlag = 100;

private slots:
    void on_pushButton_clicked();
    void receive();


private:
    Ui::MainWindow *ui;
    QextSerialPort port;
    QMessageBox error;

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // MAINWINDOW_H
