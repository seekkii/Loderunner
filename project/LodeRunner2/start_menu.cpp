#include "start_menu.h"

start_menu::start_menu(QFrame *parent)
    : QFrame(parent)
{
    resize(1000,1000);
    start = new QPushButton("&start ?",this);
    start->setObjectName(QObject::tr("start"));
    connect(start, SIGNAL(clicked()), this, SLOT(start_clicked()));

    QGridLayout *layout = new QGridLayout(this);
    start->setFixedSize(100,40);


    qDebug() << start->objectName();

    layout->addWidget(start,2,2);


    setStyleSheet("border-image: url(:/images/start_background.jpg) 0 0 0 0 stretch stretch;");
    start->setStyleSheet("QPushButton#start {border-image: url()};");

}

QPushButton* start_menu::start_button()
{
    return start;
}

void start_menu::start_clicked()
{
    gui = new ui;

    gui->show();
    close();
}

