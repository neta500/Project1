#pragma once
#include "TreeNode.h"
#include <algorithm>
#include <queue>

class Solution {
public:
    // DFS (recurrsion, stack)
    int maxDepth_dfs(TreeNode* root) {
        if (root == nullptr)
        {
            return 0;
        }

        return std::max(maxDepth_dfs(root->left), maxDepth_dfs(root->right)) + 1;
    }

    // BFS (queue)
    int maxDepth_bfs(TreeNode* root) {
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
            for (int i = 0; i < queue.size(); ++i)
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