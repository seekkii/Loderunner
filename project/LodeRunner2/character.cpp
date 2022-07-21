#include "character.h"

animation::animation(){}

void animation::setname(QString name){
    this->name = name;
}
QString animation::getname(){
    return name;
}
void animation::set_animate(int amount)
{
    animationcount = 0;
    animate.resize(amount);
    for (int i = 0; i < animate.size();i++){
        filename = ":/animation/animated/"+name+QString::number(i)+".png";

        animate[i] = QPixmap(filename);

    }
}

void animation::set_mob_animate(int amount)
{
    animationcount = 0;
    animate.resize(amount);
    for (int i = 0; i < animate.size();i++){
        filename = ":/animation/animated/enemy"+name+QString::number(i)+".png";

        animate[i] = QPixmap(filename);

    }
}

QPixmap animation::current_frame(){
    return animate[animationcount];
}

void animation::increase_counts()
{
    animationcount++;
    if (animationcount>= animate.size())
    {
        animationcount = 0;
    }
}

Character::Character()
{

    size = QSize(20,30);
    step = 10;
    x_cor = 0; y_cor = 0;
    direction = "RIGHT";
    life = 5;


    timer = new QTimer();


    ani_right.setname("right");
    ani_right.set_animate(3);
    ani_left.setname("left");
    ani_left.set_animate(3);
    ani_down.setname("down");
    ani_down.set_animate(1);
    ani_up.setname("up");
    ani_up.set_animate(2);
}

void Character::update_life(){
    life-=1;
}
int Character::get_life(){
    return life;
}

int Character::x() const{
    return x_cor;
}

int Character::y() const{
    return y_cor;
}


void Character::set_pos(int x, int y){
    if (x>=0 && x < 900 && y>=0 && y <900){
        this->x_cor = x;
        this->y_cor = y;
    }
}


QSize Character::getSize(){
    return size;
}

void Character::setSize(int h, int w){
    size.setHeight(h);
    size.setWidth(w);
}

int Character::get_walkstepdis(){
    return step;
}

int Character::row(){
    {
        return round(x_cor/30);
    }
}

int Character::col(){
    return trunc(y_cor/30);
}

QTimer* Character::get_timer(){
    return timer;
}



bool Character::on_map(){
    return (row()>0 && col()>0&&row()<1000/size.width() && col()<1000/size.height());

}

void Character::setdirection(QString direction){
    this->direction = direction;
}
QString Character::getdirection(){
    return direction;
}

QPixmap Character::char_frame(){
    if (ani_right.getname().toUpper() == direction){
            return ani_right.current_frame();
    }
    if (ani_left.getname().toUpper() == direction){
            return ani_left.current_frame();
    }else
    if (ani_up.getname().toUpper() == direction){
            return ani_up.current_frame();
    }else
    if (ani_down.getname().toUpper() == direction){
            return ani_down.current_frame();
    }else
        return QPixmap();
}

void Character::move_up(){
    set_pos(x_cor,y_cor-step);
    setdirection("UP");
    ani_up.increase_counts();
}
void Character::move_down(){
    set_pos(x_cor,y_cor+step);
    setdirection("DOWN");

}


void Character::move_right(){
    set_pos(x_cor+step,y_cor);
    setdirection("RIGHT");
    ani_right.increase_counts();
}

void Character::move_left(){
    set_pos(x_cor-step,y_cor);
    setdirection("LEFT");
    ani_left.increase_counts();
}
















