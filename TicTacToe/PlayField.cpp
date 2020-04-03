
#include <cassert>
#include "PlayField.h"

using namespace std;


int PlayField::CellIdx::getPosition() const
{
    return  row * 3 + column;
}

vector<PlayField::CellIdx> PlayField::getEmptyCells() const
{
    vector<CellIdx> emptyCells;
    for (int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            if (map[3*i + j] == csEmpty)
            {
                CellIdx cell(i,j);
                emptyCells.push_back(cell);
            } 
        }
    return emptyCells;
}
   
PlayField::mapCondition PlayField::checkFieldStatus() const
{
    for (int k = 0; k < 9; k += 3)
    {
        if (map[k] == map[k + 1]
            && map[k] == map[k + 2])
        {
            if (map[k]== csCross)
                return fsCrossesWin;
            if (map[k] == csNought)
                return fsNoughtsWin;
        }
    }

    for (int k = 0; k < 3; k++)
    {
        if (map[k] == map[k + 3]
            && map[k] == map[k + 6])
        {
            if (map[k] == csCross)
                return fsCrossesWin;
            if (map[k] == csNought)
                return fsNoughtsWin;
        }
    }

    if (map[0] == map[4] && map[0] == map[8]
        || map[2] == map[4] && map[2] == map[6])
    {
        if (map[4] == csCross)
            return fsCrossesWin;
        if (map[4] == csNought)
            return fsNoughtsWin;
    }

    for (int i = 0; i < 9; i++)
    {
        if (map[i] == csEmpty)
            return fsContinue;
    }
    return fsDraw;
}

PlayField PlayField::makeMove(PlayField::CellIdx index) const
{
    assert(this->map[index.getPosition()] == csEmpty && this->checkFieldStatus() == fsContinue);
    return *this + index;
}

PlayField::cellCondition PlayField::getStep() const
{
    int crossCount = 0, noughtCount = 0;
    for (int i = 0; i < 9; i++) {
        if (map[i] == csCross) {
            crossCount++;
        }
        if (map[i] == csNought) {
            noughtCount++;
        }
    }
    return crossCount > noughtCount ? csNought : csCross;
}
