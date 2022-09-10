#include "freamui.h"
#include "ui_freamui.h"

#include "QTreeWidget"
#include "QTableWidget"
#include "QComboBox"
freamUI::freamUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::freamUI)
{
    ui->setupUi(this);

    pqAgreement = new qAgreement();

    //显示接收的帧数据
    connect(this->pqAgreement,&qAgreement::ResultFrame_signal,this,&freamUI::writeText);

}

freamUI::~freamUI()
{
    delete ui;
}

void freamUI::readUserConf()
{
    //获取用户自定义帧配置窗口句柄
    QList<QTreeWidget*> pQTreeWidgetChildren =  this->findChildren<QTreeWidget*>();
    //    qDebug("pQTreeWidgetChildren:%lld",pQTreeWidgetChildren.size());
    QTreeWidget* pQTreeWidget = pQTreeWidgetChildren.at(0);

    //保存用户自定义帧数据类型
    for(int x=0  ; x<10 ; x++){

        //判断此帧是否为选中启用状态
        userConf[x].check_sta = pQTreeWidget->topLevelItem(x)->checkState(1);
        //        qDebug("check_sta = %d",userConf[x].check_sta);
        //保存一帧配置
        for(int y=0 ; y<10 ; y++ ){
            //找到节枝点
            QTreeWidgetItem* pQTreeWidgetItem = pQTreeWidget->topLevelItem(x)->child(y);
            //读取数据类型下拉框
            QString udt=dynamic_cast<QComboBox *>(pQTreeWidget->itemWidget(pQTreeWidgetItem, 2))->currentText();
            if(udt == "Uint8"){
                userConf[x].bit[y].udt = Uint8; //保存数据类型
            }else if(udt == "Uint16"){
                userConf[x].bit[y].udt = Uint16;
            }else if(udt == "Int16"){
                userConf[x].bit[y].udt = Int16;
            }else if(udt == "Int32"){
                userConf[x].bit[y].udt = Int32;
            }else if(udt == "Uint32"){
                userConf[x].bit[y].udt = Uint32;
            }

            //读取传输缩放下拉框
            QString ts=dynamic_cast<QComboBox *>(pQTreeWidget->itemWidget(pQTreeWidgetItem, 3))->currentText();
            if(ts == "1.0E+0"){
                userConf[x].bit[y].ts = M1; //保存传输缩放
            }else if(ts == "1.0E+1"){
                userConf[x].bit[y].ts = M2;
            }else if(ts == "1.0E+2"){
                userConf[x].bit[y].ts = M3;
            }else if(ts == "1.0E+3"){
                userConf[x].bit[y].ts = M4;
            }else if(ts == "1.0E+4"){
                userConf[x].bit[y].ts = M5;
            }else if(ts == "1.0E+5"){
                userConf[x].bit[y].ts = M6;
            }else if(ts == "1.0E+6"){
                userConf[x].bit[y].ts = M7;
            }else if(ts == "1.0E+7"){
                userConf[x].bit[y].ts = M8;
            }else if(ts == "1.0E+8"){
                userConf[x].bit[y].ts = M9;
            }else if(ts == "1.0E+9"){
                userConf[x].bit[y].ts = M10;
            }

            //            qDebug("udt = %s    ,  ts = %s",qPrintable( udt ) ,qPrintable( ts ));
            //            qDebug("x = %d    ,  y = %d",x ,y);
        }

    }
}

void freamUI::readDataConf()
{
    //    1.第一种:直接通过坐标去获取
    //    /*普通表格控件获取方式*/
    //    QString strValue = tableObject->item(0,1)->text();
    //    /*表格中下拉框获取选中值*/
    //    QString strValue=dynamic_cast<QComboBox *>(ui->tableWidget->cellWidget(0,2))->currentText();

    //获取数据容器配置窗口句柄
    QList<QTableWidget*> pQTableWidgetChildren  =  this->findChildren<QTableWidget*>();
    //    qDebug("pQTableWidgetChildren:%lld",pQTableWidgetChildren.size());
    QTableWidget* pQTableWidget = pQTableWidgetChildren.at(0);

    //保存数据容器对应哪个帧
    for(int i = 0 ; i< 20 ; i++){
        QString strValue=dynamic_cast<QComboBox *>(pQTableWidget->cellWidget(i,1))->currentText();
        if(strValue == QString("F1")){
            dataConf[i].frameNum = F1;
        }else if(strValue == QString("F2")){
            dataConf[i].frameNum = F2;
        }else if(strValue == QString("F3")){
            dataConf[i].frameNum = F3;
        }else if(strValue == QString("F4")){
            dataConf[i].frameNum = F4;
        }else if(strValue == QString("F5")){
            dataConf[i].frameNum = F5;
        }else if(strValue == QString("F6")){
            dataConf[i].frameNum = F6;
        }else if(strValue == QString("F7")){
            dataConf[i].frameNum = F7;
        }else if(strValue == QString("F8")){
            dataConf[i].frameNum = F8;
        }else if(strValue == QString("F9")){
            dataConf[i].frameNum = F9;
        }else if(strValue == QString("FA")){
            dataConf[i].frameNum = FA;
        }
    }

    //保存数据容器对应哪个数据位
    for(int i = 0 ; i< 20 ; i++){
        QString strValue=dynamic_cast<QComboBox *>(pQTableWidget->cellWidget(i,2))->currentText();
        if(strValue == QString("1")){
            dataConf[i].bitNum = B1;
        }else if(strValue == QString("2")){
            dataConf[i].bitNum = B2;
        }else if(strValue == QString("3")){
            dataConf[i].bitNum = B3;
        }else if(strValue == QString("4")){
            dataConf[i].bitNum = B4;
        }else if(strValue == QString("5")){
            dataConf[i].bitNum = B5;
        }else if(strValue == QString("6")){
            dataConf[i].bitNum = B6;
        }else if(strValue == QString("7")){
            dataConf[i].bitNum = B7;
        }else if(strValue == QString("8")){
            dataConf[i].bitNum = B8;
        }else if(strValue == QString("9")){
            dataConf[i].bitNum = B9;
        }else if(strValue == QString("10")){
            dataConf[i].bitNum = B10;
        }
    }

}

//用户自定义帧解析方法
void freamUI::combinationUserData(qAgreement &mframe)
{
    //保存帧描述
    uesrFinalFrame.head=mframe.getHead();
    uesrFinalFrame.addr=mframe.getAddr();
    uesrFinalFrame.id=mframe.getId();

    uesrFinalFrame.ac=mframe.getAc();
    uesrFinalFrame.sc=mframe.getSc();
    //根据配置解析数据
    unsigned char idindex = uesrFinalFrame.id-0xF1; //对应的功能帧索引
    qDebug("idindex res:%d", idindex);
    int lenindex = mframe.getLen() ;
    unsigned char* pBuf = mframe.getDataPoint() ;
    unsigned int bufIndex = 0 ;

    for(int i = 0 ; i<10 ; i++){
        //数据归零
        uesrFinalFrame.data[i].Uint32 = 0;
    }
    //根据配置的数据类型组合数据
    for (uesrFinalFrame.len=0; uesrFinalFrame.len<10 && lenindex > 0 ; uesrFinalFrame.len++) {
        switch (userConf[idindex].bit[uesrFinalFrame.len].udt) {
        case Uint8 :
            lenindex-=1; //读取一字节
            uesrFinalFrame.data[uesrFinalFrame.len].Uint8  =  getUInt8( pBuf , &bufIndex) ;

            qDebug("Uint8 res:%d", uesrFinalFrame.data[uesrFinalFrame.len].Uint8);
            break;
        case Int16 :
            lenindex-=2; //读取二字节
            uesrFinalFrame.data[uesrFinalFrame.len].Int16  =  getInt16( pBuf , &bufIndex) ;
            qDebug("Int16 res:%d", uesrFinalFrame.data[uesrFinalFrame.len].Int16);
            break;
        case Uint16 :
            lenindex-=2; //读取二字节
            uesrFinalFrame.data[uesrFinalFrame.len].Uint16 =  getUInt16( pBuf , &bufIndex) ;
            qDebug("Uint16 res:%d", uesrFinalFrame.data[uesrFinalFrame.len].Uint16);
            break;
        case Int32  :
            lenindex-=4; //读取四字节
            uesrFinalFrame.data[uesrFinalFrame.len].Int32  =  getInt32( pBuf , &bufIndex) ;
            qDebug("Int32 res:%d", uesrFinalFrame.data[uesrFinalFrame.len].Int32);
            break;
        case Uint32 :
            lenindex-=4; //读取四字节
            uesrFinalFrame.data[uesrFinalFrame.len].Uint32  =  getUInt32( pBuf , &bufIndex) ;
            qDebug("Uint32 res:%d", uesrFinalFrame.data[uesrFinalFrame.len].Uint32);
            break;
        }
    }

    //    qDebug("3 res:%.10f", static_cast<double>(uesrFinalFrame.data[0].Uint32)/pow(10,userConf[0].bit[0].ts));

}


void freamUI::refresh()
{
    static long int frameCount = 0;//统计接收的总数据包数(由不同的帧组合)
    frameCount++;
    //------------------------------------------------------------------------------------
    //刷新数据容器数据显示
    //获取数据容器配置窗口句柄
    QList<QTableWidget*> pQTableWidgetChildren  =  this->findChildren<QTableWidget*>();
    //    qDebug("pQTableWidgetChildren:%lld",pQTableWidgetChildren.size());
    QTableWidget* pQTableWidget = pQTableWidgetChildren.at(0);

    for(int i = 0 ; i<20 ;i++){     //遍历数据容器
        for(int x=0 ; x<10 ; x++){  //遍历数据容器配置
            //判断当前帧的id与要显示的帧id是否相符                    //如果用户帧使能
            if(uesrFinalFrame.id-0xF1 == dataConf[i].frameNum && userConf[x].check_sta==2){
                int bitNum = dataConf[i].bitNum;
                //根据缩放比例换算结果
                double res = static_cast<double>(uesrFinalFrame.data[bitNum].Uint32)/pow(10,userConf[x].bit[bitNum].ts);
                //结果转输出的字符串
                QString resStr = QString::number(res);
                //刷新表格数据
                pQTableWidget->item(i,3)->setText(resStr);
                //发送数据显示波形
                emit sendres(frameCount , i , &res);

            }
        }
    }

    //------------------------------------------------------------------------------------


}


void freamUI::writeText(qAgreement &mframe)
{
    //    //保持编辑器在光标最后一行
    //    QTextCursor cursor=ui->textEdit->textCursor();
    //    cursor.movePosition(QTextCursor::End);
    //    ui->textEdit->setTextCursor(cursor);


    //    QByteArray  frameResultHead(&head,1),
    //            frameResultAddr(&addr,1),
    //            frameResultId(&id,1),
    //            frameResultLen(&len,1),
    //            frameResultBuf(frame_data),
    //            frameResultSc(&ac,1),
    //            frameResultAc(&sc,1);

    //    QByteArray frameResult = frameResultHead +
    //            frameResultAddr +
    //            frameResultId   +
    //            frameResultLen  +
    //            frameResultBuf  +
    //            frameResultSc   +
    //            frameResultAc   ;
    //    ui->textEdit->append(frameResult.toHex(' ').toUpper() += "\n");

    readUserConf();
    readDataConf();

    combinationUserData(mframe);
    refresh();
}




unsigned char freamUI::getUInt8(unsigned char *pData, unsigned int *i)
{
    unsigned  char result = 0;
    result = (unsigned  char)pData[*i];
    *i += 1 ;
    return result ;
}

unsigned  short  freamUI::getUInt16(unsigned char *pData, unsigned int *i)
{
    unsigned  short result = 0;
    result = (unsigned  short)pData[*i];
    *i += 1 ;
    result += (unsigned  short)(pData[*i]<<8);
    *i += 1 ;
    return result ;
}

short  freamUI::getInt16(unsigned char* pData , unsigned int* i)
{
    short result = 0;
    result = (short)pData[*i];
    *i += 1 ;
    result += (short)(pData[*i]<<8);
    *i += 1 ;
    return result ;
}

unsigned  int freamUI::getUInt32(unsigned char *pData, unsigned int *i)
{
    unsigned  int result = 0;
    result = (int)pData[*i];
    *i += 1 ;
    result += (int)(pData[*i]<<8);
    *i += 1 ;
    result += (int)(pData[*i]<<16);
    *i += 1 ;
    result += (int)(pData[*i]<<24);
    *i += 1 ;
    return result ;
}

int freamUI::getInt32(unsigned char *pData, unsigned int *i)
{
    int result = 0;
    result = (int)pData[*i];
    *i += 1 ;
    result += (int)(pData[*i]<<8);
    *i += 1 ;
    result += (int)(pData[*i]<<16);
    *i += 1 ;
    result += (int)(pData[*i]<<24);
    *i += 1 ;
    return result ;
}











