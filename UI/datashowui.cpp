#include "datashowui.h"
#include "ui_datashowui.h"



dataShowUI::dataShowUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dataShowUI)
{
    ui->setupUi(this);


    frmDevice* usefrmDevice[20];
    flyFrms = new QList<QWidget *>();

    //创建飞行数据面板
    qDeleteAll(*flyFrms);
    flyFrms->clear();
    for (int i = 0; i < 10; i++) {
        frmDevice *frm = new frmDevice;
        QStringList *pQStringList = new QStringList;
        pQStringList->append("Id : 0x "+QString::number(i));
        pQStringList->append("pitch:0");
        pQStringList->append("roll:0");
        pQStringList->append("yaw:0");
        pQStringList->append("频率: 0\t\t\t   传输缩放");
        frm->addFrmDevice(pQStringList);
        flyFrms->append(frm);
    }

    ui->flyDatawidget->setWidget(*flyFrms, 4);
    ui->flyDatawidget->setMargin(9);
    ui->flyDatawidget->setSpacing(9);


    //创建用户数据面板
    userFrms = new QList<QWidget *>();
    for (int i = 1; i <= 20; i++) {
        usefrmDevice[i] = new frmDevice;
        QStringList *useQStringList  = new QStringList;
        useQStringList ->append("UserData"+QString::number(i));
        useQStringList->append("Data:\t"+QString::number(i));
        useQStringList->append("-----------------------------------------------");
        usefrmDevice[i]->addFrmDevice(useQStringList);

        userFrms->append(usefrmDevice[i]);
    }

    //放进标签页
    ui->userDatawidget_2->setWidget(*userFrms, 4);
    ui->userDatawidget_2->setMargin(9);
    ui->userDatawidget_2->setSpacing(9);

}

dataShowUI::~dataShowUI()
{
    delete ui;
}

void dataShowUI::setUserData(frmDevice *pfrmDevice, double value)
{
    QStringList *change = new QStringList;
    change->append(QString("Data :\t%1").arg(value));
    pfrmDevice->setLabelValue(change);
}


