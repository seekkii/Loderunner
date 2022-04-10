#ifndef CHARACTER_H
#define CHARACTER_H

#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include <map.h>

class Character
{
public:
    friend class ground;
    Character();// constructor

    float x() const;// return x cordinate
    float y() const;//return y cordinate
    int row();//return corresponding row to x
    int col();//return corresponding col to y
    bool on_map();//check if character position is on map
    int get_walkstepdis();// walk distance of character

    void set_pos(float x, float y);//set current pos to (x,y)
    QPixmap getpixmap();//get pix map of character
    QSize getSize();//get size of pixmap/your char
    void setSize(int h, int w);//set size of~
    QTimer* get_timer();//get timer of character





protected slots:



protected:
    float x_cor;
    float y_cor;


    int step;
    QPixmap char_img;
    QSize size;

    QTimer *timer;

};

#endif // CHARACTER_H
