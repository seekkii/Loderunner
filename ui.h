#ifndef UI_H
#define UI_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QtUiTools>
#include <QDebug>
#include <QRandomGenerator>
#include <QFile>
#include <character.h>
#include <mobs.h>

class ui:public QWidget
{
    Q_OBJECT

public:
        friend class Character;

        explicit ui(QWidget *parent = nullptr);// constructor
        void paintEvent(QPaintEvent *) override;// paintevent to draw gui

        bool falling(Character &cha);//check if an object is falling
        bool is_object(float x, float y);//check if x,y is occupied by another object from map

        void mob_action(mobs& mob);
        bool lose_case();

public slots:

       void fall(Character &cha);
       void mobfall(mobs &mob);
       void mobs_go_around(mobs &mob);

private:
       Character you;
       QVector<mobs> mob;
       map *gamemap;
       QVector<QVector<ground>> cur_map;


       QMap<int, bool> keys;


       QPointF old_pos;



protected:
     void keyPressEvent(QKeyEvent *event) override;




};




#endif
