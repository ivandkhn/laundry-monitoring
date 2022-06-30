#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/img/washing-machine-svgrepo-com.svg");
    QPixmap pix2(":/img/tum-logo.png");
    int w = ui->machine1->width();
    int h =ui->machine1->height();
    int w1 = ui->tum_logo->width();
    int h1 =ui->tum_logo->height();
    ui->machine1->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->machine2->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->machine3->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->machine4->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->machine5->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->machine6->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->tum_logo->setPixmap(pix2.scaled(w1,h1,Qt::KeepAspectRatio));
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
//            if (ch == '\n')     // End of line, start decoding
//            {
//                str.remove("\n", Qt::CaseSensitive);
//                ui->textEdit->append(str);
//                if (str.contains("Q_STATUS")){
//                    ui->textEdit_2->append("Question asked");
//                }
//                else if (str.contains("A_STATUS")){
//                    ui->textEdit_2->append("Answer received");
//                }
//
//                this->repaint();    // Update content of window immediately
//                str.clear();
//            }
        }
     ui->textEdit->append(str);
     if (str.contains("A_STATUS")){
         static QString machine_number;
         static QString status;
         for (int i = 0; i < str.length(); i++) {
             if (str[i] == "m" && str[i+1]== 'a' && str[i+2]=='c'){
                 machine_number = str[i+15];
             }

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
