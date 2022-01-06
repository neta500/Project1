#pragma once
#include "TreeNode.h"

// recurrsion���� tree�� ���鼭 �� sub-tree���� bst�� üũ�ϴ� ���

class Solution {
public:
    TreeNode* prev;

    bool isValidBST(TreeNode* root) {
        if (nullptr == root)
        {
            return true;
        }

        // left subtreeüũ -> left�� ����(sub-tree�� root) val üũ -> right üũ
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