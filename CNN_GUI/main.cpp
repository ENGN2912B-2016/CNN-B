#include "cnnviewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CNNViewer w;
    w.show();

    return a.exec();
}
