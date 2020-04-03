#pragma once
#include <vector> 

using namespace std;

class PlayField
{
public:
    enum cellCondition { csEmpty, csCross, csNought };
    enum mapCondition { fsInvalid, fsCrossesWin, fsNoughtsWin, fsDraw, fsContinue};
    class CellIdx
    {
    public:
        CellIdx() :row(0), column(0) {};
        CellIdx(int row, int column) :row(row), column(column) {};
        int getPosition() const;
    private:
        int row;
        int column;
    };

    cellCondition operator [] (CellIdx index) const
    {
        return map[index.getPosition()];
    }
    cellCondition operator () (int row, int column) const
    {
        return map[row * 3 + column];
    };

    vector<CellIdx> getEmptyCells() const;
    mapCondition checkFieldStatus() const;
    PlayField makeMove(CellIdx) const;

private:
    PlayField operator+ (CellIdx index) const 
    {
        PlayField newField = PlayField(*this);
        newField.map[index.getPosition()] = getStep();
        return newField;
    };

    cellCondition map[9]{ csEmpty,csEmpty,csEmpty,csEmpty,csEmpty,csEmpty,csEmpty,csEmpty,csEmpty };

    cellCondition getStep() const;
};
