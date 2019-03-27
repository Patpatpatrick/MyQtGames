#include "stone.h"
#include <QHash>
Stone::Stone()
{
    radius = 20;
    red = false;
    dead = false;
}
Stone::Stone(const Stone & otherstone){
    radius = otherstone.radius;
    row = otherstone.row;
    col = otherstone.col;
    id = otherstone.id;
    dead = otherstone.dead;
    red = otherstone.red;
    _type = otherstone._type;
}

void Stone::setInfo(int pradius,int prow,int pcol,int pid,bool pdead,bool pred, int p_type){
    radius = pradius;
    row = prow;
    col = pcol;
    id = pid;
    dead = pdead;
    red = pred;
    _type = StoneCommonInfo::StoneType(p_type);
}
StoneCommonInfo::StoneType Stone::getType() const{
    return _type;
}
int Stone::getRow() const{
    return row;
}
int Stone::getCol() const{
    return col;
}
void Stone::setRow(int y){
    row = y;
}
void Stone::setCol(int x){
    col = x;
}
bool Stone::isDead() const{
    return dead;
}
void Stone::setDead(){
    dead = true;
}
void Stone::setRevive(){
    dead = false;
}
bool Stone::isRed() const {
    return red;
}
int Stone::getID() const {
    return id;
}
QString Stone::Text() const{
    switch (_type) {
    case StoneCommonInfo::StoneType::ROOK:
        return "車";
    case StoneCommonInfo::StoneType::KNIGHT:
        return "馬";
    case StoneCommonInfo::StoneType::MINISTER:
        if(red)
            return "相";
        return "象";
    case StoneCommonInfo::StoneType::GUARD:
        if(red)
            return "仕";
        return "士";
    case StoneCommonInfo::StoneType::KING:
        if(red)
            return "帅";
        return "将";
    case StoneCommonInfo::StoneType::CANNON:
        if(red)
            return "炮";
        return "砲";
    case StoneCommonInfo::StoneType::PAWN:
        if(red)
            return "兵";
        return "卒";

    }
}
