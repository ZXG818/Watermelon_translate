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
    ui->txt_label->setText(QString::fromLocal8Bit("�������watermelon��д��\n"
                                                  "�������������ҳ���е�����.\n"
                                                  "���հ�Ȩ���е��������У�\n"
                                                  "�κ��˻���֯��ʹ�ø����ʱ��\n"
                                                  "δ������ͬ���Ͻ�������ҵ��;.\n"
                                                  "�����Դ����github�Ϲ���.\n"
                                                  "��ϸ���ReadMe.txt"));
}



//�ۺ���
void Dialog::agree_btn_clicked()
{
    accept();
}

void Dialog::disagree_btn_clicked()
{
    close();
}


