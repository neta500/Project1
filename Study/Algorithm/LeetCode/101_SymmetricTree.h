#pragma once
#include "TreeNode.h"
#include <queue>

class Solution {
public:
    // bfs·Î Ã¼Å©
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;

        std::queue<TreeNode*> leftQueue;
        std::queue<TreeNode*> rightQueue;
        leftQueue.push(root);
        rightQueue.push(root);

        while (false == leftQueue.empty() && false == rightQueue.empty())
        {
            const TreeNode* left = leftQueue.front();
            leftQueue.pop();

            const TreeNode* right = rightQueue.front();
            rightQueue.pop();
            
            if (left == nullptr && right == nullptr)
            {
                continue;
            }

            if (left == nullptr || right == nullptr)
            {
                return false;
            }

            leftQueue.push(left->left);
            leftQueue.push(left->right);

            rightQueue.push(right->right);
            rightQueue.push(right->left);
        }

        return true;
    }
};