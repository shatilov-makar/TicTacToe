#pragma once
#include "PlayField.h"
#include <cassert>

class TreeNode
{
public:
    TreeNode(TreeNode* parent, PlayField state) :playField(state), parent(parent) {};
    bool isTerminal() const;
    TreeNode addChild(PlayField::CellIdx);
    int childCount() const;
    const PlayField* value() const;
    
private:
    const PlayField playField;
    const TreeNode* parent;
    int childQty() const;
    vector<TreeNode> childrens;
};
