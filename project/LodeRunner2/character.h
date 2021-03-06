#ifndef CHARACTER_H
#define CHARACTER_H

#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include <map.h>
class animation
{
    public:
        animation();
        void setname(QString name);
        QString getname();
        void increase_counts();
        void set_animate(int amount);
        void set_mob_animate(int amount);
        QPixmap current_frame();
        QVector<QPixmap> animate;
        int animationcount;
        QString name;
        QString filename;
};


class Character
{
public:
    Character();// constructor
    Character(int x, int y);// constructor

    int x() const;// return x cordinate
    int y() const;//return y cordinate
    int row();//return corresponding row of x
    int col();//return corresponding col of y
    bool on_map();//check if character position is on map
    int get_walkstepdis();// walk distance of character

    void setdirection(QString direction);
    QString getdirection();
    void move_left();
    void move_right();
    void move_up();
    void move_down();


    void set_pos(int x, int y);//set current pos to (x,y)


    QString direction;
    QPixmap getpixmap();//get pix map of character
    QSize getSize();//get size of pixmap/your char
    void setSize(int h, int w);//set size of~
    QTimer* get_timer();//get timer of character

    QPixmap char_frame();

    int get_life();
    void update_life();


protected:
    float x_cor;
    float y_cor;
    int step;
    int life;

    animation ani_right;
    animation ani_left;
    animation ani_down;
    animation ani_up;

    QSize size;
    QTimer *timer;

};



#endif // CHARACTER_H
