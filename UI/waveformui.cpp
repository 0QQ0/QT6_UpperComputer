#include "waveformui.h"
#include "ui_waveformui.h"

waveFormUI::waveFormUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::waveFormUI)
{
    ui->setupUi(this);

    pQCustomPlot = new QCustomPlot(ui->widget);
    //新增20条用户数据波形
    for (int var = 0; var < 20; ++var) {

        QPen pen;
        pen.setWidth(3);//设置线宽
        pen.setStyle(Qt::PenStyle::SolidLine);//设置为实线
        pen.setColor(QColor(var*10, var*6, var%20));//设置线条颜色

        pQCustomPlot->addGraph();
        pQCustomPlot->graph(var)->setPen(pen);
    }

    pQCustomPlot->xAxis->setRange(0, 200);
    pQCustomPlot->yAxis->setRange(0, 500);

}

waveFormUI::~waveFormUI()
{
    delete ui;
}


void waveFormUI::paintUserData(long int frameCountint ,int dataNum , double* pres)
{
    //加点
    double value = *(pres);
    pQCustomPlot->graph(dataNum)->addData(frameCountint,value);
    QCPRange a = pQCustomPlot->yAxis->range(); //设置y轴范围
    if(value < a.lower){
        pQCustomPlot->yAxis->setRange(value,a.upper);
    }
    if(value > a.upper){
        pQCustomPlot->yAxis->setRange(a.lower,value);
    }

    //获取checkbox控件句柄
    QList<QCheckBox*> pQCheckBoxsChildren  =  ui->userPrint->findChildren<QCheckBox*>();
    for (int var = 0; var < 20; ++var) {//遍历checkbox
        if(pQCheckBoxsChildren.at(var)->checkState() == 2){ //显示选中的数据波形
            pQCustomPlot->graph(var)->setVisible(true);//显示曲线
        }else{
            pQCustomPlot->graph(var)->setVisible(false);//隐藏曲线
        }
    }

    pQCustomPlot->xAxis->setRange(frameCountint, 1000, Qt::AlignRight);//动态x轴
    pQCustomPlot->replot(); //刷新

}
