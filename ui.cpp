#include "ui.h"
#include <QKeyEvent>
#include <QSignalMapper>

ui::ui(QWidget *parent)
    : QWidget(parent)
{
    QUiLoader loader;
    QFile file(":/form.ui");
    file.open(QIODevice::ReadOnly| QIODevice::Text );
    QWidget *formWidget = loader.load(&file, this);
    file.close();

    gamemap = new map();//current map


    //mobs
    mob.resize(3);

    for (int i = 0; i < mob.size(); i++)
    {
         mobs new_mob;
         mob[i] = new_mob;

    }// generate new vector of mobs

    you = new Character;
    you->set_pos(40,40);

    row = gamemap->get_row();
    col = gamemap->get_col();
    gamemap->setup_map();
    cur_map = gamemap->get_map(1);


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(formWidget);





    setLayout(layout);
    QMetaObject::connectSlotsByName(this);





    timer = new QTimer(this);
    connect(timer,  &QTimer::timeout, this, [this]{ fall(you->x(),you->y()); });
    if (falling(you->x(),you->y())){
            timer->start(100);
    }

    mob_timer.resize(mob.size());

    for (int i = 0; i < mob.size();i++)
    {
        float x_mob = mob[i].x();
        float y_mob = mob[i].y();


        mob_timer[i] = new QTimer(this);
        connect(mob_timer[i],  &QTimer::timeout, this, [this]{ mobs_go_around(); });

    }


    update();

}



void ui::paintEvent(QPaintEvent *)
{
 QPainter painter(this);



 for (int i =0; i < row ;i++)
     for (int j =0; j < col;j++)
     {
         float h = i*cur_map[i][j].get_size().width();
         float w = j*cur_map[i][j].get_size().height();
         QSize size_block = cur_map[i][j].get_size();
         auto r = QRect{QPoint(h,w),size_block};
         if (cur_map[i][j].get_type() == "ro"){
             QPen pen(Qt::white, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
             painter.setPen(pen);
             painter.setBrush(Qt::white);
             painter.drawLine(h+40,w-20,h,w-20);

         }
         else
             painter.drawPixmap(r,cur_map[i][j].getpixmap());
     }

 you->setSize(40,26);
 QSize char_size = you->getSize();
 float x = you->x();
 float y = you->y();
 auto r = QRect{QPoint(x,y), char_size};
 QPixmap you_img = you->getpixmap();
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


 if (falling(x,y))
 {
     timer->start(200);

 }
 else timer->stop();


 for (int i = 0; i < mob.size(); i++){
     float x_mob = mob[i].x();
     float y_mob = mob[i].y();

     {

         mob_timer[i]->start(200);
     }



 }





}


bool ui::on_map(int i, int j)
{
   if (i>row||j>row||i<0||j<0){
       return false;

   }
   else
       return true;
}



void ui::fall(float x, float y)
{
    const int fall_per_milisec = 50;

    int j = trunc(y * col/Height);






    if (y+fall_per_milisec < gamemap->get_block_size().height()*(j+1) )
        {
            old_pos.setX(x);
            old_pos.setY(y);
            you->set_pos(x,y+fall_per_milisec);
        }
    else{
        old_pos.setX(x);
        old_pos.setY(y);
        you->set_pos(x,gamemap->get_block_size().height()*(j+1));
    }





    update();
}

bool ui::falling(float x, float y)
{

    int i = round(x*row/Width);
    int j = trunc(y * col/Height);
    qDebug()<<j<<j;


    if(!cur_map[i][j+1].isGround()){
            return true;
    }
    else{

            return false;
        }




}//



void ui::keyPressEvent(QKeyEvent *event)
{
    int dis = you->get_walkstepdis();
    float x = you->x();
    float y = you->y();

if(!falling(x,y))
    {
       old_pos.setX(x);
       old_pos.setY(y);

        if(event->key() == Qt::Key_Up)
        {
            if(!is_object(x,y-dis))
            you->set_pos(x,y-dis);

        }

        if(event->key() == Qt::Key_Down)
        {
          if(!is_object(x,y+dis))
             you->set_pos(x,y+dis);

        }

        if(event->key() == Qt::Key_Right)
        {
            if(!is_object(x+dis,y))
                you->set_pos(x+dis,y);
        }


        if(event->key() == Qt::Key_Left)
        {
            if(!is_object(x-dis,y))

                you->set_pos(x-dis,y);

        }
        update();
    }



}

bool ui::is_object(float x, float y)
{

    int i = trunc(x*row/Width);
    int j = ceil(y*col/Height);

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
    update();

}

void ui::mobs_go_around()
{

    for (int i = 0 ; i < mob.size(); i++)
    {
        mob_action(mob[i]);
    }
    update();

}











