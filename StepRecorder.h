#ifndef STEPRECORDER_H
#define STEPRECORDER_H
#include <QVector>


class StepRecorder
{
public:
    StepRecorder();
    struct Step{
        int killedID;
        int destIndex;
        int movedID;
        int previousIndex;
    };
    QVector<Step> steps;
    void recordStep(int killedID,int destIndex,int movedID,int previousIndex);
    Step getLastStep();
    bool isEmpty();
};

#endif // STEPRECORDER_H
