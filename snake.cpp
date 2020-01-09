#include "snake.h"

Snake::Snake(QWidget *parent)
    : QWidget(parent),
      move_down(false),
      move_left(false),
      move_right(false),
      move_up(true),
      ingame(true)
{
    setStyleSheet("background-color: gray");
    resize(W_WIDTH, W_HEIGHT);
    loadImages();
    initGame();
}

Snake::~Snake()
{

}

void Snake::loadImages(){
    QImage body_temp;
    QImage target_temp;
    QImage head_temp;

    if(body_temp.load(":/images/body.png"))
        body = body_temp.scaled(OBJ_SIZE, OBJ_SIZE);

    if(target_temp.load(":/images/target.png"))
        target = target_temp.scaled(OBJ_SIZE, OBJ_SIZE);

    if(head_temp.load(":/images/head.png"))
        head = head_temp.scaled(OBJ_SIZE, OBJ_SIZE);
}

void Snake::initGame(){
    bodies = initial_body;

    for(int count=0; count<bodies; count++){
        x[count] = 150;
        y[count] = 150 - count*OBJ_SIZE;
    }
    locateTarget();

    timerId = startTimer(SPEED);
}

void Snake::paintEvent(QPaintEvent *e){
   Q_UNUSED(e);
   draw();
}

void Snake::draw(){
    QPainter qp(this);

    if(ingame) {
        qp.drawImage(target_x, target_y, target);

        for(int count = 0; count < bodies; count++){
            if(count == 0) {
                qp.drawImage(x[count], y[count], head);
            } else {
                qp.drawImage(x[count], y[count], body);
            }
        }
    } else {
        gameOver(qp);
    }
}

void Snake::gameOver(QPainter &qp){

    QString message = "Game over";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(message);

    qp.setFont(font);
    int h = height();
    int w = width();

    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message);
}

void Snake::isTarget(){
    if((x[0] == target_x) && (y[0] == target_y)) {
        bodies++;
        locateTarget();
    }
}


void Snake::move(){
    for(int count = bodies; count > 0; count--){
        x[count] = x[count - 1];
        y[count] = y[count - 1];
    }

    if(move_down) {
        y[0] += OBJ_SIZE;
    }
    if(move_up) {
        y[0] -= OBJ_SIZE;
    }
    if(move_left) {
        x[0] -= OBJ_SIZE;
    }
    if(move_right) {
        x[0] += OBJ_SIZE;
    }
}

void Snake::isCollide(){
    for(int count = bodies; count > initial_body; count--){
        if((x[0] == x[count]) && (y[0] == y[count]))
            ingame = false;
    }
    if(y[0] <= 0)
        ingame = false;
    if(y[0] >= W_HEIGHT)
        ingame = false;
    if(x[0] <= 0)
        ingame = false;
    if(x[0] >= W_WIDTH)
        ingame = false;

    if(!ingame)
        killTimer(timerId);
}

void Snake::locateTarget() {

    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int r = qrand() % RAND_TARGET;
    target_x = (r * OBJ_SIZE);

    r = qrand() % RAND_TARGET;
    target_y = (r * OBJ_SIZE);
}

void Snake::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);

    if (ingame) {
        isTarget();
        isCollide();
        move();
    }
    repaint();
}

void Snake::keyPressEvent(QKeyEvent *e) {

    int key = e->key();

    if ((key == Qt::Key_Left) && (!move_right)) {
        move_left = true;
        move_up = false;
        move_down = false;
    }

    if ((key == Qt::Key_Right) && (!move_left)) {
        move_right = true;
        move_up = false;
        move_down = false;
    }

    if ((key == Qt::Key_Up) && (!move_down)) {
        move_up = true;
        move_right = false;
        move_left = false;
    }

    if ((key == Qt::Key_Down) && (!move_up)) {
        move_down = true;
        move_left = false;
        move_right = false;
    }

    QWidget::keyPressEvent(e);
}
