#include "Board.h"
#include <QPainter>
#include <QRect>
#include <QMouseEvent>
#include <QPoint>
#include <QDebug>
Board::Board(QWidget *parent) : QWidget(parent)
{
    gridwidth = 40;
    lefttopMargin = 60;
    stoneradius = 19;
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
    for(int i = 0;i<32;i++){
        Stone s;
        if(_s.size() <= 8){
            s.setinfo(stoneradius,0,j,i,false,false,typeseries[i]);
            tempx = j;
            j++;
            if(j>8) j=1;
        } else if (_s.size() <= 10){
            s.setinfo(stoneradius,2,j,i,false,false,typeseries[i]);
            tempx = j;
            tempy = 2;
            j+=6;
            if(j>7) j = 0;
        } else if (_s.size() <= 15) {
            s.setinfo(stoneradius,3,j,i,false,false,typeseries[i]);
            tempx = j;
            tempy = 3;
            j+=2;
            if(j>8) j = 0;
        } else if (_s.size() <= 20) {
            s.setinfo(stoneradius,6,j,i,false,true,typeseries[i]);
            tempx = j;
            tempy = 6;
            j+=2;
            if(j>8) j = 1;
        } else if (_s.size() <= 22) {
            s.setinfo(stoneradius,7,j,i,false,true,typeseries[i]);
            tempx = j;
            tempy = 7;
            j+=6;
            if(j>7) j = 0;
        } else if (_s.size() <= 31) {
            s.setinfo(stoneradius,9,j,i,false,true,typeseries[i]);
            tempx = j;
            tempy = 9;
            j++;
        }
        _s.push_back(s);
        stonemap[tempy*8+tempx] = i;
       // stonemap.insert(tempy*8+tempx,_s[i]);
    }



    //qDebug()<<"stonemap[0] in initStones is "<<stonemap[0].getcol()<<"  "<<stonemap[0].getrow();
}
void Board::paintStones(QPainter & painter){
    qDebug()<<"Starts Stones Painting";
    for (int i = 0;i<32;i++) {
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
        painter.setBrush(QBrush(QColor(255,255,0)));
        painter.drawEllipse(center,stoneradius,stoneradius);
        QRect rect(topleft,btmright);
        QFont font;
        font.setPointSize(20);
        painter.setFont(font);
        painter.drawText(rect,_s[i].Text(),QTextOption(Qt::AlignCenter));
    }

    //qDebug()<<"stonemap[0] in paintStones is "<<stonemap[0].getcol()<<"  "<<stonemap[0].getrow();
}
void Board::mousePressEvent(QMouseEvent * em){
    //qDebug()<<"stonemap[0] in mousePressEvent is "<<stonemap[0].getcol()<<"  "<<stonemap[0].getrow();
    QPoint pressedPoint = em->pos();
    //Stone s1= stonemap[0];
    int yInBoard = pressedPoint.y()-lefttopMargin;
    int xInBoard = pressedPoint.x()-lefttopMargin;
    if(yInBoard<-stoneradius || yInBoard>9*gridwidth+stoneradius){
        return;
    }
    if(xInBoard<-stoneradius || xInBoard>8*gridwidth+stoneradius){
        return;
    }
    int yLeftOver = yInBoard%gridwidth>=0?yInBoard%gridwidth:gridwidth+yInBoard%gridwidth;
    qDebug() << "yLeftOver is " << yLeftOver;
    int xLeftOver = xInBoard%gridwidth>=0?xInBoard%gridwidth:gridwidth+xInBoard%gridwidth;
    qDebug() << "xLeftOver is " << xLeftOver;
    if(yLeftOver<=stoneradius){
        if(xLeftOver<=stoneradius){
            int yLowerB = yInBoard>0?yInBoard/gridwidth:-1;
            int xLowerB = xInBoard>0?xInBoard/gridwidth:-1;
            if(findStone(xLowerB,yLowerB,pressedPoint)){
                Stone selectedStone = _s[stonemap[yLowerB*8+xLowerB]];
                qDebug()<<"Stone info"<<selectedStone.getcol()<<" " <<selectedStone.getrow();
            }
        }else if (xLeftOver>=gridwidth-stoneradius) {
            int yLowerB = yInBoard>0?yInBoard/gridwidth:-1;
            int xUpperB = xInBoard>0?xInBoard/gridwidth + 1:0;
            if(findStone(xUpperB,yLowerB,pressedPoint)){
                Stone selectedStone = _s[stonemap[yLowerB*8+xUpperB]];
                qDebug()<<"Stone info"<<selectedStone.getcol()<<" " <<selectedStone.getrow();
            }
        }
    }else if (yLeftOver>=gridwidth-stoneradius) {
        if(xLeftOver<=stoneradius){
            int yUpperB = yInBoard>0?yInBoard/gridwidth+1:0;
            int xLowerB = xInBoard>0?xInBoard/gridwidth:-1;
            if(findStone(xLowerB,yUpperB,pressedPoint)){
                Stone selectedStone = _s[stonemap[yUpperB*8+xLowerB]];
                qDebug()<<"Stone info"<<selectedStone.getcol()<<" " <<selectedStone.getrow();
            }
        }else if (xLeftOver>=gridwidth-stoneradius) {
            int yUpperB = yInBoard>0?yInBoard/gridwidth + 1:0;
            int xUpperB = xInBoard>0?xInBoard/gridwidth + 1:0;
            if(findStone(xUpperB,yUpperB,pressedPoint)){
               Stone selectedStone = _s[stonemap[yUpperB*8+xUpperB]];
               qDebug()<<"Stone info"<<selectedStone.getcol()<<" " <<selectedStone.getrow();
            }
        }
    }
}
bool Board::findStone(int x, int y, QPoint pressedPoint){
    int distsqr = (intercross[y][x].x()-pressedPoint.x())*(intercross[y][x].x()-pressedPoint.x())
            +(intercross[y][x].y()-pressedPoint.y())*(intercross[y][x].y()-pressedPoint.y());
    if(distsqr<=stoneradius*stoneradius){
        if(stonemap.contains(y*8+x)){
            return true;
        }
    }
    return false;
}
void Board::mouseReleaseEvent(QMouseEvent *er){

}
