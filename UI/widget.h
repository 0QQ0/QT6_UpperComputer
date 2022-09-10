#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "QTreeWidget"
#include "QVBoxLayout"

#include <QMouseEvent>
#include "SerialConf.h"
#include "sendui.h"
#include "freamui.h"
#include "userconfui.h"
#include "datashowui.h"

#include "qcustomplot.h"
#include "waveformui.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void hideAllShow();
private slots:

    void on_back_clicked();

    void on_win2_clicked();

    void on_win1_clicked();

    void on_first_clicked();

    void on_userConf_clicked();

    void on_becomesmall_clicked();

    void on_dataShow_clicked();


    void on_toolButton_clicked();

private:
    Ui::Widget *ui;
    win1* pSerialConfUI;
    sendUI* psendUI;
    freamUI* pfreamUI;
    userConfUI* puserConfUI;
    dataShowUI* pdataShowUI;
    waveFormUI* pwaveFormUI;
    //无边框拖动
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public:
    QPoint mousePoint;
    bool mouse_press;
};
#endif // WIDGET_H
