#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include "widget.h"

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);
    void loginClose();
    QSpinBox *spinbox_width = new QSpinBox(this);
    QSpinBox *spinbox_height = new QSpinBox(this);
    QLabel *label_width = new QLabel(this);
    QLabel *label_height = new QLabel(this);
    QPushButton *b_start = new QPushButton(this);
    int WIDTH_VALUE = 0;
    int HEIGHT_VALUE = 0;

signals:

private:
    void Init();
    Widget w;
};

#endif // LOGINWIDGET_H
