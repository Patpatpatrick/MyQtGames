#include "welcomeui.h"
#include "Board.h"
#include <QApplication>
#include <QWidget>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WelcomeUI window;
    window.resize(320, 240);
    window.setWindowTitle(QApplication::translate("childwidget", "Child widget"));
    window.show();
    return a.exec();
}
