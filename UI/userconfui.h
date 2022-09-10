#ifndef USERCONFUI_H
#define USERCONFUI_H

#include <QWidget>
#include <QComboBox>

namespace Ui {
class userConfUI;
}

class userConfUI : public QWidget
{
    Q_OBJECT

public:
    explicit userConfUI(QWidget *parent = nullptr);
    ~userConfUI();
private:
    Ui::userConfUI *ui;

    void setUserConfUI( );
    void setDataConfUI( );

};

#endif // USERCONFUI_H
