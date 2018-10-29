#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <Python.h>     //包含python文件


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->toolButton,SIGNAL(triggered(QAction*)),this,SLOT(on_toolButton_clicked()));
    connect(ui->translate_btn,SIGNAL(clicked()),this,SLOT(use_youdao_translate()));
    connect(ui->instruction_action,SIGNAL(triggered(bool)),this,SLOT(show_instruction_action()));
    connect(ui->choose_btn,SIGNAL(clicked()),this,SLOT(read_txt_line()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//弹出窗口来选择图片
void MainWindow::on_toolButton_clicked()
{
   QString directory = QDir::toNativeSeparators(
                QFileDialog::getOpenFileName(this,tr("Open File"),
                                             QString::fromLocal8Bit("/home"),
                                             tr("File (*.txt)")));

    if(!directory.isEmpty())
    {
        if(ui->directoryComboBox->findText(directory)==-1)
        {
            ui->directoryComboBox->addItem(directory);
        }
        ui->directoryComboBox->setCurrentIndex(ui->directoryComboBox->findText(directory));
    }

}

//显示说明
void MainWindow::show_instruction_action()
{
    QMessageBox::about(NULL, QString::fromLocal8Bit("关于"),
                       QString::fromLocal8Bit("欢迎联系我:QQ->2015572934\n"
                                              "欢迎来www.0xAA55.com交流\n"
                                              "本软件是小弟处女作，UI我也知\n"
                                              "道丑，但我会继续努力，同时也\n"
                                              "希望各位大佬来指正我。\n"
                                              "谢谢大家!!!\t\n"
                                              "\t\t     ---watermelon\t"));
}


//读取目标文件
void MainWindow::read_txt_line()
{
    QString str = ui->directoryComboBox->currentText();     //获取选中的文件名
    QFile file(str);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();
    ui->origin_textEdit->setPlainText(QString::fromLocal8Bit(t));
    file.close();

}


//借助python脚本fanyi.py来进行翻译
void MainWindow::use_youdao_translate()
{
    //初始化python模块
    Py_Initialize();
    if(!Py_IsInitialized())
    {
        QMessageBox::critical(NULL, "Error1", "Please get in touch with the Watermelon,sorry.",
                              QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }

    //导入fanyi.py文件
    PyObject *pModule = PyImport_ImportModule("fanyi");
    if(!pModule)
    {
        QMessageBox::critical(NULL, "Error2", "Please get in touch with the Watermelon,sorry.",
                              QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

    //获取fanyi模块中的get_translation_result函数
    PyObject *pGTResult = PyObject_GetAttrString(pModule,"get_translation_result");

    if(!pGTResult)
    {
        QMessageBox::critical(NULL, "Error3", "Please get in touch with the Watermelon,sorry.",
                              QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }


    //开始调用get_translation_result函数
    QString origin = ui->origin_textEdit->toPlainText();         //获取原文中的内容
    //将换行符替换成*字符，因为原脚本只能爬取没有换行符的字符串
    origin.replace('\n','*');

    char *str = NULL;
    QByteArray ba = origin.toLatin1();
    str = ba.data();                          //将QString转化为char *

    PyObject *pRet = PyObject_CallFunction(pGTResult,"s",str);

    //获取python的返回值
    char *res = NULL;
    PyArg_Parse(pRet,"s",&res);

    //将返回的结果转化成QString类型
    QString result = res;
    result.replace('*','\n');               //将输出格式换回来，我真聪明
    ui->translate_textEdit->setPlainText(result);

    //结束，释放python
    Py_Finalize();
}



