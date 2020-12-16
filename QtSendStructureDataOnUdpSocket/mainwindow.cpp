#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QUdpSocket(this);

    intvalidator = new QIntValidator(0,100);

    doublevalidator = new QDoubleValidator(0.00,360.00,2);
    doublevalidator->setNotation(QDoubleValidator::StandardNotation); //to avoid e value.
    //    QRegularExpression hexMatcher("^[0-9A-F{6}$]",QRegularExpression::CaseInsensitiveOption,);

    ui->lineEdit_msgID->setReadOnly(true);
    //    ui->lineEdit_msgID->setValidator(hexMatcher);
    ui->lineEdit_Speed->setValidator(intvalidator);

    ui->lineEdit_Range->setValidator(intvalidator);
    ui->lineEdit_angle->setValidator(doublevalidator);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PB_Send_clicked()
{
    if(ui->lineEdit_angle->text()==" " | ui->lineEdit_Speed->text()==" " | ui->lineEdit_Range->text()==" "){
        QMessageBox::warning(this,"Send Data","Enter Values",QMessageBox::Ok);
    }else {
        m_Data.msgId = ui->lineEdit_msgID->text().toInt();
        ui->lineEdit_msgID->setText(QString::number(m_Data.msgId));
        m_Data.angle =  ui->lineEdit_angle->text().toFloat();
        m_Data.speed =  ui->lineEdit_Speed->text().toInt();
        m_Data.range =  ui->lineEdit_Range->text().toInt();

        QByteArray dataToSend;
        dataToSend = QByteArray::fromRawData((char*)&m_Data,sizeof(struct ProjData));

        qreal sizeSent = socket->writeDatagram(dataToSend,QHostAddress::LocalHost,4444);
        qDebug("Sizeof m_data %d",sizeof (m_Data));
        qDebug()<<"sizeSent is : "<<sizeSent;
    }
}
