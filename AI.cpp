#include "AI.h"

AI::AI()
{

}
StepRecorder::Step AI::getBestMove(const StoneController & controller){
    StoneController copyController(controller);
    StepRecorder::Step ret;
    StepRecorder steps;
    generateAllPossibleSteps(steps,copyController);
    // after this function steps
    ret = evaluateAllStepsGetBest(steps,copyController);
//    qDebug()<<calculatedSteps.steps.size();
//    ret = calculatedSteps.getFirstStepHelper();
    return ret;
}
void AI::generateAllPossibleSteps(StepRecorder & steps, StoneController & controller){
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
}

StepRecorder::Step AI::evaluateAllStepsGetBest(StepRecorder & steps,StoneController controller){
    // by get a highest score
    int max = -100000;
    int currentScore = -100000;
    StepRecorder::Step ret = {-1,-1,-1,-1,-100000};
    for (int i = 0; i < steps.steps.size(); i++) {
        currentScore = evaluateSingleStepByTryingToMoveAndRegret(steps.steps[i],controller);
        if(max < currentScore){
            max = currentScore;
            ret = steps.steps[i];
        }
    }
    return ret;
}

int AI::evaluateSingleStepByTryingToMoveAndRegret(StepRecorder::Step &step,StoneController& controller){
    // we still want to maximize the score here;
    int score;
    if(step.killedID != -1){
        int killedIndex = step.destIndex;
        controller.processEatenStoneOn(killedIndex%9,killedIndex/9);
        controller.recordStep(step);
        controller.updateSelectedStone(step.movedID,killedIndex%9,killedIndex/9);
        // calculate score
        score = getMinScoreResultByUserAfterAIFakeMove(controller);
        controller.regretStep();
    }else {
        controller.recordStep(step);
        controller.updateSelectedStone(step.movedID,step.destIndex%9,step.destIndex/9);
        // calculate score
        score = getMinScoreResultByUserAfterAIFakeMove(controller);
        controller.regretStep();
    }
    return score;
}
int AI::getMinScoreResultByUserAfterAIFakeMove(StoneController& controller){
    // calculate the total stone power of id <=15 as sum1
    // calculate the total stone power of id > 15 as sum2
    // return sum1-sum2

    StepRecorder toRecordUserSteps;
    generateAllPossibleStepsOfUser(toRecordUserSteps,controller);
    int score = evaluateAllUserStepsGetWorstScenToAI(toRecordUserSteps,controller);
    return score;

}

void AI::generateAllPossibleStepsOfUser(StepRecorder & steps, StoneController & controller){
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
}

int AI::evaluateAllUserStepsGetWorstScenToAI(StepRecorder & steps, StoneController & controller){
    //under a computer move, evaluate all user steps, return a low
    int lowest = 100000;
    int score;
    for (int i = 0;i<steps.steps.size();i++) {
        score = evaluateSingleStepOfUser(steps.steps[i],controller);
        if(score < lowest){
            lowest = score;
        }
    }
    return lowest;
}

int AI::evaluateSingleStepOfUser(StepRecorder::Step & step, StoneController & controller){
    int score;
    if(step.killedID != -1){
        int killedIndex = step.destIndex;
        controller.processEatenStoneOn(killedIndex%9,killedIndex/9);
        controller.recordStep(step);
        controller.updateSelectedStone(step.movedID,killedIndex%9,killedIndex/9);
        int sum1 = 0;
        int sum2 = 0;
        for (int i = 0; i<=15;i++) {
            sum1+= controller._s[i].isDead() ? 0 : StoneCommonInfo::chessPower[controller._s[i]._type-1];
            sum2+= controller._s[i+16].isDead()? 0: StoneCommonInfo::chessPower[controller._s[i+16]._type-1];
        }
        step.stepResultScore = sum2-sum1;
        score = sum1-sum2;
        controller.regretStep();
    }else {
        controller.recordStep(step);
        controller.updateSelectedStone(step.movedID,step.destIndex%9,step.destIndex/9);
        // calculate score
        int sum1 = 0;
        int sum2 = 0;
        for (int i = 0; i<=15;i++) {
            sum1+= controller._s[i].isDead() ? 0 : StoneCommonInfo::chessPower[controller._s[i]._type-1];
            sum2+= controller._s[i+16].isDead()? 0: StoneCommonInfo::chessPower[controller._s[i+16]._type-1];
        }
        step.stepResultScore = sum2-sum1;
        score = sum1-sum2;
        controller.regretStep();
    }
    return score;
}
