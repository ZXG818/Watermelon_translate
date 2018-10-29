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
    void on_toolButton_clicked();          //选择目标文本进行翻译
    void show_instruction_action();        //显示说明
    void read_txt_line();                  //读取目标文件的内容
    void use_youdao_translate();           //用python脚本借助有道翻译进行翻译文本

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
