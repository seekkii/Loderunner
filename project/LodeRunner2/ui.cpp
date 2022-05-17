#include "ui.h"
#include <QKeyEvent>



ui::ui(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("gui");
    setFixedSize(1000,700);
    setFocusPolicy(Qt::WheelFocus);

    setup_losing_menu();
    setup_wining_menu();
    key_menu = new key_widget(this);

    setup_game();
    setup_score();
}

void ui::setup_score(){
    score_label = new QLabel(QString::number(score), this);
    score_label->setStyleSheet("QLabel { background-color : red; color : blue; }");
    score_label->move(0, rect().center().y()*1.84);
    QFont f( "", 40, QFont::StyleItalic);
    score_label->setFont(f);
    QString life = " LIFE "+QString::number(you.get_life())+" ";
    QString level = " LEVEL "+QString::number(gamemap->level())+" ";
    score_label->setText("00000000"+life+level);
    score_label->show();
}

void ui::update_score(){

        QString score_str = QString::number(score);
        int size = 8-score_str.size();
        for (int first = 0 ; first<size; first++){
            score_str = "0" + score_str;
            QString life = " LIFE "+QString::number(you.get_life())+" ";
            QString level = " LEVEL "+QString::number(gamemap->level())+" ";
            score_label->setText(score_str+life+level);

         }

}
void ui::setup_initial_pos(){
    if (gamemap->level() == 1){
        you.set_pos(0,0);
        mob[0].set_pos(340,200);
          mob[1].set_pos(300,500);
            mob[2].set_pos(140,500);

    }
    if (gamemap->level() == 2){
        you.set_pos(300,300);
    }

}
void ui::setup_losing_menu(){
    lose_menu = new QWidget();
    QPushButton *retry = new QPushButton("&retry ?",lose_menu);
    connect(retry, SIGNAL(clicked()), this, SLOT(reset()));
    QGridLayout *layout = new QGridLayout(lose_menu);
    retry->setFixedSize(100,40);
    layout->addWidget(retry,1,2);
}

void ui::setup_wining_menu(){
    win_menu = new QWidget();
    QPushButton *next_lv = new QPushButton("&next level ?",win_menu);
    connect(next_lv, SIGNAL(clicked()), this, SLOT(next_lv()));
    QGridLayout *layout = new QGridLayout(win_menu);
    next_lv->setFixedSize(100,40);
    layout->addWidget(next_lv,1,2);
}

void ui::respawn(int i ,int j){
    if (cur_map[i][j].get_type()==""){
        cur_map[i][j].set_type("br");
        cur_map[i][j].set_digged(false);

    }
    update();
}


void ui::setup_game()
{
    gamemap = new map();//make new map
    gamemap->setup_map();
    cur_map = gamemap->get_map(gamemap->level());//setup map lv 1
    uppath = gamemap->griduppath();
    downpath = gamemap->griddownpath();

    //mob
    mob.resize(3);
    for (int i = 0; i < mob.size(); i++)
    {
         mobs new_mob;
         mob[i] = new_mob;
         mob[i].mobpath.resize(3);

    }// generate new vector of mobs
    setup_initial_pos();
    connect(you.get_timer(),  &QTimer::timeout, this, [this]{ fall(you); });
    for (int i = 0 ; i < mob.size(); i++){
        connect(mob[i].get_rand_timer(),  &QTimer::timeout, this, [i,this]{ mobs_go_around(mob[i]); });
        connect(mob[i].get_timer(),  &QTimer::timeout, this, [i,this]{ mobfall(mob[i]); });
        connect(mob[i].get_inactivetimer(),&QTimer::timeout, this, [i,this]{ inactive(mob[i]); }); 
        mob[i].get_rand_timer()->start(100);
    }//connect mobs timer to fall() slot for fall animation



}
void ui::inactive(mobs &mob){

    cur_map[mob.row()][mob.col()].setpixmap(QPixmap(":/images/map.jpg"));
    mob.set_pos(mob.x(),mob.y()-gamemap->get_height());

    mob.get_rand_timer()->start();
    mob.get_timer()->start();
    recaculate(mob);
    update();

}
void ui::start_mobtimer()
{
    for (int i = 0 ; i < mob.size(); i++){
        if (!mob[i].on_map())
        {
            mob[i].set_pos(100,100);
        }
        if (!floor_check(mob[i].x(),mob[i].y())){
                mob[i].get_timer()->start(100);
        }
        mob[i].get_rand_timer()->start(100);
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
    for (int i =0; i < cur_map.size() ;i++)
        for (int j =0; j < cur_map[cur_map.size()-1].size();j++)
        {
            float w = (i)*cur_map[i][j].get_size().width();
            float h = (j)*cur_map[i][j].get_size().height();
            QSize size_block = cur_map[i][j].get_size();
            auto r = QRect{QPoint(w,h),size_block};

            if (cur_map[i][j].get_type() == "ro"){
                QPen pen(Qt::white, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
                painter.setPen(pen);
                painter.setBrush(Qt::white);
                int width = gamemap->get_width();
                painter.drawLine(w+width,h,w,h);
            }else{

                if (cur_map[i][j].get_type() == "fg"){
                    int x = round((you.x())/gamemap->get_width());
                    int y = trunc(you.y()/gamemap->get_height());
                    if ((x==i && y==j-1)||(x==i && y==j)){
                        QPixmap pixmap(":/images/fake_ground.png");
                        cur_map[i][j].setpixmap(pixmap);
                    }
                    painter.drawPixmap(r,cur_map[i][j].getpixmap());
                }
                else{
                    if (cur_map[i][j].get_type() == "bn"){
                        if (you.row()==i && you.col()==j){
                             cur_map[i][j].set_type("");
                             painter.drawPixmap(r,cur_map[i][j].getpixmap());

                        }
                        else{
                             painter.drawPixmap(r,cur_map[i][j].getpixmap());
                        }
                    }
                    else
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
     auto r = QRect{QPoint(you.x(),you.y()), QSize(30,30)};//rectangle that has center of your char to print pixmap from

    painter.setPen(Qt::blue);
    painter.setBrush(Qt::blue);
    painter.drawRect(r);


    //print mobs
    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);
    for (int i = 0; i < mob.size();i++){
        auto r_mob = QRect{QPoint(mob[i].x(),mob[i].y()), QSize(30,30)};
        painter.drawEllipse(r_mob);



     }
    for (int i = 0; i < mob.size(); i++){
        if (falling(mob[i]) && !mob[i].get_inactivetimer()->isActive()){
            mob[i].get_timer()->start(100);
        }
        else {
            mob[i].get_timer()->stop();//if mob falling check is true start timer to call fall slot
        }
        if(cur_map[mob[i].row()][mob[i].col()].get_type() == "bn" && mob[i].holding() == false){
            cur_map[mob[i].row()][mob[i].col()].set_type("");
            mob[i].set_holding(true);
        }
        if (!mob[i].mobpath.isEmpty()){

            QPair<int,int> youpos(you.col(),you.row());
            if (mob[i].mobpath.back()!=youpos)
                recaculate(mob[i]);
        }
    }
     if (falling(you)){
         you.get_timer()->start(100);
     }
     else{
         you.get_timer()->stop();
     } //if your char falling check is true start timer to call fall slot






}

void ui::recaculate(mobs &mob){

    QVector<QVector<int>> grid;
    if (mob.col() > you.col()){
            grid = uppath;
    }
    else{
            grid = downpath;
    }
          QPair<int,int> src(ceil(mob.y()/30), mob.row());
          QPair<int,int> dest;
          dest = QPair<int,int> (you.col(), you.row());
          pathsearch path;
          path.search(grid,src,dest);
          mob.mobpath = path.getpathlist();


}// recalculate path from mob to your character



bool ui::falling(Character &cha)
{

    int i = cha.row();
    int j = cha.col();
    if(cur_map[i][j].get_type() == "ro"){
     return false;
    }
    if(cur_map[i][j+1].get_type()=="" ||cur_map[i][j+1].get_type()=="fg" || cur_map[i][j+1].get_type()=="bn"
           ){
            return true;
    }
    else{

            return false;
        }
}
void ui::fall(Character &cha)
{
    cha.move_down();
    if (!falling(cha))
    {
        for (int i = 0 ; i < mob.size(); i++)
           {
            recaculate(mob[i]);

        }

    }



    if (lose()){
        lose_menu->show();
    }
    update_score();

    int i = you.row();
    int j = you.col();
    if (cur_map[i][j].get_type() == "bn"){
        score+=500;
        cur_map[i][j].set_type("");
    }

    update();
}// reduce cha 's y cordinate by fall_per_milisec


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
     if(falling(you)){
         return;
     }
     if(event->key() == key_map["UP"]&&(!is_object(x,y-dis))){
               you.move_up();
     }
     if(event->key() == key_map["DOWN"]&&(!floor_check(x,y+dis))){
             you.move_down();
     }
     if(event->key() == key_map["RIGHT"]&&(!is_object(x+dis,y))){
            you.move_right();

     }
     if(event->key() == key_map["LEFT"]&&(!is_object(x-dis,y))){
           you.move_left();
     }
     if(event->key() == key_map["DIG"]){
           if ((!is_object(x+dis,y))){
                        int i = you.row()+1;
                        int j = you.col()+1;
                        if (cur_map[i][j].get_type() == "br"){
                            cur_map[i][j].set_type("");
                            cur_map[i][j].set_digged(true);
                             connect(cur_map[i][j].get_respawntimer(),  &QTimer::timeout, this, [i,j,this]{ respawn(i,j); });
                            cur_map[you.row()+1][you.col()+1].get_respawntimer()->start(5000);
                            you.setdirection(you.getdirection());

                        }
            }
      }

      int i = you.row();
      int j = you.col();
      if (cur_map[i][j].get_type() == "bn"){
          score+=500;
          cur_map[i][j].set_type("");
      }

        //everytime character position change


      update_score();
      update();


      if (lose()){
         you.update_life();
         show_losing_menu();
      }
      if (win()){
         show_win_menu();
      }


      if(event->key() == Qt::Key_Shift&& !key_menu->isVisible()){
         key_menu->move(rect().center().x()/2, rect().center().y()/4);
         key_menu->show();
         stop_mobtimer();
      }




}//override keyevent to change your character cordinates on a specific button

bool ui::on_map(Character &cha){
    return (cha.row() >= 0) && (cha.row() < cur_map.size()) && (cha.col() >= 0)
            && (cha.col() < cur_map[cur_map.size()].size());
}

bool ui::is_object(float x, float y)
{

    int i = trunc((x)/gamemap->get_width());
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
    int i,j;
        i = round((x)/gamemap->get_width());
        j = ceil(y/gamemap->get_height());


    if(cur_map[i][j].get_type() == "br"){
        return true;
    }
    else{
        return false;
    }

}

bool ui::is_bonus(float x, float y){
    int i = round((x)/gamemap->get_width());
    int j = ceil(y/gamemap->get_height());
    if(cur_map[i][j].get_type() == "bn"){
            return true;
        }
        else{
            return false;
        }
}

void ui::mobfall(mobs &mob)
{

    if (cur_map[mob.row()][mob.col()].is_digged()){
        if (mob.holding()){
            bonus coin(gamemap->get_width()*mob.row(),gamemap->get_height()*mob.col());
            QPixmap pixmap(":/images/coins.png");
            coin.setpixmap(pixmap);
            cur_map[mob.row()][mob.col()-1] = coin;
            mob.set_holding(false);
        }
        mob.get_timer()->stop();
        mob.get_rand_timer()->stop();
        mob.get_inactivetimer()->start(5000);
        cur_map[mob.row()][mob.col()].set_type("br");
         cur_map[mob.row()][mob.col()].setpixmap(QPixmap());
    }
    else{
        mob.move_down();
    }
    update();
}// reduce mob's y cordinate by fall_per_milisec

void ui::mob_action(mobs &mob)
{
    if (falling(mob) ){
        return;
    }
    if (mob.mobpath.isEmpty()){
        return;
    }
    if(mob.x()== mob.mobpath.front().second*30 && mob.y()== mob.mobpath.front().first*30){
       mob.mobpath.dequeue();
    }
    if (mob.mobpath.size() != 0){
        if(mob.x()< mob.mobpath.front().second*30){
            mob.move_right();
            return;
        }
        if(mob.x() > mob.mobpath.front().second*30){
            mob.move_left();
            return;
        }
        if(mob.y()> mob.mobpath.front().first*30){
            mob.move_up();
            return;
        }
        if(mob.y()< mob.mobpath.front().first*30){
            mob.move_down();
            return;
        }

    }


   update();


}

void ui::mobs_go_around(mobs &mob)
{
    mob_action(mob);
    update();
}//slot that performs mob_action() for corresponding mob


bool ui::lose()
{
    bool lose_case = false;
    for (int i = 0; i < mob.size();i++)
    {
        if (abs(you.row()-mob[i].row()) < 1 && abs(you.col()-mob[i].col()) < 1 )
        {
           lose_case = true;
        }
    }
    return lose_case;


}//case of losing


void ui::show_losing_menu(){
    for (int i = 0 ; i < mob.size(); i++){
       mob[i].get_timer()->stop();
       mob[i].get_rand_timer()->stop();
    }
    lose_menu->resize(300,300);
    lose_menu->setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    lose_menu->show();
}

bool ui::win(){
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
    for (int i = 0 ; i < mob.size(); i++){
       mob[i].get_rand_timer()->start(100);
    }
    setup_initial_pos();
    update();
    lose_menu->close();
    you.update_life();
}

void ui::next_lv()
{
    gamemap->set_level(gamemap->level()+1);
    cur_map = gamemap->get_map(gamemap->level());
    uppath = gamemap->griduppath();
    downpath = gamemap->griddownpath();

    start_mobtimer();
    setup_initial_pos();
    update();
    win_menu->close();
}










