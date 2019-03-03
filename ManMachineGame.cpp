#include "ManMachineGame.h"
#include <QThread>
#include <QDebug>
#include <QElapsedTimer>
#include <QTime>
ManMachineGame::ManMachineGame()
{

}
ManMachineGame::ManMachineGame(bool redDown)
    :Board (redDown)
{
    if(!stoneController.redIsDown()){
        // QThread::msleep(3000);
        // computer move turn;
    }
}
void ManMachineGame::mouseDoubleClickEvent(QMouseEvent * em){
    if(redTurn != stoneController.redIsDown()){
        return;
    }
    Board::mouseDoubleClickEvent(em);
}
void ManMachineGame::mousePressEvent(QMouseEvent * em){
    Board::mousePressEvent(em);
    computerMove();
}
void ManMachineGame::computerMove(){
    //get all possible moves
    StepRecorder steps;
    stoneController.getAllPossibleMoves(steps);
    qDebug()<<"Computer has moved!!";
}


