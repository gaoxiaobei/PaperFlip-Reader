#include <QApplication>
#include "ui/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("PaperFlip");
    app.setApplicationVersion("0.1");

    MainWindow window;
    window.show();

    return app.exec();
}