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
#include <map.h>
#include <mobs.h>

class ui:public QWidget
{
    Q_OBJECT

public:
        friend class Character;

        explicit ui(QWidget *parent = nullptr);// constructor
        void paintEvent(QPaintEvent *) override;// paintevent to draw gui
        bool on_map(int i, int j);
        bool falling(float x, float y);
        bool is_object(float x, float y);
        QVector<QVector<QString>> print_readable_board();

        void mob_action(mobs& mob);

public slots:

       void fall(float x, float y);
       void mobs_go_around();

private:
       Character *you;
       QVector<mobs> mob;
       map *gamemap;
       QVector<QVector<ground>> cur_map;
       QTimer *timer;
       QVector<QTimer*> mob_timer;

       QMap<int, bool> keys;


       int row;
       int col;
       QPointF old_pos;



protected:
     void keyPressEvent(QKeyEvent *event) override;











};




#endif
