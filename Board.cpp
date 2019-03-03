#include "Board.h"
#include <QPainter>
#include <QRect>
#include <QMouseEvent>
#include <QPoint>
#include <QDebug>
Board::Board(bool redDown,QWidget *parent,int selectedID) :
    QWidget(parent),
    stoneController(selectedID,redDown)
{
    this->resize(800, this->height());
    initInterCrosses();
    redTurn = true;
    stoneController.initStones(stoneradius);
    regretBtn = new QPushButton("Regret Step",this);
    regretBtnFunction();
    setAttribute(Qt::WA_DeleteOnClose);
}
void Board::regretBtnFunction(){
    connect(regretBtn,&QPushButton::clicked,[=](){
        qDebug()<<"=============supertype regret called==============";
        stoneController.regretStep();
        redTurn = !redTurn;
        update();
    });
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
    qDebug()<<"Finish Grid Painting";
}

void Board::paintStones(QPainter & painter){
    qDebug()<<"Starts Stones Painting";
    drawLiveStones(painter);
    drawDeadStones(painter);
}
void Board::drawLiveStones(QPainter & painter){
    for (int i = 0;i<32;i++) {
        if(!stoneController.isDead(i)){
            if(!stoneController._s[i].isRed()){
                painter.setPen(Qt::black);
            }else {
                painter.setPen(Qt::red);
            }
            int col = gridwidth*stoneController.getCol(i);
            int row = gridwidth*stoneController.getRow(i);
            QPoint center(lefttopMargin+col,lefttopMargin+row);

            if(stoneController.isThisSelected(i)){
                painter.setBrush(QBrush(Qt::cyan));
            }else
                painter.setBrush(QBrush(QColor(255,255,0)));
            painter.drawEllipse(center,stoneradius,stoneradius);
            QPoint topleft(lefttopMargin-stoneradius+col,lefttopMargin-stoneradius+row);
            QPoint btmright(lefttopMargin+stoneradius+col,lefttopMargin+stoneradius+row);
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
    }
}

void Board::drawDeadStones(QPainter & painter){
    int basicXShift = 10*gridwidth;
    int basicYShift = 0;
    int xcount = 0;
    int ycount = 0;
    int redDrawn = 0;
    int blackDrawn = 0;
    for (int i = 0 ; i < stoneController.deadStone.size() ; i++) {
        qDebug()<<"Black pawn should set black pen right?"<<!stoneController.deadShouldDrawAtBottom(i);
        if(!stoneController.deadShouldDrawAtBottom(i)){
            if(stoneController.redIsDown())
                painter.setPen(Qt::black);

            else {
                painter.setPen(Qt::red);

            }
            basicYShift = 0;
            xcount = blackDrawn % 5;
            ycount = blackDrawn / 5;
            blackDrawn++;
        }else {
            if(stoneController.redIsDown())
                painter.setPen(Qt::red);

            else {
                painter.setPen(Qt::black);

            }
            basicYShift = 5*gridwidth;
            xcount = redDrawn % 5;
            ycount = redDrawn / 5;
            redDrawn++;
        }
        QPoint center(lefttopMargin+basicXShift+xcount*gridwidth,
                      lefttopMargin+basicYShift+ycount*gridwidth);
        QPoint topleft(lefttopMargin-stoneradius+basicXShift+xcount*gridwidth,
                       lefttopMargin-stoneradius+basicYShift+ycount*gridwidth);
        QPoint btmright(lefttopMargin+stoneradius+basicXShift+xcount*gridwidth,
                        lefttopMargin+stoneradius+basicYShift+ycount*gridwidth);
        painter.setBrush(QBrush(QColor(255,255,0)));
        painter.drawEllipse(center,stoneradius,stoneradius);
        QRect rect(topleft,btmright);
        QFont font;
        font.setPointSize(20);
        painter.setFont(font);
        painter.drawText(rect,
                         stoneController.Text(stoneController.getIndexByPosInDeadVec(i)),
                         QTextOption(Qt::AlignCenter));
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
    if(canFindStoneWIthClick(closeX,closeY,pressedPoint)){
        // select the stone on position closeY*9+closeX
        if(redTurn == stoneController._s[stoneController.getIdByIndex(closeY*9+closeX)].isRed()){
            stoneController.selectThisOne(stoneController.getIdByIndex(closeY*9+closeX));
            update();
        }
    }
}

bool Board::canFindStoneWIthClick(int x, int y, QPoint pressedPoint){
    if(!stoneController.hasStoneOn(y*9+x)) return false;
    int distsqr = (intercross[y][x].x()-pressedPoint.x())*(intercross[y][x].x()-pressedPoint.x())
            +(intercross[y][x].y()-pressedPoint.y())*(intercross[y][x].y()-pressedPoint.y());
    if(distsqr<=stoneradius*stoneradius){
        return true;
    }
    return false;
}

bool Board::isOutOfBoard(int pressedx,int pressedy){
    int yInBoard = pressedy-lefttopMargin+stoneradius;
    int xInBoard = pressedx-lefttopMargin+stoneradius;
    return((yInBoard<0 || yInBoard>9*gridwidth+2*stoneradius)
    ||(xInBoard<0 || xInBoard>8*gridwidth+2*stoneradius));
}
void Board::mousePressEvent(QMouseEvent * em){
    qDebug()<<"Mouse Pressed!";
    qDebug()<<"Shoul return directly"<<stoneController.isThisSelected(-1);
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
        //qDebug()<<"isCliking itSelf?"<<stoneController.isClickingItself(x,y);
        if(stoneController.isClickingItself(stoneController._selectedId,x,y)){
            stoneController.selectThisOne(-1);
            update();
            return;
        }
        // qDebug()<<"canMoveToDest?"<<stoneController.canMoveToDest(x,y);
        // stoneController.canMoveToDest(x,y);
        if(stoneController.canMoveToDest(stoneController._selectedId,x,y)){
//            qDebug()<<"canFindStoneWIthClick?"<<canFindStoneWIthClick(x,y,pressedPoint);
            int eatenStoneID = -1;
//            int movedId = stoneController.getSelectedID();
//            int previousIndex = stoneController.
            if(canFindStoneWIthClick(x,y,pressedPoint)){
                // previous stone on this position is eaten
                eatenStoneID = stoneController.getIdByIndex(9*y+x);
                stoneController.processEatenStoneOn(x,y);
                //update();
                qDebug()<<"EatenID is "<<eatenStoneID;
            }
            stoneController.recordStep(eatenStoneID,9*y+x,stoneController._selectedId,
                                       stoneController.getIndexById(stoneController._selectedId));
            stoneController.updateSelectedStone(x,y);
            stoneController.selectThisOne(-1);
            redTurn = !redTurn;
            update();
            // we finish a full process of choosing and placing stone, now selectedId is -1 again.
        }
    }
}
void Board::conductMove(StepRecorder::Step bestMove){
    stoneController._selectedId = bestMove.movedID;
    update();
    stoneController.conductMove(bestMove);
    redTurn = !redTurn;
    update();
}
