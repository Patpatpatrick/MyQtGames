#include "StoneController.h"
StoneController::StoneController(){
    _selectedId = -1;
    deadStonesCount = 0;
}
StoneController::StoneController(int ID):_selectedId(ID){
    deadStonesCount = 0;
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

void StoneController::processEatenStoneOn(int posX, int posY){
    _s[stonemap[posY*9+posX]].setDead();
    // TODO stone drawn aside
    // remove the eaten stone out of the stonemap
    stonemap.remove(posY*9+posX);
    deadStonesCount++;
}
void StoneController::updateSelectedStone(int x, int y){
    // To update the postion of the moved stone, first take it out of the stonemap from where it used to be
    stonemap.remove(_s[_selectedId].getRow()*9+_s[_selectedId].getCol());
    // set new col and row with respect to this moved stone,
    _s[_selectedId].setRow(y);
    _s[_selectedId].setCol(x);
    // update its record in the stone map
    stonemap[y*9+x] = _selectedId;
}
bool StoneController::isThisSelected(int i){
    return _selectedId == i;
}
void StoneController::selectThisOne(int i){
    _selectedId = i;
}
bool StoneController::canMoveToDest(int destX, int destY){
    return true;
//    if (hasSameColorOnDest(destX,destY)){
//        return false;
//    } else {
//        switch (_s[_selectedId].getType()) {
//            case StoneCommonInfo::StoneType::KING :
//                return KINGCanMoveTo(destX,destY);

//            case StoneCommonInfo::StoneType::ROOK :
//                return ROOKCanMoveTo(destX,destY);

//            case StoneCommonInfo::StoneType::KNIGHT :
//                return KNIGHTCanMoveTo(destX,destY);

//            case StoneCommonInfo::StoneType::MINISTER :
//                return MINISTERCanMoveTo(destX,destY);

//            case StoneCommonInfo::StoneType::CANNON :
//                return CANNONCanMoveTo(destX,destY);

//            case StoneCommonInfo::StoneType::GUARD :
//                return GUARDCanMoveTo(destX,destY);

//            case StoneCommonInfo::StoneType::PAWN :
//                return PAWNCanMoveTo(destX,destY);
//        }
//    }
}

bool StoneController::KINGCanMoveTo(int destX,int destY){
//    int row = _s[_selectedId].getRow();
//    int col = _s[_selectedId].getCol();
//    if(InOneLine(_selectedId,31-_selectedId))
//        return false;
//    return (destY == row && destX - col == 1)
//            || (destY == row && destX - col == -1)
//            || (destX == col && destY - row == 1)
//            || (destX == col && destY - row == -1);
    return true;
}
bool StoneController::InOneLine(int currID,int examinedID){
//    return _s[currID].getCol()==_s[examinedID].getCol()
//            || _s[currID].getRow()==_s[examinedID].getRow();
    return true;
}
bool StoneController::ROOKCanMoveTo(int destX,int destY){
    return true;
}
bool StoneController::KNIGHTCanMoveTo(int destX,int destY){
//    int r = relationBetweenStones(destX, destY);
//    if(r != 12 && r != 21)
//        return false;
//    if(r == 12){

//    }
//    else{

//    }

    return true;
}
int StoneController::relationBetweenStones(int destX,int destY){
    int row = _s[_selectedId].getRow();
    int col = _s[_selectedId].getCol();
    int xdigit = destX-col>=0?destX-col:col-destX;
    int ydigit = destY-row>=0?destY-row:row-destY;
    return ydigit*10+xdigit;
}

bool StoneController::MINISTERCanMoveTo(int destX,int destY){
    return true;
}
bool StoneController::CANNONCanMoveTo(int destX,int destY){
    return true;
}
bool StoneController::GUARDCanMoveTo(int destX,int destY){
    return true;
}
bool StoneController::PAWNCanMoveTo(int destX,int destY){
    return true;
}
bool StoneController::isClickingItself(int destx, int desty){
    return _s[_selectedId].getRow() == desty && _s[_selectedId].getCol() == destx;
}
bool StoneController::hasSameColorOnDest(int destx, int desty){
    bool isRed = _s[stonemap[desty*9+destx]].isRed();
    return isRed == _s[_selectedId].isRed();
}
