#include "SerialConf.h"
#include "ui_SerialConf.h"


win1::win1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::win1)
{
    ui->setupUi(this);
    //设置无边框
    //    setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::FramelessWindowHint);

    //连接按钮信号和槽
    QObject::connect( ui->OpenSerialPortPushButton,&QPushButton::clicked,this, &win1::OpenSerialPortSlot );
    QObject::connect( ui->RxDataSavePushButton,&QPushButton::clicked,this, &win1::RxDataSaveSlot );
    QObject::connect( ui->RxDataTextClearPushButton,&QPushButton::clicked,this, &win1::RxDataTextClearSlot );
    QObject::connect( ui->SendDataTextClearPushButton,&QPushButton::clicked,this, &win1::SendDataTextClearSlot );
    QObject::connect( ui->SendDataTextClearPushButton,&QPushButton::clicked,this, &win1::SendDataTextClearSlot );
    QObject::connect( ui->SendDataPushButton,&QPushButton::clicked,this, &win1::SendDataSlot );
    //连接复选框信号和槽
    QObject::connect( ui->RxDataForHexCheckBox,&QCheckBox::stateChanged,this, &win1::RxDataForHexSlot );
    QObject::connect( ui->SendDataForHexCheckBox,&QCheckBox::stateChanged,this, &win1::SendDataForHexSlot );
    QObject::connect( ui->SendDataPeriodCheckBox,&QCheckBox::stateChanged,this, &win1::SendDataPeriodSlot );

    /*设置串口初始化的控件默认状态*/
    ui->BaudRateComboBox->setCurrentIndex(13);      /*默认波特率115200*/
    ui->SendDataPushButton->setEnabled(false);      /*失能串口发送按键*/
    ui->SendDataPeriodCheckBox->setEnabled(false);  /*未打开串口前不能设置自动发送*/
    ui->SendDataPeriodLineEdit->setEnabled(false);  /*未打开串口前不能设置自动发送时间*/

    Timer1 = new QTimer;
    connect(Timer1,&QTimer::timeout,this,[=](){ SendDataSlot();  });

    findSerialPort();

}

win1::~win1()
{
    delete ui;
}

void win1::findSerialPort()
{
    QStringList SerialPortNameList;/*保存搜索到的串口，存入列表中*/
    ui->RxDataTextEdit->append("存在的串口：");
    foreach (const QSerialPortInfo &SerialPortInfo, QSerialPortInfo::availablePorts()) /*遍历可使用的串口*/
    {
        SerialPortNameList.append(SerialPortInfo.portName());/*把搜索到的串口存入列表中*/
        ui->RxDataTextEdit->append(SerialPortInfo.portName() + " " + SerialPortInfo.description());
    }
    ui->SerialPortChooseComboBox->addItems(SerialPortNameList);/*将搜索到的串口显示到UI界面上*/

    ui->OpenSerialPortPushButton->setText("打开串口");
    return;
}


void win1::OpenSerialPortSlot()
{

    if(ui->OpenSerialPortPushButton->text() == "打开串口")
    {
        SerialPort = new QSerialPort();

        QSerialPort::DataBits PortDataBits = QSerialPort::Data8;                /*数据位，默认Data8*/
        QSerialPort::Parity PortParityBits = QSerialPort::NoParity;             /*校验位，默认NoParity*/
        QSerialPort::StopBits PortStopBits = QSerialPort::OneStop;              /*停止位，默认OneStop*/
        QSerialPort::FlowControl PortFlowControl = QSerialPort::NoFlowControl;  /*串口控制，默认NoFlowControl*/

        int PortBandRate = ui->BaudRateComboBox->currentText().toInt();/*获取波特率*/
        switch (ui->PortDataBitsComboBox->currentText().toInt())/*获取数据位*/
        {
        case 8:
            PortDataBits = QSerialPort::Data8;
            break;
        case 7:
            PortDataBits = QSerialPort::Data7;
            break;
        case 6:
            PortDataBits = QSerialPort::Data6;
            break;
        case 5:
            PortDataBits = QSerialPort::Data5;
            break;
        default:
            break;
        }
        switch (ui->PortParityComboBox->currentIndex())/*获取校验方式*/
        {
        case 0:         /*选择序号0，无校验*/
            PortParityBits = QSerialPort::NoParity;
            break;
        case 1:         /*选择序号1，奇校验*/
            PortParityBits = QSerialPort::OddParity;
            break;
        case 2:         /*选择序号2，偶校验*/
            PortParityBits = QSerialPort::EvenParity;
            break;
        default:
            break;
        }
        switch (ui->PortStopBitsComboBox->currentIndex())/*获取停止位*/
        {
        case 0:         /*选择序号0，1个停止位*/
            PortStopBits = QSerialPort::OneStop;
            break;
        case 1:         /*选择序号1，1.5个停止位*/
            PortStopBits = QSerialPort::OneAndHalfStop;
            break;
        case 2:         /*选择序号2，2个停止位*/
            PortStopBits = QSerialPort::TwoStop;
            break;
        default:
            break;
        }
        SerialPort->setPortName(ui->SerialPortChooseComboBox->currentText());   /*设置选中的COM口*/
        SerialPort->setBaudRate(PortBandRate);                                  /*设置串口的波特率*/
        SerialPort->setDataBits(PortDataBits);                                  /*设置数据位数*/
        SerialPort->setParity(PortParityBits);                                  /*设置奇偶校验,NoParit无校验*/
        SerialPort->setStopBits(PortStopBits);                                  /*设置停止位，OneStop一个停止位*/
        SerialPort->setFlowControl(PortFlowControl);                            /*设置流控制，NoFlowControl无流控制*/

        if(SerialPort->open(QIODevice::ReadWrite) == true)                      /*ReadWrite设置的是可读可写的属性*/
        {
            //QMessageBox::information(this,"提示","成功");
            ui->RxDataTextEdit->append(ui->SerialPortChooseComboBox->currentText() + "已连接");

            ui->SendDataPushButton->setEnabled(true);/*使能串口发送按键*/

            ui->BaudRateComboBox->setEnabled(false);
            ui->PortStopBitsComboBox->setEnabled(false);
            ui->PortDataBitsComboBox->setEnabled(false);
            ui->PortParityComboBox->setEnabled(false);/*连接成功后设置ComboBox不可选择*/

            ui->SendDataPeriodCheckBox->setEnabled(true);  /*打开串口后可以设置自动发送*/
            ui->SendDataPeriodLineEdit->setEnabled(true);  /*打开串口后可以设置自动发送时间*/

            /*打开串口成功，连接信号和槽*/
            connect(SerialPort,&QSerialPort::readyRead,this,&win1::DataReadyReadSlot);

        }
        else
        {
            ui->RxDataTextEdit->append(ui->SerialPortChooseComboBox->currentText() + "连接失败");
            //QMessageBox::critical(this,"提示","打开失败，请检查串口是否连接正常");
            return;
        }

        ui->SerialPortChooseComboBox->setEnabled(false);/*列表框无效*/
        ui->OpenSerialPortPushButton->setText("关闭串口");
        return;
    }

    if(ui->OpenSerialPortPushButton->text() == "关闭串口")
    {

        SerialPort->close();/*关闭串口*/

        ui->RxDataTextEdit->append(ui->SerialPortChooseComboBox->currentText() + "已关闭");
        ui->SerialPortChooseComboBox->clear();/*清除显示的串口列表*/
        ui->SerialPortChooseComboBox->setEnabled(true);/*列表框有效*/
        ui->OpenSerialPortPushButton->setText("打开串口");
        ui->SendDataPushButton->setEnabled(false);/*失能串口发送按键*/

        ui->BaudRateComboBox->setEnabled(true);
        ui->PortStopBitsComboBox->setEnabled(true);
        ui->PortDataBitsComboBox->setEnabled(true);
        ui->PortParityComboBox->setEnabled(true);/*关闭连接后设置ComboBox选择*/

        ui->SendDataPeriodCheckBox->setEnabled(false);  /*未打开串口前不能设置自动发送*/
        ui->SendDataPeriodLineEdit->setEnabled(false);  /*未打开串口前不能设置自动发送时间*/
        findSerialPort();
        return;
    }
}

void win1::RxDataSaveSlot()
{
    qDebug() << ui->TxDataTextEdit->toPlainText().toLocal8Bit();
    //
}

void win1::RxDataTextClearSlot()
{
    ui->RxDataTextEdit->clear();
}

void win1::DataReadyReadSlot()
{
    QByteArray SerialPortDataBuf;
    SerialPortDataBuf = SerialPort->readAll();
    emit DatatoCRC_signal(SerialPortDataBuf);
    if(ui->RxDataForHexCheckBox->isChecked() == false)
    {
        if(ui->RxDataWithTimeCheckBox->isChecked() == true)/*显示时间戳*/
        {
            QDateTime NowTime = QDateTime::currentDateTime();
            ui->RxDataTextEdit->append("[" + NowTime.toString("hh:mm:ss:zzz") + "]  :");
            //qDebug() << NowTime.toString("hh:mm:ss:zzz");
        }
        ui->RxDataTextEdit->insertPlainText(QString::fromLocal8Bit(SerialPortDataBuf));/*正常显示文本*/
    }
    else
    {
        ui->RxDataTextEdit->insertPlainText(SerialPortDataBuf.toHex(' ').toUpper());/*显示HEX*/
    }
}

void win1::SendDataSlot()
{

    if(ui->SendDataForHexCheckBox->isChecked() == true)
    {
        QByteArray GetHexShowArray;
        GetHexShowArray = ui->TxDataTextEdit->toPlainText().toLocal8Bit();       /*得到原始数据，同时删除其中的空格元素*/
        for(int i=0;i<GetHexShowArray.size();i++)
        {
            if(GetHexShowArray[i] == ' ')
            {
                GetHexShowArray.remove(i,1);
            }
        }
        QByteArray HexArray = QByteArray::fromHex(GetHexShowArray);/*原始数据转换成HEX格式*/
        SerialPort->write(HexArray);
        if(ui->SendDataWithEnterCheckBox->isChecked() == true)
        {
            SerialPort->write("\r\n");/*发送回车*/
        }

    }
    else
    {
        SerialPort->write(ui->TxDataTextEdit->toPlainText().toLocal8Bit());/*正常发送文本*/
        if(ui->SendDataWithEnterCheckBox->isChecked() == true)
        {
            SerialPort->write("\r\n");/*发送回车*/
        }
    }

}

void win1::SendDataTextClearSlot()
{
    ui->TxDataTextEdit->clear();
}

void win1::RxDataForHexSlot()
{
    if(ui->RxDataForHexCheckBox->isChecked() == true)/*选中Hex显示*/
    {
        QByteArray HexShowArray;

        HexShowArray = ui->RxDataTextEdit->toPlainText().toLocal8Bit();
        ui->RxDataTextEdit->clear();
        ui->RxDataTextEdit->append(HexShowArray.toHex(' ').toUpper());/*文本转换显示HEX*/
        return;

    }
    if(ui->RxDataForHexCheckBox->isChecked() == false)/*未选中Hex显示*/
    {
        QByteArray GetHexShowArray;

        GetHexShowArray = ui->RxDataTextEdit->toPlainText().toLocal8Bit();       /*得到原始数据，同时删除其中的空格元素*/
        ui->RxDataTextEdit->clear();
        for(int i=0;i<GetHexShowArray.size();i++)
        {
            if(GetHexShowArray[i] == ' ')
            {
                GetHexShowArray.remove(i,1);
            }
        }

        QByteArray HexArray = QByteArray::fromHex(GetHexShowArray);/*原始数据转换成HEX格式*/
        QString  HexShowSring = QString ::fromLocal8Bit(HexArray);/*QbyteArray转换Qstring显示*/
        ui->RxDataTextEdit->append(HexShowSring);
        return;
    }
}

void win1::SendDataForHexSlot()
{
    if(ui->SendDataForHexCheckBox->isChecked() == true)/*选中Hex显示*/
    {
        QByteArray HexShowArray;

        HexShowArray = ui->TxDataTextEdit->toPlainText().toLocal8Bit();
        ui->TxDataTextEdit->clear();
        ui->TxDataTextEdit->append(HexShowArray.toHex(' ').toUpper());/*文本转换显示HEX*/
        return;

    }
    if(ui->SendDataForHexCheckBox->isChecked() == false)/*未选中Hex显示*/
    {
        QByteArray GetHexShowArray;

        GetHexShowArray = ui->TxDataTextEdit->toPlainText().toLocal8Bit();       /*得到原始数据，同时删除其中的空格元素*/
        ui->TxDataTextEdit->clear();
        for(int i=0;i<GetHexShowArray.size();i++)
        {
            if(GetHexShowArray[i] == ' ')
            {
                GetHexShowArray.remove(i,1);
            }
        }

        QByteArray HexArray = QByteArray::fromHex(GetHexShowArray);/*原始数据转换成HEX格式*/
        QString  HexShowSring = QString ::fromLocal8Bit(HexArray);/*QbyteArray转换Qstring显示*/
        ui->TxDataTextEdit->append(HexShowSring);
        return;
    }

}

void win1::SendDataPeriodSlot()
{
    if(ui->SendDataPeriodLineEdit->text() == "")
    {
        /*设置的发送时间为空，不启动发送*/
        ui->SendDataPeriodCheckBox->setCheckState(Qt::Unchecked);
        QMessageBox::information(this,"提示","请检查发送时间设置是否正确！");
        return;
    }
    int SendPeriod = 0;
    if(ui->SendDataPeriodCheckBox->isChecked() == true)
    {
        SendPeriod = ui->SendDataPeriodLineEdit->text().toInt();
        Timer1->setInterval(SendPeriod);/*设置定时时间*/
        Timer1->setTimerType(Qt::PreciseTimer);/*定时器定时精度*/
        Timer1->start();/*开启定时器*/
    }
    if(ui->SendDataPeriodCheckBox->isChecked() == false)
    {
        Timer1->stop();/*停止定时器*/
    }

}
