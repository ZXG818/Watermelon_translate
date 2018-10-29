#include "dialog.h"
#include "ui_dialog.h"
#include <QString>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    pic_label_show();
    txt_label_show();

    connect(ui->agree_btn,SIGNAL(clicked()),this,SLOT(agree_btn_clicked()));
    connect(ui->disagree_btn,SIGNAL(clicked()),this,SLOT(disagree_btn_clicked()));


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::pic_label_show()
{
    ui->pic_label->setPixmap(QString("../translation/images/pic1.jpg"));
}

void Dialog::txt_label_show()
{
    ui->txt_label->setText(QString::fromLocal8Bit("本软件由watermelon编写，\n"
                                                  "翻译引擎采用网页版有道翻译.\n"
                                                  "最终版权归有道翻译所有，\n"
                                                  "任何人或组织在使用该软件时，\n"
                                                  "未经本人同意严禁用于商业用途.\n"
                                                  "本软件源码在github上公开.\n"
                                                  "详细请见ReadMe.txt"));
}



//槽函数
void Dialog::agree_btn_clicked()
{
    accept();
}

void Dialog::disagree_btn_clicked()
{
    close();
}


