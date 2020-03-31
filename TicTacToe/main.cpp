using namespace std;
#include "PlayField.h"
#include "TreeNode.h"
#include <iostream>

//Шатилов М.Р.  РИ-280002


struct statistic
{
    statistic()
    {
        winCrosses;
        winNoughts;
        draws;
    }
    int winCrosses = 0;
    int winNoughts = 0;
    int draws = 0;
};

void makeStep(TreeNode&, statistic*, PlayField::cellCondition);
void inputResult(TreeNode, statistic*);

statistic* getStatistic(TreeNode node, statistic* stat)
{
    if (node.isTerminal())
    {
        if (node.value()->checkFieldStatus() == PlayField::mapCondition::fsCrossesWin)
        {
            stat->winCrosses++;
            return stat;
        }
        if (node.value()->checkFieldStatus() == PlayField::mapCondition::fsNoughtsWin)
        {
            stat->winNoughts++;
            return stat;
        }
        else
            stat->draws++;
        return stat;
    }
    if (node.value()->getEmptyCells().size() % 2 == 1)
        makeStep(node, stat, PlayField::cellCondition::csCross);
    else
        makeStep(node, stat, PlayField::cellCondition::csNought);
   
    if (node.childCount() == 8 )
    {
        inputResult(node, stat);
        stat->draws = 0; stat->winCrosses = 0; stat->winNoughts = 0;
        return stat;
    }
}

void makeStep(TreeNode& node, statistic* stat, PlayField::cellCondition cond)
{
    int row = 0; int column = 0;
    for (int i = 0; i < 9; i++)
    {
        row = i / 3; column = i % 3;
        auto condition = node.value()->operator()(row, column);
        if (condition == PlayField::cellCondition::csEmpty)
        {
            auto childNode = node.addChild(PlayField::CellIdx(row, column, cond));
            getStatistic(childNode, stat);
            if (stat->winNoughts == 0 && stat->winCrosses == 0 && stat->draws == 0)
                return;
        }
    }
}

int main()
{
    TreeNode rootNode(nullptr, PlayField());
    
    TreeNode corner(&rootNode, PlayField().makeMove(PlayField::CellIdx(0, 0, PlayField::cellCondition::csCross)));
    TreeNode top(&rootNode, PlayField().makeMove(PlayField::CellIdx(0, 1, PlayField::cellCondition::csCross)));
    TreeNode center(&rootNode, PlayField().makeMove(PlayField::CellIdx(1, 1, PlayField::cellCondition::csCross)));

    statistic cornerStat;
    getStatistic(corner, &cornerStat);

    statistic topStat;
    getStatistic(top, &topStat);

    statistic centerStat;
    getStatistic(center, &centerStat);

    return 0;
}

void inputResult(TreeNode node, statistic* stat)
{
    auto condition = node.value()->operator()(0, 0);
    if (condition == PlayField::cellCondition::csCross)
        cout << "x - x" << endl << "- - -" << endl << "x - x" << endl;
    
    condition = node.value()->operator()(0, 1);
    if (condition == PlayField::cellCondition::csCross)
        cout << "- x -" << endl << "x - x" << endl << "- x -" << endl;
    
    condition = node.value()->operator()(1, 1);
    if (condition == PlayField::cellCondition::csCross)
        cout << "- - -" << endl << "- x -" << endl << "- - -" << endl;
    cout << "You can win in " << stat->winCrosses << " ways,  you can lose in " << stat->winNoughts << " ways, and will be a draw " << stat->draws << " ways" << endl << endl;
}