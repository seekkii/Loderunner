#ifndef MAP_H
#define MAP_H


#include <QPixmap>
#include <QLabel>
#include <character.h>
const int Height = 1000;
const int Width = 1000;



class ground
{
public:
    ground();
    ground(float x, float y);

    void set_ground_pos(float x, float y);
    QPointF get_ground_pos() const;

    void setpixmap(QPixmap pm);
    QPixmap getpixmap() const;

    void set_size(float h, float w);
    QSize get_size();

    void set_type(QString type);
    QString get_type();

    bool isGround();
    bool isStair();


protected:
    float x;
    float y;
    QString type;
    QPixmap ground_img;
    QSize size;
};//ground

class stair :public ground
{
    public:
    stair(float x, float y): ground(x,y)
    {
        QPixmap pixmap(":/images/stairkek.png");
        ground_img = pixmap;
        size.setHeight(40);
        size.setWidth(40);
        type = "st";
    }
};

class rope :public ground
{
    public:
    rope(float x, float y): ground(x,y)
    {
        QPixmap pixmap(":/images/string.png");
        ground_img = pixmap;
        size.setHeight(40);
        size.setWidth(40);
        type = "ro";
    }
};




class map
{
    public:
        map();
        int get_row();
        int get_col();
        QVector<QVector<ground>> get_map(int lv);
       void setup_map();

        void setup_from_readablemap(QVector<QVector<QString>> map, int lv);
        QSize get_block_size();
        bool falling();
    protected slots:
        void fall();
    private:
        Character you;
        QMap<int,QVector<QVector<ground>>> board;
        const int block_Height = 40;
        const int block_Width = 40;
        QVector<QVector<ground>> current_map;
        int current_lv;


};

#endif // MAP_H
