#pragma once
#include <vector>
#include <stack>
#include <unordered_set>
#include <queue>

class Solution {
public:
    std::unordered_set<int> visited;
    std::unordered_set<int> keys;

    void dfs(std::vector<std::vector<int>>& rooms, int depth)
    {
        visited.emplace(depth);

        for (const int key : rooms[depth])
        {
            keys.emplace(key);
        }

        for (const int key : keys)
        {
            if (false == visited.contains(key))
            {
                dfs(rooms, key);
            }
        }
    }

    bool canVisitAllRooms_dfs(std::vector<std::vector<int>>& rooms) {       

        dfs(rooms, 0);
        return visited.size() == rooms.size();
    }

    bool canVisitAllRooms_bfs(std::vector<std::vector<int>>& rooms) {
        std::queue<int> queue; // queue���� �����ؾ��� ���ȣ�� �ִ´�.
        // 0���� �Լ�
        visited.emplace(0);
        queue.emplace(0);

        while (false == queue.empty())
        {
            int roomNumber = queue.front(); queue.pop();
            for (const int key : rooms[roomNumber])
            {
                if (visited.contains(key))
                {
                    continue;
                }

                visited.emplace(key);
                queue.push(key); // �ߺ�üũ ���� ���?
            }
        }

        return visited.size() == rooms.size();
    }
};

// rooms�� ��ȸ�ϸ� ���� ȹ�� �� ���� room�� �� �� �ִ� �� üũ.
// ��� ���� �� �� ������ true, �ƴϸ� false
// 0������ �׻� �����ִ�. (0������ key�� �� ȹ�� ����)

// ���� [[1,3], [3,0,1], [2], [0]] -> false
// BFS
// queue(0), visited(0)
// 0���� - key(1,3) ȹ��, queue(1, 3), visited(0)
// 1���� - key(3,0,1) ȹ��, queue(3, 3, 0, 1), visited(0, 1)
// 3���� - key(0) ȹ��, queue(3, 0, 1, 0), visited(0, 1, 3)
// 3���� - visited�̹Ƿ� �н�
// 0����, 1����, 0���� - visited�̹Ƿ� �н�
// queue�� ������Ƿ� ��� üũ


// DFS
// 0���� - key(1,3) ȹ��, 1, 3���� ��ȸ
// 0���� - ������ �ִ� key�� ��ȸ�ϸ� �� üũ (1, 3)
// 0���� -> 1���� - key(3,0,1) ȹ��, 0, 1, 3���� ��ȸ
// 0���� -> 1���� -> 0���� - visited�̹Ƿ� Ž�� ��
// 0���� -> 1���� -> 1���� - visited�̹Ƿ� Ž�� ��
// 0���� -> 1���� -> 3���� - key ȹ��, 0���� ��ȸ
// 0���� -> 1���� -> 3���� - 0���� - visited�̹Ƿ� Ž�� ��
// 0���� -> 3���� - key(0) ȹ��, 0���� ��ȸ
// 0���� -> 3���� -> 0���� - visited�̹Ƿ� Ž�� ��
// ��� Ž�� ��, visited�� rooms�� ��. 2���濡 ������ ������ false