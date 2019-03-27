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

    int evaluateSingleStep(StepRecorder::Step & step,StoneController & controller);

    int calculateScore(StepRecorder::Step & step,StoneController& controller);

    StepRecorder::Step genStep(int killedID, int destIndex, int movedID, int previousIndex, int score);

};

#endif // AI_H
