#include "qagreement.h"


qAgreement::qAgreement(QObject *parent)
    : QObject{parent}
{
}

/**********************************************
 *  解析格式 :
 *  帧头 地址 ID 数据长度 数据0-N ac sc
 *
 *
 ************************************************/
void qAgreement::analysis(QByteArray ReciveData  )
{

    indexof=0x00;//新的数据包索引位置置零
    if(!ReciveData.isEmpty())//数据流非空
    {
        int ReciveData_size = ReciveData.size() ;
        // 如果上一帧数据未接收完
        if(rec_sta != 0){
            qDebug("Same  frame") ;
            //新的数据包中获取帧描述信息
            for(; -3 <= rec_sta && rec_sta <0 ;rec_sta--)
            {
                if(ReciveData_size -  indexof  <1){ // 到达数据流末尾
                    break;
                }

                if(rec_sta == -1){  // rec_sta为-1表示待读取帧地址
                    addr =  ReciveData.at(indexof++);
                }

                if(rec_sta == -2){   // rec_sta为-2表示待读取帧id
                    id   =  ReciveData.at(indexof++);
                }

                if(rec_sta == -3){   //rec_sta为-3表示待读取帧数据长度
                    len  =  ReciveData.at(indexof++)+2;
                    rec_sta = len ;//此时rec_sta的值表示剩余读取数据长度(数据长度+2包括crc两位)
                    break;
                }
            }
            //rec_sta>0证明已经接收完帧描述信息
            //新的数据包中获取帧数据内容
            for(;ReciveData_size -  indexof  >1 && rec_sta >2 ; rec_sta--)
            {
                frame_data[len-rec_sta] = ReciveData.at(indexof++);
                qDebug("frame_data[%d]:0x%x"  ,  len - rec_sta ,frame_data[len-rec_sta]) ;
            }
            //新的数据包中获取帧src校验结果
            for(;ReciveData_size -  indexof  >0 && 0<rec_sta && rec_sta <=2 ; indexof++)
            {
                rec_sta--;
                if(rec_sta == 1){// rec_sta为-2表示待读取帧id
                    sc   =  ReciveData.at(indexof);
                    qDebug("Sc:0x%x",sc) ;
                }
                if(rec_sta == 0){// rec_sta为-2表示待读取帧id
                    ac   =  ReciveData.at(indexof);
                    qDebug("Ac:0x%x",ac) ;
                }
            }
            //接收完成
            if(rec_sta == 0){
                receivedOk();
            }
        }
        //新的一帧
        while(rec_sta == 0)
        {
            indexof = ReciveData.indexOf(myHead , indexof);
            //找到帧头
            if(indexof != -1){
                qDebug("new mframe") ;
                head =  ReciveData.at(indexof); //储存帧头索引
                //获取帧描述信息
                for(; rec_sta >-3 ;){
                    rec_sta--;
                    if(ReciveData_size -  indexof  <=1){   // 到达数据流末尾
                        break;
                    }
                    if(rec_sta == -1){  // rec_sta为-1表示待读取帧地址
                        addr =  ReciveData.at(++indexof);
                    }
                    if(rec_sta == -2){   // rec_sta为-2表示待读取帧id
                        id   =  ReciveData.at(++indexof);
                    }
                    if(rec_sta == -3){   //rec_sta为-3表示待读取帧数据长度
                        len  =  ReciveData.at(++indexof)+2;
                        rec_sta = len ;//此时rec_sta的值表示剩余读取数据长度(数据长度+2包括crc两位)
                        break;
                    }
                }
                //rec_sta>0证明接收完帧描述信息
                //获取帧数据内容
                if(rec_sta>0){
                    for(;ReciveData_size -  indexof  >1 && rec_sta!=2;rec_sta--){
                        frame_data[len - rec_sta ] = ReciveData.at(++indexof);
                        qDebug("frame_data[%d]:0x%x"  ,  len - rec_sta ,frame_data[len-rec_sta]) ;
                    }

                    //获取帧src校验结果
                    for(;ReciveData_size -  indexof  >1 && rec_sta!=0;)
                    {
                        rec_sta--;
                        if(rec_sta == 1){// rec_sta为1表示待读取帧sc
                            sc   =  ReciveData.at(++indexof);
                            qDebug("Sc:0x%x",sc) ;
                        }
                        if(rec_sta == 0){// rec_sta为0表示待读取帧ac
                            ac   =  ReciveData.at(++indexof);
                            qDebug("Ac:0x%x",ac) ;
                        }
                    }
                }
                //接收完成
                if(rec_sta == 0){
                    receivedOk();
                }
            }
            else{
                break;
            }
        }

    }
}

void qAgreement::receivedOk()
{
    len-=2; //len值还原成数据内容长度
    if(crcCheck() == true){//广播结果
        emit ResultFrame_signal(getClassQuote()); //将类引用广播出去
        qDebug("mframe right") ;
    }
    else{
        qDebug("mframe Error") ;
    }
    refresh();// 刷新帧描述
}

bool qAgreement::crcCheck()
{
    unsigned char sumcheck = 0;
    unsigned char addcheck = 0;

    sumcheck += head;
    addcheck += sumcheck;
    sumcheck += addr;
    addcheck += sumcheck;
    sumcheck += id;
    addcheck += sumcheck;
    sumcheck += len;
    addcheck += sumcheck;
    for(unsigned char i=0; i < len ; i++)
    {
        sumcheck += frame_data[i]; //从帧头开始，对每一字节进行求和，直到DATA区结束
        addcheck += sumcheck; //每一字节的求和操作，进行一次sumcheck的累加
    }

    qDebug("crcCheck sc:0x%x",sumcheck) ;
    qDebug("crcCheck ac:0x%x",addcheck) ;
    //如果计算出的sumcheck和addcheck和接收到的check数据相等，代表校验通过，反之数据有误
    if(sumcheck == sc && addcheck == ac)
        return true; //校验通过
    else
        return false; //校验失败

}

void qAgreement::refresh()
{
    head=0x00;
    addr=0x00;
    id=0x00;
    len=0x00;
    sc=0x00;
    ac=0x00;
    rec_sta=0x00;
    //     indexof=0x00;

}


