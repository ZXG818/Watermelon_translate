#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void pic_label_show();      //��ʾͼƬ
    void txt_label_show();      //��ʾ��Ȩ��Ϣ

private slots:
    void agree_btn_clicked();
    void disagree_btn_clicked();


private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
