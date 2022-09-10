#include "sendui.h"
#include "ui_sendui.h"

sendUI::sendUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sendUI)
{
    ui->setupUi(this);
}

sendUI::~sendUI()
{
    delete ui;
}
