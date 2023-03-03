#include "imageviewer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageViewer w;
    w.showMaximized();
    return a.exec();
}
