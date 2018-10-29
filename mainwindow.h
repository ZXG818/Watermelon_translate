#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_toolButton_clicked();          //ѡ��Ŀ���ı����з���
    void show_instruction_action();        //��ʾ˵��
    void read_txt_line();                  //��ȡĿ���ļ�������
    void use_youdao_translate();           //��python�ű������е�������з����ı�

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
