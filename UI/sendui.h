#ifndef SENDUI_H
#define SENDUI_H

#include <QWidget>

namespace Ui {
class sendUI;
}

class sendUI : public QWidget
{
    Q_OBJECT

public:
    explicit sendUI(QWidget *parent = nullptr);
    ~sendUI();

private:
    Ui::sendUI *ui;
};

#endif // SENDUI_H
