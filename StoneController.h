#ifndef STONECONTROLLER_H
#define STONECONTROLLER_H

#include <QVector>
#include "stone.h"
#include <QHash>
#include <QString>
using namespace StoneCommonInfo;
class StoneController
{
public:
    StoneController();
    StoneController(int _selectedID);

    void initStones(int radius);
    bool isDead(int i);
    int getRow(int i);
    int getCol(int i);
    bool canMoveToDest(int destx, int desty);

    bool isClickingItself(int destx, int desty);
    bool hasSameColorOnDest(int destx, int desty);
    void processEatenStoneOn(int x, int y);
    void updateSelectedStone(int x, int y);
    bool isThisSelected(int i);
    bool deadIsRed(int i);

    void selectThisOne(int i);
    QString Text(int i);
    QVector<int> deadStone;
    QVector<Stone> _s;
    int getIndexByPosInDeadVec(int i);
    bool hasStoneOn(int index);
    int getIdByIndex(int i);
private:
    int _selectedId;
    QHash<int,int> stonemap;
    int relationBetweenStones(int ExamID,int destX, int destY);
    bool KINGCanMoveTo(int destX, int destY);
    bool ROOKCanMoveTo(int destX, int destY);
    bool KNIGHTCanMoveTo(int destX, int destY);
    bool MINISTERCanMoveTo(int destX, int destY);
    bool noOtherStoneInTheWay(int toExaminID, int destX, int destY);
    bool destXYInOneLineWithExamine(int toExaminID, int destX, int destY);
    // bool destXYInOneLineWithExamine(int destX, int destY);
    bool GUARDCanMoveTo(int destX, int destY);
    bool PAWNCanMoveTo(int destX, int destY);
    bool CANNONCanMoveTo(int destX, int destY);
    bool twoStonesOrPosFaceToFace(int destIndex, int examinedID);
    bool canKINGEatKING(int destX,int destY);
};

#endif // STONECONTROLLER_H
