#include "widget.h"
#include "ui_widget.h"

#include <QDesktopServices>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置无边框
    this->setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::FramelessWindowHint);

    //------------------------------------------------------------------------------------
    //创建窗口
    pSerialConfUI = new win1(this);
    psendUI = new sendUI(this);
    pfreamUI = new  freamUI(this);
    puserConfUI = new userConfUI(pfreamUI);
    pdataShowUI = new dataShowUI(this);

    //------------------------------------------------------------------------------------
    //设置窗口大小
    int width=979  , hight = 672 ;
    pSerialConfUI->resize(width , hight);
    psendUI->resize(width , hight);
    pfreamUI->resize(width , hight);
    puserConfUI->resize(width*1/2 , hight);
    pdataShowUI->resize(width , hight);

    pwaveFormUI = new waveFormUI(this);
    pwaveFormUI->resize(width , hight);
    pwaveFormUI->pQCustomPlot->resize(747 , hight);


    hideAllShow();
    pSerialConfUI->show();
    //连接信号和槽的关系
    connect(pSerialConfUI ,&win1::DatatoCRC_signal,pfreamUI->pqAgreement,&qAgreement::analysis);/*发送接收到的串口数据*/
    connect(pfreamUI ,&freamUI::sendres,pwaveFormUI,&waveFormUI::paintUserData);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::hideAllShow()
{
    pSerialConfUI->hide();
    psendUI->hide();
    pfreamUI->hide();
    puserConfUI->hide();
    pdataShowUI->hide();
    pwaveFormUI->hide();
}

//关闭程序按钮
void Widget::on_back_clicked()
{
    qDebug("back");
    //    delete pSerialConfUI;
    //    delete pfreamUI;
    //    delete psendUI;
    //    delete pdataShowUI;
    //    delete puserConfUI;
    this->close();
    //     delete ui;
}

//命令发送按钮
void Widget::on_win2_clicked()
{
    hideAllShow();
    psendUI->show();
}

//用户配置按钮
void Widget::on_win1_clicked()
{
    hideAllShow();
    pSerialConfUI->show();

    //    //新窗口对齐偏移
    //    QPoint* x = new QPoint;
    //    x->setX(-1);
    //    x->setY(-1);
    //    //对齐主窗口
    //    pSerialConfUI->move(this->pos()- *x  );
}

//协议解析按钮
void Widget::on_first_clicked()
{
    hideAllShow();
    pfreamUI->show();

}

//用户配置按钮
void Widget::on_userConf_clicked()
{
    static bool i =true;
    if(i){
        puserConfUI->hide();
        puserConfUI->show();
        i=false;
    }
    else{
        puserConfUI->hide();
        i=true;
    }
}

//最小化程序
void Widget::on_becomesmall_clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}

//数据面板按钮
void Widget::on_dataShow_clicked()
{
    hideAllShow();
    pdataShowUI->show();
}

//波形显示按钮
void Widget::on_toolButton_clicked()
{
    hideAllShow();
    pwaveFormUI->show();
}




void Widget::mousePressEvent(QMouseEvent *event)
{
    if( (event->button() == Qt::LeftButton) ){
        mouse_press = true;
        mousePoint = event->globalPos() - this->pos();

    }
    else if(event->button() == Qt::RightButton){
        //如果是右键
        //this->close();
    }
}
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(mouse_press){
        //win1跟随移动
        //        pSerialConfUI->move(event->globalPos() - mousePoint);
        move(event->globalPos() - mousePoint);
    }
}
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_press = false;
}


