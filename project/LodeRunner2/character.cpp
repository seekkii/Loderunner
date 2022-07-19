#include "character.h"

animation::animation(){}

void animation::setname(QString name){
    this->name = name;
}
QString animation::getname(){
    return name;
}
void animation::set_animate()
{
    animationcount = 0;
    animate.resize(3);
    for (int i = 0; i < animate.size();i++){
        filename = "C:/Users/Umi/Pictures/Screenshots/"+name+QString::number(i)+".png";
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
    set_type("ch");

    timer = new QTimer();
    inactive_timer = new QTimer();
    inactive_timer->setSingleShot(true);

    ani_right.setname("right");
    ani_right.set_animate();
    ani_left.setname("left");
    ani_left.set_animate();
    ani_down.setname("down");
    ani_down.set_animate();
    ani_up.setname("up");
    ani_up.set_animate();
}

void Character::update_life(){
    life--;
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

QTimer* Character::get_inactivetimer(){
    return inactive_timer;
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

}
















