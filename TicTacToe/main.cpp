using namespace std;
#include "PlayField.h"
#include "TreeNode.h"
#include <iostream>

//Shatilov M.R. 


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
        cout << "You can win in " << stat->winCrosses << " ways,  you can lose in " << stat->winNoughts << " ways, and will be a draw " << stat->draws << " ways" << endl << endl;
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
            auto childNode = node.addChild(PlayField::CellIdx(row, column));
            getStatistic(childNode, stat);

        }
    }
}

int main()
{
    TreeNode rootNode(nullptr, PlayField());
    statistic statistic;
    getStatistic(rootNode, &statistic);
    return 0;
}
