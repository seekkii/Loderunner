#ifndef MAP_H
#define MAP_H


#include <QPixmap>
#include <QLabel>
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
    bool isGround();


protected:
    float x;
    float y;
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

    }
};


class map
{
    public:
        map();
        int ratio_between_height();
        int ratio_between_width();
        QVector<QVector<ground>> get_map(int lv);
        void setup_map();
        void setup_brick(int i, int j);//setup a brick at pos i,j
        void setup_coin();
        void setup_stair(int i, int j);
        void setup_string();
        QSize get_block_size();

    private:
        QMap<int,QVector<QVector<ground>>> board;
        const int block_Height = 40;
        const int block_Width = 40;
        QVector<QVector<ground>> current_map;
        int current_lv;


};

#endif // MAP_H
