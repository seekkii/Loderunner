#ifndef MAP_H
#define MAP_H


#include <QPixmap>
#include <QLabel>
const int Height = 1000;
const int Width = 1000;



class ground
{
public:
    ground();//constructor
    ground(float x, float y);//parameter constructor

    void set_ground_pos(float x, float y);//set postion of ground
    QPointF get_ground_pos() const;//get position

    void setpixmap(QPixmap pm);//set pixmap of ground
    QPixmap getpixmap() const;//get pixmap

    void set_size(float h, float w);//set size of pixmap
    QSize get_size();//get size

    void set_type(QString type);//type of ground diffrentiate by qstring
    QString get_type();//get type

    bool isGround();//check if ground is of type ground



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
        size.setHeight(30);
        size.setWidth(30);
        type = "st";
    }
};//stair is child class of ground with different type "st"

class rope :public ground
{
    public:
    rope(float x, float y): ground(x,y)
    {
        QPixmap pixmap(":/images/string.png");
        ground_img = pixmap;
        type = "ro";
    }
};//rope is child class of ground with different type "ro"


class fake_ground :public ground
{
    public:
        fake_ground(float x, float y): ground(x,y){
            QPixmap pixmap(":/images/map.jpg");
            ground_img = pixmap;
            size.setHeight(30);
            size.setWidth(30);
            type = "fg";
        }


};//stair is child class of ground with different type "st"




class map
{
    public:
        map();
        int get_height();
        int get_width();
        QVector<QVector<ground>> get_map(int lv);
       void setup_map();

        void setup_from_readablemap(QVector<QVector<QString>> map, int lv);

    protected slots:
        void fall();
    private:

        QVector<QVector<ground>> current_map;

        QMap<int,QVector<QVector<ground>>> board;
        const int block_Height = 30;
        const int block_Width = 30;

        int current_lv;


};// map combines of grounds

#endif // MAP_H
