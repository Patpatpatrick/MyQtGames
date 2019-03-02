#ifndef STONE_H
#define STONE_H
#include <QString>

namespace StoneCommonInfo
{
    enum StoneType{
        KING = 1,
        ROOK = 2,
        KNIGHT = 3,
        MINISTER = 4,
        CANNON = 5,
        GUARD = 6,
        PAWN = 7
    };
}

class Stone
{
public:
    Stone();
    void setInfo(int radius,int row,int col,int id,bool dead,bool red, int _type);
    int getRow();
    int getCol();
    QString Text();
    void setDead();
    bool isDead();
    void setRow(int y);
    void setCol(int x);
    bool isRed();
    StoneCommonInfo::StoneType getType();
    int getID();
private:
    int radius;
    int row;
    int col;
    int id;
    bool dead;
    bool red;
    StoneCommonInfo::StoneType _type;
};

#endif // STONE_H
