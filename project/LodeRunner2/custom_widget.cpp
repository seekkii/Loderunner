#include "custom_widget.h"

custom_widget::custom_widget()
{
    setFixedSize(500,500);
    QPushButton *newbutton = new QPushButton("Start" ,this);
    newbutton->move(rect().center());
}

void custom_widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    auto back = QRect{QPoint(0,0), QSize(500,500)};//rectangle that has center of your char to print pixmap from
    QPixmap m = QPixmap(":/images/background.jpg");
    painter.drawPixmap(back,m);

}
