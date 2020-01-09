#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QPainter>
#include <QTime>
#include <QKeyEvent>

class Snake : public QWidget
{
    Q_OBJECT

public:
    Snake(QWidget *parent = 0);
    ~Snake();

protected:
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void timerEvent(QTimerEvent *e);

private:
    QImage body;
    QImage target;
    QImage head;

    static const int W_WIDTH = 300;
    static const int W_HEIGHT = 300;
    static const int OBJ_SIZE = 10;
    static const int ALL_DOTS = 900;
    static const int RAND_TARGET = 29;
    static const int SPEED = 140;

    int timerId;
    int bodies;
    int target_x;
    int target_y;
    int initial_body = 4;

    int x[ALL_DOTS];
    int y[ALL_DOTS];

    bool move_left;
    bool move_right;
    bool move_up;
    bool move_down;
    bool ingame;

    void loadImages();
    void initGame();
    void locateTarget();
    void isCollide();
    void isTarget();
    void move();
    void draw();
    void gameOver(QPainter &);
};

#endif // SNAKE_H
