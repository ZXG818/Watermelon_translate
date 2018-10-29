#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <Python.h>     //����python�ļ�


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

//����������ѡ��ͼƬ
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

//��ʾ˵��
void MainWindow::show_instruction_action()
{
    QMessageBox::about(NULL, QString::fromLocal8Bit("����"),
                       QString::fromLocal8Bit("��ӭ��ϵ��:QQ->2015572934\n"
                                              "��ӭ��www.0xAA55.com����\n"
                                              "�������С�ܴ�Ů����UI��Ҳ֪\n"
                                              "���󣬵��һ����Ŭ����ͬʱҲ\n"
                                              "ϣ����λ������ָ���ҡ�\n"
                                              "лл���!!!\t\n"
                                              "\t\t     ---watermelon\t"));
}


//��ȡĿ���ļ�
void MainWindow::read_txt_line()
{
    QString str = ui->directoryComboBox->currentText();     //��ȡѡ�е��ļ���
    QFile file(str);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();
    ui->origin_textEdit->setPlainText(QString::fromLocal8Bit(t));
    file.close();

}


//����python�ű�fanyi.py�����з���
void MainWindow::use_youdao_translate()
{
    //��ʼ��pythonģ��
    Py_Initialize();
    if(!Py_IsInitialized())
    {
        QMessageBox::critical(NULL, "Error1", "Please get in touch with the Watermelon,sorry.",
                              QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }

    //����fanyi.py�ļ�
    PyObject *pModule = PyImport_ImportModule("fanyi");
    if(!pModule)
    {
        QMessageBox::critical(NULL, "Error2", "Please get in touch with the Watermelon,sorry.",
                              QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

    //��ȡfanyiģ���е�get_translation_result����
    PyObject *pGTResult = PyObject_GetAttrString(pModule,"get_translation_result");

    if(!pGTResult)
    {
        QMessageBox::critical(NULL, "Error3", "Please get in touch with the Watermelon,sorry.",
                              QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }


    //��ʼ����get_translation_result����
    QString origin = ui->origin_textEdit->toPlainText();         //��ȡԭ���е�����
    //�����з��滻��*�ַ�����Ϊԭ�ű�ֻ����ȡû�л��з����ַ���
    origin.replace('\n','*');

    char *str = NULL;
    QByteArray ba = origin.toLatin1();
    str = ba.data();                          //��QStringת��Ϊchar *

    PyObject *pRet = PyObject_CallFunction(pGTResult,"s",str);

    //��ȡpython�ķ���ֵ
    char *res = NULL;
    PyArg_Parse(pRet,"s",&res);

    //�����صĽ��ת����QString����
    QString result = res;
    result.replace('*','\n');               //�������ʽ���������������
    ui->translate_textEdit->setPlainText(result);

    //�������ͷ�python
    Py_Finalize();
}



