#ifndef WAVEFORMUI_H
#define WAVEFORMUI_H

#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class waveFormUI;
}

class waveFormUI : public QWidget
{
    Q_OBJECT

public:
    explicit waveFormUI(QWidget *parent = nullptr);
    ~waveFormUI();

    QCustomPlot* pQCustomPlot;

public slots:
    void paintUserData(long int frameCountint ,int dataNum , double* res);

private:
    Ui::waveFormUI *ui;
};

#endif // WAVEFORMUI_H
