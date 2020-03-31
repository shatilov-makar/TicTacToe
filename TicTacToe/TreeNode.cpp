#include "TreeNode.h"


    bool TreeNode::isTerminal()
    {
        if (playField.checkFieldStatus() == PlayField::mapCondition::fsContinue)
            return false;
        return true;
    }

    TreeNode TreeNode::addChild(PlayField::CellIdx indx)
    {
        int curChildCount = childCount(); int possibleChildCount = childQty();
        assert(curChildCount = childCount() < possibleChildCount || curChildCount == possibleChildCount);
        auto childPlayField = *this->value();
        TreeNode child(this, childPlayField.makeMove(indx));
        childrens.push_back(child);
        return child;
    }

    int TreeNode::childCount()
    {
        return childrens.size();
    }

    const PlayField* TreeNode::value() const
    {
        return &playField;
    }

    int TreeNode::childQty()
    {
        return playField.getEmptyCells().size();
    }

