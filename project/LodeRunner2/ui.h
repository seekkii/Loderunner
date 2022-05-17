#ifndef UI_H
#define UI_H

#include <QMainWindow>


#include <QDebug>
#include <QRandomGenerator>
#include <QFile>
#include <map.h>
#include <mobs.h>
#include <key_widget.h>

class ui:public QWidget
{
    Q_OBJECT

public:
        explicit ui(QWidget *parent = nullptr);// constructor
        void paintEvent(QPaintEvent *) override;// paintevent to draw gui
        void setup_game();

        bool is_object(float x, float y);//check if x,y is occupied by another object from map
        bool floor_check(float x, float y);
        bool is_bonus(float x, float y);
        bool falling(Character &cha);
        void mob_action(mobs& mob);
        void recaculate(mobs& mob);
        void print_map(QPainter &painter);

        bool lose();
        void show_losing_menu();
        void setup_losing_menu();

        bool win();
        void setup_wining_menu();
        void show_win_menu();


        void start_mobtimer();
        void stop_mobtimer();
        void setup_initial_pos();

        void setup_score();
        void update_score();

        bool on_map(Character &cha);

public slots:

       void fall(Character &cha);
       void mobfall(mobs &mob);
       void mobs_go_around(mobs &mob);

       void reset();
       void next_lv();
       void inactive(mobs &mob);
       void respawn(int i , int j);
private:

       Character you;
       QVector<mobs> mob;

       map *gamemap;
       QVector<QVector<ground>> cur_map;

       long int score;


       QVector<QVector<int>> uppath;
       QVector<QVector<int>> downpath;
       QWidget *lose_menu;
       QWidget *win_menu;
       key_widget *key_menu;
       QLabel * score_label;

protected:
     void keyPressEvent(QKeyEvent *event) override;
     void mousePressEvent(QMouseEvent *event) override;

};










#endif
