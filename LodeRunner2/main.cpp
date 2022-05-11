#include "mainwindow.h"

#include <QApplication>
#include "ui.h"
#include "start_menu.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);
    QApplication app{argc, argv};


   ui s;


   s.show();






    return app.exec();
}
