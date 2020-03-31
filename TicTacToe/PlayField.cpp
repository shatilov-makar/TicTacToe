
#include <cassert>
#include "PlayField.h"

using namespace std;

PlayField::cellCondition PlayField::CellIdx::getState() const
{
    return condition;
}

int PlayField::CellIdx::getPosition() const
{
    return  row * 3 + column;
}


vector<PlayField::CellIdx> PlayField::getEmptyCells() const
{
    vector<PlayField::CellIdx> emptyCells;
    for (int i = 0; i < 9; i++)
    {
        if (map[i].getState() == PlayField::csEmpty)
            emptyCells.push_back(map[i]);
    }
    return emptyCells;
}
   

PlayField::mapCondition PlayField::checkFieldStatus() const
{
    for (int k = 0; k < 9; k += 3)
    {
        if (map[k].getState() == map[k + 1].getState()
            && map[k].getState() == map[k + 2].getState())
        {
            if (map[k].getState() == csCross)
                return fsCrossesWin;
            if (map[k].getState() == csNought)
                return fsNoughtsWin;
        }
    }

    for (int k = 0; k < 3; k++)
    {
        if (map[k].getState() == map[k + 3].getState() 
            && map[k].getState() == map[k + 6].getState())
        {
            if (map[k].getState() == csCross)
                return fsCrossesWin;
            if (map[k].getState() == csNought)
                return fsNoughtsWin;
        }
    }

    if (map[0].getState() == map[4].getState() && map[0].getState() == map[8].getState()
        || map[2].getState() == map[4].getState() && map[2].getState() == map[6].getState())
    {
        if (map[4].getState() == csCross)
            return fsCrossesWin;
        if (map[4].getState() == csNought)
            return fsNoughtsWin;
    }

    for (int i = 0; i < 9; i++)
    {
        if (map[i].getState() == csEmpty)
            return fsContinue;
    }
    return fsDraw;
}

PlayField PlayField::makeMove(PlayField::CellIdx index) 
{
    assert(this->map[index.getPosition()].getState() == csEmpty && this->checkFieldStatus() == fsContinue);
    return (*this + index);
}