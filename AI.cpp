#include "AI.h"
#include <QDebug>
AI::AI()
{
    _level = 3;
}
StepRecorder::Step AI::getBestMove(const StoneController & controller){
    StoneController copyController(controller);
    StepRecorder::Step ret;
    // after this function steps
    ret = getBestMoveWithSafeCopy(copyController);
//    qDebug()<<calculatedSteps.steps.size();
//    ret = calculatedSteps.getFirstStepHelper();
    return ret;
}
StepRecorder AI::AIgenerateAllPossibleSteps(StoneController & controller){
    StepRecorder steps;
    for (int i = 0;i<=15;i++) {
        if(controller._s[i].isDead())
            continue;
        for(int row = 0;row<=9;row++){
            for(int col = 0;col <=8;col++){
                if(controller.isClickingItself(i,col,row))
                    continue;
                if(controller.canMoveToDest(i,col,row)){
                    int killedId = -1;
                    if(controller.hasStoneOn(row*9+col)){
                        killedId = controller.getIdByIndex(row*9+col);
                    }
                    // StepRecorder::Step newstep = {killedId,row*9+col,i,controller.getIndexById(i),maxScore};
                    steps.recordStep(killedId,row*9+col,i,controller.getIndexById(i));
                }
            }
        }
    }
    return steps;
}

StepRecorder::Step AI::getBestMoveWithSafeCopy(StoneController & controller){
    StepRecorder steps = AIgenerateAllPossibleSteps(controller);
    // by get a highest score
    int maxInAllMinScore = -100000;
    int topStepScore = -100000;
    StepRecorder::Step ret = {-1,-1,-1,-1};
    for (int i = 0; i < steps.steps.size(); i++) {
        topStepScore = trueIsMin(steps.steps[i],controller,_level,true);
        qDebug()<<topStepScore;
        if(maxInAllMinScore < topStepScore){
            maxInAllMinScore = topStepScore;
            ret = steps.steps[i];
        }
    }
    return ret;
}

int AI::trueIsMin(StepRecorder::Step &step,StoneController& controller,int level,bool min){
    // we still want to maximize the score here;
    int score;
    if(step.killedID != -1){
        int killedIndex = step.destIndex;
        controller.processEatenStoneOn(killedIndex%9,killedIndex/9);
    }
    controller.recordStep(step);
    controller.updateSelectedStone(step.movedID,step.destIndex%9,step.destIndex/9);
    if(level == 0){
        score = calculateScore(controller);
    }else if(min){
        score = nextLevelMin(controller,level);
    }else{
        score = nextLevelBest(controller,level);
    }
    controller.regretStep();
    return score;
}

StepRecorder AI::generateAllPossibleStepsOfUser(StoneController & controller){
    StepRecorder steps;
    for (int i = 16;i<=31;i++) {
        if(controller._s[i].isDead())
            continue;
        for(int row = 0;row<=9;row++){
            for(int col = 0;col <=8;col++){
                if(controller.isClickingItself(i,col,row))
                    continue;
                if(controller.canMoveToDest(i,col,row)){
                    int killedId = -1;
                    if(controller.hasStoneOn(row*9+col)){
                        killedId = controller.getIdByIndex(row*9+col);
                    }
                    // StepRecorder::Step newstep = {killedId,row*9+col,i,controller.getIndexById(i),maxScore};
                    steps.recordStep(killedId,row*9+col,i,controller.getIndexById(i));
                }
            }
        }
    }
    return steps;
}

int AI::nextLevelBest(StoneController & controller,int level){
    StepRecorder steps = AIgenerateAllPossibleSteps(controller);
    //under a computer move, evaluate all user steps, return a low
    int max = -100000;
    int score;
    for (int i = 0;i<steps.steps.size();i++) {
        score = trueIsMin(steps.steps[i],controller,level-1,true);
        if(score > max){
            max = score;
        }
    }
    return max;
}

int AI::nextLevelMin(StoneController & controller,int level){
    StepRecorder steps = generateAllPossibleStepsOfUser(controller);
    //under a computer move, evaluate all user steps, return a low
    int lowest = 100000;
    int score;
    for (int i = 0;i<steps.steps.size();i++) {
        score = trueIsMin(steps.steps[i],controller,level-1,false);
        if(score < lowest){
            lowest = score;
        }

    }
    return lowest;
}

int AI::calculateScore(StoneController & controller){

    int sum1 = 0;
    int sum2 = 0;
    for (int i = 0; i<=15;i++) {
        sum1+= controller._s[i].isDead() ? 0 : StoneCommonInfo::chessPower[controller._s[i]._type-1];
        sum2+= controller._s[i+16].isDead()? 0: StoneCommonInfo::chessPower[controller._s[i+16]._type-1];
    }
    // step.stepResultScore = sum2-sum1;
//    if(sum1-sum2 > 0)
//        qDebug()<<sum1-sum2;
    return sum1-sum2;
}



