#include "StepRecorder.h"
#include <QDebug>
StepRecorder::StepRecorder()
{

}
StepRecorder::StepRecorder(const StepRecorder & stepRecorder){
    steps = stepRecorder.steps;
}

void StepRecorder::recordStep(int killedID,int destIndex,int movedID,int previousIndex){
    Step newstep = {killedID,destIndex,movedID,previousIndex,-100000};
    steps.push_back(newstep);
    // qDebug()<<movedID<<" moves from "<<previousIndex%9<<" "<<previousIndex/9<<" to "<<destIndex%9<< " "<< destIndex/9<< " It kills "<<killedID;
    // qDebug()<<"After recording step, Steps' size is"<<steps.size();
}
void StepRecorder::appendStep(Step & step){
    steps.push_back(step);
}

StepRecorder::Step StepRecorder::getFirstStepHelper(){
    Step ret;
    if(!steps.isEmpty()){
        ret = steps.first();
    }
//    qDebug()<<"After poping the last step, Steps' size is"<<steps.size();
//    qDebug()<<"ret's killedID is "<<ret.killedID;
//    qDebug()<<"ret's movedID is "<<ret.movedID;
//    qDebug()<<"ret's previousIndex is "<<ret.previousIndex;
//    qDebug()<<"ret's destIndex is "<<ret.destIndex;
    return ret;
}

StepRecorder::Step StepRecorder::getAndRemoveLastStep(){
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

