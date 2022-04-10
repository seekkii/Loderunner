#include "map.h"

ground::ground()
{}

ground::ground(float x, float y)
{
    QPixmap pixmap(":/images/map.jpg");
    ground_img = pixmap;
    type = "br";

    QSize size(30,30);
    this->size = size;
    this->x = x;
    this->y = y;
}

QPointF ground::get_ground_pos() const
{
    QPointF pos(x,y);
    return pos;
}

void ground::set_ground_pos(float x, float y)
{
    this->x = x;
    this->y = y;
}

QPixmap ground::getpixmap() const
{
    return ground_img;
}

void ground::setpixmap(QPixmap pm)
{
    ground_img = pm;
}

bool ground::isGround()
{
    if (ground_img.isNull())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void ground::set_size(float h, float w)
{
    QSize size(h,w);
    this->size = size;
}

QSize ground::get_size()
{
    return size;
}

void ground::set_type(QString type)
{
   this->type = type;
}

QString ground::get_type()
{
   return type;
}



bool ground::isStair()
{
   if (type == "stair")
       return true;
   else
       return false;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
//map
map::map()
{

    current_lv = 1;
    current_map = board[current_lv];
}

QVector<QVector<ground>> map::get_map(int lv)
{
   return board[lv];
}

int map::get_width()
{
    return block_Width;
}// return the corresponding ratio between position on board and on screen of the width

int map::get_height()
{
    return block_Width;
}// return the corresponding ratio between position on board and on screen of the height



void map::setup_map()
{
     QVector<QVector<QString>> map{
{"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},
{"br","br","br","br","br","br","br","br","br","br","br","st","br","br","br","br","br","br","br","br","br","br","br","br"},
{"br","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","br","  ","  ","  ","  ","  ","  ","  ","  ","br"},
{"br","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","br","  ","  ","  ","  ","  ","  ","  ","  ","br"},
{"br","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","br","  ","  ","  ","  ","  ","  ","  ","  ","br"},
{"br","br","br","br","br","br","br","br","br","br","br","st","  ","  ","br","br","br","br","st","  ","  ","  ","  ","br"},
{"br","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","br"},
{"br","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","br"},
{"br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","st","br","br","br","br","br"},
{"br","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","br"},
{"br","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","st","ro","ro","ro","ro","ro","ro","st","  ","  ","  ","  ","br"},
{"br","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","br"},
{"br","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","br","br","br","st","st","br","br","  ","br"},
{"br","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","  ","st","st","  ","  ","br"},
{"br","br","br","br","br","br","br","br","st","br","br","br","br","br","br","br","  ","  ","  ","st","st","  ","  ","br"},
{"br","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","br","st","  ","  ","br"},
{"br","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","br","st","  ","  ","br"},
{"br","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","  ","  ","  ","br","br","st","  ","  ","br"},
{"br","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","br","st","br","br","br","br","br","br","  ","br"},
{"br","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","  ","br"},
{"br","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","  ","br"},
{"br","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","  ","br"},
{"br","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","  ","br"},
{"br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br"},
      };


    setup_from_readablemap(map,1);

}




void map::setup_from_readablemap(QVector<QVector<QString>> map, int lv)
{
    current_map.resize(Width/get_width(), QVector<ground>(Height/get_height()));

    for (int i = 0; i < map.size(); i ++){
         for (int j = 0; j < map.size(); j ++){
            if (map[j][i] == "br"){
               ground brick(block_Width*i,block_Height*j);
               current_map[i][j] = brick;
            }

            if (map[j][i] == "st"){
                  stair stai_r(block_Width*i,block_Height*j);
                  current_map[i][j] = stai_r;
            }

            if (map[j][i] == "ro"){
                  rope ro_pe(block_Width*i,block_Height*j);
                  current_map[i][j] = ro_pe;
            }
         }
     }
     board[lv] = current_map;


}














