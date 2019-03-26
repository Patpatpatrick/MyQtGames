#include "ManMachineGame.h"
#include <QThread>
#include <QDebug>
#include <QElapsedTimer>
#include <QTime>
#include <QCoreApplication>
ManMachineGame::ManMachineGame()
{

}
ManMachineGame::ManMachineGame(bool redDown)
    :Board (redDown)
{
    regretBtnFunction();
    if(!stoneController.redIsDown()){
        // QThread::msleep(3000);
        // computer move turn;
    }
}
bool ManMachineGame::manDone(){
    return !(redTurn == stoneController.redIsDown());
}

void ManMachineGame::regretBtnFunction(){
    connect(regretBtn,&QPushButton::clicked,[=](){
//        qDebug()<<"=============subtype regret called==============";
        stoneController.regretStep();
        redTurn = !redTurn;
//        stoneController.regretStep();
        update();
    });
}

void ManMachineGame::mouseDoubleClickEvent(QMouseEvent * em){
    if(manDone()){
//        qDebug()<<"redTurn ?"<<redTurn<<"red is down"<<stoneController.redIsDown();
        return;
    }
    Board::mouseDoubleClickEvent(em);
//    qDebug()<<"After man-machine double click the selectedId is "<<stoneController._selectedId;
}
void ManMachineGame::mousePressEvent(QMouseEvent * em){
//    qDebug()<<"Call subtype mousePressEvent!! Now select Id is "<<stoneController._selectedId;
    Board::mousePressEvent(em);
    if( manDone()){
        computerMove();
    }
}
void ManMachineGame::computerMove(){
    //get all possible moves
    QTime _Timer = QTime::currentTime().addMSecs(2000);
    while( QTime::currentTime() < _Timer )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    StepRecorder steps;
    StepRecorder::Step bestMove = stoneController.evaluateAllSteps(steps);
    conductMove(bestMove);
    qDebug()<<"Computer Moves!";
}


