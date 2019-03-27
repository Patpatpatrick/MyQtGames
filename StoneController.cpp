#include "StoneController.h"
#include <QElapsedTimer>
#include <QDebug>
StoneController::StoneController(){
    _selectedId = -1;
}
StoneController::StoneController(int ID,bool redDown)
    :_selectedId(ID),
     redDown(redDown)
{
}

StoneController::StoneController(const StoneController & controller){
    deadStone = controller.deadStone;
    _s = controller._s;
    _selectedId = controller._selectedId;
    redDown = controller.redDown;
    stonemap = controller.stonemap;
    stepRecorder = controller.stepRecorder;
}

bool StoneController::isOnBottomHalfAtFirst(int i) const {
    return _s[i].isRed() == redDown;
}
void StoneController::initStones(int stoneradius){
    int j = 0;
    int tempx = 0;
    int tempy = 0;
    int typeseries[32] = {2,3,4,6,1,6,4,3,2,5,5,7,7,7,7,7,7,7,7,7,7,5,5,2,3,4,6,1,6,4,3,2};
    for(int stoneIndex = 0;stoneIndex<32;stoneIndex++){
        Stone s;
        if(_s.size() <= 8){
            s.setInfo(stoneradius,0,j,stoneIndex,false,!redDown,typeseries[stoneIndex]);
            tempx = j;
            j++;
            if(j>8) j=1;
        } else if (_s.size() <= 10){
            s.setInfo(stoneradius,2,j,stoneIndex,false,!redDown,typeseries[stoneIndex]);
            tempx = j;
            tempy = 2;
            j+=6;
            if(j>7) j = 0;
        } else if (_s.size() <= 15) {
            s.setInfo(stoneradius,3,j,stoneIndex,false,!redDown,typeseries[stoneIndex]);
            tempx = j;
            tempy = 3;
            j+=2;
            if(j>8) j = 0;
        } else if (_s.size() <= 20) {
            s.setInfo(stoneradius,6,j,stoneIndex,false,redDown,typeseries[stoneIndex]);
            tempx = j;
            tempy = 6;
            j+=2;
            if(j>8) j = 1;
        } else if (_s.size() <= 22) {
            s.setInfo(stoneradius,7,j,stoneIndex,false,redDown,typeseries[stoneIndex]);
            tempx = j;
            tempy = 7;
            j+=6;
            if(j>7) j = 0;
        } else if (_s.size() <= 31) {
            s.setInfo(stoneradius,9,j,stoneIndex,false,redDown,typeseries[stoneIndex]);
            tempx = j;
            tempy = 9;
            j++;
        }
        _s.push_back(s);
        stonemap[tempy*9+tempx] = stoneIndex;
    }
}
bool StoneController::isDead(int i) const {
    return _s[i].isDead();
}
int StoneController::getRow(int i) const {
    return _s[i].getRow();
}
int StoneController::getCol(int i) const {
    return _s[i].getCol();
}
QString StoneController::Text(int i) const {
    return _s[i].Text();
}
bool StoneController::deadShouldDrawAtBottom(int i) const {
    // qDebug()<<"Black pawn is red?"<<_s[deadStone[i]].isRed();
    return _s[deadStone[i]].isRed() == redDown;
}
bool StoneController::redIsDown() const {
    return redDown;
}
int StoneController::getIndexByPosInDeadVec(int i) const {
    return _s[deadStone[i]].getID();
}
int StoneController::getIdByIndex(int i) const {
    // qDebug()<<"getIdByIndex function. Size"<<stonemap.size();
    return stonemap[i];
}
bool StoneController::hasStoneOn(int index) const {
    // qDebug()<<"hasStoneOn function. Size"<<stonemap.size();
    return stonemap.contains(index);
}
void StoneController::processEatenStoneOn(int posX, int posY) {
    qDebug()<<"processEatenStoneOn function. Size"<<stonemap.size();
    if(stonemap.contains(posY*9+posX)){
        _s[stonemap[posY*9+posX]].setDead();
        deadStone.push_back(stonemap[posY*9+posX]);
        // remove the eaten stone out of the stonemap
        stonemap.remove(posY*9+posX);
    }
}
void StoneController::updateSelectedStone(int x, int y){
    // qDebug()<<"updateSelectedStone function 1 . Size"<<stonemap.size();

    // To update the postion of the moved stone, first take it out of the stonemap from where it used to be
    stonemap.remove(_s[_selectedId].getRow()*9+_s[_selectedId].getCol());
    // set new col and row with respect to this moved stone,

    // qDebug()<<"updateSelectedStone function 2 . Size"<<stonemap.size();


    _s[_selectedId].setRow(y);
    _s[_selectedId].setCol(x);
    // update its record in the stone map

    // qDebug()<<"updateSelectedStone function 3 . Size"<<stonemap.size();

    stonemap[y*9+x] = _selectedId;
}
void StoneController::updateSelectedStone(int currStoneID,int x,int y){
    // qDebug()<<"updateSelectedStone function 1 . Size"<<stonemap.size();

    // To update the postion of the moved stone, first take it out of the stonemap from where it used to be
    stonemap.remove(_s[currStoneID].getRow()*9+_s[currStoneID].getCol());
    // set new col and row with respect to this moved stone,

    // qDebug()<<"updateSelectedStone function 2 . Size"<<stonemap.size();


    _s[currStoneID].setRow(y);
    _s[currStoneID].setCol(x);
    // update its record in the stone map

    qDebug()<<"updateSelectedStone function 3 . Size"<<stonemap.size();

    stonemap[y*9+x] = currStoneID;
}
void StoneController::conductMove(StepRecorder::Step bestMove){
    if(bestMove.killedID != -1){
        // previous stone on this position is eaten
        qDebug()<<"Trying to eat stone on col  "<<bestMove.destIndex%9<<" row "<<bestMove.destIndex/9;
        processEatenStoneOn(bestMove.destIndex%9,bestMove.destIndex/9);
    }
    recordStep(bestMove.killedID,bestMove.destIndex,bestMove.movedID,bestMove.previousIndex);
    updateSelectedStone(bestMove.destIndex%9,bestMove.destIndex/9);
    selectThisOne(-1);
}
bool StoneController::isThisSelected(int i) const {
    return _selectedId == i;
}
void StoneController::selectThisOne(int i){
    qDebug()<<"Successfully select!";
    _selectedId = i;
}
bool StoneController::canMoveToDest(int currRef, int destX, int destY) const {
    if (hasSameColorOnDest(currRef,destX,destY)){
        return false;
    } else {
        switch (_s[currRef].getType()) {
            case StoneCommonInfo::StoneType::KING :
                return KINGCanMoveTo(currRef,destX,destY);

            case StoneCommonInfo::StoneType::ROOK :
                return ROOKCanMoveTo(currRef,destX,destY);

            case StoneCommonInfo::StoneType::KNIGHT :
                return KNIGHTCanMoveTo(currRef,destX,destY);

            case StoneCommonInfo::StoneType::MINISTER :
                return MINISTERCanMoveTo(currRef,destX,destY);

            case StoneCommonInfo::StoneType::CANNON :
                return CANNONCanMoveTo(currRef,destX,destY);

            case StoneCommonInfo::StoneType::GUARD :
                return GUARDCanMoveTo(currRef,destX,destY);

            case StoneCommonInfo::StoneType::PAWN :
                return PAWNCanMoveTo(currRef,destX,destY);
        }
    }
}
bool StoneController::canKINGEatKING(int currentRef, int destX,int destY) const {
    if(_s[31-currentRef].getCol()==destX&&_s[31-currentRef].getRow()==destY){
        if(twoStonesOrPosFaceToFace(9*destY+destX,currentRef))
            return true;
    }
    return false;
}
bool StoneController::KINGCanMoveTo(int currentRef, int destX,int destY) const {
    if(canKINGEatKING(currentRef,destX,destY)){
        return true;
    }
    if(!inNinePalace(currentRef,destX,destY))
        return false;
    int row = _s[currentRef].getRow();
    int col = _s[currentRef].getCol();
    if(twoStonesOrPosFaceToFace(destY*9+destX,31-currentRef)){
        qDebug()<<"No you shouldn't move like this";
        return false;
    }
    return (destY == row && destX - col == 1)
            || (destY == row && destX - col == -1)
            || (destX == col && destY - row == 1)
            || (destX == col && destY - row == -1);
}
bool StoneController::inNinePalace(int currentRef,int destX,int destY) const {
    if(isOnBottomHalfAtFirst(currentRef)){
        qDebug()<<"OutOf 9 palace?"<<!(3<=destX && 5>=destX && 7<=destY && 9>=destY);
        if(!(3<=destX && 5>=destX && 7<=destY && 9>=destY))
            return false;
    }
    if(!isOnBottomHalfAtFirst(currentRef)){
        if(!(3<=destX && 5>=destX && 0<=destY && 2>=destY))
            return false;
    }
    return true;
}
bool StoneController::twoStonesOrPosFaceToFace(int destIndex,int examinedID) const {
    qDebug()<<"No other stone in the way?"<<stoneCountInTheWay(examinedID,destIndex%9,destIndex/9);
    if(stoneCountInTheWay(examinedID,destIndex%9,destIndex/9)==0){
        return (destIndex%9)==_s[examinedID].getCol();
    }
    return false;
}
bool StoneController::ROOKCanMoveTo(int currRef,int destX,int destY) const {
    if(destXYInOneLineWithExamine(currRef,destX,destY)){
        if(stoneCountInTheWay(currRef,destX,destY)==0){
            return true;
        }
    }
    return false;
}
bool StoneController::destXYInOneLineWithExamine(int currRef,int destX, int destY) const {
    return ( _s[currRef].getCol()==destX)!=(_s[currRef].getRow()==destY);
}
int StoneController::stoneCountInTheWay(int currRef,int destX,int destY) const {
//    qDebug()<<"TOExamined Stone is in one line with "<<destX<<" "<<destY<<"?"<<destXYInOneLineWithExamine(toExaminID,destX,destY);
    int rev = 0;
    if(!destXYInOneLineWithExamine(currRef,destX,destY))
        return false;
    if(relationBetweenStones(currRef,destX,destY)%10==0){
        //implies x coordinates are the same, two stones are in one col
        int topY = destY>_s[currRef].getRow()?destY:_s[currRef].getRow();
        int bottomY = destY>_s[currRef].getRow()?_s[currRef].getRow():destY;
        for(int i = bottomY+1; i<topY; i++){
            if(stonemap.contains(9*i+destX)){
                rev++;
            }
        }

    } else {
        //implies y are the same, two stones are in one row
        int topX = destX>_s[currRef].getCol()?destX:_s[currRef].getCol();
        int bottomX = destX>_s[currRef].getCol()?_s[currRef].getCol():destX;
        for(int i = bottomX+1; i < topX; i++){
            if(stonemap.contains(9*destY+i)){
                rev++;
            }
        }
    }
    return rev;
}
bool StoneController::KNIGHTCanMoveTo(int currRef,int destX,int destY) const {
    int r = relationBetweenStones(currRef,destX, destY);
    if(r != 12 && r != 21)
        return false;
    if(r == 12){
        if(destX>_s[currRef].getCol()
                &&stonemap.contains(_s[currRef].getRow()*9+_s[currRef].getCol()+1))
            return false;
        if(destX<_s[currRef].getCol()
                &&stonemap.contains(_s[currRef].getRow()*9+_s[currRef].getCol()-1))
            return false;
    }
    else{
        if(destY>_s[currRef].getRow()
                &&stonemap.contains(_s[currRef].getRow()*9+9+_s[currRef].getCol()))
            return false;
        if(destY<_s[currRef].getRow()
                &&stonemap.contains(_s[currRef].getRow()*9-9+_s[currRef].getCol()))
            return false;
    }
    return true;
}
int StoneController::relationBetweenStones(int ExamID ,int destX,int destY) const {
    int row = _s[ExamID].getRow();
    int col = _s[ExamID].getCol();
    int xdigit = destX-col>=0?destX-col:col-destX;
    int ydigit = destY-row>=0?destY-row:row-destY;
    return ydigit*10+xdigit;
}

int StoneController::getIndexById(int ID) const {
    return _s[ID].getRow()*9+_s[ID].getCol();
}
bool StoneController::MINISTERCanMoveTo(int currRef,int destX,int destY) const {
    int r = relationBetweenStones(currRef, destX, destY);
    if(r != 22)
        return false;
    int middleX = ( destX + _s[currRef].getCol())/2;
    int middleY = (destY + _s[currRef].getRow())/2;
    if(stonemap.contains(middleY*9+middleX))
        return false;
    return     (isOnBottomHalfAtFirst(currRef)  && !destOnAboveHalf(destY))
            || (!isOnBottomHalfAtFirst(currRef)  && destOnAboveHalf(destY));

}
bool StoneController::destOnAboveHalf(int destY) const {
    return destY<=4;
}
bool StoneController::CANNONCanMoveTo(int currRef,int destX,int destY) const {
    return destIsValidBlankPlace(currRef,destX,destY) || CANNONTryingToEat(currRef,destX,destY);
}
bool StoneController::destIsValidBlankPlace(int currRef,int destX, int destY) const {
    if(destXYInOneLineWithExamine(currRef,destX,destY)){
        if(stoneCountInTheWay(currRef,destX,destY)==0){
            if(!stonemap.contains(9*destY+destX))
                return true;
        }
    }
    return false;
}
bool StoneController::CANNONTryingToEat(int currRef,int destX,int destY) const {
    if(destXYInOneLineWithExamine(currRef,destX,destY)){
        if(stoneCountInTheWay(currRef,destX,destY)==1){
            if(stonemap.contains(9*destY+destX))
                return true;
        }
    }
    return false;
}
bool StoneController::GUARDCanMoveTo(int currRef,int destX,int destY) const {
    int r = relationBetweenStones(currRef,destX, destY);
    if(r != 11)
        return false;
    if(!inNinePalace(currRef,destX,destY))
        return false;
    return true;
}
bool StoneController::PAWNCanMoveTo(int currRef,int destX,int destY) const {
    if(isOnBottomHalfAtFirst(currRef)){
        if( _s[currRef].getRow()<=4){
            return (relationBetweenStones(currRef,destX,destY) == 1)
                    || (relationBetweenStones(currRef,destX,destY) == 10 && destY<_s[currRef].getRow());
        }
        else {
            return (relationBetweenStones(currRef,destX,destY) == 10 && destY<_s[currRef].getRow());
        }
    }else {
        if( _s[currRef].getRow()>=5){
            return (relationBetweenStones(currRef,destX,destY) == 1)
                    || (relationBetweenStones(currRef,destX,destY) == 10 &&  destY>_s[currRef].getRow());
        }
        else {
            return (relationBetweenStones(currRef,destX,destY) == 10 && destY>_s[currRef].getRow());
        }
    }
}
bool StoneController::isClickingItself(int currRef,int destx, int desty) const{
    return _s[currRef].getRow() == desty && _s[currRef].getCol() == destx;
}
bool StoneController::hasSameColorOnDest(int currRef, int destx, int desty) const {
    if(!stonemap.contains(desty*9+destx)){
        return false;
    }
    bool isRed = _s[stonemap[desty*9+destx]].isRed();
    return isRed == _s[currRef].isRed();
}
void StoneController::recordStep(int killedID, int destIndex,int movedId,int previousIndex){
    qDebug()<<"killedId = "<<killedID;
    stepRecorder.recordStep(killedID,destIndex,movedId,previousIndex);
}
void StoneController::recordStep(StepRecorder::Step step){
    stepRecorder.appendStep(step);
}

void StoneController::regretStep(){
    if(stepRecorder.isEmpty()) return;
    StepRecorder::Step a = stepRecorder.getAndRemoveLastStep();
    //qDebug()<<"killed Id is"<<a.killedID;
    //qDebug()<<_s[a.killedID].getID()<<"x="<<_s[a.killedID].getCol()<<"y="<<_s[a.killedID].getRow();
    if(a.killedID != -1){
        _s[a.killedID].setRevive();
        deadStone.pop_back();
        updateSpecifiedStone(a.movedID,a.previousIndex%9,a.previousIndex/9);
        replaceReviveStone(a.killedID,a.destIndex%9,a.destIndex/9);
    }else {
//        qDebug()<<"Regreting a step without eating anything, killedID is "<<a.killedID;
        updateSpecifiedStone(a.movedID,a.previousIndex%9,a.previousIndex/9);
    }
}
void StoneController::updateSpecifiedStone(int StoneID, int destX, int destY){
    stonemap.remove(_s[StoneID].getRow()*9+_s[StoneID].getCol());
    _s[StoneID].setRow(destY);
    _s[StoneID].setCol(destX);
    stonemap[destY*9+destX] = StoneID;
}
void StoneController::replaceReviveStone(int killedID, int destX,int destY){
//    qDebug()<<_s[killedID].getID()<<"x="<<_s[killedID].getCol()<<"y="<<_s[killedID].getRow();
    stonemap[destY*9+destX] = killedID;
}
