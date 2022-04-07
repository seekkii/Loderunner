#ifndef CHARACTER_H
#define CHARACTER_H

#include <QPixmap>
#include <QLabel>
class Character
{
public:
    Character();
    QPointF get_pos() const;
    void set_pos(float x, float y);
    QPixmap getpixmap();
    QSize getSize();
    void setSize(int h, int w);

private:
    float x;
    float y;
    QPixmap char_img;
    QSize size;


};

#endif // CHARACTER_H
