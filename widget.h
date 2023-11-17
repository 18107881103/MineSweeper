#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QRandomGenerator>
#include <QMouseEvent>
#include <QMessageBox>
#include <QPushButton>

QT_BEGIN_NAMESPACE
class LoginWidget;
namespace Ui { class Widget; }
QT_END_NAMESPACE

const int ROW_COUNT = 15;
const int COLUMN_COUNT = 15;
const int BLOCK_WIDTH = 32;
const int BLOCK_HEIGHT = 32;
const int BOOM_COUNT = 30;
const int WINDOW_WIDTH = ROW_COUNT*BLOCK_WIDTH;
const int WINDOW_HEIGHT = COLUMN_COUNT*BLOCK_HEIGHT;

enum BLOCK{
    ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,UNKNOWN,BOOM,FLAG
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void InitMap();
    void InitData();
    void paintEvent(QPaintEvent *e);
    void dfs(int x, int y);
    bool isNum(BLOCK b);
    bool Win();
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void whenGameOver();
    void whenWin();
    void widgetClose();
    void widgetStart();

private:
    Ui::Widget *ui;
    QMap<BLOCK, QPixmap> map;
    BLOCK data[ROW_COUNT][COLUMN_COUNT];
    BLOCK view[ROW_COUNT][COLUMN_COUNT];
    bool gameOver;
    bool youWin;
    bool showRect;
    bool gameStart;
    int rx;
    int ry;

};
#endif // WIDGET_H
