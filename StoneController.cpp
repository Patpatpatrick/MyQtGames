#include "StoneController.h"
#include <QDebug>
StoneController::StoneController(){
    _selectedId = -1;
}
StoneController::StoneController(int ID):_selectedId(ID){
}

void StoneController::initStones(int stoneradius){
    int j = 0;
    int tempx = 0;
    int tempy = 0;
    int typeseries[32] = {2,3,4,6,1,6,4,3,2,5,5,7,7,7,7,7,7,7,7,7,7,5,5,2,3,4,6,1,6,4,3,2};
    for(int stoneIndex = 0;stoneIndex<32;stoneIndex++){
        Stone s;
        if(_s.size() <= 8){
            s.setInfo(stoneradius,0,j,stoneIndex,false,false,typeseries[stoneIndex]);
            tempx = j;
            j++;
            if(j>8) j=1;
        } else if (_s.size() <= 10){
            s.setInfo(stoneradius,2,j,stoneIndex,false,false,typeseries[stoneIndex]);
            tempx = j;
            tempy = 2;
            j+=6;
            if(j>7) j = 0;
        } else if (_s.size() <= 15) {
            s.setInfo(stoneradius,3,j,stoneIndex,false,false,typeseries[stoneIndex]);
            tempx = j;
            tempy = 3;
            j+=2;
            if(j>8) j = 0;
        } else if (_s.size() <= 20) {
            s.setInfo(stoneradius,6,j,stoneIndex,false,true,typeseries[stoneIndex]);
            tempx = j;
            tempy = 6;
            j+=2;
            if(j>8) j = 1;
        } else if (_s.size() <= 22) {
            s.setInfo(stoneradius,7,j,stoneIndex,false,true,typeseries[stoneIndex]);
            tempx = j;
            tempy = 7;
            j+=6;
            if(j>7) j = 0;
        } else if (_s.size() <= 31) {
            s.setInfo(stoneradius,9,j,stoneIndex,false,true,typeseries[stoneIndex]);
            tempx = j;
            tempy = 9;
            j++;
        }
        _s.push_back(s);
        stonemap[tempy*9+tempx] = stoneIndex;
    }
}
bool StoneController::isDead(int i){
    return _s[i].isDead();
}
int StoneController::getRow(int i){
    return _s[i].getRow();
}
int StoneController::getCol(int i){
    return _s[i].getCol();
}
QString StoneController::Text(int i){
    return _s[i].Text();
}
bool StoneController::deadIsRed(int i){
    return _s[deadStone[i]].isRed();
}
int StoneController::getIndexByPosInDeadVec(int i){
    return _s[deadStone[i]].getID();
}
int StoneController::getIdByIndex(int i){
    qDebug()<<"getIdByIndex function. Size"<<stonemap.size();
    return stonemap[i];
}
bool StoneController::hasStoneOn(int index){
    qDebug()<<"hasStoneOn function. Size"<<stonemap.size();
    return stonemap.contains(index);
}
void StoneController::processEatenStoneOn(int posX, int posY){
    qDebug()<<"processEatenStoneOn function. Size"<<stonemap.size();

    _s[stonemap[posY*9+posX]].setDead();
    deadStone.push_back(stonemap[posY*9+posX]);
    // remove the eaten stone out of the stonemap
    stonemap.remove(posY*9+posX);
}
void StoneController::updateSelectedStone(int x, int y){
    qDebug()<<"updateSelectedStone function 1 . Size"<<stonemap.size();

    // To update the postion of the moved stone, first take it out of the stonemap from where it used to be
    stonemap.remove(_s[_selectedId].getRow()*9+_s[_selectedId].getCol());
    // set new col and row with respect to this moved stone,

    qDebug()<<"updateSelectedStone function 2 . Size"<<stonemap.size();


    _s[_selectedId].setRow(y);
    _s[_selectedId].setCol(x);
    // update its record in the stone map

    qDebug()<<"updateSelectedStone function 3 . Size"<<stonemap.size();

    stonemap[y*9+x] = _selectedId;
}
bool StoneController::isThisSelected(int i){
    return _selectedId == i;
}
void StoneController::selectThisOne(int i){
    qDebug()<<"Successfully select!";
    _selectedId = i;
}
bool StoneController::canMoveToDest(int destX, int destY){
    if (hasSameColorOnDest(destX,destY)){
        return false;
    } else {
        switch (_s[_selectedId].getType()) {
            case StoneCommonInfo::StoneType::KING :
                return KINGCanMoveTo(destX,destY);

            case StoneCommonInfo::StoneType::ROOK :
                return ROOKCanMoveTo(destX,destY);

            case StoneCommonInfo::StoneType::KNIGHT :
                return KNIGHTCanMoveTo(destX,destY);

            case StoneCommonInfo::StoneType::MINISTER :
                return MINISTERCanMoveTo(destX,destY);

            case StoneCommonInfo::StoneType::CANNON :
                return CANNONCanMoveTo(destX,destY);

            case StoneCommonInfo::StoneType::GUARD :
                return GUARDCanMoveTo(destX,destY);

            case StoneCommonInfo::StoneType::PAWN :
                return PAWNCanMoveTo(destX,destY);
        }
    }
}
bool StoneController::canKINGEatKING(int destX,int destY){
    if(_s[31-_selectedId].getCol()==destX&&_s[31-_selectedId].getRow()==destY){
        if(twoStonesOrPosFaceToFace(9*destY+destX,_selectedId))
            return true;
    }
    return false;
}
bool StoneController::KINGCanMoveTo(int destX,int destY){
    qDebug()<<"Can directly eat King?"<<canKINGEatKING(destX,destY);
    if(canKINGEatKING(destX,destY)){
        return true;
    }
    if(_s[_selectedId].isRed()){
        qDebug()<<"OutOf 9 palace?"<<!(3<=destX && 5>=destX && 7<=destY && 9>=destY);
        if(!(3<=destX && 5>=destX && 7<=destY && 9>=destY))
            return false;
    }
    if(!_s[_selectedId].isRed()){
        if(!(3<=destX && 5>=destX && 0<=destY && 2>=destY))
            return false;
    }
    int row = _s[_selectedId].getRow();
    int col = _s[_selectedId].getCol();
    if(twoStonesOrPosFaceToFace(destY*9+destX,31-_selectedId)){
        qDebug()<<"No you shouldn't move like this";
        return false;
    }
    return (destY == row && destX - col == 1)
            || (destY == row && destX - col == -1)
            || (destX == col && destY - row == 1)
            || (destX == col && destY - row == -1);
}
bool StoneController::twoStonesOrPosFaceToFace(int destIndex,int examinedID){
    qDebug()<<"No other stone in the way?"<<noOtherStoneInTheWay(examinedID,destIndex%9,destIndex/9);
    if(noOtherStoneInTheWay(examinedID,destIndex%9,destIndex/9)){
        return (destIndex%9)==_s[examinedID].getCol();
    }
    return false;
}
bool StoneController::ROOKCanMoveTo(int destX,int destY){
    //ROOK TESTED!
    if(destXYInOneLineWithExamine(_selectedId,destX,destY)){
        if(noOtherStoneInTheWay(_selectedId,destX,destY)){
            return true;
        }
    }
    return false;
}
bool StoneController::destXYInOneLineWithExamine(int toExaminID,int destX, int destY){
    return ( _s[toExaminID].getCol()==destX)^(_s[toExaminID].getRow()==destY);
}
bool StoneController::noOtherStoneInTheWay(int toExaminID,int destX,int destY){
    qDebug()<<"TOExamined Stone is in one line with "<<destX<<" "<<destY<<"?"<<destXYInOneLineWithExamine(toExaminID,destX,destY);
    if(!destXYInOneLineWithExamine(toExaminID,destX,destY))
        return false;
    if(relationBetweenStones(toExaminID,destX,destY)%10==0){
        //implies x coordinates are the same, two stones are in one col
        int topY = destY>_s[toExaminID].getRow()?destY:_s[toExaminID].getRow();
        int bottomY = destY>_s[toExaminID].getRow()?_s[toExaminID].getRow():destY;
        for(int i = bottomY+1; i<topY; i++){
            if(stonemap.contains(9*i+destX)){
                qDebug()<<"THere is stone in the middle!";
                return false;
            }
        }

    } else {
        //implies y are the same, two stones are in one row
        int topX = destX>_s[_selectedId].getCol()?destX:_s[_selectedId].getCol();
        int bottomX = destX>_s[_selectedId].getCol()?_s[_selectedId].getCol():destX;
        for(int i = bottomX+1; i < topX; i++){
            if(stonemap.contains(9*destY+i)){
                qDebug()<<"THere is stone in the middle!";
                return false;
            }
        }
    }
    return true;
}
bool StoneController::KNIGHTCanMoveTo(int destX,int destY){
    int r = relationBetweenStones(_selectedId,destX, destY);
    if(r != 12 && r != 21)
        return false;
    if(r == 12){
        if(destX>_s[_selectedId].getCol()
                &&stonemap.contains(_s[_selectedId].getRow()*9+_s[_selectedId].getCol()+1))
            return false;
        if(destX<_s[_selectedId].getCol()
                &&stonemap.contains(_s[_selectedId].getRow()*9+_s[_selectedId].getCol()-1))
            return false;
    }
    else{
        if(destY>_s[_selectedId].getRow()
                &&stonemap.contains(_s[_selectedId].getRow()*9+9+_s[_selectedId].getCol()))
            return false;
        if(destY<_s[_selectedId].getRow()
                &&stonemap.contains(_s[_selectedId].getRow()*9-9+_s[_selectedId].getCol()))
            return false;
    }
    return true;
}
int StoneController::relationBetweenStones(int ExamID ,int destX,int destY){
    int row = _s[ExamID].getRow();
    int col = _s[ExamID].getCol();
    int xdigit = destX-col>=0?destX-col:col-destX;
    int ydigit = destY-row>=0?destY-row:row-destY;
    return ydigit*10+xdigit;
}

bool StoneController::MINISTERCanMoveTo(int destX,int destY){
//    qDebug()<<"MinisterCanMoveToDest? Yes! "<<true;

    return true;
}
bool StoneController::CANNONCanMoveTo(int destX,int destY){
    qDebug()<<"CannonCanMoveToDest? Yes! "<<true;

    return true;
}
bool StoneController::GUARDCanMoveTo(int destX,int destY){
    qDebug()<<"GuardCanMoveToDest? Yes! "<<true;

    return true;
}
bool StoneController::PAWNCanMoveTo(int destX,int destY){
    qDebug()<<"PAWNCanMoveToDest? Yes! "<<true;
    return true;
}
bool StoneController::isClickingItself(int destx, int desty){
    return _s[_selectedId].getRow() == desty && _s[_selectedId].getCol() == destx;
}
bool StoneController::hasSameColorOnDest(int destx, int desty){
    if(!stonemap.contains(desty*9+destx)){
        return false;
    }
    bool isRed = _s[stonemap[desty*9+destx]].isRed();
    return isRed == _s[_selectedId].isRed();
}
