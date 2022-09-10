#ifndef FREAMUI_H
#define FREAMUI_H

#include <QWidget>

#include "qagreement.h"
#include "SerialConf.h"

//------------------------------------------------------------------------------------
//自定义帧结构体
enum user_data_type{
    Uint8=1, Uint16, Int16, Int32, Uint32
};

enum transmission_scaling{
    //缩放10的几次方倍数
    M1=0, M2, M3, M4, M5 , M6, M7, M8, M9, M10
};

typedef struct bitConf1         //一个数据位
{
    user_data_type udt;         //一个数据位的数据类型
    transmission_scaling ts;    //一个数据位的传输缩放
}bituserConf;

typedef struct  Conf1
{
    unsigned int check_sta;      //此帧选择状态
    bitConf1 bit[10];            //此帧各个位的情况
}frameuserConf;                  //一帧自定义配置
//------------------------------------------------------------------------------------
//数据容器结构体
enum whatFrame{
    F1=0, F2 , F3 ,F4 ,F5 ,F6 ,F7,F8 ,F9 ,FA
};
enum whatBit{
    B1=0, B2 , B3 ,B4 ,B5 ,B6 ,B7,B8 ,B9 ,B10
};
typedef struct Container        //一个数据容器
{
    whatFrame frameNum;         //数据容器对应的帧
    whatBit bitNum;             //数据容器对应的帧数据位置
}dataContainer;
//------------------------------------------------------------------------------------
//用户自定义帧最终解析结果
union databit
{
    unsigned char Uint8 ;
    unsigned short Uint16 ;
    short Int16 ;
    int   Int32;
    unsigned int   Uint32;
};
typedef struct frameResult                  //最终解析出来的帧数据
{
    //帧内容
    unsigned char  head = 0x00;             //帧头
    unsigned char  addr = 0x00;             //帧地址
    unsigned char  id   = 0x00;             //帧ID
    unsigned char  len  = 0x00;             //帧数据长度
    databit data[10];
    unsigned char  sc   = 0x00;             //帧和校验
    unsigned char  ac   = 0x00;             //帧附加校验
}finalFrame;
//------------------------------------------------------------------------------------

namespace Ui {
class freamUI;
}

class freamUI : public QWidget
{
    Q_OBJECT

public:
    explicit freamUI(QWidget *parent = nullptr);
    ~freamUI();

    qAgreement *pqAgreement;

    frameuserConf  userConf[10];//F1-FA 共十帧配置
    dataContainer  dataConf[20];//1-10  共十个数据容器
    double         uesrDataBuf[20] ;//储存的用户数据值


    finalFrame uesrFinalFrame;

    void readUserConf();
    void readDataConf();
    void combinationUserData(qAgreement &mframe);
    void refresh();

signals:
    void sendres(long int frameCountint ,int dataNum , double*  uesrData);
private slots:
    void writeText(qAgreement &mframe);

private:
    Ui::freamUI *ui;

    //组合一个字节
    unsigned char getUInt8(unsigned char* pData , unsigned int* i);
    //组合两个字节
    unsigned short getUInt16(unsigned char* pData , unsigned int* i);
    short getInt16(unsigned char* pData , unsigned int* i);
    //组合四个字节
    unsigned int getUInt32(unsigned char* pData , unsigned int* i);
    int getInt32(unsigned char* pData , unsigned int* i);



};

#endif // FREAMUI_H



//------------------------------------------------------------------------------------
//#ifndef DATACOMBINATION_H
//#define DATACOMBINATION_H

//#include <QObject>


////此类用于按指定格式组合帧数据
////数据区使用小端模式，低字节在前
//class dataCombination
//{
//public:
//    dataCombination();

//    //读取目标地址 id
//    void findTarget(unsigned char mAddr , unsigned char mId,unsigned char* pData);

//    //    ID：0x01：数据长度 13 惯性传感器数据
//    //    ACC、GYR：依次为加速度、陀螺仪传感器数据。
//    //    SHOCK_STA：震动状态。
//    short AccX(){return accX;}
//    short AccY(){return accY;}
//    short AccZ(){return accZ;}
//    short GyrX(){return gyrX;}
//    short GyrY(){return gyrY;}
//    short GyrZ(){return gyrZ;}
//    unsigned char ShockSta(){return SHOCK_STA;}

//    //    ID：0x02：罗盘、气压、温度传感器数据
//    //    MAG：磁罗盘传感器数据。
//    //    TMP: 传感器温度，放大 10 倍传输，0.1 摄氏度。
//    //    ALT_BAR：气压计高度，单位 cm。
//    //    BAR_STA、MAG_STA：依次为气压状态、罗盘状态
//    short MagX(){return magX;}
//    short MagY(){return magY;}
//    short MagZ(){return magZ;}
//    int   AltBar(){return altBar;}
//    short Tmp(){return tmp;}
//    unsigned char MagSta(){return MAG_STA;}
//    unsigned char BarSta(){return BAR_STA;}

//    // ADDR: 0xFF ID：0x03 数据长度 7 飞控姿态：欧拉角格式
//    short Roll(){return roll;}
//    short Pit(){return pit;}
//    short Yaw(){return yaw;}
//    unsigned char fusionSta(){return FUSION_STA;}



//private:

//    //组合两个字节
//    unsigned short getUInt16(unsigned char* pData , unsigned int* i);
//    short getInt16(unsigned char* pData , unsigned int* i);
//    //组合四个字节
//    unsigned int getUInt32(unsigned char* pData , unsigned int* i);
//    int getInt32(unsigned char* pData , unsigned int* i);


//    //    ID：0x01：数据长度 13 惯性传感器数据
//    //    ACC、GYR：依次为加速度、陀螺仪传感器数据。
//    //    SHOCK_STA：震动状态。
//    short accX  = 0 ;
//    short accY  = 0 ;
//    short accZ  = 0 ;
//    short gyrX  = 0 ;
//    short gyrY  = 0 ;
//    short gyrZ  = 0 ;
//    unsigned char SHOCK_STA = 0;
//    void FF01combination(unsigned char* pData);

//    //    ID：0x02：罗盘、气压、温度传感器数据
//    //    MAG：磁罗盘传感器数据。
//    //    TMP: 传感器温度，放大 10 倍传输，0.1 摄氏度。
//    //    ALT_BAR：气压计高度，单位 cm。
//    //    BAR_STA、MAG_STA：依次为气压状态、罗盘状态
//    short magX  = 0 ;
//    short magY  = 0 ;
//    short magZ  = 0 ;
//    int   altBar  = 0 ;
//    short tmp  = 0 ;
//    unsigned char BAR_STA  = 0 ;
//    unsigned char MAG_STA  = 0 ;
//    void FF02combination(unsigned char* pData);


//    //    ID：0x03：数据长度 13 飞控姿态：欧拉角格式
//    //    三个姿态角数据放大100倍数
//    short roll = 0 ;
//    short pit = 0 ;
//    short yaw = 0 ;
//    unsigned char FUSION_STA = 0 ;
//    void FF03combination(unsigned char* pData);

//};

//#endif // DATACOMBINATION_H


//------------------------------------------------------------------------------------

//#include "datacombination.h"

//dataCombination::dataCombination()
//{

//}

//void dataCombination::findTarget(unsigned char mAddr , unsigned char mId , unsigned char* pData)
//{
//    if(mAddr == 0xFF)
//    {
//        switch (mId) {
//        //固定
//        case 0x01:// ADDR: 0xFF ID：0x03：飞控姿态：欧拉角格式
//            FF01combination(pData);
//            break;
//        case 0x02:// ADDR: 0xFF ID：0x03：飞控姿态：欧拉角格式
//            FF02combination(pData);
//            break;
//        case 0x03:// ADDR: 0xFF ID：0x03：飞控姿态：欧拉角格式
//            FF03combination(pData);
//            break;

//        //用户自定义
//        }
//    }
//}


//// ADDR: 0xFF
////ID：0x01：数据长度 13 惯性传感器数据
//void dataCombination::FF01combination(unsigned char* pData)
//{
//    unsigned int i = 0;
//    accX  = getInt16(pData , &i) ;
//    accY  = getInt16(pData , &i) ;
//    accZ  = getInt16(pData , &i) ;
//    gyrX  = getInt16(pData , &i) ;
//    gyrY  = getInt16(pData , &i) ;
//    gyrZ  = getInt16(pData , &i) ;
//    SHOCK_STA = pData[i++];
//    qDebug("accX : %d , accY : %d , accZ : %d , SHOCK_STA : %d" ,accX , accY , accZ, SHOCK_STA) ;
//}

//void dataCombination::FF02combination(unsigned char *pData)
//{
//    unsigned int i = 0;
//      magX  = getInt16(pData , &i) ;
//      magY  = getInt16(pData , &i) ;
//      magZ  = getInt16(pData , &i) ;
//      altBar  = getInt32(pData , &i) ;
//      tmp  = getInt16(pData , &i) ;
//      BAR_STA  = pData[i++];
//      MAG_STA  = pData[i++];
//      qDebug("magX : %d , magY : %d , tmp : %d , altBar : %d" ,magX , magY , tmp, altBar) ;
//}

////ID：0x03 数据长度 7 飞控姿态：欧拉角格式
//void dataCombination::FF03combination(unsigned char* pData)
//{
//    unsigned int i = 0;
//    roll = getInt16(pData , &i) ;
//    pit  = getInt16(pData , &i) ;
//    yaw  = getInt16(pData , &i) ;
//    FUSION_STA = pData[i++];

//    qDebug("roll : %d , pit : %d , yaw : %d , FUSION_STA : %d" ,Roll() , Pit() , Yaw(), fusionSta()) ;
//}


//------------------------------------------------------------------------------------

