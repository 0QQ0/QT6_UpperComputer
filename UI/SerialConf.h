#ifndef SERIALCONF_H
#define SERIALCONF_H

#include <QWidget>

#include <QMouseEvent>

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QTime>
#include <QTimer>



namespace Ui {
class win1;
}

class win1 : public QWidget
{
    Q_OBJECT

public:
    explicit win1(QWidget *parent = nullptr);
    ~win1();

    QSerialPort *SerialPort;
    QTimer *Timer1;

private slots:
    void OpenSerialPortSlot();
    void RxDataSaveSlot();
    void RxDataTextClearSlot();
    void DataReadyReadSlot();/*串口数据接收槽函数*/
    void SendDataSlot();
    void SendDataTextClearSlot();
    void RxDataForHexSlot();
    void SendDataForHexSlot();
    void SendDataPeriodSlot();


private:
    Ui::win1 *ui;

    void  findSerialPort();
    signals:
        void DatatoCRC_signal(QByteArray SendData);
};

#endif // SERIALCONF_H
