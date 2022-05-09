#ifndef MOBS_H
#define MOBS_H
#include<character.h>
#include<QRandomGenerator>

class mobs :public Character
{
    public:
    QTimer *rand_timer;
    mobs():Character()
    {
        x_cor = QRandomGenerator::global()->bounded(50,500);
        y_cor = QRandomGenerator::global()->bounded(50,500);
        QPixmap pixmap(":/images/yourchar.png");
        rand_timer = new QTimer();
    }


    QTimer* get_rand_timer();

};

#endif // MOBS_H
