#include "MainWindow.h"
#include <QApplication>
#include <QFont>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFont font;
    font=w.font();
    font.setFamily("unifont");
//    w.setFont(font);
    w.show();

    return a.exec();
}
