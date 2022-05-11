#include "ui.h"
#include <QKeyEvent>

ui::ui(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("gui");
    setMinimumSize(1000,1000);
    setFocusPolicy(Qt::WheelFocus);


    setup_losing_menu();
    setup_wining_menu();
    key_menu = new key_widget(this);
    key_menu->setWindowFlags(Qt::FramelessWindowHint);
    key_menu->hide();

    current_lv = 1;

    setup_game();

}
void ui::setup_initial_pos()
{
   if (current_lv == 1){
       you.set_pos(100,100);
   }
   if (current_lv == 2){
       you.set_pos(400,470);
   }


}
void ui::setup_losing_menu()
{
    lose_menu = new QWidget();
    QPushButton *retry = new QPushButton("&retry ?",lose_menu);
    connect(retry, SIGNAL(clicked()), this, SLOT(reset()));
    QGridLayout *layout = new QGridLayout(lose_menu);
    retry->setFixedSize(100,40);
    layout->addWidget(retry,1,2);
}

void ui::setup_wining_menu()
{
    win_menu = new QWidget();
    QPushButton *next_lv = new QPushButton("&next level ?",win_menu);
    connect(next_lv, SIGNAL(clicked()), this, SLOT(next_lv()));
    QGridLayout *layout = new QGridLayout(win_menu);
    next_lv->setFixedSize(100,40);
    layout->addWidget(next_lv,1,2);

}

void ui::respawn(int i ,int j){
    cur_map[i][j].set_type("br");
    update();
}
void ui::setup_game()
{
    gamemap = new map();//make new map
    gamemap->setup_map();
    cur_map = gamemap->get_map(current_lv);//setup map lv 1





    mob.resize(3);
    for (int i = 0; i < mob.size(); i++)
    {
         mobs new_mob;
         mob[i] = new_mob;

    }// generate new vector of mobs
    setup_initial_pos();


    connect(you.get_timer(),  &QTimer::timeout, this, [this]{ fall(you); });
    if (falling(you)){
            you.get_timer()->start(100);
    }//connect your char timer to fall() slot for fall animation

    for (int i = 0 ; i < mob.size(); i++){
        if (!mob[i].on_map())
        {
            mob[i].set_pos(100,100);
        }
        connect(mob[i].get_rand_timer(),  &QTimer::timeout, this, [i,this]{ mobs_go_around(mob[i]); });
        connect(mob[i].get_timer(),  &QTimer::timeout, this, [i,this]{ mobfall(mob[i]); });

        if (falling(mob[i])){
                mob[i].get_timer()->start(100);
        }
        mob[i].get_rand_timer()->start(200);
    }//connect mobs timer to fall() slot for fall animation



}

void ui::start_mobtimer()
{
    for (int i = 0 ; i < mob.size(); i++){
        if (!mob[i].on_map())
        {
            mob[i].set_pos(100,100);
        }
        if (falling(mob[i])){
                mob[i].get_timer()->start(100);
        }
        mob[i].get_rand_timer()->start(200);
    }
}

void ui::stop_mobtimer()
{
    for (int i = 0 ; i < mob.size(); i++){
        mob[i].get_timer()->stop();
        mob[i].get_rand_timer()->stop();
    }
}



void ui::print_map(QPainter &painter)
{
    for (int i =0; i < gamemap->get_map(1).size() ;i++)
        for (int j =0; j < gamemap->get_map(1).size();j++)
        {
            float w = i*cur_map[i][j].get_size().width();
            float h = j*cur_map[i][j].get_size().height();
            QSize size_block = cur_map[i][j].get_size();
            auto r = QRect{QPoint(w,h),size_block};

            if (cur_map[i][j].get_type() == "ro"){
                QPen pen(Qt::white, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
                painter.setPen(pen);
                painter.setBrush(Qt::white);
                int width = gamemap->get_width();
                painter.drawLine(w+width,h-width/2,w,h-width/2);

            }else{
                if (cur_map[i][j].get_type() == "fg"){
                    int x = round((you.x())/gamemap->get_width());
                    int y = trunc(you.y()/gamemap->get_height());

                    if ((x==i && y==j-1)||(x==i && y==j)){
                        QPixmap pixmap(":/images/fake_ground.png");
                        cur_map[i][j].setpixmap(pixmap);
                    }

                    painter.drawPixmap(r,cur_map[i][j].getpixmap());
                }else{
                    if (cur_map[i][j].get_type() != "")
                        painter.drawPixmap(r,cur_map[i][j].getpixmap());
                }
            }

        }//print map



}

void ui::paintEvent(QPaintEvent *)
{
 QPainter painter(this);
 auto back = QRect{QPoint(0,0), QSize(1000,1000)};//rectangle that has center of your char to print pixmap from
 QPixmap m = QPixmap(":/images/background.jpg");
 painter.drawPixmap(back,m);

 print_map(painter);


 QSize char_size = you.getSize();//get your character's size
 float x = you.x();//get your character's x cordinate
 float y = you.y();//get your character's y cordinate
 auto r = QRect{QPoint(x,y), char_size};//rectangle that has center of your char to print pixmap from
 QPixmap you_img = you.getpixmap();//get pixmap of your char
 painter.setPen(Qt::blue);
 painter.setBrush(Qt::blue);
 painter.drawRect(r);

 //print mobs
 for (int i = 0; i < mob.size();i++){
     painter.setPen(Qt::red);
      painter.setBrush(Qt::red);
     auto r_mob = QRect{QPoint(mob[i].x(),mob[i].y()), char_size};
     painter.drawEllipse(r_mob);
 }


 if (falling(you)){
     you.get_timer()->start(100);
 }
 else
     you.get_timer()->stop(); //if your char falling check is true start timer to call fall slot

 for (int i = 0; i < mob.size(); i++)
 if (falling(mob[i]))
 {
     mob[i].get_timer()->start(100);

 } else mob[i].get_timer()->stop();//if mob falling check is true start timer to call fall slot










}


void ui::fall(Character &cha)
{
    float x = cha.x();
    float y = cha.y();
    const int fall_per_milisec = 50;
    int j = trunc(y /gamemap->get_height());
    if (y+fall_per_milisec < gamemap->get_height()*(j+1) )
        {
            cha.set_pos(x,y+fall_per_milisec);
        }
    else{

        cha.set_pos(x,gamemap->get_height()*(j+1));
    }
    update();
}// reduce cha 's y cordinate by fall_per_milisec


void ui::mobfall(mobs &mob)
{
    float x = mob.x();
    float y = mob.y();
    const int fall_per_milisec = 50;
    int j = trunc(y /gamemap->get_height());
    if (y+fall_per_milisec < gamemap->get_height()*(j+1) )
        {
            mob.set_pos(x,y+fall_per_milisec);
        }
    else{

        mob.set_pos(x,gamemap->get_height()*(j+1));
    }
    update();
}// reduce mob's y cordinate by fall_per_milisec


bool ui::falling(Character &cha)
{

    int i = round((cha.x())/gamemap->get_width());
    int j = trunc(cha.y()/gamemap->get_height());


    if (!cha.on_map())
    {
        return true;
    }
    if(cur_map[i][j+1].get_type()=="" ||cur_map[i][j+1].get_type()=="fg"){
            return true;
    }
    else{

            return false;
        }
}//if cha is not on map, falling is definitely true. Check if [i][i+1] is ground, return true if so and false otherwise

void ui::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    if (pos.x()>key_menu->rect().x() && pos.y()>key_menu->rect().y()){
        key_menu->hide();
        start_mobtimer();
    }
}

void ui::keyPressEvent(QKeyEvent *event)
{
    int dis = you.get_walkstepdis();
    float x = you.x();
    float y = you.y();
    QMap<QString,Qt::Key> key_map = key_menu->get_key_map();
if(!falling(you))
    {

        if(event->key() == key_map["UP"]){
            if(!is_object(x,y-dis))
            you.set_pos(x,y-dis);
            you.setdirection("UP");
        }
        if(event->key() == key_map["DOWN"]){
          if(!floor_check(x,y+dis))
             you.set_pos(x,y+dis);
           you.setdirection("DOWN");
        }
        if(event->key() == key_map["RIGHT"]){
            if(!is_object(x+dis,y))
                you.set_pos(x+dis,y);
             you.setdirection("RIGHT");
        }
        if(event->key() == key_map["LEFT"]){
            if(!is_object(x-dis,y))
                you.set_pos(x-dis,y);
             you.setdirection("LEFT");
        }
        if(event->key() == key_map["DIG"]){
            qDebug()<<you.row() << you.col() << you.getdirection() <<you.x()<<you.y()<< cur_map[you.row()-1][you.col()+1].get_type()<<cur_map.size();
            if (you.getdirection() == "LEFT"&& (!is_object(x-dis,y))){
                int i = you.row()-1;
                int j = you.col()+1;
                if (cur_map[you.row()-1][you.col()+1].get_type() == "br"){
                    cur_map[you.row()-1][you.col()+1].set_type("");
                     connect(cur_map[i][j].get_respawntimer(),  &QTimer::timeout, this, [i,j,this]{ respawn(i,j); });
                    cur_map[you.row()-1][you.col()+1].get_respawntimer()->start(2000);
                }
            }
            if (you.getdirection() == "RIGHT"&&(!is_object(x+dis,y))){
                int i = you.row()+1;
                int j = you.col()+1;
                if (cur_map[you.row()+1][you.col()+1].get_type() == "br"){
                    cur_map[you.row()+1][you.col()+1].set_type("");
                     connect(cur_map[i][j].get_respawntimer(),  &QTimer::timeout, this, [i,j,this]{ respawn(i,j); });
                    cur_map[you.row()+1][you.col()+1].get_respawntimer()->start(2000);
                }
            }
        }
        update();
    }

    if (win()){
      show_win_menu();
    }
    if (lose()){
       show_losing_menu();
    }

    if(event->key() == Qt::Key_Shift&& !key_menu->isVisible()){
        key_menu->move(rect().center().x()/2, rect().center().y()/4);
        key_menu->show();
        stop_mobtimer();
    }



}//override keyevent to change your character cordinates on a specific button

bool ui::is_object(float x, float y)
{

    int i = round((x)/gamemap->get_width());
    int j = round(y/gamemap->get_height());

        if(cur_map[i][j].get_type() == "br"){
            return true;
        }
        else{
            return false;
        }

}//check if position i,j is of type br(brick), return true if it is and false in other cases("ro"(rope),"st"(stair))

bool ui::floor_check(float x, float y)
{
    int i = round((x)/gamemap->get_width());
    int j = ceil(y/gamemap->get_height());
    if(cur_map[i][j].get_type() == "br"){
        return true;
    }
    else{
        return false;
    }

}

void ui::mob_action(mobs &mob)
{

    float x = mob.x();
    float y = mob.y();
    int dis = mob.get_walkstepdis();

    int selection = QRandomGenerator::global()->bounded(0,4);
if(!falling(mob))
{

    if(selection == 0)
    {
        if(!is_object(x,y-dis))
        mob.set_pos(x,y-dis);

    }

    if(selection == 1)
    {
         if(!floor_check(x,y+dis))
         mob.set_pos(x,y+dis);

    }

    if(selection == 2)
    {
         if(!is_object(x+dis,y))
            mob.set_pos(x+dis,y);
    }


    if(selection == 3)
    {
         if(!is_object(x-dis,y))
            mob.set_pos(x-dis,y);

    }

}
    if (lose()){
       show_losing_menu();
    }
    else{
        update();
    }

}//mob_action() randomly chooses a number between 0 and 4,on each number choosen ,mobs will perform a different action according to how their's cordinates are changed

void ui::mobs_go_around(mobs &mob)
{
    mob_action(mob);
    update();
}//slot that basically perform mob_action() for corresponding mob


bool ui::lose()
{
    bool lose_case = false;
    for (int i = 0; i < mob.size();i++)
    {
        if (abs(you.row()-mob[i].row()) < 2 && abs(you.col()-mob[i].col()) < 1 )
        {
            lose_case = true;
            break;
        }
    }

    return lose_case;
}//case of losing


void ui::show_losing_menu()
{
    for (int i = 0 ; i < mob.size(); i++){
       mob[i].get_timer()->stop();
       mob[i].get_rand_timer()->stop();
    }

    lose_menu->resize(300,300);
    lose_menu->setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    lose_menu->show();
}

bool ui::win()
{
    if (you.row()>22||you.col()>22)
        return true;
    else
        return false;
}//case of losing


void ui::show_win_menu()
{
    for (int i = 0 ; i < mob.size(); i++){
       mob[i].get_timer()->stop();
       mob[i].get_rand_timer()->stop();
    }

    win_menu->resize(300,300);
    win_menu->setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    win_menu->show();
}




void ui::reset()
{
    you.set_pos(100,100);
    for (int i = 0 ; i < mob.size(); i++){
       mob[i].get_rand_timer()->start(200);
    }
    cur_map = gamemap->get_map(current_lv);
    setup_initial_pos();
    update();
    lose_menu->close();
}

void ui::next_lv()
{
    current_lv++;
    cur_map = gamemap->get_map(current_lv);
    start_mobtimer();
    setup_initial_pos();
    update();
    win_menu->close();
}










