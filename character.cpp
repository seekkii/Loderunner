#include "character.h"

Character::Character()
{
    QPixmap pixmap(":/images/yourchar.png");
    char_img = pixmap;
    QSize s(50,50);
    size = s;
    step = 20;
    x_cor = 0;
    y_cor = 0;
}

float Character::x() const
{
    return x_cor;
}

float Character::y() const
{
    return y_cor;
}


void Character::set_pos(float x, float y)
{
    this->x_cor = x;
    this->y_cor = y;
}

QPixmap Character::getpixmap()
{
    return char_img;
}

QSize Character::getSize()
{
    return size;
}

void Character::setSize(int h, int w)
{
    size.setHeight(h);
    size.setWidth(w);
}

int Character::get_walkstepdis()
{
    return step;
}

int Character::row()
{
    return (x_cor/size.width());
}

int Character::col()
{
    return(y_cor/size.height());
}








