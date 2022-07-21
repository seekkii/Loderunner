#include "map.h"
#include <QTimer>
ground::ground()
{}
ground::ground(float x, float y)
{
    QPixmap pixmap(":/images/map.jpg");
    respawn = new QTimer();
    ground_img = pixmap;
    type = "br";
    digged = false;

    QSize size(30,30);
    this->size = size;
    this->x = x;
    this->y = y;
}

bool ground::isground(){
    return (type == "br"||type =="st");
}

bool ground::isnotground(){
    return (type == ""||type =="bn"||type=="fg"||type=="ro");
}
QTimer* ground::get_respawntimer(){
    return respawn;
}
QPointF ground::get_ground_pos() const{
    QPointF pos(x,y);
    return pos;
}

void ground::set_ground_pos(float x, float y){
    this->x = x;
    this->y = y;
}

QPixmap ground::getpixmap() const{
    return ground_img;
}

void ground::setpixmap(QPixmap pm){
    ground_img = pm;
}

void ground::set_size(float h, float w){
    QSize size(h,w);
    this->size = size;
}

QSize ground::get_size(){
    return size;
}

void ground::set_type(QString type){
   this->type = type;
}

QString ground::get_type(){
   return type;
}

bool ground::is_digged(){
    return digged;
}

void ground::set_digged(bool digged){
    this->digged = digged;
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
    current_map = board[lv];
   return current_map;

}


int map::get_width()
{
    return block_Width;
}// return the corresponding ratio between position on board and on screen of the width

int map::get_height()
{
    return block_Width;
}// return the corresponding ratio between position on board and on screen of the height

QVector<QVector<int>> map::getuppath(){
     return upgrid;
}
QVector<QVector<int>> map::getdownpath(){
     return downgrid;
}




void map::setup_map()
{
    // br = brick, st = stair, bn = bonus(gold coin), ro = rope, fg = fake ground
     QVector<QVector<QString>> map_1
     {
         {"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},
         {"  ","ro","  ","  ","ro","ro","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},
         {"br","  ","br","br","  ","  ","st","  ","  ","  ","  ","st","  ","  ","br","  ","  ","  ","  ","  ","  ","  ","  ","br"},
         {"br","  ","br","  ","  ","  ","st","  ","  ","  ","  ","st","  ","  ","br","  ","  ","  ","  ","  ","  ","  ","  ","br"},
         {"br","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","st","  ","  ","br","  ","  ","  ","  ","  ","  ","  ","  ","br"},
         {"br","br","br","br","br","br","st","br","br","br","br","st","ro","ro","ro","ro","ro","ro","st","  ","  ","  ","  ","br"},
         {"br","  ","  ","  ","  ","br","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","br"},
         {"br","  ","  ","  ","  ","br","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","fg"},
         {"  ","  ","  ","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","st","br","br","br","br","br"},
         {"br","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","br"},
         {"br","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","st","ro","ro","ro","ro","ro","ro","st","  ","  ","  ","  ","br"},
         {"br","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","br"},
         {"br","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","br","br","br","st","fg","st","br","  ","br"},
         {"br","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","st","mo","  ","  ","  ","  ","  ","  ","fg","st","  ","  ","br"},
         {"br","br","br","br","fg","br","br","br","st","br","br","br","br","br","br","br","  ","  ","  ","fg","st","  ","  ","br"},
         {"br","  ","  ","  ","fg","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","fg","fg","  ","  ","br"},
         {"br","  ","  ","  ","fg","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","  ","  ","  ","br","fg","fg","  ","  ","br"},
         {"br","  ","  ","  ","fg","  ","  ","  ","st","  ","  ","  ","  ","  ","br","st","br","br","br","br","br","br","  ","br"},
         {"br","  ","  ","  ","br","  ","bn","bn","st","bn","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","  ","fg"},
         {"br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br"},
    };



    QVector<QVector<QString>> map_2{
{"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},
{"  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","  "},
{"br","st","  ","  ","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","br","  ","  ","  ","  ","  ","  ","  ","  ","br"},
{"br","st","  ","  ","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","br","  ","  ","  ","  ","  ","  ","  ","  ","br"},
{"br","st","  ","  ","  ","  ","  ","  ","  ","  ","  ","st","  ","  ","br","  ","  ","  ","  ","  ","  ","  ","  ","br"},
{"br","br","br","br","br","br","br","br","br","br","br","st","ro","ro","ro","ro","ro","ro","st","  ","  ","  ","  ","br"},
{"br","  ","  ","  ","  ","br","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","br"},
{"br","  ","  ","  ","  ","br","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","fg"},
{"  ","  ","  ","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","st","br","br","br","br","br"},
{"br","  ","  ","  ","  ","  ","  ","bn","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","br"},
{"br","  ","  ","  ","  ","  ","  ","bn","  ","  ","  ","st","ro","ro","ro","ro","ro","ro","st","  ","  ","  ","  ","br"},
{"br","  ","  ","  ","  ","  ","  ","bn","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","br"},
{"br","  ","  ","  ","  ","  ","  ","bn","  ","  ","  ","st","  ","  ","  ","br","br","br","st","fg","st","br","  ","br"},
{"br","bn","bn","bn","bn","bn","bn","bn","  ","  ","  ","st","mo","  ","  ","  ","  ","  ","  ","fg","st","  ","  ","br"},
{"br","br","br","br","fg","br","br","br","st","br","br","br","br","br","br","br","  ","  ","  ","fg","st","  ","  ","br"},
{"br","  ","  ","  ","fg","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","  ","  ","  ","  ","fg","fg","  ","  ","br"},
{"br","  ","  ","  ","fg","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","  ","  ","  ","br","fg","fg","  ","  ","br"},
{"br","  ","  ","  ","fg","  ","  ","  ","st","  ","  ","  ","  ","  ","br","st","br","br","br","br","br","br","  ","br"},
{"br","  ","  ","  ","br","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","st","  ","  ","  ","  ","  ","  ","  ","fg"},
{"br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br","br"},
     };

      setup_from_readablemap(map_1,1);
      setup_from_readablemap(map_2,2);

}

QVector<QVector<int>> map::griddownpath(){
    QVector<QVector<int>> grid;
   grid = griduppath();

   for (int i = 0 ; i <grid.size() ;i++)
       for (int j = 0 ; j <grid[grid.size()-1].size()-1; j++)
       {
             if(grid[i][j] == 1 && current_map[j+1][i].get_type()!="br" && current_map[j+1][i+1].get_type()=="")

               for (int down = i; down<grid.size();down++){
                  if (current_map[j+1][down].get_type()=="br"){
                      break;
                  }
                  else{
                      grid[down][j+1] = 1;
                  }
              }
       }

   for (int i = 0 ; i <grid.size() ;i++)
       for (int j = 1 ; j <grid[grid.size()-1].size()-1; j++)
       {
             if(grid[i][j] == 1 && current_map[j-1][i].get_type()!="br" && current_map[j-1][i+1].get_type()=="")

               for (int down = i; down<grid.size();down++){
                  if (current_map[j-1][down].get_type()=="br"){
                      break;
                  }
                  else{
                      grid[down][j-1] = 1;
                  }
              }
       }





    return grid;
}

QVector<QVector<int>> map::griduppath(){
    QVector<QVector<int>> grid;
    grid.resize(current_map[current_map.size()-1].size(),QVector<int>(current_map.size()));
        for (int i = 0 ; i < current_map.size();i++)
            for (int j = 0 ; j <current_map[current_map.size()-1].size()-1; j++)
        {
            if ((current_map[i][j].get_type()==""&& current_map[i][j+1].isground()) ||
                 current_map[i][j].get_type()=="st" || current_map[i][j].get_type() == "ro"
              || current_map[i][j].get_type() == "bn" || current_map[i][j].get_type() == "fg"  ){
                grid[j][i] = 1;
            }
            else grid[j][i] = 0;

        }
    return grid;
}



void map::setup_from_readablemap(QVector<QVector<QString>> map, int lv)
{
    current_map.clear();
    current_map.resize(map[map.size()-1].size(), QVector<ground>(map.size()+1));
    for (int i = 0; i < map[map.size()-1].size(); i ++){
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

            if (map[j][i] == "fg"){
                  fake_ground fake(block_Width*i,block_Height*j);
                  QPixmap pixmap(":/images/map.jpg");
                  fake.setpixmap(pixmap);
                  current_map[i][j] = fake;
            }

            if (map[j][i] == "bn"){
                  bonus coin(block_Width*i,block_Height*j);
                  QPixmap pixmap(":/images/coins.png");
                  coin.setpixmap(pixmap);
                  current_map[i][j] = coin;
            }
            if (map[j][i] == "  "){

                current_map[i][j].set_digged(false);

            }


         }
     }
     board[lv] = current_map;
}














