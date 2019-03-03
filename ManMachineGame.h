#ifndef MANMACHINEGAME_H
#define MANMACHINEGAME_H

#include "Board.h"
class ManMachineGame : public Board
{
public:
    ManMachineGame();
    ManMachineGame(bool redDown);
    void mouseDoubleClickEvent(QMouseEvent *em) override;
    void mousePressEvent(QMouseEvent * em) override;
    void computerMove();
    void regretBtnFunction() override;
    bool manDone();

};

#endif // MANMACHINEGAME_H
