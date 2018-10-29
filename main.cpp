#include "mainwindow.h"
#include <QApplication>
#include "dialog.h"
#include <QString>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Watermelon-translation");
    Dialog dlg;
    dlg.setWindowTitle(QString::fromLocal8Bit("–≠“È"));
    if(dlg.exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else
    {
        return 0;
    }

}
