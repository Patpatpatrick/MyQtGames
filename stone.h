#ifndef STONE_H
#define STONE_H
#include <QString>

class Stone
{
public:
    Stone();
    void setinfo(int radius,int row,int col,int id,bool dead,bool red, int _type);
    int getrow();
    int getcol();
    QString Text();
private:
    int radius;
    int row;
    int col;
    int id;
    bool dead;
    bool red;
    enum StoneType{
        KING = 1,
        ROOK = 2,
        KNIGHT = 3,
        MINISTER = 4,
        CANNON = 5,
        GUARD = 6,
        PAWN = 7
    };
    StoneType _type;
};

#endif // STONE_H
