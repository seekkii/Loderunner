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
#include <map.h>

class ui:public QWidget
{
    Q_OBJECT

public:
        friend class Character;

        explicit ui(QWidget *parent = nullptr);// constructor
        void paintEvent(QPaintEvent *) override;// paintevent to draw gui
        bool falling();

public slots:

       void fall();

private:
       Character *you;
       map *gamemap;
       QVector<QVector<ground>> cur_map;
       QTimer *timer;


       int row;
       int col;

       bool i_m_falling;


protected:
     void keyPressEvent(QKeyEvent *event) override;
     void keyReleaseEvent(QKeyEvent*event) override;










};




#endif
