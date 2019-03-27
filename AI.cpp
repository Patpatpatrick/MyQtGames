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
        for(int row = 0;row<=9;row++){
            for(int col = 0;col <=8;col++){
                if(controller._s[i].isDead())
                    continue;
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
    int max = -100000;
    int currentScore = -100000;
    StepRecorder::Step ret = {-1,-1,-1,-1,-100000};
    for (int i = 0; i < steps.steps.size(); i++) {
        currentScore = evaluateSingleStep(steps.steps[i],controller);
        if(max < currentScore){
            max = currentScore;
            ret = steps.steps[i];
        }
    }
    return ret;
}

int AI::evaluateSingleStep(StepRecorder::Step &step,StoneController& controller){
    int score;
    if(step.killedID != -1){
        int killedIndex = step.destIndex;
        controller.processEatenStoneOn(killedIndex%9,killedIndex/9);
        controller.recordStep(step);
        controller.updateSelectedStone(step.movedID,killedIndex%9,killedIndex/9);
        // calculate score
        score = calculateScore(step,controller);
        controller.regretStep();
    }else {
        controller.recordStep(step);
        controller.updateSelectedStone(step.movedID,step.destIndex%9,step.destIndex/9);
        // calculate score
        score = calculateScore(step,controller);
        controller.regretStep();
    }
    return score;
}
int AI::calculateScore(StepRecorder::Step & step,StoneController& controller){
    // calculate the total stone power of id <=15 as sum1
    // calculate the total stone power of id > 15 as sum2
    // return sum1-sum2
    int sum1 = 0;
    int sum2 = 0;
    for (int i = 0; i<=15;i++) {
        sum1+= controller._s[i].isDead() ? 0 : StoneCommonInfo::chessPower[controller._s[i]._type-1];
        sum2+= controller._s[i+16].isDead()? 0: StoneCommonInfo::chessPower[controller._s[i+16]._type-1];
    }
    step.stepResultScore = sum1-sum2;
    return sum1-sum2;
}


