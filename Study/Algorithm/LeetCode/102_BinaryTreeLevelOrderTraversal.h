#pragma once
#include "TreeNode.h"
#include <vector>
#include <queue>

class Solution {
public:
    std::vector<std::vector<int>> levelOrder(TreeNode* root) {
        std::vector<std::vector<int>> result;

        std::queue<TreeNode*> queue;
        queue.push(root);

        while (queue.empty() == false)
        {
            std::vector<int> level;
            const int size = queue.size();

            for (int i = 0; i < size; ++i)
            {
                TreeNode* front = queue.front();
                queue.pop();

                if (front)
                {
                    level.push_back(front->val);
                    queue.push(front->left);
                    queue.push(front->right);
                }
            }

            if (level.empty() == false)
            {
                result.push_back(std::move(level));
            }
        }

        return result;
    }
};