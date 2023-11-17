#include "loginwidget.h"
LoginWidget::LoginWidget(QWidget *parent)
    : QWidget{parent}
{
    label_width->setText("宽度为：");
    label_height->setText("长度为：");
    b_start->setText("游戏开始!!");
    label_height->move(100,200);
    label_width->move(100,250);
    spinbox_height->move(350, 200);
    spinbox_width->move(350, 250);
    b_start->move(200,300);
    Init();
    HEIGHT_VALUE = spinbox_height->value();
    WIDTH_VALUE = spinbox_width->value();
    connect(b_start, &QPushButton::clicked,
            [=](){
                loginClose();
                w.show();
            });
}

void LoginWidget::Init(){
    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

}

void LoginWidget::loginClose(){
    this->close();
}
