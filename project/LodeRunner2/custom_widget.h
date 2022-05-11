#ifndef CUSTOM_WIDGET_H
#define CUSTOM_WIDGET_H

#include <QWidget>
#include <QtUiTools>

class custom_widget:public QWidget
{
    Q_OBJECT
    public:
        custom_widget();
         void paintEvent(QPaintEvent *) override;

};



#endif // CUSTOM_WIDGET_H
