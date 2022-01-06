#pragma once
#include "TreeNode.h"

// recurrsion으로 tree를 돌면서 각 sub-tree들의 bst를 체크하는 방식

class Solution {
public:
    TreeNode* prev;

    bool isValidBST(TreeNode* root) {
        if (nullptr == root)
        {
            return true;
        }

        // left subtree체크 -> left와 본인(sub-tree의 root) val 체크 -> right 체크
        return isValidBST(root->left) && valCheck(root) && isValidBST(root->right);
    }
        
    bool valCheck(TreeNode* root)
    {
        if (nullptr == prev)
        {
            prev = root;
            return true;
        }

        if (prev->val >= root->val)
        {
            return false;
        }

        prev = root;
        return true;
    }
};