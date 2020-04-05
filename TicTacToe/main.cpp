using namespace std;
#include "PlayField.h"
#include "TreeNode.h"
#include <iostream>

//Shatilov M.R. 


struct statistic 
{
    int winCrosses = 0;
    int winNoughts = 0;
    int draws = 0;
};

const int maxChildsAfterFirstStep = 8;
const int sideLength = 3;
const int countCells = 9;

void makeStep(TreeNode&, statistic*);

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
    makeStep(node, stat);
    if (node.childCount() == maxChildsAfterFirstStep)
    {
        cout << "You can win in " << stat->winCrosses << " ways,  you can lose in " << stat->winNoughts << " ways, and will be a draw " << stat->draws << " ways" << endl << endl;
        stat->draws = 0; stat->winCrosses = 0; stat->winNoughts = 0;
        return stat;
    }
}

void makeStep(TreeNode& node, statistic* stat)
{
    int row = 0; int column = 0;
    for (int i = 0; i < countCells; i++)
    {
        row = i / sideLength; column = i % sideLength;
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
