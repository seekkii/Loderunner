#ifndef CHARACTER_H
#define CHARACTER_H

#include <QPixmap>
#include <QLabel>

class Character
{
public:
    Character();
    float x() const;
    float y() const;
    int get_walkstepdis();
    int row();
    int col();
    void set_pos(float x, float y);
    QPixmap getpixmap();
    QSize getSize();
    void setSize(int h, int w);

    bool is_object(float x, float y);


protected slots:


protected:
    float x_cor;
    float y_cor;


    int step;
    QPixmap char_img;
    QSize size;


};

#endif // CHARACTER_H
