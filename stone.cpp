#include "stone.h"

Stone::Stone()
{
    radius = 20;
    red = false;
    dead = false;
}
void Stone::setinfo(int pradius,int prow,int pcol,int pid,bool pdead,bool pred, int p_type){
    radius = pradius;
    row = prow;
    col = pcol;
    id = pid;
    dead = pdead;
    red = pred;
    _type = StoneType(p_type);
}
int Stone::getrow(){
    return row;
}
int Stone::getcol(){
    return col;
}
void Stone::setRow(int y){
    row = y;
}
void Stone::setCol(int x){
    col = x;
}
bool Stone::isDead(){
    return dead;
}
void Stone::setDead(){
    dead = true;
}
QString Stone::Text(){
    switch (this->_type) {
    case ROOK:
        return "車";
    case KNIGHT:
        return "馬";
    case MINISTER:
        if(red)
            return "相";
        return "象";
    case GUARD:
        if(red)
            return "仕";
        return "士";
    case KING:
        if(red)
            return "帅";
        return "将";
    case CANNON:
        if(red)
            return "炮";
        return "砲";
    case PAWN:
        if(red)
            return "兵";
        return "卒";

    }
}
