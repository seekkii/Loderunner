#include "key_widget.h"

CustomButton::CustomButton()
{
    resize(QSize(500,30));
    selectpix = QPixmap(":/images/keyselection_bar.png");
    textpix = QPixmap(":/images/textbar.png");
    namepix = QPixmap(":/images/namebar.png");
    x = 0;
    y = 0;
    select_rect = QRect{QPoint(x,y), QSize(500,30)};
    name_rect = QRect{QPoint(x+270,y), QSize(230,30)};
    text_rect = QRect{QPoint(x,y), QSize(330,30)};
    keyname_is_selected = false;
    keytext_is_selected = false;
}

QRect CustomButton::get_select_rect(){
    return select_rect;
}

QRect CustomButton::get_name_rect(){
    return name_rect;
}

QRect CustomButton::get_text_rect(){
    return text_rect;
}

QPixmap CustomButton::get_selectpix(){
    return selectpix;
}

QPixmap CustomButton::get_textpix()
{
    return  textpix;
}

QPixmap CustomButton::get_namepix()
{
    return namepix;
}
void CustomButton::set_up( QString key_text, QString key_name, int x, int y){
    this->key_text = key_text;
    this->key_name = key_name;
    this->x = x;
    this->y = y;
    select_rect = QRect{QPoint(x,y), QSize(500,30)};
    name_rect = QRect{QPoint(x+270,y), QSize(230,30)};
    text_rect = QRect{QPoint(x,y), QSize(330,30)};
}

bool CustomButton::get_keyname_selected()
{
    return keyname_is_selected;
}

bool CustomButton::get_keytext_selected()
{
    return keytext_is_selected;
}

void CustomButton::set_keyname_selected(bool selected)
{
    keyname_is_selected = selected;
}

void CustomButton::set_keytext_selected(bool selected)
{
    keytext_is_selected = selected;
}

void CustomButton::set_keytext(QString key_text)
{
   this->key_text = key_text;
}

void CustomButton::set_keyname(QString key_name)
{
   this->key_name = key_name;
}
QString CustomButton::get_keyname()
{
    return key_name;
}

QString CustomButton::get_keytext()
{
    return key_text;
}

int CustomButton::getx()
{
    return x;
}

int CustomButton::gety()
{
    return y;
}


key_widget::key_widget(QWidget *parent): QWidget(parent)
{
    resize(500,500);
    setup_init_key();
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    setWindowFlags(Qt::FramelessWindowHint);
    hide();

    left_button.set_up("LEFT", "←" ,0,20);
    right_button.set_up("RIGHT","→",0,60);
    up_button.set_up("UP","↑",0,100);
    down_button.set_up("DOWN","↓",0,140);
    dig_button.set_up("DIG","z",0,180);

    setkey["LEFT"] = false;
    setkey["RIGHT"] =false;
    setkey["UP"] = false;
    setkey["DOWN"] = false;
    setkey["DIG"] = false;

    update();
}

void key_widget::mouseMoveEvent(QMouseEvent * event)
{
         mousepos = event->pos();
         key_hovering(left_button);
         key_hovering(right_button);
         key_hovering(up_button);
         key_hovering(down_button);
         key_hovering(dig_button);


}

bool key_widget::key_being_edited(CustomButton &custom)
{
     if (custom.get_keyname_selected()&& setkey[custom.get_keytext()]){
         return true;
     }
     else return false;

}
void key_widget::mousePressEvent(QMouseEvent * event)
{
        mousepos = event->pos();

        if (left_button.get_keyname_selected() && setkey["LEFT"] == false){
            setkey["LEFT"] = true;
        }
        else{
            setkey["LEFT"] = false;
        }
        if (right_button.get_keyname_selected() && setkey["RIGHT"] == false){
            setkey["RIGHT"] = true;
        }
        else {
            setkey["RIGHT"] = false;
        }
        if (up_button.get_keyname_selected() && setkey["UP"] == false){
            setkey["UP"] = true;
        }
        else {
            setkey["UP"] = false;
        }
        if (down_button.get_keyname_selected() && setkey["DOWN"] == false){
            setkey["DOWN"] = true;
        }
        else {
            setkey["DOWN"] = false;
        }
        if (dig_button.get_keyname_selected() && setkey["DIG"] == false){
            setkey["DIG"] = true;
        }
        else {
            setkey["DIG"] = false;
        }

}
void key_widget::keyPressEvent(QKeyEvent *event)
{

    QString cur =  event->text();//current event text;
    key_map[cur.toUpper()] = mappingkey(event->key());
    if (mappingkey(event->key()) == Qt::Key_Left){
        cur = "←";
    }
    if (mappingkey(event->key()) == Qt::Key_Right){
        cur = "→";
    }
    if (mappingkey(event->key()) == Qt::Key_Up){
        cur = "↑";
    }
    if (mappingkey(event->key()) == Qt::Key_Down){
        cur = "↓";
    }




    if(key_being_edited(left_button)){
        key_map[left_button.get_keytext()] = mappingkey(event->key());
        left_button.set_keyname(cur);
        update();
    }
    if(key_being_edited(right_button)){
        key_map[right_button.get_keytext()] = mappingkey(event->key());
        right_button.set_keyname(cur);
        update();
    }
    if(key_being_edited(up_button)){
        key_map[up_button.get_keytext()] = mappingkey(event->key());
        up_button.set_keyname(cur);
        update();
    }
    if(key_being_edited(down_button)){
        key_map[down_button.get_keytext()] = mappingkey(event->key());
        down_button.set_keyname(cur);
        update();
    }
    if(key_being_edited(dig_button)){
        key_map[dig_button.get_keytext()] = mappingkey(event->key());
        dig_button.set_keyname(cur);
        update();
    }

}
Qt::Key key_widget::mappingkey(long code)
{

    if (code == 49){
        return Qt::Key_1;
    }
    if (code == 50){
        return Qt::Key_2;
    }
    if (code == 51){
        return Qt::Key_3;
    }
    if (code == 52){
        return Qt::Key_4;
    }
    if (code == 53){
        return Qt::Key_5;
    }
    if (code == 54){
        return Qt::Key_6;
    }
    if (code == 55){
        return Qt::Key_7;
    }
    if (code == 56){
        return Qt::Key_8;
    }
    if (code == 57){
        return Qt::Key_9;
    }
    if (code == 48){
        return Qt::Key_0;
    }
    if (code == 45){
        return Qt::Key_Minus;
    }
    if (code == 61){
        return Qt::Key_Equal;
    }
    if (code == 65){
        return Qt::Key_A;
    }
    if (code == 66){
        return Qt::Key_B;
    }
    if (code == 67){
        return Qt::Key_C;
    }
    if (code == 68){
        return Qt::Key_D;
    }
    if (code == 69){
        return Qt::Key_E;
    }
    if (code == 70){
        return Qt::Key_F;
    }
    if (code == 71){
        return Qt::Key_G;
    }
    if (code == 72){
        return Qt::Key_H;
    }
    if (code == 73){
        return Qt::Key_I;
    }
    if (code == 74){
        return Qt::Key_J;
    }
    if (code == 75){
        return Qt::Key_K;
    }
    if (code == 76){
        return Qt::Key_L;
    }
    if (code == 77){
        return Qt::Key_M;
    }
    if (code == 78){
        return Qt::Key_N;
    }
    if (code == 79){
        return Qt::Key_O;
    }
    if (code == 80){
        return Qt::Key_P;
    }
    if (code == 81){
        return Qt::Key_Q;
    }
    if (code == 82){
        return Qt::Key_R;
    }
    if (code == 83){
        return Qt::Key_S;
    }if (code == 84){
        return Qt::Key_T;
    }
    if (code == 85){
        return Qt::Key_U;
    }
    if (code == 86){
        return Qt::Key_V;
    }
    if (code == 87){
        return Qt::Key_W;
    }
    if (code == 88){
        return Qt::Key_X;
    }
    if (code == 89){
        return Qt::Key_Y;
    }
    if (code == 90){
        return Qt::Key_Z;
    }
    if (code == 91){
        return Qt::Key_BracketLeft;
    }
    if (code == 92){
        return Qt::Key_Minus;
    }
    if (code == 93){
        return Qt::Key_BracketRight;
    }
    if (code == 59){
        return Qt::Key_Semicolon;
    }
    if (code == 39){
        return Qt::Key_Colon;
    }
    if (code == 44){
        return Qt::Key_Comma;
    }
    if (code == 46){
        return Qt::Key_Period;
    }
    if (code == 16777234){
        return Qt::Key_Left;
    }
    if (code == 16777235){
        return Qt::Key_Up;
    }
    if (code == 16777236){
        return Qt::Key_Right;
    }
    if (code == 16777237){
        return Qt::Key_Down;
    }
    if (code == 16777238){
        return Qt::Key_PageUp;
    }
    if (code == 16777239){
        return Qt::Key_PageDown;
    }
    if (code == 16777248){
        return Qt::Key_Shift;
    }

    return Qt::Key_Shift;
}


void key_widget::key_hovering(CustomButton &custom)
{
    int border = custom.gety() + custom.size().height();
    if (mousepos.x() >= 290 && mousepos.y()<border && mousepos.y()>=custom.gety()){
        custom.set_keyname_selected(true);
        custom.set_keytext_selected(false);
        update();
    }
    if (mousepos.x() < 290 && mousepos.y()<border && mousepos.y()>=custom.gety()){
        custom.set_keytext_selected(true);
        custom.set_keyname_selected(false);
        update();
    }
    if (mousepos.y()>border || mousepos.y()<custom.gety()){
            custom.set_keytext_selected(false);
            custom.set_keyname_selected(false);
            update();
    }
}

void key_widget::setup_init_key()
{
    key_map["UP"] = Qt::Key_Up;
    key_map["DOWN"] = Qt::Key_Down;
    key_map["RIGHT"] = Qt::Key_Right;
    key_map["LEFT"] = Qt::Key_Left;
    key_map["DIG"] = Qt::Key_Z;
}


QMap<QString,Qt::Key> key_widget::get_key_map()
{
    return key_map;
}

void key_widget::draw_key(QPainter &painter, CustomButton &custom)
{
    QPoint text_p = custom.get_text_rect().center() +QPoint(0,5);
    QPoint name_p = custom.get_name_rect().center() +QPoint(0,5);
    painter.drawPixmap(custom.get_select_rect(),custom.get_selectpix());
    painter.drawText(text_p,custom.get_keytext());
    painter.drawText(name_p,custom.get_keyname());
    if (custom.get_keyname_selected() == true){
         painter.drawPixmap(custom.get_name_rect(),custom.get_namepix());
         painter.drawText(text_p,custom.get_keytext());
         painter.drawText(name_p,custom.get_keyname());
    }
    if (custom.get_keytext_selected() == true){
         painter.drawPixmap(custom.get_text_rect(),custom.get_textpix());
         painter.drawText(text_p,custom.get_keytext());
         painter.drawText(name_p,custom.get_keyname());
    }

}

void key_widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap background(":/images/key_background.jpg");
    QRect size_rect = QRect{QPoint(0,0), QSize(500,500)};
    painter.drawPixmap(size_rect,background);
    draw_key(painter,left_button);
    draw_key(painter,right_button);
    draw_key(painter,up_button);
    draw_key(painter,down_button);
    draw_key(painter,dig_button);

}
