using namespace std;
#include "PlayField.h"
#include "TreeNode.h"
#include <iostream>

//Shatilov M.R. 


struct result
{
int wins = 0;
int loses = 0;
int draws = 0;
result& operator +=(const result& ir)
{
    wins += ir.wins;
    loses += ir.loses;
    draws += ir.draws;
    return *this;
}
};

const int maxChildsAfterFirstStep = 8;
const int sideLength = 3;
const int countCells = 9;

void makeStep(TreeNode, result*);

result getStatistic(TreeNode node)
{
    result res;
    if (node.isTerminal())
    {
        if (node.value()->checkFieldStatus() == PlayField::mapCondition::fsCrossesWin)
            res.wins++;
        else if (node.value()->checkFieldStatus() == PlayField::mapCondition::fsNoughtsWin)
            res.loses++;
        else
            res.draws++;
        return res;
    }
    makeStep(node, &res);
    return res;
}

void makeStep(TreeNode node, result* res)
{
    int row = 0; int column = 0;
    for (int i = 0; i < countCells; i++)
    {
        row = i / sideLength; column = i % sideLength;
        auto condition = node.value()->operator()(row, column);
        if (condition == PlayField::cellCondition::csEmpty)
        {
            auto childNode = node.addChild(PlayField::CellIdx(row, column));
            *res += getStatistic(childNode);
        }
    }
    if (node.childCount() == maxChildsAfterFirstStep)
    {
        cout << "You can win in " << res->wins << " ways,  you can lose in " << res->loses << " ways, and will be a draw " << res->draws << " ways" << endl << endl;
        res->draws = 0; res->wins = 0; res->loses = 0;
    }
}

int main()
{
    TreeNode rootNode(nullptr, PlayField());
    result res;
    makeStep(rootNode, &res);
    return 0;
}
