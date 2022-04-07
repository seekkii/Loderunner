#include "mainwindow.h"

#include <QApplication>
#include "ui.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);
    QApplication app{argc, argv};
    ui w;
    QPalette pal = QPalette();

    // set black background
    // Qt::black / "#000000" / "black"
    pal.setColor(QPalette::Window, Qt::black);

    w.setAutoFillBackground(true);
    w.setPalette(pal);
    w.setMinimumSize(1000,1000);
    w.show();

    return app.exec();
}
