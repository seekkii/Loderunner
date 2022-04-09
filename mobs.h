#ifndef MOBS_H
#define MOBS_H
#include<character.h>
#include<QRandomGenerator>

class mobs :public Character
{
    public:
    mobs():Character()
    {
        x_cor = QRandomGenerator::global()->bounded(0,1000);
        y_cor = QRandomGenerator::global()->bounded(0,1000);
        QPixmap pixmap(":/images/yourchar.png");

    }
};

#endif // MOBS_H
