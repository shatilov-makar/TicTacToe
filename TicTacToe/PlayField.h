#pragma once
#include <vector> 

using namespace std;

class PlayField
{
public:
    enum cellCondition { csEmpty, csCross, csNought };
    enum mapCondition { fsInvalid, fsCrossesWin, fsNoughtsWin, fsDraw, fsContinue}; // добавил fsContinue для состояния, когда игра продолжается
    class CellIdx
    {
    public:
        CellIdx() :row(0), column(0), condition(csEmpty) {};
        CellIdx(int row, int column, cellCondition cond = csEmpty) :row(row), column(column), condition(cond) {};
        cellCondition getState() const;
        int getPosition() const;
    private:
        int row;
        int column;
        cellCondition condition;
    };

    PlayField()
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                map[3 * i + j] = CellIdx(i, j);
    }
    cellCondition operator [] (CellIdx index) const
    {
        return index.getState();
    }
    cellCondition operator () (int a, int b) const
    {
        int f = a * 3 + b;
        CellIdx ind = map[f];
        return ind.getState();
    };

    vector<CellIdx> getEmptyCells() const;
    mapCondition checkFieldStatus() const;
    PlayField makeMove(CellIdx);
private:
    PlayField operator+ (CellIdx index) const
    {
        CellIdx index1 = this->map[index.getPosition()];
        PlayField plf = *this;
        plf.map[index.getPosition()] = index;
        return plf;
    };
    CellIdx map[9];
};