#ifndef DATASHOWUI_H
#define DATASHOWUI_H

#include <QWidget>

#include "QGroupBox"
#include "QVBoxLayout"
#include "QLabel"

#include <QStringListModel>
#include <QStandardItemModel>
#include <QModelIndex>

#include "extend/frmdevice.h"

namespace Ui {
class dataShowUI;
}

class dataShowUI : public QWidget
{
    Q_OBJECT

public:
    explicit dataShowUI(QWidget *parent = nullptr);
    ~dataShowUI();

public slots:

private:
    Ui::dataShowUI *ui;

    QRect location;
    QList<QWidget *>* flyFrms;
    QList<QWidget *>* userFrms;

    void setUserData(frmDevice* pfrmDevice , double value);


};

#endif // DATASHOWUI_H
