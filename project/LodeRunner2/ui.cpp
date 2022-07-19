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
    key_menu->move(rect().center().x()/2, rect().center().y()/4);

    setup_game();
    setup_score();
}//constructor

void ui::show_menu(){
   if (lose()){
      you.update_life();
      show_losing_menu();
   }
   if (win()){
       qDebug()<< score;
      for (int i = 0 ; i < 10;i++)
          {
              stair stai_r(30*8,30*i);
              cur_map[8][i] = stai_r;
          }
      update();

   }
}// showing menus

void ui::setup_score(){
    score = 0;
    score_label = new QLabel(QString::number(score), this);
    score_label->setStyleSheet("QLabel { background-color : red; color : blue; }");
    score_label->move(0, rect().center().y()*1.84);
    QFont f( "", 40, QFont::StyleItalic);
    score_label->setFont(f);
    QString life = " LIFE "+QString::number(you.get_life())+" ";
    QString level = " LEVEL "+QString::number(gamemap->level())+" ";
    score_label->setText("00000000"+life+level);
    score_label->show();
}//setup score board

void ui::update_score(){

        QString score_str = QString::number(score);
        int size = 8-score_str.size();
        for (int first = 0 ; first<size; first++){
            score_str = "0" + score_str;
            QString life = " LIFE "+QString::number(you.get_life())+" ";
            QString level = " LEVEL "+QString::number(gamemap->level())+" ";
            score_label->setText(score_str+life+level);

         }

}// update score board

void ui::setup_initial_pos(){
    //mob

    if (gamemap->level() == 1){
        you.set_pos(0,0);
        mob.resize(3);
        for (int i = 0; i < mob.size(); i++)
        {
             mobs new_mob;
             mob[i] = new_mob;
             mob[i].mobpath.resize(3);
        }// generate new vector of mobs

        mob[0].set_pos(90,450);
        mob[1].set_pos(300,450);
        mob[2].set_pos(90,450);


    }
    if (gamemap->level() == 2){
        you.set_pos(0,0);
        mob.resize(5);
        for (int i = 0; i < mob.size(); i++)
        {
             mobs new_mob;
             mob[i] = new_mob;
             mob[i].mobpath.resize(3);


        }// generate new vector of mobs

       mob[0].set_pos(90,450);
       mob[1].set_pos(150,450);
       mob[2].set_pos(90,480);
       mob[3].set_pos(60,120);
       mob[4].set_pos(150,380);

    }

    if (gamemap->level() == 3){
        mob.resize(7);
        for (int i = 0; i < mob.size(); i++)
        {
             mobs new_mob;
             mob[i] = new_mob;


        }// generate new vector of mobs
       you.set_pos(0,0);
       mob[0].set_pos(90,450);
       mob[1].set_pos(300,450);
       mob[2].set_pos(90,450);
       mob[3].set_pos(70,350);
       mob[4].set_pos(150,250);
       mob[5].set_pos(90,150);
       mob[6].set_pos(90,650);


    }

    for (int i = 0; i < mob.size(); i++)
    {
         mob[i].mobpath.resize(3);
         connect(mob[i].get_rand_timer(),  &QTimer::timeout, this, [i,this]{ mobs_go_around(mob[i]); });
         connect(mob[i].get_timer(),  &QTimer::timeout, this, [i,this]{ mobfall(mob[i]); });
         connect(mob[i].get_inactivetimer(),&QTimer::timeout, this, [i,this]{ inactive(mob[i]); });
         mob[i].get_rand_timer()->start(100);
    }// generate new vector of mobs



}// setup initial position


void ui::setup_losing_menu(){
    lose_menu = new QWidget();
    QPushButton *retry = new QPushButton("&retry ?",lose_menu);
    connect(retry, SIGNAL(clicked()), this, SLOT(reset()));
    QGridLayout *layout = new QGridLayout(lose_menu);
    retry->setFixedSize(100,40);
    layout->addWidget(retry,1,2);
}// retry menu

void ui::setup_wining_menu(){
    win_menu = new QWidget();
    QPushButton *next_lv = new QPushButton("&next level ?",win_menu);
    connect(next_lv, SIGNAL(clicked()), this, SLOT(next_lv()));
    QGridLayout *layout = new QGridLayout(win_menu);
    next_lv->setFixedSize(100,40);
    layout->addWidget(next_lv,1,2);
}// next level menu

void ui::respawn(int i ,int j){
    if (cur_map[i][j].get_type()==""){
        cur_map[i][j].set_type("br");
        cur_map[i][j].setpixmap(  QPixmap(":/images/map.jpg"));
        cur_map[i][j].set_digged(false);
    }
    update();
}// respawn block after being digged


void ui::setup_game()
{
    gamemap = new map();//make new map
    gamemap->setup_map();
    cur_map = gamemap->get_map(gamemap->level());//setup map lv 1
    uppath = gamemap->griduppath();
    downpath = gamemap->griddownpath();


    setup_initial_pos();
    connect(you.get_timer(),  &QTimer::timeout, this, [this]{ fall(you); });
    for (int i = 0 ; i < mob.size(); i++){
        connect(mob[i].get_rand_timer(),  &QTimer::timeout, this, [i,this]{ mobs_go_around(mob[i]); });
        connect(mob[i].get_timer(),  &QTimer::timeout, this, [i,this]{ mobfall(mob[i]); });
        connect(mob[i].get_inactivetimer(),&QTimer::timeout, this, [i,this]{ inactive(mob[i]); });
        mob[i].get_rand_timer()->start(100);
    }//connect mobs timer to fall() slot for fall animation



}// setup game

void ui::inactive(mobs &mob){

    mob.set_pos(mob.x(),mob.y()-gamemap->get_height());
    cur_map[mob.row()][mob.col()+1].setpixmap(QPixmap((":/images/map.jpg")));
    mob.get_rand_timer()->start();
    mob.get_timer()->start();
    recalculate_path(mob);
    update();

} // make mob inactive when falled on the digged block
void ui::start_mobtimer()
{
    for (int i = 0 ; i < mob.size(); i++){
                mob[i].get_timer()->start(100);
        mob[i].get_rand_timer()->start(100);
    }
}//start timer to run mobs_go_around slot

void ui::stop_mobtimer()
{
    for (int i = 0 ; i < mob.size(); i++){
        mob[i].get_timer()->stop();
        mob[i].get_rand_timer()->stop();
        mob[i].get_inactivetimer()->stop();
    }
}// stop mobs's timers



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
            }

            if (cur_map[i][j].get_type() == "fg"){
                int x = round((you.x())/gamemap->get_width());
                int y = round(you.y()/gamemap->get_height());
                if ((x==i && y==j)){
                     QPixmap pixmap(":/images/fake_ground.png");
                     cur_map[i][j].setpixmap(pixmap);
                }
                painter.drawPixmap(r,cur_map[i][j].getpixmap());
            }

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

}//Running through the string representation of map and print block according to their type

void ui::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    auto back = QRect{QPoint(0,0), QSize(1000,1000)};//rectangle that has center of your char to print pixmap from
    QPixmap m = QPixmap(":/images/background.jpg");
    painter.drawPixmap(back,m);

    print_map(painter);
     auto r = QRect{QPoint(you.x(),you.y()), QSize(30,30)};//rectangle that has center of your char to print pixmap from

    painter.drawPixmap(r,you.char_frame());


    //print mobs
    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);
    QRect rmob;
    for (int i = 0; i < mob.size();i++){
        if (mob[i].getdirection() == "UP" || mob[i].getdirection() == "DOWN"){
            rmob = QRect{QPoint(mob[i].x(),mob[i].y()), QSize(34,33)};
        }
        else{
            rmob = QRect{QPoint(mob[i].x(),mob[i].y()), QSize(30,30)};
        }
        painter.drawPixmap(rmob,mob[i].char_frame());
    }

    //if your cha is falling, start timer
    if (falling(you)){
         you.get_timer()->start(100);
    }
    else{
         you.get_timer()->stop();
    } //if your char falling check is true start timer to call fall slot



}

void ui::recalculate_path(mobs &mob){

    QVector<QVector<int>> grid;
    if (mob.col() >= you.col()){
            grid = uppath;
    }
    else{
            grid = downpath;
    }
          QPair<int,int> src(round(mob.y()/30), mob.row());
          QPair<int,int> dest(you.col(), you.row());
          if (grid[you.col()][you.row()] == 0){
              for (int i = you.row();i < grid.size() ;i++)
              {
                  bool terminate = false;
                  for (int j = you.col(); j < grid[0].size();j++)
                  {
                      if (grid[i][j] == 1){
                          dest = QPair<int,int>(i,j);
                          terminate = true;
                          break;
                      }
                  }
                  if (terminate){
                      break;
                  }
              }
          }

          pathsearch path;
          path.search(grid,src,dest);
          mob.mobpath = path.getpathlist();

          QPair<int,int> youpos(you.col(),you.row());

}// recalculate a path from mob to your character

void ui::recalculate(){
   for (int i = 0 ; i < mob.size(); i++)
   {
        recalculate_path(mob[i]);
    }
}// recalculate a path for all the mobs


bool ui::falling(Character &cha)
{
    int i = cha.row();
    int j = (cha.col());

    if(cur_map[i][j].get_type() == "ro" || cur_map[i][j].get_type()=="st"){
        return false;
    }



    if (cur_map[i][j+1].isnotground()){
            return true;
    }else
        {

            return false;
        }


}//check if cha is falling

void ui::fall(Character &cha)
{

    int i = you.row();
    int j = floor(cha.y()/30)+1;
    cha.move_down();

    if (cur_map[i][j].get_type() == "bn"){
        score+=500;
        cur_map[i][j].set_type("");
    }

    update_score();
    update();
}// if cha is falling, call this slot which will reduce cha 's y cordinate by fall_per_milisec


void ui::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    if (pos.x()>key_menu->rect().x() && pos.y()>key_menu->rect().y()){
        key_menu->hide();
        start_mobtimer();
    }
}//mouse press to exit key menu

void ui::keyPressEvent(QKeyEvent *event)
{
    int dis = you.get_walkstepdis();
    float x = you.x();
    float y = you.y();
    QMap<QString,Qt::Key> key_map = key_menu->get_key_map();
     if(falling(you)){
         return;
     }
     if(event->key() == key_map["UP"]&&
        (cur_map[x/30][ceil(y/30)].get_type() == "st")) {
               you.move_up();
     }// if up key is pressed
     if(event->key() == key_map["DOWN"]&&(!floor_check(x,y+dis))){
             you.move_down();

     }// if down key is pressed
     if(event->key() == key_map["RIGHT"]&&(!is_object(x+dis,y))){
            you.move_right();

     }// if right key is pressed
     if(event->key() == key_map["LEFT"]&&(!is_object(x-dis,y))){
           you.move_left();
     }// if left key is pressed
     if(event->key() == key_map["DIG"]){
         int i = you.row()+1;
         int j = you.col()+1;
           if ((!is_object(x+dis,y)) && !cur_map[i][j].is_digged()){

                        if (cur_map[i][j].get_type() == "br"){
                            cur_map[i][j].set_type("");
                            cur_map[i][j].set_digged(true);
                             connect(cur_map[i][j].get_respawntimer(),  &QTimer::timeout, this, [i,j,this]{ respawn(i,j); });
                            cur_map[you.row()+1][you.col()+1].get_respawntimer()->start(5000);
                            you.setdirection(you.getdirection());

                        }
            }
      }// if dig key is pressed

     if(event->key() == Qt::Key_Shift&& !key_menu->isVisible()){
        key_menu->show();
        stop_mobtimer();
     }//menu key

      int i = you.row();
      int j = you.col();
      if (cur_map[i][j].get_type() == "bn"){
          score+=500;
          cur_map[i][j].set_type("");
      }
      update_score();

      if (x/30!=i||y/30!=j){
          recalculate();
      }
      show_menu();
      if (you.col() == 0 && win()){
          show_win_menu();
      }
        //everytime character position change
      update();









}//override keyevent to change your character cordinates on a specific button

bool ui::on_map(Character &cha){
    return (cha.row() >= 0) && (cha.row() < cur_map.size()) && (cha.col() >= 0)
            && (cha.col() < cur_map[cur_map.size()].size());
}

bool ui::is_object(int x, int y)
{
    int i = round((x)/gamemap->get_width());
    int j = round(y/gamemap->get_height());

    if(cur_map[i][j].get_type() == "br" ){
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
    if (!falling(mob)&&!cur_map[mob.row()][mob.col()].is_digged()){
        mob.get_timer()->stop();
        mob.get_rand_timer()->start();
        recalculate_path(mob);
        return;
    }
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

bool ui::is_mob(float x, float y){
    bool is_mob = false;
    for (int i = 0 ; i < this->mob.size();i++){
        double dis = sqrt( (x-this->mob[i].x()) * (x-this->mob[i].x()) + (y-this->mob[i].y()) * (y-this->mob[i].y()));
        if (dis>10 && dis<30){
            is_mob = true;
            break;
        }
    }
    return is_mob;
}

void ui::mob_action(mobs &mob)
{
    if(cur_map[mob.row()][mob.col()].get_type() == "bn" && mob.holding() == false){
            cur_map[mob.row()][mob.col()].set_type("");
            mob.set_holding(true);
    }
    if (falling(mob)){
        mob.get_timer()->start(100);
        return;
    }

    if (mob.mobpath.isEmpty()){
        return;
    }

    if(mob.x()== mob.mobpath.front().second*30 && mob.y()== mob.mobpath.front().first*30){
       mob.mobpath.dequeue();
    }
    int dis = mob.get_walkstepdis();

    if (mob.mobpath.size() != 0){

        if(mob.x()< mob.mobpath.front().second*30 && !is_object(mob.x()+dis,mob.y()) && !is_mob(mob.x()+dis,mob.y())){
            mob.move_right();
            return;
        }
        if(mob.x() > mob.mobpath.front().second*30 &&!is_object(mob.x()-dis,mob.y()) && !is_mob(mob.x()-dis,mob.y())){
            mob.move_left();
            return;
        }
        if(mob.y()> mob.mobpath.front().first*30 && !is_object(mob.x(),mob.y()-dis)  && !is_mob(mob.x(),mob.y()-dis)){
            mob.move_up();
            return;
        }
        if(mob.y()< mob.mobpath.front().first*30 && !is_object(mob.x(),mob.y()+dis)  && !is_mob(mob.x(),mob.y()+dis)){
            mob.move_down();
            return;
        }

    }
    // everytime character's position is changed, recalculate the path



   update();


}// algorithm to control mobs

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
    if (score == 500*(gamemap->level()+2)){
        return true;
    }
    else {
        return false;
    }
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

void ui::reset(){
    lose_menu->close();
    you.update_life();
    you.get_timer()->start();

    setup_initial_pos();
    cur_map = gamemap->get_map(gamemap->level());
    for (int i = 0 ; i < mob.size(); i++){
        mob[i].set_holding(false);
    }
    recalculate();
    update();
}//reset everything

void ui::next_lv(){
    gamemap->set_level(gamemap->level()+1);
    cur_map = gamemap->get_map(gamemap->level());
    uppath = gamemap->griduppath();
    downpath = gamemap->griddownpath();
    setup_initial_pos();
    recalculate();

    update();
    win_menu->close();
} //go to next level










