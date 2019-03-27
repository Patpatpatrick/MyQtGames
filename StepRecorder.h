#ifndef STEPRECORDER_H
#define STEPRECORDER_H
#include <QVector>


class StepRecorder
{
public:
    StepRecorder();
    StepRecorder(const StepRecorder & stepRecorder);
    struct Step{
        int killedID;
        int destIndex;
        int movedID;
        int previousIndex;
        int stepResultScore;
    };
    QVector<Step> steps;
    void recordStep(int killedID,int destIndex,int movedID,int previousIndex);
    void appendStep(Step & step);
    Step getAndRemoveLastStep();
    bool isEmpty();
    StepRecorder::Step getFirstStepHelper();
};

#endif // STEPRECORDER_H
