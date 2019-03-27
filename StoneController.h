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
    StoneController(const StoneController & controller);

    void initStones(int radius);
    bool isDead(int i) const;
    int getRow(int i) const;
    int getCol(int i)const;
    QString Text(int i) const;
    
    bool canMoveToDest(int ExaminedID, int destX, int destY)const;
    bool isClickingItself(int currRef,int destx, int desty) const;
    bool hasSameColorOnDest(int ExaminedID, int destx, int desty)const;
    void processEatenStoneOn(int x, int y);
//    void processEatenStoneOn(int x, int y);

    void processEatenStoneOn(QHash<int, int> &currMap, int x, int y);
    void updateSelectedStone(int x, int y);
    void updateSelectedStone(int currStoneID,int x,int y);
    bool isThisSelected(int i)const;

    bool deadShouldDrawAtBottom(int i)const;
    void selectThisOne(int i);
    int getIndexByPosInDeadVec(int i)const;
    bool hasStoneOn(int index)const;
    int getIdByIndex(int i)const;

    bool inNinePalace(int currentRef, int destX, int destY)const;
    void recordStep(int killedID, int destIndex,int movedId,int previousIndex);
    void recordStep(StepRecorder::Step step);

    void regretStep();
    void updateSpecifiedStone(int StoneID, int destX, int destY);
    void replaceReviveStone(int killedID, int destX, int destY);

    bool isOnBottomHalfAtFirst(int i)const;
    bool redIsDown()const;

    
    QVector<int> deadStone;
    QVector<Stone> _s;
    int _selectedId;
    int getIndexById(int ID)const;
    void conductMove(StepRecorder::Step bestMove);
protected:
    bool redDown;
    QHash<int,int> stonemap;
    StepRecorder stepRecorder;

    bool KINGCanMoveTo(int currRef, int destX, int destY)const;

    // bool KINGCanMoveTo(int destX, int destY);
    bool ROOKCanMoveTo(int currRef, int destX, int destY)const;
    bool KNIGHTCanMoveTo(int currRef, int destX, int destY)const;
    bool MINISTERCanMoveTo(int currRef, int destX, int destY)const;

    bool GUARDCanMoveTo(int currRef,int destX, int destY)const;
    bool PAWNCanMoveTo(int currRef,int destX, int destY)const;
    bool CANNONCanMoveTo(int currRef,int destX, int destY)const;

    int relationBetweenStones(int ExamID,int destX, int destY)const;
    int stoneCountInTheWay(int toExaminID, int destX, int destY)const;
    bool destXYInOneLineWithExamine(int toExaminID, int destX, int destY)const;
    bool twoStonesOrPosFaceToFace(int destIndex, int examinedID)const;
    bool canKINGEatKING(int ExaminedID, int destX, int destY)const;
    bool destOnAboveHalf(int destY)const;
    bool destIsValidBlankPlace(int currRef,int destX, int destY)const;
    bool CANNONTryingToEat(int currRef,int destX,int destY)const;

private:
};

#endif // STONECONTROLLER_H
