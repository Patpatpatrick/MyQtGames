#include "Board.h"
#include <QPainter>
#include <QRect>
#include <QMouseEvent>
#include <QPoint>
#include <QDebug>
Board::Board(QWidget *parent) : QWidget(parent)
{
    _selectedId = -1;
    gridwidth = 40;
    lefttopMargin = 60;
    stoneradius = 20;
    for(int i = 0; i< 10; i++){
        QVector<QPoint> row;
        for(int j=0;j<9; j++) {
            QPoint p(lefttopMargin+gridwidth*j,lefttopMargin+gridwidth*i);
            row.push_back(p);
        }
        intercross.push_back(row);
    }
    initStones();
    setAttribute(Qt::WA_DeleteOnClose);
}
void Board::paintEvent(QPaintEvent * ev){
    QPainter painter(this);
    // QPainter * painterptr = & painter;
    paintGrid(painter);
    paintStones(painter);
}
void Board::paintGrid(QPainter & painter){
    // draw 10 horizontal lines
    for (int i = 0; i< 10 ; i++){
        if (i == 0 || i == 9){
            //draw bold line
            painter.setPen(QPen(Qt::black, 2));
            painter.drawLine(intercross[i][0],intercross[i][8]);
        }
        else {
            painter.setPen(QPen(Qt::black, 1));
            painter.drawLine(intercross[i][0],intercross[i][8]);
        }
    }
    for (int i = 0; i< 9; i++) {
        if(i==0 || i==8){
            //draw bold line
            painter.setPen(QPen(Qt::black, 2));
            painter.drawLine(intercross[0][i],intercross[9][i]);
        }
        else{
            painter.setPen(QPen(Qt::black, 1));
            painter.drawLine(intercross[0][i],intercross[4][i]);
            painter.drawLine(intercross[5][i],intercross[9][i]);
        }
    }
    painter.setPen(QPen(Qt::black, 1.5));
    painter.drawLine(intercross[0][3],intercross[2][5]);
    painter.drawLine(intercross[0][5],intercross[2][3]);
    painter.drawLine(intercross[9][3],intercross[7][5]);
    painter.drawLine(intercross[9][5],intercross[7][3]);
    qDebug()<<"Finish Grid Painting";
}
void Board::initStones(){
    qDebug()<<"Start stones initializing";
    int j = 0;
    int tempx = 0;
    int tempy = 0;
    int typeseries[32] = {2,3,4,6,1,6,4,3,2,5,5,7,7,7,7,7,7,7,7,7,7,5,5,2,3,4,6,1,6,4,3,2};
    for(int stoneIndex = 0;stoneIndex<32;stoneIndex++){
        Stone s;
        if(_s.size() <= 8){
            s.setinfo(stoneradius,0,j,stoneIndex,false,false,typeseries[stoneIndex]);
            tempx = j;
            j++;
            if(j>8) j=1;
        } else if (_s.size() <= 10){
            s.setinfo(stoneradius,2,j,stoneIndex,false,false,typeseries[stoneIndex]);
            tempx = j;
            tempy = 2;
            j+=6;
            if(j>7) j = 0;
        } else if (_s.size() <= 15) {
            s.setinfo(stoneradius,3,j,stoneIndex,false,false,typeseries[stoneIndex]);
            tempx = j;
            tempy = 3;
            j+=2;
            if(j>8) j = 0;
        } else if (_s.size() <= 20) {
            s.setinfo(stoneradius,6,j,stoneIndex,false,true,typeseries[stoneIndex]);
            tempx = j;
            tempy = 6;
            j+=2;
            if(j>8) j = 1;
        } else if (_s.size() <= 22) {
            s.setinfo(stoneradius,7,j,stoneIndex,false,true,typeseries[stoneIndex]);
            tempx = j;
            tempy = 7;
            j+=6;
            if(j>7) j = 0;
        } else if (_s.size() <= 31) {
            s.setinfo(stoneradius,9,j,stoneIndex,false,true,typeseries[stoneIndex]);
            tempx = j;
            tempy = 9;
            j++;
        }
        _s.push_back(s);
        stonemap[tempy*9+tempx] = stoneIndex;
       // stonemap.insert(tempy*8+tempx,_s[i]);
       // qDebug()<<"initStones" ;

    }
}
void Board::paintStones(QPainter & painter){
    qDebug()<<"Starts Stones Painting";
    for (int i = 0;i<32;i++) {
        if(_s[i].isDead()){
            continue;
        }
        if(i<=15){
            painter.setPen(Qt::black);
        }else {
            painter.setPen(Qt::red);
        }
        int col = gridwidth*_s[i].getcol();
        int row = gridwidth*_s[i].getrow();
        QPoint center(lefttopMargin+col,lefttopMargin+row);
        QPoint topleft(lefttopMargin-stoneradius+col,lefttopMargin-stoneradius+row);
        QPoint btmright(lefttopMargin+stoneradius+col,lefttopMargin+stoneradius+row);
        if(i == _selectedId){
            painter.setBrush(QBrush(Qt::cyan));
        }else
            painter.setBrush(QBrush(QColor(255,255,0)));
        painter.drawEllipse(center,stoneradius,stoneradius);
        QRect rect(topleft,btmright);
        if(i == _selectedId){
            QPen pen(Qt::DashDotLine);
            painter.setPen(pen);
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(rect);
        }
        QFont font;
        font.setPointSize(20);
        painter.setFont(font);
        painter.drawText(rect,_s[i].Text(),QTextOption(Qt::AlignCenter));
    }

    //qDebug()<<"stonemap[0] in paintStones is "<<stonemap[0].getcol()<<"  "<<stonemap[0].getrow();
}
int Board::findClosestIndex(int xInBoard, int yInBoard){
    int y = 0;
    int x = 0;
    y = yInBoard/gridwidth;
    x = xInBoard/gridwidth;
//    int yLeftOver = yInBoard%gridwidth;
//    int xLeftOver = xInBoard%gridwidth;
//    if(yLeftOver<stoneradius){
//        if(xLeftOver<stoneradius){
//            y = yInBoard/gridwidth;
//            x = xInBoard/gridwidth;
//        }else if (xLeftOver>gridwidth-stoneradius) {
//            y = yInBoard/gridwidth;
//            x = xInBoard/gridwidth + 1;
//        }
//    }else if (yLeftOver>gridwidth-stoneradius) {
//        if(xLeftOver<stoneradius){
//            y = yInBoard/gridwidth + 1;
//            x = xInBoard/gridwidth;
//        }else if (xLeftOver>gridwidth-stoneradius) {
//            y = yInBoard/gridwidth + 1;
//            x = xInBoard/gridwidth + 1;
//        }
//    }
    return y*9+x;
}
void Board::mouseDoubleClickEvent(QMouseEvent * em){
    //qDebug()<<"stonemap[0] in mousePressEvent is "<<stonemap[0].getcol()<<"  "<<stonemap[0].getrow();
    QPoint pressedPoint = em->pos();
    if(isOutOfBoard(pressedPoint.x(),pressedPoint.y())){
        return;
    }
    int yInBoard = pressedPoint.y()-lefttopMargin+stoneradius;
    int xInBoard = pressedPoint.x()-lefttopMargin+stoneradius;
    int finedIndex = findClosestIndex(xInBoard,yInBoard);
    int closeX = finedIndex % 9;
    int closeY = finedIndex / 9;
    if(findStone(closeX,closeY,pressedPoint)){
        Stone selectedStone = _s[stonemap[closeY*9+closeX]];
        qDebug()<<"Stone info"<<selectedStone.getcol()<<" " <<selectedStone.getrow();
        _selectedId = stonemap[closeY*9+closeX];
        update();
    }
}
bool Board::findStone(int x, int y, QPoint pressedPoint){
    int distsqr = (intercross[y][x].x()-pressedPoint.x())*(intercross[y][x].x()-pressedPoint.x())
            +(intercross[y][x].y()-pressedPoint.y())*(intercross[y][x].y()-pressedPoint.y());
    if(distsqr<=stoneradius*stoneradius){
        if(stonemap.contains(y*9+x)){
            return true;
        }
    }
    return false;
}
void Board::mouseReleaseEvent(QMouseEvent *er){

    qDebug()<<"dajiahao";
}
bool Board::isOutOfBoard(int pressedx,int pressedy){
    int yInBoard = pressedy-lefttopMargin+stoneradius;
    int xInBoard = pressedx-lefttopMargin+stoneradius;
    return((yInBoard<0 || yInBoard>9*gridwidth+2*stoneradius)
    ||(xInBoard<0 || xInBoard>8*gridwidth+2*stoneradius));
}
void Board::mousePressEvent(QMouseEvent * em){
    if(_selectedId != -1){
        QPoint pressedPoint = em->pos();
        if(isOutOfBoard(pressedPoint.x(),pressedPoint.y())){
            return;
        }
        int yInBoard = pressedPoint.y()-lefttopMargin+stoneradius;
        int xInBoard = pressedPoint.x()-lefttopMargin+stoneradius;
        int finedIndex = findClosestIndex(xInBoard,yInBoard);
        int x = finedIndex % 9;
        int y = finedIndex / 9;
        if(findStone(x,y,pressedPoint)){
            _s[stonemap[y*9+x]].setDead();
            stonemap.remove(y*9+x);
            update();
            qDebug()<<"放下棋子,吃";
        } else{
            qDebug()<<"放下棋子";
        }
        stonemap.remove(_s[_selectedId].getrow()*9+_s[_selectedId].getcol());
        _s[_selectedId].setRow(y);
        _s[_selectedId].setCol(x);
        stonemap[y*9+x] = _selectedId;
        update();
        _selectedId = -1;
    }
}
