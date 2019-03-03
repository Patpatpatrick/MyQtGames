#ifndef BOARD_H
#define BOARD_H
#include <QWidget>
#include <QPoint>
#include <QPushButton>
#include "StoneController.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    //explicit Board(QWidget *parent = nullptr);
    explicit Board(bool redDown = true,QWidget *parent = nullptr,int selectedID = -1);
    void paintEvent(QPaintEvent * ev);
    void paintGrid(QPainter & painterptr);
    void paintStones(QPainter & painterptr);
    void mousePressEvent(QMouseEvent * em);
    void drawLiveStones(QPainter & painter);
    void drawDeadStones(QPainter & painter);

    // 9*y+x is a intercross on the board, when the pressed point is with a circle of radius of 20 of the
    // intercross, and there is a stone on index 9*y+x, then return true
    bool canFindStoneWIthClick(int x, int y, QPoint pressedPoint);
    void mouseDoubleClickEvent(QMouseEvent *em);
    int findClosestIndex(int pressedx, int pressedy);
    bool isOutOfBoard(int pressedx, int pressedy);
    void initInterCrosses();

    QVector<QVector<QPoint>> intercross;
    const static int gridwidth = 40;
    const static int lefttopMargin = 60;
    const static int stoneradius = 20;
    void conductMove(StepRecorder::Step bestMove);
signals:

public slots:

protected:
    bool redTurn;
    StoneController stoneController;
    QPushButton * regretBtn;
    virtual void regretBtnFunction();
private:
};

#endif // BOARD_H
