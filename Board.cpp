#include "Board.h"
#include <QPainter>
#include <QRect>
#include <QMouseEvent>

Board::Board(QWidget *parent) : QWidget(parent)
{
    gridwidth = 40;
    for(int i = 0; i< 10; i++){
        QVector<QPoint> row;
        for(int j=0;j<9; j++) {
            QPoint p(60+gridwidth*j,60+gridwidth*i);
            row.push_back(p);
        }
        intercross.push_back(row);
    }
    // 00 01 02 03 04 05 06 07 08
    // 10 11 12 13 14 15 16 17 18
    // 20 21 22 23 24 25 26 27 28
    // 30 31 32 33 34 35 36 37 38
    // 40 41 42 43 44 45 46 47 48
    // 50 51 52 53 54 55 56 57 58
    // 60 61 62 63 64 65 66 67 68
    // 70 71 72 73 74 75 76 77 78
    // 80 81 82 83 84 85 86 87 88
    // 90 91 92 93 94 95 96 97 98
}
void Board::paintEvent(QPaintEvent * ev){
    QPainter painter(this);
    QPainter * painterptr = & painter;
    paintGrid(painterptr);
    paintStones(painterptr);
}
void Board::paintGrid(QPainter * painter){
    // draw 10 horizontal lines
    for (int i = 0; i< 10 ; i++){
        if (i == 0 || i == 9){
            //draw bold line
            painter->setPen(QPen(Qt::black, 2));
            painter->drawLine(intercross[i][0],intercross[i][8]);
        }
        else {
            painter->setPen(QPen(Qt::black, 1));
            painter->drawLine(intercross[i][0],intercross[i][8]);
        }
    }
    for (int i = 0; i< 9; i++) {
        if(i==0 || i==8){
            //draw bold line
            painter->setPen(QPen(Qt::black, 2));
            painter->drawLine(intercross[0][i],intercross[9][i]);
        }
        else{
            painter->setPen(QPen(Qt::black, 1));
            painter->drawLine(intercross[0][i],intercross[4][i]);
            painter->drawLine(intercross[5][i],intercross[9][i]);
        }
    }
    painter->setPen(QPen(Qt::black, 1.5));
    painter->drawLine(intercross[0][3],intercross[2][5]);
    painter->drawLine(intercross[0][5],intercross[2][3]);
    painter->drawLine(intercross[9][3],intercross[7][5]);
    painter->drawLine(intercross[9][5],intercross[7][3]);
}
void Board::paintStones(QPainter * painter){
    int j = 0;
    int tempx = 0;
    int tempy = 0;
    int typeseries[32] = {2,3,4,6,1,6,4,3,2,5,5,7,7,7,7,7,7,7,7,7,7,5,5,2,3,4,6,1,6,4,3,2};
    for(int i = 0;i<32;i++){
        Stone s;
        if(_s.size() <= 8){
            s.setinfo(20,0,j,i,false,false,typeseries[i]);
            tempx = j;
            j++;
            if(j>8) j=1;
        } else if (_s.size() <= 10){
            s.setinfo(20,2,j,i,false,false,typeseries[i]);
            _s.push_back(s);
            tempx = j;
            tempy = 2;
            j+=6;
            if(j>7) j = 0;
        } else if (_s.size() <= 15) {
            s.setinfo(20,3,j,i,false,false,typeseries[i]);
            _s.push_back(s);
            tempx = j;
            tempy = 3;
            j+=2;
            if(j>8) j = 0;
        } else if (_s.size() <= 20) {
            s.setinfo(20,6,j,i,false,true,typeseries[i]);
            _s.push_back(s);
            tempx = j;
            tempy = 6;
            j+=2;
            if(j>8) j = 1;
        } else if (_s.size() <= 22) {
            s.setinfo(20,7,j,i,false,true,typeseries[i]);
            _s.push_back(s);
            tempx = j;
            tempy = 7;
            j+=6;
            if(j>7) j = 0;
        } else if (_s.size() <= 31) {
            s.setinfo(20,9,j,i,false,true,typeseries[i]);
            _s.push_back(s);
            tempx = j;
            tempy = 9;
            j++;
        }
        _s.push_back(s);
        stonemap.insert(tempy*8+tempx,s);
    }
    for (int i = 0;i<32;i++) {
        if(i<=15){
            painter->setPen(Qt::black);
        }else {
            painter->setPen(Qt::red);
        }
        int col = gridwidth*_s[i].getcol();
        int row = gridwidth*_s[i].getrow();
        QPoint center(60+col,60+row);
        QPoint topleft(41+col,41+row);
        QPoint btmright(79+col,79+row);
        painter->setBrush(QBrush(QColor(255,255,0)));
        painter->drawEllipse(center,19,19);
        QRect rect(topleft,btmright);
        QFont font;
        font.setPointSize(20);
        painter->setFont(font);
        painter->drawText(rect,_s[i].Text(),QTextOption(Qt::AlignCenter));
    }
}
void Board::mousePressEvent(QMouseEvent * em){
    QPoint pressedPoint = em->pos();

}
void Board::mouseReleaseEvent(QMouseEvent *er){

}
