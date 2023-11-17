#include "widget.h"
#include "ui_widget.h"
#include "loginwidget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT+40);

    InitData();
}

Widget::~Widget()
{
    delete ui;
}
bool Widget::isNum(BLOCK b){
    return b == ONE || b == TWO || b == THREE ||b == FOUR || b == FIVE || b == SIX || b == SEVEN ||b == EIGHT;
}
void Widget::dfs(int x, int y){
    if(view[x][y] != UNKNOWN) return;
    if(gameOver || youWin) return;

    view[x][y] = data[x][y];
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if(i == 0 && j == 0) continue;

            int travalx = x+i, travely = y+j;
            if(travalx >= 0 && travalx < ROW_COUNT && travely >= 0 && travely < COLUMN_COUNT){
                if(data[travalx][travely] == ZERO) dfs(travalx, travely);
                else if(isNum(data[travalx][travely])) view[travalx][travely] = data[travalx][travely];
            }
        }
    }
}
bool Widget::Win()
{
    for(int i=0;i<ROW_COUNT;i++)
        for(int j=0;j<COLUMN_COUNT;j++)
        {
            if((view[i][j]==UNKNOWN||view[i][j]==FLAG)&&data[i][j]!=BOOM)
            {
                return false;
            }
        }
    return true;
}
void Widget::InitMap()
{
    QPixmap *tiles = new QPixmap(":/img/tiles.jpg");
    //这样就可以直接通过map[ZERO]来获得0对应的格子图片;
    map.insert(ZERO, tiles->copy(0, 0, 32, 32));
    map.insert(ONE, tiles->copy(BLOCK_WIDTH * 1, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
    map.insert(TWO, tiles->copy(BLOCK_WIDTH * 2, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
    map.insert(THREE, tiles->copy(BLOCK_WIDTH * 3, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
    map.insert(FOUR, tiles->copy(BLOCK_WIDTH * 4, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
    map.insert(FIVE, tiles->copy(BLOCK_WIDTH * 5, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
    map.insert(SIX, tiles->copy(BLOCK_WIDTH * 6, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
    map.insert(SEVEN, tiles->copy(BLOCK_WIDTH * 7, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
    map.insert(EIGHT, tiles->copy(BLOCK_WIDTH * 8, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
    map.insert(BOOM, tiles->copy(BLOCK_WIDTH * 9, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
    map.insert(UNKNOWN, tiles->copy(BLOCK_WIDTH * 10, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
    map.insert(FLAG, tiles->copy(BLOCK_WIDTH * 11, 0, BLOCK_WIDTH, BLOCK_HEIGHT));
}

void Widget::InitData(){
    gameOver = false;
    youWin = false;
    showRect = false;
    gameStart = false;
    rx = -1;
    ry = -1;

    InitMap();
    for (int i = 0; i < ROW_COUNT; i++) {
        for (int j = 0; j < COLUMN_COUNT; j++) {
            data[i][j] = ZERO;
            view[i][j] = UNKNOWN;
        }
    }
    for(int i=0;i<BOOM_COUNT;i++){
        int v=QRandomGenerator::global()->generate()%(ROW_COUNT*COLUMN_COUNT);
        data[v/ROW_COUNT][v%ROW_COUNT]=BOOM;
    }
    for (int i = 0; i < ROW_COUNT; ++i) {
        for (int j = 0; j < COLUMN_COUNT; ++j) {
            if(data[i][j] == BOOM) continue;

            int boomNum = 0;
            for (int x = -1; x <= 1; ++x) {
                if(x+i < 0|| x+i > ROW_COUNT) continue;
                for (int y = -1; y <= 1; ++y) {
                    if(y+j < 0|| y+j > COLUMN_COUNT) continue;
                    if(data[x+i][y+j] == BOOM) boomNum++;
                }
            }

            switch(boomNum){
                case 0: data[i][j] = ZERO; break;
                case 1: data[i][j] = ONE; break;
                case 2: data[i][j] = TWO; break;
                case 3: data[i][j] = THREE; break;
                case 4: data[i][j] = FOUR; break;
                case 5: data[i][j] = FIVE; break;
                case 6: data[i][j] = SIX; break;
                case 7: data[i][j] = SEVEN; break;
                case 8: data[i][j] = EIGHT; break;
            }
        }
    }
}

void Widget::paintEvent(QPaintEvent *e){
    Q_UNUSED(e);
    QPainter painter(this);
    painter.drawPixmap(223, 5, map[BOOM]);
    for (int i = 0; i < ROW_COUNT; ++i)
        for (int j = 0; j < COLUMN_COUNT; ++j)
            painter.drawPixmap(BLOCK_WIDTH * i, BLOCK_HEIGHT * j+40,
                               gameOver ? map[data[i][j]] : map[view[i][j]]);
}
void Widget::mousePressEvent(QMouseEvent *e){
    if(gameOver||youWin) return;

    int start_x = e->pos().x();
    int start_y = e->pos().y();
    int x = e->pos().x()/BLOCK_WIDTH;
    int y = (e->pos().y()-40)/BLOCK_HEIGHT;
    if(start_y>5 && start_y<37 && start_x>223 && start_x<255 && gameStart == false && e->button() == Qt::LeftButton){
        gameStart = true;
    }
    if(gameStart && (start_y<5 || start_y>37 || start_x<223 || start_x>255)){
        if(view[x][y] == UNKNOWN && e->button() == Qt::LeftButton){
            if(data[x][y] == BOOM){
                gameOver = true;
                update();
                return;
            }

            dfs(x,y);
            youWin = Win();
            update();
        }
        else if(view[x][y] == UNKNOWN && e->button() == Qt::RightButton){
            view[x][y] = FLAG;
            update();
        }
        else if(view[x][y] == FLAG && e->button() == Qt::RightButton){
            view[x][y] = UNKNOWN;
            update();
        }
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *e){
    whenGameOver();
    whenWin();
}

void Widget::whenGameOver(){
    if(gameOver){
        QMessageBox *messageBox = new QMessageBox(this);
        QPushButton *b = new QPushButton(this);
        b->setText("重新开始吧~~~");
        messageBox->setText("点到炸弹啦！！！");
        messageBox->setVisible(true);
        b = messageBox->addButton("重新开始吧~", QMessageBox::AcceptRole);
        connect(b, &QPushButton::clicked,
                [=](){
                    gameOver = false;
                    for (int i = 0; i < ROW_COUNT; ++i) {
                        for (int j = 0; j < COLUMN_COUNT; ++j) {
                            view[i][j] = UNKNOWN;
                            }
                    }
                    update();
                });
    }
}

void Widget::whenWin(){
    if(youWin){
        QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setText("大胜利！！！");
        messageBox->setVisible(true);
    }
}

void Widget::widgetClose(){
    this->close();
}

void Widget::widgetStart(){
    this->show();
}
