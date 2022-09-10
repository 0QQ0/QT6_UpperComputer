#include "userconfui.h"
#include "ui_userconfui.h"


userConfUI::userConfUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userConfUI)
{
    ui->setupUi(this);

    setUserConfUI( );
    setDataConfUI( );
}

userConfUI::~userConfUI()
{
    delete ui;
}

void userConfUI::setUserConfUI( )
{
    //绘制自定义用户帧表
    QList<QTreeWidgetItem *> items;
    ui->frameconf->setColumnCount(4);
    ui->frameconf->setHeaderLabels(QStringList()<<"用户帧"<<"数据位"<<"数据类型"<<"传输缩放");

    for(int i =1   ; i<=10 ; i++)
    {
        if(i<10){
            //父节点设置
            QTreeWidgetItem * item=new QTreeWidgetItem(QStringList()<<"F"+QString::number(i));
            ui->frameconf->addTopLevelItem(item);
            //使能选择框设置
            item->setCheckState(1, Qt::Unchecked);
            item->setText(1,  "使能该帧");
            //子节点设置
            for(int x =0 ; x<10 ; x++)
            {
                QTreeWidgetItem * childitem=new QTreeWidgetItem(QStringList()<<"F"+QString::number(i));
                item->addChild(childitem);

                childitem->setText(1,QString::number(x+1));

                //设置数据类型下拉框控件
                QComboBox *frameBox = new QComboBox;
                frameBox->addItem("Uint8" );
                frameBox->addItem("Uint16" );
                frameBox->addItem("Int16" );
                frameBox->addItem("Int32" );
                frameBox->addItem("Uint32" );
                ui->frameconf->setItemWidget(childitem, 2, frameBox);

                //设置传输缩放下拉框控件
                QComboBox *frameBox1 = new QComboBox;
                for(int y=0;y<10;y++)
                    frameBox1->addItem("1.0E+" + QString::number(y) );
                ui->frameconf->setItemWidget(childitem, 3, frameBox1);
            }
        }else{
            //父节点设置
            QTreeWidgetItem * item=new QTreeWidgetItem(QStringList()<<"FA" );
            ui->frameconf->addTopLevelItem(item);
            //使能选择框设置
            item->setCheckState(1, Qt::Unchecked);
            item->setText(1,  "使能该帧");

            //子节点设置
            for(int x =0 ; x<10 ; x++)
            {
                QTreeWidgetItem * childitem=new QTreeWidgetItem(QStringList()<<"FA");
                item->addChild(childitem);

                childitem->setText(1,QString::number(x+1));

                //设置数据类型下拉框控件
                QComboBox *frameBox = new QComboBox;
                frameBox->addItem("Uint8" );
                frameBox->addItem("Uint16" );
                frameBox->addItem("Int16" );
                frameBox->addItem("Int32" );
                frameBox->addItem("Uint32" );
                ui->frameconf->setItemWidget(childitem, 2, frameBox);

                //设置传输缩放下拉框控件
                QComboBox *frameBox1 = new QComboBox;
                for(int y=0;y<10;y++)
                    frameBox1->addItem("1.0E+" + QString::number(y) );
                ui->frameconf->setItemWidget(childitem, 3, frameBox1);

            }

        }

    }

}


//    1.第一种:直接通过坐标去获取
//    /*普通表格控件获取方式*/
//    QString strValue = tableObject->item(0,1)->text();
//    /*表格中下拉框获取选中值*/
//    QString strValue=dynamic_cast<QComboBox *>(ui->tableWidget->cellWidget(0,2))->currentText();

//    2.第二种:点击QTableWidget里的表格信号触发
//    信号:doubleClicked(const QModelIndex &)
//         itemDoubleClicked(QTableWidgetItem *)

//    槽: void itemDoubleClick(QTableWidgetItem *item)
//         {
//             int row=item->row();
//             QString tableObject = item->tableWidget()->objectName();
//             QString itemValue = item->tableWidget()->item(row,1)->text().trimmed();
//             QString itemValue = dynamic_cast<QComboBox *>(item->tableWidget()->cellWidget(0,2))->currentText();//表格里的下拉框获取方式
//         }

void userConfUI::setDataConfUI()
{

    //绘制容器表格
    QStringList tableHeaderList;
    tableHeaderList<<tr("容器")<<tr("用户帧")<<tr("数据位")<<tr("数据值");
    ui->dataconf->setRowCount(20);
    ui->dataconf->setColumnCount(tableHeaderList.size());          //表头列文本设置
    for (int i=0;i<tableHeaderList.size();i++) {
        ui->dataconf->setHorizontalHeaderItem(i,new QTableWidgetItem(tableHeaderList.at(i)));
        ui->dataconf->setColumnWidth(i,ui->dataconf->width());
    }
    ui->dataconf->horizontalHeader()->setStretchLastSection(true);
    ui->dataconf->verticalHeader()->setMinimumSectionSize(35);
    ui->dataconf->resizeRowsToContents();
    ui->dataconf->setSelectionBehavior(QAbstractItemView::SelectRows);//行选中
    ui->dataconf->setAlternatingRowColors(true);
    ui->dataconf->setFocusPolicy(Qt::NoFocus); //去除选中虚线框
    ui->dataconf->verticalHeader()->setVisible(false); //设置垂直头不可见
    //   ui->dataconf->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//去掉水平滚动条
    ui->dataconf->setEditTriggers(QAbstractItemView::NoEditTriggers);//不能编写
    ui->dataconf->setSelectionMode(QAbstractItemView::SingleSelection);//只能单次选中
    //容器名
    for(int x=0 , y=0 ; x<20 ; x++)
    {
        QString num = QString::number(x+1);
        ui->dataconf->setItem(x,y, new QTableWidgetItem("userData"+num));
        ui->dataconf->item(x,y)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }

    //用户帧下拉框设置
    for(int i =0   ; i<20 ; i++)
    {    //用户帧下拉框内容
        QComboBox *frameBox = new QComboBox;
        for(int i =1   ; i<=9 ; i++)
        {
            frameBox->addItem("F"+QString::number(i) );
            if(i==9)
                frameBox->addItem("FA"  );
        }
        //放在哪个地方
        ui->dataconf->setCellWidget(i,1,frameBox);
        //默认选择
        frameBox->setCurrentText("F1");
    }

    //数据位下拉框位置
    for(int i =0   ; i<20 ; i++)
    {    //数据位下拉框内容
        QComboBox *dataLenBox = new QComboBox;
        for(int i =0   ; i<10 ; i++)
        {
            dataLenBox->addItem(QString::number(i+1));
        }
        ui->dataconf->setCellWidget(i,2,dataLenBox);
        //默认选择
        dataLenBox->setCurrentText("1");
    }

    //默认数据值
    for(int i =0   ; i<20 ; i++)
    {
        ui->dataconf->setItem(i,3, new QTableWidgetItem("0"));
    }
}
