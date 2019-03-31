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
    const int chessPower[] = {1500,200,120,80,170,50,30};
    // king 1500 ; rook 200; knight 120; minister 80;cannon 130;guard 50;pawn 30
}

class Stone
{
public:
    Stone();
    Stone(const Stone & otherstone);

    void setInfo(int radius,int row,int col,int id,bool dead,bool red, int _type);
    int getRow() const;
    int getCol() const;
    void setDead();
    bool isDead() const;
    void setRow(int y);
    void setCol(int x);
    void setRevive();
    QString Text() const;
    int getID() const;
    bool isRed() const;
    StoneCommonInfo::StoneType getType() const;
    StoneCommonInfo::StoneType _type;
private:
    int radius;
    int row;
    int col;
    int id;
    bool dead;
    bool red;
};

#endif // STONE_H
