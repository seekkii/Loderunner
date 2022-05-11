#ifndef START_MENU_H
#define START_MENU_H

#include <ui.h>

class start_menu: public QFrame
{
     Q_OBJECT
    public:
        start_menu(QFrame *parent = nullptr);// constructor
        QPushButton* start_button();


    public slots:
       void start_clicked();

    private:
        QPushButton *start;
        ui *gui;


};



#endif // START_MENU_H
