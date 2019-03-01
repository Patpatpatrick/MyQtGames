#include "Board.h"
#include <QPainter>
#include <QRect>
#include <QMouseEvent>
#include <QPoint>
#include <QDebug>
Board::Board(QWidget *parent,int selectedID) :
    QWidget(parent),
    stoneController(selectedID)
{
    initInterCrosses();
    stoneController.initStones(stoneradius);
    setAttribute(Qt::WA_DeleteOnClose);
}
void Board::initInterCrosses()
{
    for(int i = 0; i< 10; i++){
        QVector<QPoint> row;
        for(int j=0;j<9; j++) {
            QPoint p(lefttopMargin+gridwidth*j,lefttopMargin+gridwidth*i);
            row.push_back(p);
        }
        intercross.push_back(row);
    }
}
void Board::paintEvent(QPaintEvent * ev){
    QPainter painter(this);
    paintGrid(painter);
    paintStones(painter);
}
void Board::paintGrid(QPainter & painter){
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
    //qDebug()<<"Finish Grid Painting";
}

void Board::paintStones(QPainter & painter){
    qDebug()<<"Starts Stones Painting";
    for (int i = 0;i<32;i++) {
        if(stoneController.isDead(i)){
            drawDeadStone(painter,i);
        }
        else
            drawLiveStone(painter,i);
    }

}
void Board::drawLiveStone(QPainter & painter,int i){
    qDebug()<<"Live Painting"<<i;

    if(i<=15){
        painter.setPen(Qt::black);
    }else {
        painter.setPen(Qt::red);
    }
    int col = gridwidth*stoneController.getCol(i);
    int row = gridwidth*stoneController.getRow(i);
    QPoint center(lefttopMargin+col,lefttopMargin+row);
    QPoint topleft(lefttopMargin-stoneradius+col,lefttopMargin-stoneradius+row);
    QPoint btmright(lefttopMargin+stoneradius+col,lefttopMargin+stoneradius+row);
    if(stoneController.isThisSelected(i)){
        painter.setBrush(QBrush(Qt::cyan));
    }else
        painter.setBrush(QBrush(QColor(255,255,0)));
    painter.drawEllipse(center,stoneradius,stoneradius);
    QRect rect(topleft,btmright);
    if(stoneController.isThisSelected(i)){
        QPen pen(Qt::DashDotLine);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(rect);
    }
    QFont font;
    font.setPointSize(20);
    painter.setFont(font);
    painter.drawText(rect,stoneController.Text(i),QTextOption(Qt::AlignCenter));
}

void Board::drawDeadStone(QPainter & painter,int i){
    qDebug()<<"Dead Painting"<<i;
    static int xcount=10*gridwidth;
    static int ycount=0;
    static int deadCounts = deadCounts;
    if(i<=15){
        painter.setPen(Qt::black);
    }else {
        painter.setPen(Qt::red);
    }
    QPoint center(lefttopMargin+xcount,lefttopMargin+ycount);
    QPoint topleft(lefttopMargin-stoneradius+xcount,lefttopMargin-stoneradius+ycount);
    QPoint btmright(lefttopMargin+stoneradius+xcount,lefttopMargin+stoneradius+ycount);
    painter.setBrush(QBrush(QColor(255,255,0)));
    painter.drawEllipse(center,stoneradius,stoneradius);
    QRect rect(topleft,btmright);
    QFont font;
    font.setPointSize(20);
    painter.setFont(font);
    painter.drawText(rect,stoneController.Text(i),QTextOption(Qt::AlignCenter));
    if(stoneController.deadStonesCount>deadCounts){
        deadCounts = stoneController.deadStonesCount;
        xcount+=gridwidth;
        if(xcount == 13*gridwidth){
            ycount+=gridwidth;
        }
    }
}
int Board::findClosestIndex(int xInBoard, int yInBoard){
    int y = 0;
    int x = 0;
    y = yInBoard/gridwidth;
    x = xInBoard/gridwidth;
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
        // select the stone on position closeY*9+closeX
        stoneController.selectThisOne(stoneController.stonemap[closeY*9+closeX]);
        update();
    }
}
bool Board::findStone(int x, int y, QPoint pressedPoint){
    int distsqr = (intercross[y][x].x()-pressedPoint.x())*(intercross[y][x].x()-pressedPoint.x())
            +(intercross[y][x].y()-pressedPoint.y())*(intercross[y][x].y()-pressedPoint.y());
    if(distsqr<=stoneradius*stoneradius){
        if(stoneController.stonemap.contains(y*9+x)){
            return true;
        }
    }
    return false;
}
void Board::mouseReleaseEvent(QMouseEvent *er){
    qDebug()<<"Mouse Released!";
}
bool Board::isOutOfBoard(int pressedx,int pressedy){
    int yInBoard = pressedy-lefttopMargin+stoneradius;
    int xInBoard = pressedx-lefttopMargin+stoneradius;
    return((yInBoard<0 || yInBoard>9*gridwidth+2*stoneradius)
    ||(xInBoard<0 || xInBoard>8*gridwidth+2*stoneradius));
}
void Board::mousePressEvent(QMouseEvent * em){
    qDebug()<<"Mouse Pressed!";
    if(!stoneController.isThisSelected(-1)){
        QPoint pressedPoint = em->pos();
        if(isOutOfBoard(pressedPoint.x(),pressedPoint.y())){
            return;
        }
        int yInBoard = pressedPoint.y()-lefttopMargin+stoneradius;
        int xInBoard = pressedPoint.x()-lefttopMargin+stoneradius;
        // they must be positive.
        int finedIndex = findClosestIndex(xInBoard,yInBoard);
        int x = finedIndex % 9;
        int y = finedIndex / 9;
        if(stoneController.isClickingItself(x,y)){
            stoneController.selectThisOne(-1);
            update();
            return;
        }
        if(stoneController.canMoveToDest(x,y)){
            if(findStone(x,y,pressedPoint)){
                // previous stone on this position is eaten
                stoneController.processEatenStoneOn(x,y);
                // update();
            }
            stoneController.updateSelectedStone(x,y);
            stoneController.selectThisOne(-1);
            update();
            // we finish a full process of choosing and placing stone, now selectedId is -1 again.
        }
    }
}

