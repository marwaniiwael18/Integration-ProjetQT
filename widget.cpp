#include "widget.h"
#include "ui_widget.h"
#include <QGridLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    lineEdit = new QLineEdit();
    captchaBox = new CaptchaBox(this);
    label = new QLabel();
    yesBtn =new QPushButton(tr("Valider"));
    connect(yesBtn,SIGNAL(clicked()),this,SLOT(checkCode()));
    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->setColumnStretch(0,1);
    gridLayout->setColumnStretch(1,1);
    gridLayout->addWidget(lineEdit,0,0);
    gridLayout->addWidget(captchaBox,0,1);
    gridLayout->addWidget(label,1,0);
    gridLayout->addWidget(yesBtn,1,1);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::checkCode()
{
    QString text = lineEdit->text();
    if(captchaBox->checkCaptcha(text))
    {
        label->setText(tr("Le code de vérification est entré correctement"));
    }
    else
    {
        label->setText(tr("code de vérification incorrect"));
    }
}
