#ifndef KEY_WIDGET_H
#define KEY_WIDGET_H

#include <QWidget>
#include <QObject>
#include <QMouseEvent>
#include <QPainter>
class CustomButton:public QWidget
{
public:
    CustomButton();

    QRect get_select_rect();
    QRect get_text_rect();
    QRect get_name_rect();
    QPixmap get_textpix();//return pixmap of text
    QPixmap get_namepix();//return pixmap of name
    QPixmap get_selectpix();

    void set_up(QString key_text, QString key_name , int x, int y);
    QString get_keytext();
    QString get_keyname();
    void set_keytext(QString key_text);
    void set_keyname(QString key_name);
    void set_keytext_selected(bool selected);
    void set_keyname_selected(bool selected);
    bool get_keytext_selected();
    bool get_keyname_selected();
    int getx();
    int gety();


private:
    QRect select_rect;
    QRect text_rect;
    QRect name_rect;
    int x;
    int y;

    bool keytext_is_selected;
    bool keyname_is_selected;
    QPixmap selectpix;
    QPixmap namepix; //pixmap of name button
    QPixmap textpix;//pixmap of text button
    QString key_text;
    QString key_name;
};



class key_widget : public QWidget
{
     Q_OBJECT
     public:
        explicit key_widget(QWidget *parent = nullptr);// constructor
        void paintEvent(QPaintEvent *) override;// paintevent to draw gui
        void mouseMoveEvent(QMouseEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;

        void setup_init_key();
        void draw_key(QPainter &painter, CustomButton &custom);
        void key_hovering(CustomButton &custom);
        bool key_being_edited(CustomButton &custom);
        Qt::Key mappingkey(long code);
        QMap<QString, bool> setkey;

        QMap<QString,Qt::Key> get_key_map();
     private:
        CustomButton left_button;
        CustomButton up_button;
        CustomButton down_button;
        CustomButton right_button;
        CustomButton dig_button;

        QMap<QString,Qt::Key> key_map;
        QPoint mousepos;

};

#endif // KEY_WIDGET_H
