#include "mainwindow.h"

#include <QApplication>
#include "ui.h"
#include "start_menu.h"


#include "custom_widget.h"
int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);
    QApplication app{argc, argv};


    ui gui;
    gui.show();




    return app.exec();
}
