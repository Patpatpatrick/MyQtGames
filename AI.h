#ifndef AI_H
#define AI_H

#include "StepRecorder.h"
#include "StoneController.h"
class AI
{

public:

    AI();

    StepRecorder::Step getBestMove(const StoneController & controller);

private:
    StepRecorder bestMoves;

    void generateAllPossibleSteps(StepRecorder &steps,StoneController & controller);

    StepRecorder::Step evaluateAllStepsGetBest(StepRecorder & steps,StoneController controller);

    int evaluateSingleStepByTryingToMoveAndRegret(StepRecorder::Step & step,StoneController & controller);

    int getMinScoreResultByUserAfterAIFakeMove(StoneController& controller);

    StepRecorder::Step genStep(int killedID, int destIndex, int movedID, int previousIndex, int score);

    void generateAllPossibleStepsOfUser(StepRecorder &steps, StoneController &controller);

    int evaluateAllUserStepsGetWorstScenToAI(StepRecorder & steps,StoneController & controller);
    int evaluateSingleStepOfUser(StepRecorder::Step &step, StoneController &controller);


};

#endif // AI_H
