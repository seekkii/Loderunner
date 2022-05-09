#include "character.h"

Character::Character()
{

    char_img = QPixmap(":/images/yourchar.png");
    size = QSize(20,30);
    step = 20;
    x_cor = 0;
    y_cor = 0;
    timer = new QTimer();
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
    return round(x_cor/size.width());
}

int Character::col()
{
    return round(y_cor/size.height());
}

QTimer* Character::get_timer()
{
    return timer;
}

bool Character::on_map()
{
    if (row()<0 || col()<0||row()>50 || col()>50)
    {
        return false;
    }
    else
    {
        return true;
    }
}













