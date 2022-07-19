#ifndef MOBS_H
#define MOBS_H
#include<character.h>
#include<QRandomGenerator>
#include <QStack>
#include <QPair>
#include <QQueue>

#define ROW 23
#define COL 23
#define FLT_MAX 1e5

// A structure to hold the necessary parameters
struct cell {
    // Row and Column index of its parent
    // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    int parent_i, parent_j;
    // f = g + h
    double f, g, h;
};



class mobs :public Character
{
    public:

    mobs():Character()
    {
        QPixmap pixmap(":/images/yourchar.png");
        rand_timer = new QTimer();
        hold = false;

    }


    void set_holding(bool hold);
    bool holding();


    QTimer *rand_timer;
    QTimer* get_rand_timer();
    bool hold;
    QQueue<QPair<int, int>> mobpath;

};


class pathsearch
{
    public:
        bool isValid(int row, int col);
        void tracePath(QVector<QVector<cell>> cellDetails, QPair<int, int> dest);
        void search(QVector<QVector<int>>,QPair<int,int> src, QPair<int,int> dest);
        void aStarSearch(QVector<QVector<int>> grid, QPair<int,int> src, QPair<int,int> dest);
        void setlastnode(QPair<int,int> node){
            lastnode = node;
        };
        void setnextnext(QPair<int,int> node){
            nextnext = node;
        };
        int pathlistsize(){
            return pathlist.size();
        }
        QQueue<QPair<int,int>> pathlist;
        QQueue<QPair<int,int>> getpathlist();

        QPair<int,int> lastnode;
        QPair<int,int> nextnext;


};


#endif // MOBS_H
