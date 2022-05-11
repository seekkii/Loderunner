#include "mainwindow.h"

#include <QApplication>
#include "ui.h"
#include "start_menu.h"


#include "custom_widget.h"
int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);
    QApplication app{argc, argv};



    start_menu new_game;
    new_game.show();






    return app.exec();
}
