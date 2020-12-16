#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QValidator>
#include <QDoubleValidator>
#include <QMessageBox>
#include <QRegularExpression>
//#pragma pack(1)
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_PB_Send_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket *socket;
    QValidator *intvalidator;
    QDoubleValidator *doublevalidator;
    struct ProjData{
        int msgId;
        float angle;
        int speed;
        int range;
    }__attribute__((packed));
    ProjData m_Data;
};

#endif // MAINWINDOW_H
