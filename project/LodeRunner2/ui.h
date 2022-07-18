#ifndef UI_H
#define UI_H

#include <QMainWindow>


#include <QDebug>
#include <QRandomGenerator>
#include <QFile>
#include <character.h>
#include <mobs.h>
#include <key_widget.h>

class ui:public QWidget
{
    Q_OBJECT

public:
        explicit ui(QWidget *parent = nullptr);// constructor
        void paintEvent(QPaintEvent *) override;// paintevent to draw gui
        void setup_game();

        bool is_object(int x, int y);//check if x,y is occupied by another object from map
        bool floor_check(float x, float y);
        bool is_bonus(float x, float y);
        bool is_mob(float x, float y);
        bool falling(Character &cha);
        void mob_action(mobs& mob);// algorithm for mob to move
        bool mob_closeto_others(mobs&mob);

        void recalculate_path(mobs& mob);// calculate path from mob to character
        void recalculate();// calculate path for all mobs

        void print_map(QPainter &painter);// print out the map

        bool lose();
        void show_losing_menu();
        void setup_losing_menu();

        bool win();
        void setup_wining_menu();
        void show_win_menu();


        void start_mobtimer();// start all mobs' timers
        void stop_mobtimer();// stop all mob's timer
        void setup_initial_pos();// setup initial position of charactaer

        void setup_score();//set up score
        void update_score();// update scor

        bool on_map(Character &cha);
        void show_menu();

public slots:

       void fall(Character &cha);// fall slot that reduces y cordinate of a character per mili sec
       void mobfall(mobs &mob);// fall slot that reduces y cordinate of a mob per mili sec
       void mobs_go_around(mobs &mob);// slot that excute the algorithm that controls mobs

       void reset();//reset
       void next_lv();// go to next level
       void inactive(mobs &mob); // make mob inactive
       void respawn(int i , int j);// respawn mob
private:

       Character you; // your character
       QVector<mobs> mob; // enemies

       map *gamemap;//gamemap
       QVector<QVector<ground>> cur_map;//current map

       long int score;// score


       QVector<QVector<int>> uppath;// graph that is used to search paths for mob from down to up
       QVector<QVector<int>> downpath;// graph that is used to search paths for mob from up to down

       //widget
       QWidget *lose_menu;//lose menu
       QWidget *win_menu;//win menu
       key_widget *key_menu;// changing key
       QLabel * score_label;// score label

protected:
     void keyPressEvent(QKeyEvent *event) override;
     void mousePressEvent(QMouseEvent *event) override;

};










#endif
