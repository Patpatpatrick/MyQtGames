#include "StepRecorder.h"
#include <QDebug>
StepRecorder::StepRecorder()
{

}

void StepRecorder::recordStep(int killedID,int destIndex,int movedID,int previousIndex){
    Step newstep = {killedID,destIndex,movedID,previousIndex};
    steps.push_back(newstep);
    qDebug()<<"After recording step, Steps' size is"<<steps.size();
}

StepRecorder::Step StepRecorder::getLastStep(){
    Step ret;
    if(!steps.isEmpty()){
        ret = steps.last();
        steps.pop_back();
    }
    qDebug()<<"After poping the last step, Steps' size is"<<steps.size();
    qDebug()<<"ret's killedID is "<<ret.killedID;
    qDebug()<<"ret's movedID is "<<ret.movedID;
    qDebug()<<"ret's previousIndex is "<<ret.previousIndex;
    qDebug()<<"ret's destIndex is "<<ret.destIndex;
    return ret;
}
bool StepRecorder::isEmpty(){
    return steps.isEmpty();
}

