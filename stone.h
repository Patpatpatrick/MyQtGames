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
    const int chessPower[] = {1500,100,50,40,50,40,20};
    // king 1500 ; rook 100; knight 50; minister 40;cannon 50;guard 40;pawn 20
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
