#pragma once
#include "TreeNode.h"
#include <algorithm>
#include <queue>

class Solution {
public:
    // DFS (recurrsion, stack)
    int maxDepth(TreeNode* root) {
        if (root == nullptr)
        {
            return 0;
        }

        return std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }

    // BFS (queue)
    int maxDepth(TreeNode* root) {
        if (root == nullptr)
        {
            return 0;
        }

        int depth = 0;

        std::queue<TreeNode*> queue;
        queue.push(root);

        while (false == queue.empty())
        {
            depth++;
            int size = queue.size();
            for (int i = 0; i < size; ++i)
            {
                TreeNode* front = queue.front();
                queue.pop();

                if (front->left)
                {
                    queue.push(front->left);
                }
                if (front->right)
                {
                    queue.push(front->right);
                }
            }
        }

        return depth;
    }
};