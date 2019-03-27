#ifndef MANMACHINEGAME_H
#define MANMACHINEGAME_H

#include "BasicGame.h"
#include "AI.h"
class ManMachineGame : public BasicGame
{
public:
    ManMachineGame();
    ManMachineGame(bool redDown);
    void mouseDoubleClickEvent(QMouseEvent *em) override;
    void mousePressEvent(QMouseEvent * em) override;
    void computerMove();
    void regretBtnFunction() override;
    bool manDone();
private:
    AI ai;
};

#endif // MANMACHINEGAME_H
