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





class mobs :public Character
{
    public:

    mobs();
    void set_holding(bool hold);
    bool holding();


    QTimer* get_inactivetimer();
    QTimer* get_rand_timer();


    QTimer *rand_timer;
    QTimer* inactive_timer;
    bool hold;
    QQueue<QPair<int, int>> mobpath;

};


struct cell {
    // row and column index of parent
    int parent_i, parent_j;
    // f = g + h
    double f, g, h;
};

// Struct for pair<int, pair<int, int>> type
typedef QPair<double, QPair<int, int> > pPair;

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
