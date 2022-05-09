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
        void print_map(QPainter &painter);

        bool lose();
        void show_losing_menu();
        void setup_losing_menu();

        bool win();
        void setup_wining_menu();
        void show_win_menu();

        void start_mobtimer();
        void setup_initial_pos();

public slots:

       void fall(Character &cha);
       void mobfall(mobs &mob);
       void mobs_go_around(mobs &mob);
       void setup_game();
       void reset();
       void next_lv();
private:
       Character you;
       QVector<mobs> mob;

       map *gamemap;
       QVector<QVector<ground>> cur_map;

       int current_lv;

       QWidget *lose_menu;
       QWidget *win_menu;



protected:
     void keyPressEvent(QKeyEvent *event) override;

};





#endif
