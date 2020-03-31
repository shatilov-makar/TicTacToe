#pragma once
#include "PlayField.h"
#include <cassert>

class TreeNode
{
public:

    TreeNode(TreeNode* parent, PlayField state) :playField(state), parent(parent) {};
 

    bool isTerminal();
 
    TreeNode addChild(PlayField::CellIdx);

    int childCount();

    const PlayField* value() const;
    
private:
    const PlayField playField;
    const TreeNode* parent;
    int childQty();
    vector<TreeNode> childrens;
};