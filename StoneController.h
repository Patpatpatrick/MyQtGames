#ifndef STONECONTROLLER_H
#define STONECONTROLLER_H

#include <QVector>
#include "stone.h"
#include "StepRecorder.h"
#include <QHash>
#include <QString>
using namespace StoneCommonInfo;
class StoneController
{
public:
    StoneController();
    StoneController(int _selectedID,bool redDown);

    void initStones(int radius);
    bool isDead(int i);
    int getRow(int i);
    int getCol(int i);
    bool canMoveToDest(int ExaminedID, int destX, int destY);
    bool isClickingItself(int currRef,int destx, int desty);
    bool hasSameColorOnDest(int ExaminedID, int destx, int desty);
    void processEatenStoneOn(int x, int y);
//    void processEatenStoneOn(int x, int y);

    void processEatenStoneOn(QHash<int, int> &currMap, int x, int y);
    void updateSelectedStone(int x, int y);
    void updateSelectedStone(int currStoneID,int x,int y);
    bool isThisSelected(int i);

    bool deadShouldDrawAtBottom(int i);
    void selectThisOne(int i);
    int getIndexByPosInDeadVec(int i);
    bool hasStoneOn(int index);
    int getIdByIndex(int i);

    bool inNinePalace(int currentRef, int destX, int destY);
    void recordStep(int killedID, int destIndex,int movedId,int previousIndex);
    void regretStep();
    void updateSpecifiedStone(int StoneID, int destX, int destY);
    void replaceReviveStone(int killedID, int destX, int destY);

    bool isOnBottomHalfAtFirst(int i);
    bool redIsDown();

    QString Text(int i);
    QVector<int> deadStone;
    QVector<Stone> _s;
    int _selectedId;
    int getIndexById(int ID);
    StepRecorder::Step evaluateAllSteps(StepRecorder & steps);
    int calculateScore(StepRecorder &culculatedSteps, int killedID, int destIndex, int movedID, int previousIndex);
    void conductMove(StepRecorder::Step bestMove);
protected:
    bool redDown;
    QHash<int,int> stonemap;
    StepRecorder stepRecorder;

    bool KINGCanMoveTo(int currRef, int destX, int destY);

    // bool KINGCanMoveTo(int destX, int destY);
    bool ROOKCanMoveTo(int currRef, int destX, int destY);
    bool KNIGHTCanMoveTo(int currRef, int destX, int destY);
    bool MINISTERCanMoveTo(int currRef, int destX, int destY);

    bool GUARDCanMoveTo(int currRef,int destX, int destY);
    bool PAWNCanMoveTo(int currRef,int destX, int destY);
    bool CANNONCanMoveTo(int currRef,int destX, int destY);

    int relationBetweenStones(int ExamID,int destX, int destY);
    int stoneCountInTheWay(int toExaminID, int destX, int destY);
    bool destXYInOneLineWithExamine(int toExaminID, int destX, int destY);
    bool twoStonesOrPosFaceToFace(int destIndex, int examinedID);
    bool canKINGEatKING(int ExaminedID, int destX, int destY);
    bool destOnAboveHalf(int destY);
    bool destIsValidBlankPlace(int currRef,int destX, int destY);
    bool CANNONTryingToEat(int currRef,int destX,int destY);

private:
    void genStep(StepRecorder::Step &ret, int killedID, int destIndex, int movedID, int previousIndex, int score);
    void evaluateSingleStep(StepRecorder &culculatedSteps, StepRecorder::Step &ret, int i, int row, int col, int &maxScoreStandard);
    int evaluateScore();
};

#endif // STONECONTROLLER_H
