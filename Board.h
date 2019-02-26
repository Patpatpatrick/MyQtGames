#ifndef BOARD_H
#define BOARD_H
#include <QVector>
#include <QWidget>
#include <QPoint>
#include <QHash>
#include "stone.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent * ev);
    void paintGrid(QPainter * painterptr);
    void paintStones(QPainter * painterptr);
    void mousePressEvent(QMouseEvent * em);
    void mouseReleaseEvent(QMouseEvent *er);
signals:

public slots:


private:
    QVector<QVector<QPoint>> intercross;
    QVector<Stone> _s;
    int gridwidth;
    QHash<int,Stone> stonemap;
};

#endif // BOARD_H
