#ifndef MANMACHINEGAME_H
#define MANMACHINEGAME_H

#include "Board.h"
class ManMachineGame : public Board
{
public:
    ManMachineGame();
    ManMachineGame(bool redDown);
    void mouseDoubleClickEvent(QMouseEvent *em);
    void mousePressEvent(QMouseEvent * em);
    void computerMove();
};

#endif // MANMACHINEGAME_H
