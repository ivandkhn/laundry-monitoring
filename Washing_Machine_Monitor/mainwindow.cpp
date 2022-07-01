#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <QPixmap>
#include <QPainter>
#include <QPicture>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/img/washing-machine-svgrepo-com.svg");
    QPixmap pix2(":/img/tum-logo.png");
    QPixmap pix3(":/img/smartphone-with-wireless-internet-svgrepo-com.svg");
    int w = ui->machine1->width();
    int h =ui->machine1->height();
    int w1 = ui->tum_logo->width();
    int h1 =ui->tum_logo->height();
    int w2 = ui->gateway_node->width();
    int h2 =ui->gateway_node->height();
    ui->machine1->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->machine2->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->machine3->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->machine4->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->machine5->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->machine6->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->tum_logo->setPixmap(pix2.scaled(w1,h1,Qt::KeepAspectRatio));
    ui->gateway_node->setPixmap(pix3.scaled(w2,h2,Qt::KeepAspectRatio));
    ui->edge_node->setPixmap(pix3.scaled(w2,h2,Qt::KeepAspectRatio));
    ui->edge_node_2->setPixmap(pix3.scaled(w2,h2,Qt::KeepAspectRatio));
    ui->sensor_node_1->setPixmap(pix3.scaled(w2,h2,Qt::KeepAspectRatio));
    ui->sensor_node_2->setPixmap(pix3.scaled(w2,h2,Qt::KeepAspectRatio));
    ui->sensor_node_3->setPixmap(pix3.scaled(w2,h2,Qt::KeepAspectRatio));
    ui->sensor_node_4->setPixmap(pix3.scaled(w2,h2,Qt::KeepAspectRatio));
    ui->sensor_node_5->setPixmap(pix3.scaled(w2,h2,Qt::KeepAspectRatio));
    ui->sensor_node_6->setPixmap(pix3.scaled(w2,h2,Qt::KeepAspectRatio));
    // Get all available COM Ports and store them in a QList.
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();

    port.setQueryMode(QextSerialPort::EventDriven);
    port.setPortName("/dev/ttyUSB0");
    port.setBaudRate(BAUD115200);
    port.setFlowControl(FLOW_OFF);
    port.setParity(PAR_NONE);
    port.setDataBits(DATA_8);
    port.setStopBits(STOP_1);
    port.open(QIODevice::ReadWrite);



    if (!port.isOpen())
    {
        error.setText("Unable to open port!");
        error.show();
        return;
    }
    QObject::connect(&port, SIGNAL(readyRead()), this, SLOT(receive()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QMainWindow::close();
}


void MainWindow::receive()
{
    static QString str;

    char ch;
    while (port.getChar(&ch))
    {
         str.append(ch);
    }
     ui->textEdit->append(str);
     if(str.contains("Q_STATUS")){
         static QString machine_number;
         static QString edge_mote_number;
         for (int i = 0; i < str.length(); i++) {
             if (str[i] == "m" && str[i+1]== 'a' && str[i+2]=='c'){
                 machine_number = str[i+16];
             }

             if (str[i] == "v" && str[i+1] == "i" && str[i+2] == "a"){
                 edge_mote_number = str[i+8];
             }



         }

         if (edge_mote_number == '7' && machine_number == '1'){
             testFlag = 0;
             update();
         } else if (edge_mote_number == '7' && machine_number == '2'){
             testFlag = 1;
             update();
         } else if (edge_mote_number == '7' && machine_number == '3'){
             testFlag = 2;
             update();
         } else if (edge_mote_number == '7' && machine_number == '4'){
             testFlag = 3;
             update();
         } else if (edge_mote_number == '7' && machine_number == '5'){
             testFlag = 4;
             update();
         } else if (edge_mote_number == '7' && machine_number == '6'){
             testFlag = 5;
             update();
         } else if (edge_mote_number == '8' && machine_number == '1'){
             testFlag = 6;
             update();
         } else if (edge_mote_number == '8' && machine_number == '2'){
             testFlag = 7;
             update();
         } else if (edge_mote_number == '8' && machine_number == '3'){
             testFlag = 8;
             update();
         } else if (edge_mote_number == '8' && machine_number == '4'){
             testFlag = 9;
             update();
         } else if (edge_mote_number == '8' && machine_number == '5'){
             testFlag = 10;
             update();
         } else if (edge_mote_number == '8' && machine_number == '6'){
             testFlag = 11;
             update();
         }





     }

     if (str.contains("A_STATUS")){
         static QString machine_number;
         static QString edge_mote_number;
         static QString status;
         for (int i = 0; i < str.length(); i++) {
             if (str[i] == "m" && str[i+1]== 'a' && str[i+2]=='c'){
                 machine_number = str[i+16];
             }

             if (str[i] == "v" && str[i+1] == "i" && str[i+2] == "a"){
                 edge_mote_number = str[i+8];
             }

         }

         if (edge_mote_number == '7' && machine_number == '1'){
             testFlag = 12;
             update();
         } else if (edge_mote_number == '7' && machine_number == '2'){
             testFlag = 13;
             update();
         } else if (edge_mote_number == '7' && machine_number == '3'){
             testFlag = 14;
             update();
         } else if (edge_mote_number == '7' && machine_number == '4'){
             testFlag = 15;
             update();
         } else if (edge_mote_number == '7' && machine_number == '5'){
             testFlag = 16;
             update();
         } else if (edge_mote_number == '7' && machine_number == '6'){
             testFlag = 17;
             update();
         } else if (edge_mote_number == '8' && machine_number == '1'){
             testFlag = 18;
             update();
         } else if (edge_mote_number == '8' && machine_number == '2'){
             testFlag = 19;
             update();
         } else if (edge_mote_number == '8' && machine_number == '3'){
             testFlag = 20;
             update();
         } else if (edge_mote_number == '8' && machine_number == '4'){
             testFlag = 21;
             update();
         } else if (edge_mote_number == '8' && machine_number == '5'){
             testFlag = 22;
             update();
         } else if (edge_mote_number == '8' && machine_number == '6'){
             testFlag = 23;
             update();
         }

         status.append("Machine Number ");
         status.append(machine_number);

         if (str.contains("STATUS_FREE")){
             status.append(" is FREE");
         }

         else if (str.contains("STATUS_FINISHING")){
             status.append(" is FINISHING");
         }

         else if (str.contains("STATUS_BUSY")){
             status.append(" is BUSY");
         }
         else {
             status.append(" is MALFUNCTIONING");
         }

        if (machine_number == '1'){
            if (str.contains("STATUS_FREE")){
                ui->machine1->setStyleSheet("QLabel { background-color : green;}");
            }
            else if (str.contains("STATUS_BUSY")){
                ui->machine1->setStyleSheet("QLabel { background-color : red;}");
            }
            else if (str.contains("STATUS_FINISHING")){
                ui->machine1->setStyleSheet("QLabel { background-color : yellow;}");
            }
            else if (str.contains("STATUS_UNKNOWN")){
                ui->textEdit_malfunc->append("Washer 1 is malfunctioning");
            }
        }

        if (machine_number == '2'){
            if (str.contains("STATUS_FREE")){
                ui->machine2->setStyleSheet("QLabel { background-color : green;}");
            }
            else if (str.contains("STATUS_BUSY")){
                ui->machine2->setStyleSheet("QLabel { background-color : red;}");
            }
            else if (str.contains("STATUS_FINISHING")){
                ui->machine2->setStyleSheet("QLabel { background-color : yellow;}");
            }
            else if (str.contains("STATUS_UNKNOWN")){
                ui->textEdit_malfunc->append("Washer 2 is malfunctioning");
            }
        }

        if (machine_number == '3'){
            if (str.contains("STATUS_FREE")){
                ui->machine3->setStyleSheet("QLabel { background-color : green;}");
            }
            else if (str.contains("STATUS_BUSY")){
                ui->machine3->setStyleSheet("QLabel { background-color : red;}");
            }
            else if (str.contains("STATUS_FINISHING")){
                ui->machine3->setStyleSheet("QLabel { background-color : yellow;}");
            }
            else if (str.contains("STATUS_UNKNOWN")){
                ui->textEdit_malfunc->append("Washer 3 is malfunctioning");
            }
        }

        if (machine_number == '4'){
            if (str.contains("STATUS_FREE")){
                ui->machine4->setStyleSheet("QLabel { background-color : green;}");
            }
            else if (str.contains("STATUS_BUSY")){
                ui->machine4->setStyleSheet("QLabel { background-color : red;}");
            }
            else if (str.contains("STATUS_FINISHING")){
                ui->machine4->setStyleSheet("QLabel { background-color : yellow;}");
            }
            else if (str.contains("STATUS_UNKNOWN")){
                ui->textEdit_malfunc->append("Dryer 1 is malfunctioning");
            }
        }

        if (machine_number == '5'){
            if (str.contains("STATUS_FREE")){
                ui->machine5->setStyleSheet("QLabel { background-color : green;}");
            }
            else if (str.contains("STATUS_BUSY")){
                ui->machine5->setStyleSheet("QLabel { background-color : red;}");
            }
            else if (str.contains("STATUS_FINISHING")){
                ui->machine5->setStyleSheet("QLabel { background-color : yellow;}");
            }
            else if (str.contains("STATUS_UNKNOWN")){
                ui->textEdit_malfunc->append("Dryer 2 is malfunctioning");
            }
        }

        if (machine_number == '6'){
            if (str.contains("STATUS_FREE")){
                ui->machine6->setStyleSheet("QLabel { background-color : green;}");
            }
            else if (str.contains("STATUS_BUSY")){
                ui->machine6->setStyleSheet("QLabel { background-color : red;}");
            }
            else if (str.contains("STATUS_FINISHING")){
                ui->machine6->setStyleSheet("QLabel { background-color : yellow;}");
            }
            else if (str.contains("STATUS_UNKNOWN")){
                ui->textEdit_malfunc->append("Dryer 3 is malfunctioning");
            }
        }

         ui->textEdit_2->append(status);
         this->repaint();
         status.clear();
         str.clear();
     }
}

void MainWindow::paintEvent(QPaintEvent *e){
//green is the starting point and yellow the ending point
    QPainter painter(this);

    //questions from gateway to sensors

    if (testFlag == 0){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node->x() + ui->edge_node->width()/2;
        int y2 = ui->edge_node->y() + ui->edge_node->height()/2;
        int x3 = ui->sensor_node_1->x() + ui->sensor_node_1->width()/2;
        int y3 = ui->sensor_node_1->y() + ui->sensor_node_1->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::red);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen1);
        painter.drawPoint(p1);
        painter.setPen(pointpen2);
        painter.drawPoint(p2);

    }


    else if (testFlag == 1){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node->x() + ui->edge_node->width()/2;
        int y2 = ui->edge_node->y() + ui->edge_node->height()/2;
        int x3 = ui->sensor_node_2->x() + ui->sensor_node_2->width()/2;
        int y3 = ui->sensor_node_2->y() + ui->sensor_node_2->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::red);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen1);
        painter.drawPoint(p1);
        painter.setPen(pointpen2);
        painter.drawPoint(p2);
        //this->repaint();
    }

    else if (testFlag == 2){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node->x() + ui->edge_node->width()/2;
        int y2 = ui->edge_node->y() + ui->edge_node->height()/2;
        int x3 = ui->sensor_node_3->x() + ui->sensor_node_3->width()/2;
        int y3 = ui->sensor_node_3->y() + ui->sensor_node_3->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::red);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen1);
        painter.drawPoint(p1);
        painter.setPen(pointpen2);
        painter.drawPoint(p2);
        //this->repaint();
    }

    else if (testFlag == 3){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node->x() + ui->edge_node->width()/2;
        int y2 = ui->edge_node->y() + ui->edge_node->height()/2;
        int x3 = ui->sensor_node_4->x() + ui->sensor_node_4->width()/2;
        int y3 = ui->sensor_node_4->y() + ui->sensor_node_4->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::red);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen1);
        painter.drawPoint(p1);
        painter.setPen(pointpen2);
        painter.drawPoint(p2);
        //this->repaint();
    }

    else if (testFlag == 4){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node->x() + ui->edge_node->width()/2;
        int y2 = ui->edge_node->y() + ui->edge_node->height()/2;
        int x3 = ui->sensor_node_5->x() + ui->sensor_node_5->width()/2;
        int y3 = ui->sensor_node_5->y() + ui->sensor_node_5->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::red);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen1);
        painter.drawPoint(p1);
        painter.setPen(pointpen2);
        painter.drawPoint(p2);
        //this->repaint();
    }

    else if (testFlag == 5){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node->x() + ui->edge_node->width()/2;
        int y2 = ui->edge_node->y() + ui->edge_node->height()/2;
        int x3 = ui->sensor_node_6->x() + ui->sensor_node_6->width()/2;
        int y3 = ui->sensor_node_6->y() + ui->sensor_node_6->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::red);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen1);
        painter.drawPoint(p1);
        painter.setPen(pointpen2);
        painter.drawPoint(p2);
        //this->repaint();
    }

    else if (testFlag == 6){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node_2->x() + ui->edge_node_2->width()/2;
        int y2 = ui->edge_node_2->y() + ui->edge_node_2->height()/2;
        int x3 = ui->sensor_node_1->x() + ui->sensor_node_1->width()/2;
        int y3 = ui->sensor_node_1->y() + ui->sensor_node_1->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::red);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen1);
        painter.drawPoint(p1);
        painter.setPen(pointpen2);
        painter.drawPoint(p2);
        //this->repaint();
    }

    else if (testFlag == 7){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node_2->x() + ui->edge_node_2->width()/2;
        int y2 = ui->edge_node_2->y() + ui->edge_node_2->height()/2;
        int x3 = ui->sensor_node_2->x() + ui->sensor_node_2->width()/2;
        int y3 = ui->sensor_node_2->y() + ui->sensor_node_2->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::red);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen1);
        painter.drawPoint(p1);
        painter.setPen(pointpen2);
        painter.drawPoint(p2);
        //this->repaint();
    }

    else if (testFlag == 8){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node_2->x() + ui->edge_node_2->width()/2;
        int y2 = ui->edge_node_2->y() + ui->edge_node_2->height()/2;
        int x3 = ui->sensor_node_3->x() + ui->sensor_node_3->width()/2;
        int y3 = ui->sensor_node_3->y() + ui->sensor_node_3->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::red);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen1);
        painter.drawPoint(p1);
        painter.setPen(pointpen2);
        painter.drawPoint(p2);
        //this->repaint();
    }

    else if (testFlag == 9){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node_2->x() + ui->edge_node_2->width()/2;
        int y2 = ui->edge_node_2->y() + ui->edge_node_2->height()/2;
        int x3 = ui->sensor_node_4->x() + ui->sensor_node_4->width()/2;
        int y3 = ui->sensor_node_4->y() + ui->sensor_node_4->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::red);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen1);
        painter.drawPoint(p1);
        painter.setPen(pointpen2);
        painter.drawPoint(p2);
        //this->repaint();
    }

    else if (testFlag == 10){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node_2->x() + ui->edge_node_2->width()/2;
        int y2 = ui->edge_node_2->y() + ui->edge_node_2->height()/2;
        int x3 = ui->sensor_node_5->x() + ui->sensor_node_5->width()/2;
        int y3 = ui->sensor_node_5->y() + ui->sensor_node_5->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::red);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen1);
        painter.drawPoint(p1);
        painter.setPen(pointpen2);
        painter.drawPoint(p2);
        //this->repaint();
    }

    else if (testFlag == 11){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node_2->x() + ui->edge_node_2->width()/2;
        int y2 = ui->edge_node_2->y() + ui->edge_node_2->height()/2;
        int x3 = ui->sensor_node_6->x() + ui->sensor_node_6->width()/2;
        int y3 = ui->sensor_node_6->y() + ui->sensor_node_6->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::red);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen1);
        painter.drawPoint(p1);
        painter.setPen(pointpen2);
        painter.drawPoint(p2);
        //this->repaint();
    }

    //answers from sensor to gateway

    else if (testFlag == 12){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node->x() + ui->edge_node->width()/2;
        int y2 = ui->edge_node->y() + ui->edge_node->height()/2;
        int x3 = ui->sensor_node_1->x() + ui->sensor_node_1->width()/2;
        int y3 = ui->sensor_node_1->y() + ui->sensor_node_1->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::blue);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen2);
        painter.drawPoint(p1);
        painter.setPen(pointpen1);
        painter.drawPoint(p2);
    }

    else if (testFlag == 13){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node->x() + ui->edge_node->width()/2;
        int y2 = ui->edge_node->y() + ui->edge_node->height()/2;
        int x3 = ui->sensor_node_2->x() + ui->sensor_node_2->width()/2;
        int y3 = ui->sensor_node_2->y() + ui->sensor_node_2->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::blue);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen2);
        painter.drawPoint(p1);
        painter.setPen(pointpen1);
        painter.drawPoint(p2);
    }

    else if (testFlag == 14){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node->x() + ui->edge_node->width()/2;
        int y2 = ui->edge_node->y() + ui->edge_node->height()/2;
        int x3 = ui->sensor_node_3->x() + ui->sensor_node_3->width()/2;
        int y3 = ui->sensor_node_3->y() + ui->sensor_node_3->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::blue);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen2);
        painter.drawPoint(p1);
        painter.setPen(pointpen1);
        painter.drawPoint(p2);
    }

    else if (testFlag == 15){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node->x() + ui->edge_node->width()/2;
        int y2 = ui->edge_node->y() + ui->edge_node->height()/2;
        int x3 = ui->sensor_node_4->x() + ui->sensor_node_4->width()/2;
        int y3 = ui->sensor_node_4->y() + ui->sensor_node_4->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::blue);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen2);
        painter.drawPoint(p1);
        painter.setPen(pointpen1);
        painter.drawPoint(p2);
    }

    else if (testFlag == 16){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node->x() + ui->edge_node->width()/2;
        int y2 = ui->edge_node->y() + ui->edge_node->height()/2;
        int x3 = ui->sensor_node_5->x() + ui->sensor_node_5->width()/2;
        int y3 = ui->sensor_node_5->y() + ui->sensor_node_5->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::blue);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen2);
        painter.drawPoint(p1);
        painter.setPen(pointpen1);
        painter.drawPoint(p2);
    }

    else if (testFlag == 17){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node->x() + ui->edge_node->width()/2;
        int y2 = ui->edge_node->y() + ui->edge_node->height()/2;
        int x3 = ui->sensor_node_6->x() + ui->sensor_node_6->width()/2;
        int y3 = ui->sensor_node_6->y() + ui->sensor_node_6->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::blue);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen2);
        painter.drawPoint(p1);
        painter.setPen(pointpen1);
        painter.drawPoint(p2);
    }

    else if (testFlag == 18){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node_2->x() + ui->edge_node_2->width()/2;
        int y2 = ui->edge_node_2->y() + ui->edge_node_2->height()/2;
        int x3 = ui->sensor_node_1->x() + ui->sensor_node_1->width()/2;
        int y3 = ui->sensor_node_1->y() + ui->sensor_node_1->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::blue);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen2);
        painter.drawPoint(p1);
        painter.setPen(pointpen1);
        painter.drawPoint(p2);
    }

    else if (testFlag == 19){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node_2->x() + ui->edge_node_2->width()/2;
        int y2 = ui->edge_node_2->y() + ui->edge_node_2->height()/2;
        int x3 = ui->sensor_node_2->x() + ui->sensor_node_2->width()/2;
        int y3 = ui->sensor_node_2->y() + ui->sensor_node_2->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::blue);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen2);
        painter.drawPoint(p1);
        painter.setPen(pointpen1);
        painter.drawPoint(p2);
    }

    else if (testFlag == 20){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node_2->x() + ui->edge_node_2->width()/2;
        int y2 = ui->edge_node_2->y() + ui->edge_node_2->height()/2;
        int x3 = ui->sensor_node_3->x() + ui->sensor_node_3->width()/2;
        int y3 = ui->sensor_node_3->y() + ui->sensor_node_3->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::blue);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen2);
        painter.drawPoint(p1);
        painter.setPen(pointpen1);
        painter.drawPoint(p2);
    }

    else if (testFlag == 21){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node_2->x() + ui->edge_node_2->width()/2;
        int y2 = ui->edge_node_2->y() + ui->edge_node_2->height()/2;
        int x3 = ui->sensor_node_4->x() + ui->sensor_node_4->width()/2;
        int y3 = ui->sensor_node_4->y() + ui->sensor_node_4->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::blue);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen2);
        painter.drawPoint(p1);
        painter.setPen(pointpen1);
        painter.drawPoint(p2);
    }

    else if (testFlag == 22){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node_2->x() + ui->edge_node_2->width()/2;
        int y2 = ui->edge_node_2->y() + ui->edge_node_2->height()/2;
        int x3 = ui->sensor_node_5->x() + ui->sensor_node_5->width()/2;
        int y3 = ui->sensor_node_5->y() + ui->sensor_node_5->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::blue);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen2);
        painter.drawPoint(p1);
        painter.setPen(pointpen1);
        painter.drawPoint(p2);
    }


    else if (testFlag == 23){
        int x1 = ui->gateway_node->x() + ui->gateway_node->width()/2;
        int y1 = ui->gateway_node->y() + ui->gateway_node->height()/2;
        int x2 = ui->edge_node_2->x() + ui->edge_node_2->width()/2;
        int y2 = ui->edge_node_2->y() + ui->edge_node_2->height()/2;
        int x3 = ui->sensor_node_6->x() + ui->sensor_node_6->width()/2;
        int y3 = ui->sensor_node_6->y() + ui->sensor_node_6->height()/2;
        QPoint p1(x1,y1);
        QPoint p2(x3,y3);
        QPen linepen(Qt::blue);
        QPen pointpen1(Qt::green);
        QPen pointpen2(Qt::yellow);
        pointpen2.setWidth(6);
        pointpen1.setWidth(6);
        linepen.setWidth(4);
        painter.setPen(linepen);
        painter.drawLine(x1,y1,x2,y2);
        painter.drawLine(x2,y2,x3,y3);
        painter.setPen(pointpen2);
        painter.drawPoint(p1);
        painter.setPen(pointpen1);
        painter.drawPoint(p2);
    }



}
