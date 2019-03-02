#ifndef BOARD_H
#define BOARD_H
#include <QWidget>
#include <QPoint>
#include "StoneController.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    //explicit Board(QWidget *parent = nullptr);
    explicit Board(QWidget *parent = nullptr,int selectedID = -1);

    void paintEvent(QPaintEvent * ev);
    void paintGrid(QPainter & painterptr);
    void paintStones(QPainter & painterptr);
    void mousePressEvent(QMouseEvent * em);
    void mouseReleaseEvent(QMouseEvent *er);
    void drawLiveStones(QPainter & painter);
    void drawDeadStones(QPainter & painter);

    bool canFindStoneWIthClick(int x, int y, QPoint pressedPoint);
    void mouseDoubleClickEvent(QMouseEvent *em);
    int findClosestIndex(int pressedx, int pressedy);
    bool isOutOfBoard(int pressedx, int pressedy);
    void initInterCrosses();

    QVector<QVector<QPoint>> intercross;
    const static int gridwidth = 40;
    const static int lefttopMargin = 60;
    const static int stoneradius = 20;
signals:

public slots:

private:
    StoneController stoneController;
};

#endif // BOARD_H
