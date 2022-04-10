#include "ui.h"
#include <QKeyEvent>


ui::ui(QWidget *parent)
    : QWidget(parent)
{
    QUiLoader loader;
    QFile file(":/form.ui");
    file.open(QIODevice::ReadOnly| QIODevice::Text );
    QWidget *formWidget = loader.load(&file, this);
    file.close();

    gamemap = new map();//make new map



    mob.resize(3);
    for (int i = 0; i < mob.size(); i++)
    {
         mobs new_mob;
         mob[i] = new_mob;

    }// generate new vector of mobs


    you.set_pos(100,100); //set initial pos of your char

    gamemap->setup_map();
    cur_map = gamemap->get_map(1);//setup map lv 1


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(formWidget);





    setLayout(layout);

    connect(you.get_timer(),  &QTimer::timeout, this, [this]{ fall(you); });
    if (falling(you)){
            you.get_timer()->start(100);
    }//connect your char timer to fall() slot for fall animation

    for (int i = 0 ; i < mob.size(); i++){
        if (!mob[i].on_map())
        {
            mob[i].set_pos(100,100);
            qDebug()<< mob[i].x() << mob[i].y();
        }
        connect(mob[i].get_rand_timer(),  &QTimer::timeout, this, [i,this]{ mobs_go_around(mob[i]); });
        connect(mob[i].get_timer(),  &QTimer::timeout, this, [i,this]{ mobfall(mob[i]); });

        if (falling(mob[i])){
                mob[i].get_timer()->start(100);
        }
        mob[i].get_rand_timer()->start(200);
    }//connect mobs timer to fall() slot for fall animation




    update();

}



void ui::paintEvent(QPaintEvent *)
{
 QPainter painter(this);
 if (lose_case())
 {
 }


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

         }
         else
             painter.drawPixmap(r,cur_map[i][j].getpixmap());
     }//print map

 you.setSize(30,20);//set your character's size
 QSize char_size = you.getSize();//get your character's size
 float x = you.x();//get your character's x cordinate
 float y = you.y();//get your character's y cordinate
 auto r = QRect{QPoint(x,y), char_size};//rectangle that has center of your char to print pixmap from
 QPixmap you_img = you.getpixmap();//get pixmap of your char
 painter.setPen(Qt::blue);
 painter.setBrush(Qt::blue);
 painter.drawRect(r);

 //print mobs
 for (int i = 0; i < mob.size();i++)
 {
     painter.setPen(Qt::red);
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

    int i = round(cha.x()/gamemap->get_width());
    int j = trunc(cha.y()/gamemap->get_height());


    if (!cha.on_map())
    {
        return true;
    }
    if(!cur_map[i][j+1].isGround()){
            return true;
    }
    else{

            return false;
        }
}//if cha is not on map, falling is definitely true. Check if [i][i+1] is ground, return true if so and false otherwise



void ui::keyPressEvent(QKeyEvent *event)
{
    int dis = you.get_walkstepdis();
    float x = you.x();
    float y = you.y();

if(!falling(you))
    {
        if(event->key() == Qt::Key_Up)
        {
            if(!is_object(x,y-dis))
            you.set_pos(x,y-dis);

        }

        if(event->key() == Qt::Key_Down)
        {
          if(!is_object(x,y+dis))
             you.set_pos(x,y+dis);

        }

        if(event->key() == Qt::Key_Right)
        {
            if(!is_object(x+dis,y))
                you.set_pos(x+dis,y);
        }


        if(event->key() == Qt::Key_Left)
        {
            if(!is_object(x-dis,y))

                you.set_pos(x-dis,y);

        }
        update();
    }

}//override keyevent to change your character cordinates on a specific button

bool ui::is_object(float x, float y)
{

    int i = round(x/gamemap->get_width());
    int j = round(y/gamemap->get_height());

        if(cur_map[i][j].get_type() == "br"){
            return true;
        }
        else{
            return false;
        }

}//check if position i,j is of type br(brick), return true if it is and false in other cases("ro"(rope),"st"(stair))

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
         if(!is_object(x,y+dis))
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



    update();

}//mob_action() randomly chooses a number between 0 and 4,on each number choosen ,mobs will perform a different action according to how their's cordinates are changed

void ui::mobs_go_around(mobs &mob)
{
    mob_action(mob);
    update();
}//slot that basically perform mob_action() for corresponding mob


bool ui::lose_case()
{
    qDebug()<<you.row()<< you.col();
        if (you.row()==3 && you.col()==4)
        {
            return true;
        }
        else return false;
}//case of losing









