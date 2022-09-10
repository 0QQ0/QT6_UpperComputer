#ifndef QAGREEMENT_H
#define QAGREEMENT_H

#include <QObject>


class qAgreement : public QObject
{
    Q_OBJECT
public:

    explicit qAgreement(QObject *parent = nullptr);


    //解析收到的数据流中的数据
    void analysis(QByteArray ReciveData);


    //获取实例对象中的数据函数
    unsigned char getHead(){ return head  ; }
    unsigned char getAddr(){ return addr  ; }
    unsigned char getId(){  return id ; }
    unsigned char getLen(){ return len  ; }
    unsigned char* getDataPoint( ){ return frame_data  ; }
    unsigned char getSc(){ return sc  ; }
    unsigned char getAc(){ return ac  ; }

    signed char getRecSta(){ return  rec_sta ; }
    int         getIndexof(){ return indexof  ; }
    qAgreement& getClassQuote(){ return *this  ; } //返回自身引用


private:
    //协议头
    unsigned char  myHead = 0xAA;

    //帧内容
    unsigned char  head = 0x00;             //帧头
    unsigned char  addr = 0x00;             //帧地址
    unsigned char  id   = 0x00;             //帧ID
    unsigned char  len  = 0x00;             //帧数据长度
    unsigned char  frame_data[254]={};      //帧数据
    unsigned char  sc   = 0x00;             //帧和校验
    unsigned char  ac   = 0x00;             //帧附加校验
    signed char  rec_sta= 0x00;             //一帧接收状态
    int          indexof= 0x00;             //帧头索引

    //接收成功执行函数
    void receivedOk();
    //私有属性复位
    void refresh();
    //对结果进行低八位累加CRC校验(unsigned char)
    bool crcCheck();


signals:
    //接收完成一帧数据后将类对象传递出去的信号
    void ResultFrame_signal(qAgreement &mframe);

};




#endif // MYAGREEMENT_H
